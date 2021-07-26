#include "pch.h"
#include "AddItemControl.h"
#include "MainPage.h"
#if __has_include("AddItemControl.g.cpp")
#include "AddItemControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	AddItemControl::AddItemControl()
	{
		InitializeComponent();
	}

	NutritionBasket::BluePrintList AddItemControl::LocalSearchList()
	{
		return m_localSearchList;
	}

	NutritionBasket::BluePrint AddItemControl::SelectedItem()
	{
		return m_selectedItem;
	}

	void AddItemControl::SearchBarEntryHandler(IInspectable const& sender, Input::KeyRoutedEventArgs const& e)
	{
		winrt::hstring entryName = SearchBar().Text();
		if (entryName.size() == 0) return; // if user typed enter or bksp on empty searchBox
		// Update LocalSearchList
		SearchResults().Visibility(Visibility::Visible);
		m_selectedItem = NULL;
		m_localSearchList.BluePrints().Clear();
		// triggers strstr() on each BluePrint : BluePrintList, to populate LocalSearchList()
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		for (int i = 0; i < main->LocalBluePrints().BluePrints().Size(); ++i) {
			winrt::hstring bluePrintName = main->LocalBluePrints().BluePrints().GetAt(i).Name();
			char lowerBluePrintName[50];
			char lowerEntryName[50];
			strcpy_s(lowerBluePrintName, 50, winrt::to_string(bluePrintName).c_str());
			strcpy_s(lowerEntryName, 50, winrt::to_string(entryName).c_str());
			main->LowerCase(lowerBluePrintName);
			main->LowerCase(lowerEntryName);
			if (strstr(lowerBluePrintName, lowerEntryName) != NULL) {
				m_localSearchList.BluePrints().Append(main->LocalBluePrints().BluePrints().GetAt(i));
			}
		}
	}

	void AddItemControl::ClearSearchBarHandler(IInspectable const& sender, RoutedEventArgs const& e)
	{
		// Update LocalSearchList
		SearchBar().Text(L"");
		searchUSDA().Visibility(Visibility::Visible);
		USDASearchResults().Visibility(Visibility::Collapsed);
		SearchResults().Visibility(Visibility::Collapsed);
	}

	void AddItemControl::SelectItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		SearchBar().Text(sender.as<Controls::Button>().Content().as<winrt::hstring>());
		SearchResults().Visibility(Visibility::Collapsed);
		// update selected item
		m_selectedItem = sender.as<Controls::Button>().DataContext().as<NutritionBasket::BluePrint>();
	}

	void AddItemControl::LocalExpandClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
	}

	void AddItemControl::SearchUSDAClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		USDASearchResults().Visibility(Visibility::Visible);
		searchUSDA().Visibility(Visibility::Collapsed);
	}

	void AddItemControl::USDAExpandClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
	}

	void AddItemControl::AddItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		int index = main->BodyList().SelectedIndex();
		// attach name input
		if (SelectedItem() == NULL) {
			NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(L"Invalid", L"150g");
			ClickItem.BasketIndex(index);
			ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
			// attach nutri input
			ClickItem.AddElem(L"Fat", L"30g");
			ClickItem.AddElem(L"Sugar", L"110g");
			ClickItem.AddElem(L"Carbs", L"1111g");
			main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);
		} else {
			NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(SelectedItem().Name(), SelectedItem().Amount());
			ClickItem.BasketIndex(index);
			ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
			// attach nutri input
			for (int i = 0; i < SelectedItem().Elems().Size(); ++i) {
				ClickItem.AddElem(SelectedItem().Elems().GetAt(i).Nutrient(), SelectedItem().Elems().GetAt(i).Amount());
			}
			main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);
		}
		SearchBar().Text(L"");
		main->ClosePopUps();
	}

	void AddItemControl::AddItemCancelClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		SearchBar().Text(L"");
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->ClosePopUps();
	}
}
