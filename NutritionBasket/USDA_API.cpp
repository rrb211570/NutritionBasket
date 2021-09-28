#include "pch.h"
#include "USDA_API.h"
#include "MainPage.h"
#include <regex>
constexpr int RESULTSPERQUERY = 7;
using namespace winrt;

USDA_API::USDA_API() {}
int USDA_API::GetCurrentPage() { return currentPage; }
int USDA_API::GetLastPage() { return totalPages; }

// Returns nutrient/amount mapping for item represented by fdcid
// Said item is found in class member "USDA_API_response", populated by query sent in "USDA_API::Search()"
NutritionBasket::BluePrint USDA_API::ResponseItemNutri(int fdcid)
{
	NutritionBasket::BluePrint item = make<NutritionBasket::implementation::BluePrint>();
	if (USDA_API_response.is_null()) return NULL;
	for (int i = 0; i < numItems; ++i) {
		if (USDA_API_response.at("foods").at(i).at("fdcId") == fdcid) {
			item.Name(to_hstring(USDA_API_response.at("foods").at(i).at("description")));
			item.Amount(L"100");
			for (int p = 0; p < USDA_API_response.at("foods").at(i).at("foodNutrients").size(); ++p) {
				hstring nutrientName = to_hstring(USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("nutrientName"));
				hstring units = to_hstring(USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("unitName"));
				if (nutrientName == L"Energy" && units == L"kJ") continue; // Remove a particular entry
				int value = USDA_API_response.at("foods").at(i).at("foodNutrients").at(p).at("value");
				item.AddElem(nutrientName, to_hstring(value));
			}
		}
	}
	return item;
}

// Returns name/fdcid mapping for a search query.
// Query response is stored in class member "USDA_API_response"
std::map<hstring, int> USDA_API::Search(hstring term, int inputPageNumber)
{
	std::map<hstring, int> ret;
	std::regex pattern(" ");
	std::string adjustedTerm = regex_replace(to_string(term),pattern, "%20");

	auto headers{ httpClient.DefaultRequestHeaders() };
	std::wstring header{ L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)" };
	if (!headers.UserAgent().TryParseAdd(header)) throw L"Invalid header value: " + header;
	std::string url("https://api.nal.usda.gov/fdc/v1/foods/search?api_key=IkNHoKvfYmMmiN1fX9WaBsClEtgCg4Zsh6bOysLt&query=" + adjustedTerm + "&dataType=SR%20Legacy&pageSize=" + std::to_string(RESULTSPERQUERY) + "&pageNumber=" + std::to_string(inputPageNumber));
	std::wstring wurl = std::wstring(url.length(), L' ');
	std::copy(url.begin(), url.end(), wurl.begin());
	try {
		auto processOp{ ProcessGETAsync(wurl) };
		while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
	}
	catch (hresult_error const& ex) {
		httpResponseBody = ex.message();
	}
	USDA_API_response = nlohmann::json::parse(httpResponseBody);
	if (USDA_API_response.at("totalHits") == 0) return ret;
	LogResponse(); // optional for debugging

	UpdateResultsDetails();
	for (int i = 0; i < numItems; ++i) {
		ret.insert(std::pair(to_hstring(USDA_API_response.at("foods").at(i).at("description")), USDA_API_response.at("foods").at(i).at("fdcId")));
	}
	return ret;
}

Windows::Foundation::IAsyncAction USDA_API::ProcessGETAsync(std::wstring wurl) {
	Windows::Foundation::Uri requestUri{ wurl };
	co_await resume_background();
	httpResponseMessage = co_await httpClient.GetAsync(requestUri);
	httpResponseMessage.EnsureSuccessStatusCode();
	httpResponseBody = co_await httpResponseMessage.Content().ReadAsStringAsync();
}

void USDA_API::LogResponse() {
	std::string s; // Debug Output
	s.append("Total hits/pageSize/pageNumber: " + to_string(USDA_API_response.at("totalHits")) + "/" + to_string(USDA_API_response.at("foodSearchCriteria").at("pageSize")) + "/" + to_string(USDA_API_response.at("foodSearchCriteria").at("pageNumber")) + "\n");
	std::wstring str2(s.length(), L' ');
	std::copy(s.begin(), s.end(), str2.begin());
	OutputDebugStringW(str2.c_str());

	// Capture response in local file
	std::string resp = USDA_API_response.dump(3); // File Output
	try {
		auto processOp{ Storage::Test_CollectResponseAsync(&resp) };
		while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
	}
	catch (hresult_error const& ex) {
		httpResponseBody = ex.message();
	}
}

void USDA_API::UpdateResultsDetails() {
	int pageSize = USDA_API_response.at("foodSearchCriteria").at("pageSize");
	currentPage = USDA_API_response.at("currentPage");
	totalPages = USDA_API_response.at("totalPages");
	int totalHits = USDA_API_response.at("totalHits");
	numItems = (currentPage != totalPages ? pageSize : totalHits - (pageSize * (totalPages - 1)));
}