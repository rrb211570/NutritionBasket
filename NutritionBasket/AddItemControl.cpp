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

	void AddItemControl::OpenSearchDialogHandler(IInspectable const& sender, RoutedEventArgs const& e)
	{
		SearchBar().Text(L"");
		searchUSDA().Visibility(Visibility::Visible);
		USDASearchResults().Visibility(Visibility::Collapsed);
		SearchResults().Visibility(Visibility::Collapsed);
		m_selectedItem = NULL;
		ResetEntryBG();
		AddItemDialog().ShowAsync();
	}

	void AddItemControl::SearchBarEntryHandler(IInspectable const& sender, Controls::TextChangedEventArgs const& e)
	{
		NoLocalResults().Visibility(Visibility::Collapsed);
		winrt::hstring entryName = SearchBar().Text();
		if(m_selectedItem==NULL) ResetEntryBG();
		if (m_selectedItem != NULL && m_selectedItem.Name() != entryName) {
			m_selectedItem = NULL;
			ResetEntryBG();
		} else if(m_selectedItem != NULL && m_selectedItem.Name() == entryName) return;
		m_localSearchList.BluePrints().Clear();
		if (entryName.size() == 0) {
			SearchResults().Visibility(Visibility::Collapsed);
			return;
		}
		SearchResults().Visibility(Visibility::Visible);
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
			if (m_localSearchList.BluePrints().Size() == 5) break;
		}
		if (m_localSearchList.BluePrints().Size() == 0) NoLocalResults().Visibility(Visibility::Visible);
	}

	void AddItemControl::SelectItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		SearchBar().Text(sender.as<Controls::Button>().Content().as<winrt::hstring>());
		SearchResults().Visibility(Visibility::Collapsed);
		// update selected item
		m_selectedItem = sender.as<Controls::Button>().DataContext().as<NutritionBasket::BluePrint>();
		HighlightValidEntry();
	}

	void AddItemControl::SearchUSDAClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		searchUSDA().Visibility(Visibility::Collapsed);
		USDASuccess().Visibility(Visibility::Collapsed);
		USDAError().Visibility(Visibility::Collapsed);
		USDASearchResults().Visibility(Visibility::Visible);
		// Rest API to get USDA results

		// if successful, show USDASuccess
		USDASuccess().Visibility(Visibility::Visible);
		// if failure, show USDAError
		USDAError().Visibility(Visibility::Visible);
	}

	void AddItemControl::USDAPrevClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
	}

	void AddItemControl::USDANextClickHandler(IInspectable const& sender, RoutedEventArgs const&)
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
		ResetEntryBG();
		AddItemDialog().Hide();
	}

	void AddItemControl::CustomClickHandler(IInspectable const& sender, Controls::ContentDialogButtonClickEventArgs const&)
	{
		ResetEntryBG();
	}

	void AddItemControl::AddItemCancelClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
	{
		SearchBar().Text(L"");
		ResetEntryBG();
	}

	void AddItemControl::HighlightValidEntry()
	{
		SearchBar().Style(validEntry());
		AddItemButton().IsEnabled(true);
	}

	void AddItemControl::ResetEntryBG()
	{
		Controls::TextBox tmp;
		SearchBar().Style(tmp.Style());
		AddItemButton().IsEnabled(false);
	}
}
