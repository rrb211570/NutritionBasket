#pragma once
#include "BasketItem.h"
#include "BluePrint.h"
#include "BluePrintList.h"
#include "MainPage.h"

using namespace winrt;
namespace Parsing {
	void LoadBluePrintData(std::string* data, NutritionBasket::BluePrintList* bluePrints);
	void RebuildLayout(std::string* layout, NutritionBasket::BluePrintList* localList, NutritionBasket::BodyViewModel* baskets);
}