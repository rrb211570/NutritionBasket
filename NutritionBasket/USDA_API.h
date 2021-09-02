#pragma once
#include "json.hpp"

class USDA_API {
public:
	USDA_API();
	std::map<winrt::hstring, int> Search(winrt::hstring term);
	std::map<winrt::hstring, int> ResponseItemNutri(int fdcid);
	winrt::Windows::Foundation::IAsyncAction ProcessGETAsync();
private:
	nlohmann::json USDA_API_response;
	std::wstring wurl;
	winrt::Windows::Web::Http::HttpClient httpClient;
	winrt::Windows::Web::Http::HttpResponseMessage httpResponseMessage;
	std::wstring httpResponseBody;
};