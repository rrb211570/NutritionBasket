#include "pch.h"
#include "Parsing.h"
#include "Mainpage.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
namespace Parsing {
	void LoadBluePrintData(std::string* data, NutritionBasket::BluePrintList* bluePrints) {
		if (data->size() != 0) {
			auto it = data->begin();
			std::string curChar;
			int flag = 0; // 0 = name start, 1 = amount start, 2 = elem start
			while (1) {
				NutritionBasket::BluePrint BluePrintEntry = make<NutritionBasket::implementation::BluePrint>();
				std::string name, amount, nutrient, nutrientAmount;
				flag = 0;
				while ((*it) != '\n') {
					switch (flag) {
					case 0: {
						while (*(++it) != '\"') { // "(N)ame",
							curChar = (*it);
							name.append(curChar);
						}
						std::wstring hName(name.length(), L' ');;
						std::copy(name.begin(), name.end(), hName.begin());
						BluePrintEntry.Name(hName);
						name.clear();
						++it;
						flag = 1;
						break;
					}
					case 1: {
						while (*(++it) != ',') { // (1)94
							curChar = (*it);
							amount.append(curChar);
						}
						std::wstring hAmount(amount.length(), L' ');;
						std::copy(amount.begin(), amount.end(), hAmount.begin());
						BluePrintEntry.Amount(hAmount);
						amount.clear();
						++it;
						flag = 2;
						break;
					}
					case 2: {
						while (*it != '\n') {
							while (*(++it) != '\"') { // "(N)utrient",
								curChar = (*it);
								nutrient.append(curChar);
							}
							++it;
							while (*(++it) != ',' && *it != '\n') { // (1)94,
								curChar = (*it);
								nutrientAmount.append(curChar);
							}
							// Add Nutrient
							std::wstring hNutrient(nutrient.length(), L' ');;
							std::copy(nutrient.begin(), nutrient.end(), hNutrient.begin());
							std::wstring hNutrientAmount(nutrientAmount.length(), L' ');;
							std::copy(nutrientAmount.begin(), nutrientAmount.end(), hNutrientAmount.begin());
							BluePrintEntry.AddElem(hNutrient, hNutrientAmount);
							nutrient.clear();
							nutrientAmount.clear();
							if (*it != '\n') ++it;
						}
						break;
					}
					}
				}
				bluePrints->BluePrints().Append(BluePrintEntry);
				if (++it == data->end()) break;
			}
		}
	}

	// FSM to populate BodyViewModel
	void RebuildLayout(std::string* layout, NutritionBasket::BluePrintList* localList, NutritionBasket::BodyViewModel* baskets) {
		// FSM to populate BodyViewModel
		if (layout->size() != 0) {
			auto it = layout->begin();
			std::string curChar;
			NutritionBasket::BasketViewModel MyBasket = make<NutritionBasket::implementation::BasketViewModel>();
			NutritionBasket::BasketItem MyItemEntry = make<NutritionBasket::implementation::BasketItem>();
			NutritionBasket::BluePrint MyBluePrint = make<NutritionBasket::implementation::BluePrint>();
			std::string basketName, itemName, itemAmount;
			int basketIndex = 0;
			int itemIndex = 0;
			int flag = 0; // 0 = basketName start, 1 = ItemName start, 2 = itemAmount start
			while (it != layout->end()) {
				switch (flag) {
				case 0: {
					while (*it != '\n') { // (D)ay 4\n
						curChar = *(it++);
						basketName.append(curChar);
					}
					MyBasket.Name(to_hstring(basketName));
					MyBasket.BasketIndex(basketIndex);
					basketName.clear();
					++it;
					flag = 1;
					break;
				}
				case 1: {
					while (*it != '\n') { // (B)roccoli, chinese, raw\n
						curChar = *(it++);
						itemName.append(curChar);
					}
					MyBluePrint.Name(to_hstring(itemName));
					MyItemEntry.BasketIndex(basketIndex);
					MyItemEntry.ItemIndex(itemIndex++);
					++it;
					flag = 2;
					break;
				}
				case 2: {
					while (*it != '\n') { // (1)48
						curChar = *(it++);
						itemAmount.append(curChar);
					}
					MyBluePrint.Amount(to_hstring(itemAmount));
					MyItemEntry.UpdateBluePrint(MyBluePrint);
					for (int i = 0; i < localList->BluePrints().Size(); ++i) {
						auto s1 = itemName.c_str();
						auto tmp = to_string(localList->BluePrints().GetAt(i).Name());
						auto s2 = tmp.c_str();
						if (strcmp(s1, s2) == 0) {
							Util::CopyItemElems(&MyItemEntry, &(localList->BluePrints().GetAt(i)), stod(itemAmount));
							break;
						}
					}
					itemName.clear();
					itemAmount.clear();
					MyBasket.Basket().Append(MyItemEntry);
					MyItemEntry = make<NutritionBasket::implementation::BasketItem>();
					MyBluePrint = make<NutritionBasket::implementation::BluePrint>();
					++it;
					if (*it != '\n') {
						flag = 1;
					}
					else {
						baskets->BasketViews().Append(MyBasket);
						if (++it == layout->end()) break;
						basketIndex++;
						itemIndex = 0;
						MyBasket = make<NutritionBasket::implementation::BasketViewModel>();
						flag = 0;
					}
					break;
				}
				}
			}
		}
	}
}