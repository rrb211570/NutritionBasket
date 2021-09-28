#pragma once
#include "BasketItem.h"
#include "BluePrint.h"

namespace Util {
	std::wstring StrToWStr(std::string str);
	void LowerCase(char* arr);
	void CopyItemElems(winrt::NutritionBasket::BasketItem* basketItem, winrt::NutritionBasket::BluePrint* bluePrint, double itemAmount);
}