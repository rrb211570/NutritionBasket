#include "pch.h"
#include "USDA_API.h"
#include "json.hpp"

USDA_API::USDA_API()
{
}

std::map<winrt::hstring, int> USDA_API::Search(winrt::hstring term)
{
    // Create an HttpClient object.
    winrt::Windows::Web::Http::HttpClient httpClient;

    // Add a user-agent header to the GET request.
    auto headers{ httpClient.DefaultRequestHeaders() };

    // The safe way to add a header value is to use the TryParseAdd method, and verify the return value is true.
    // This is especially important if the header value is coming from user input.

    std::wstring header{ L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)" };
    if (!headers.UserAgent().TryParseAdd(header))
    {
        throw L"Invalid header value: " + header;
    }

    std::string url("https://api.nal.usda.gov/fdc/v1/foods/search?api_key=DEMO_KEY&query=" + to_string(term) + "&dataType=Foundation,SR%20Legacy");
    std::wstring wurl(url.length(), L' ');
    std::copy(url.begin(), url.end(), wurl.begin());
    winrt::Windows::Foundation::Uri requestUri{ wurl };

    // Send the GET request asynchronously, and retrieve the response as a string.
    winrt::Windows::Web::Http::HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;

    try
    {
        // Send the GET request.
        httpResponseMessage = httpClient.GetAsync(requestUri).get();
        httpResponseMessage.EnsureSuccessStatusCode();
        httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
    }
    catch (winrt::hresult_error const& ex)
    {
        httpResponseBody = ex.message();
    }
    std::wstring resp = httpResponseBody.c_str();
    nlohmann::json j = nlohmann::json::parse(resp);
    std::string s(j.dump(3));
    std::wstring str2(s.length(), L' ');
    std::copy(s.begin(), s.end(), str2.begin());
    OutputDebugStringW(str2.c_str());
    
    std::map<winrt::hstring, int> ret;
    if (j.at("totalHits") == 0) return ret;
    for (int i = 0; i < j.at("totalHits"); ++i) {
        std::string name = j.at("foods").at(i).at("description");
        std::wstring wname(name.length(), L' ');
        std::copy(name.begin(), name.end(), wname.begin());
        ret.insert(std::pair(wname, j.at("foods").at(i).at("fdcId")));
    }
    return ret;
}
