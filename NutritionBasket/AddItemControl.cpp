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

		NutritionBasket::BluePrint PreLoadedBluePrint = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint.Name(L"My BluePrint");
		PreLoadedBluePrint.Amount(L"30g");
		PreLoadedBluePrint.AddElem(L"Fat", L"1g");
		PreLoadedBluePrint.AddElem(L"Sugar", L"200g");
		PreLoadedBluePrint.AddElem(L"Carb", L"47850g");
		NutritionBasket::BluePrint PreLoadedBluePrint2 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint2.Name(L"My Second BluePrint");
		PreLoadedBluePrint2.Amount(L"333g");
		PreLoadedBluePrint2.AddElem(L"Fat", L"3g");
		PreLoadedBluePrint2.AddElem(L"Sugar", L"333g");
		PreLoadedBluePrint2.AddElem(L"Carb", L"3333333g");
		m_localSearchList.BluePrints().Append(PreLoadedBluePrint);
		m_localSearchList.BluePrints().Append(PreLoadedBluePrint2);
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
		// Update LocalSearchList
		SearchResults().Visibility(Visibility::Visible);
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
			NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(SearchBar().Text(), L"150g");
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
