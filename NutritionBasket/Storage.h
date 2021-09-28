#pragma once
#include "BluePrint.h"
#include "BasketItem.h"
#include "BasketViewModel.h"
#include "BasketItemNutriElem.h"

namespace Storage{
	void SetAliveFlag(boolean val);
	void SetChangeFlag(boolean val);
	boolean GetAliveFlag();
	boolean GetChangeFlag();

	// Load BluePrints
	winrt::Windows::Foundation::IAsyncAction ReadStorageAsync(std::string* data);
	// Save New BluePrint
	winrt::Windows::Foundation::IAsyncAction SaveNewItemAsync(winrt::NutritionBasket::BluePrint* NewItem);

	//Save Layout
	void SaveLayout();
	void GetLayout(std::string* layout);
	winrt::Windows::Foundation::IAsyncAction AutoSaveLayoutAsync();
	winrt::Windows::Foundation::IAsyncAction SaveLayoutAsync(std::string* layout);
	// Load Layout
	winrt::Windows::Foundation::IAsyncAction GetLayoutMappingAsync(std::string* layout);
	
	// Write USDA API response
	winrt::Windows::Foundation::IAsyncAction Test_CollectResponseAsync(std::string* resp);
};

