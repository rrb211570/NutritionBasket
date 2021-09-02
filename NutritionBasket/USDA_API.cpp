#include "pch.h"
#include "USDA_API.h"

USDA_API::USDA_API()
{
}

std::map<winrt::hstring, int> USDA_API::ResponseItemNutri(int fdcid)
{
	std::map<winrt::hstring, int> ret;
	if (USDA_API_response.is_null()) return ret;
	for (int i = 0; i < USDA_API_response.at("totalHits"); ++i) {
		if (USDA_API_response.at("foods").at(i).at("fdcId") == fdcid) {
			for (int p = 0; p < USDA_API_response.at("foods").at(i).at("foodNutrients").size(); ++p) {
				winrt::hstring nutrientName = winrt::to_hstring(USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("nutrientName"));
				winrt::hstring units = winrt::to_hstring(USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("unitName"));
				if (nutrientName == L"Energy" && units == L"kJ") continue;
				int value = USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("value");
				ret.insert(std::pair(nutrientName,value));
			}
		}
	}
	return ret;
}

std::map<winrt::hstring, int> USDA_API::Search(winrt::hstring term)
{
	// Add a user-agent header to the GET request.
	auto headers{ httpClient.DefaultRequestHeaders() };

	// The safe way to add a header value is to use the TryParseAdd method, and verify the return value is true.
	// This is especially important if the header value is coming from user input.

	std::wstring header{ L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)" };
	if (!headers.UserAgent().TryParseAdd(header))
	{
		throw L"Invalid header value: " + header;
	}

	std::string url("https://api.nal.usda.gov/fdc/v1/foods/search?api_key=DEMO_KEY&query=" + to_string(term) + "&dataType=SR%20Legacy");
	wurl = std::wstring(url.length(), L' ');
	std::copy(url.begin(), url.end(), wurl.begin());

	// Send the GET request asynchronously, and retrieve the response as a string.

	try
	{
		int y = 4;
		int ut = GetCurrentThreadId();
		auto processOp{ ProcessGETAsync() };
		int kt = 0;
		processOp.get();
		//
		
		int k = 0;
		
	}
	catch (winrt::hresult_error const& ex)
	{
		httpResponseBody = ex.message();
	}
	std::wstring resp = httpResponseBody.c_str();
	nlohmann::json j = nlohmann::json::parse(resp);
	USDA_API_response = j;
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

winrt::Windows::Foundation::IAsyncAction USDA_API::ProcessGETAsync() {
	winrt::Windows::Foundation::Uri requestUri{ wurl };
	co_await winrt::resume_background();

	httpResponseMessage = co_await httpClient.GetAsync(requestUri);
	httpResponseMessage.EnsureSuccessStatusCode();
	httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
}
