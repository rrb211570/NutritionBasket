#pragma once

class USDA_API {
public:
	USDA_API();
	std::map<winrt::hstring, int> Search(winrt::hstring term);

private:

};