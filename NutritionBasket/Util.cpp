#include "pch.h"
#include "Util.h"

using namespace winrt;
namespace Util {

	std::wstring StrToWStr(std::string str) {
		std::wstring wstr(str.length(), L' ');
		std::copy(str.begin(), str.end(), wstr.begin());
		return wstr;
	}

	void LowerCase(char* arr) {
		if (arr[0] == '\0') return;
		int i = -1;
		while (arr[++i] != '\0') {
			if (arr[i] <= 'Z' && arr[i] >= 'A') arr[i] = arr[i] - ('Z' - 'z');
		}
	}

	void CopyItemElems(NutritionBasket::BasketItem* basketItem, NutritionBasket::BluePrint* bluePrint, double itemAmount) {
		double ratio = itemAmount / 100;
		for (int i = 0; i < bluePrint->Elems().Size(); ++i) {
			double quantity = (round(stod(to_string(bluePrint->Elems().GetAt(i).Amount())) * ratio * 1000)) / 1000;
			basketItem->BluePrint().AddElem(bluePrint->Elems().GetAt(i).Nutrient(), to_hstring(quantity));
		}
	}
}