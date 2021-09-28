#pragma once
#include "json.hpp"
#include "BluePrint.h"
using namespace winrt;

class USDA_API {
public:
	USDA_API();
	int GetCurrentPage();
	int GetLastPage();

	std::map<hstring, int> Search(hstring term, int pageNumber);
	NutritionBasket::BluePrint ResponseItemNutri(int fdcid);
	Windows::Foundation::IAsyncAction ProcessGETAsync(std::wstring wurl);

	void LogResponse();
	void UpdateResultsDetails();
private:
	nlohmann::json USDA_API_response;
	int numItems;
	int currentPage;
	int totalPages;
	Windows::Web::Http::HttpClient httpClient;
	Windows::Web::Http::HttpResponseMessage httpResponseMessage;
	std::wstring httpResponseBody;
};