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
		m_customClick = false;
		m_customAdd = false;
		m_USDAResults = winrt::single_threaded_observable_vector<NutritionBasket::Result>();
		m_USDA_API = USDA_API();
	}

	NutritionBasket::BluePrintList AddItemControl::LocalSearchList()
	{
		return m_localSearchList;
	}

	NutritionBasket::BluePrint AddItemControl::SelectedItem()
	{
		return m_selectedItem;
	}

	Windows::Foundation::Collections::IObservableVector<NutritionBasket::Result> AddItemControl::USDAResults()
	{
		return m_USDAResults;
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
		USDASearchResults().Visibility(Visibility::Collapsed);
		searchUSDA().Visibility(Visibility::Visible);
		winrt::hstring entryName = SearchBar().Text();
		if (m_selectedItem == NULL) ResetEntryBG();
		if (m_selectedItem != NULL && m_selectedItem.Name() != entryName) {
			m_selectedItem = NULL;
			ResetEntryBG();
		}
		else if (m_selectedItem != NULL && m_selectedItem.Name() == entryName) return;
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
		m_USDAResults.Clear();
		searchUSDA().Visibility(Visibility::Collapsed);
		USDASuccess().Visibility(Visibility::Collapsed);
		USDAEmpty().Visibility(Visibility::Collapsed);
		USDAError().Visibility(Visibility::Collapsed);
		USDASearchResults().Visibility(Visibility::Visible);

		SearchCoRoutine();

		if (m_USDAResults.Size() != 0) USDASuccess().Visibility(Visibility::Visible);
		else USDAEmpty().Visibility(Visibility::Visible);
	}

	void AddItemControl::SearchCoRoutine() {

		std::map<winrt::hstring, int> names = m_USDA_API.Search(SearchBar().Text());
		// if(names.network error) USDAError().Visibility(Visibility::Visible); return;
		for (auto entry = names.begin(); entry != names.end(); ++entry) m_USDAResults.Append
			(winrt::make<NutritionBasket::implementation::Result>(entry->first, to_hstring(entry->second)));
	}

	void AddItemControl::SelectUSDAItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		SearchBar().Text(sender.as<Controls::Button>().Content().as<winrt::hstring>());
		SearchResults().Visibility(Visibility::Collapsed);
		// update selected item
		m_selectedItem = winrt::make<NutritionBasket::implementation::BluePrint>();
		m_selectedItem.Name(SearchBar().Text());
		m_selectedItem.Amount(L"99g");
		NutritionBasket::Result entry = sender.as<Controls::Button>().DataContext().as<NutritionBasket::Result>();
		std::map<winrt::hstring, int> nutrients = m_USDA_API.ResponseItemNutri(std::stoi(entry.Fdcid().c_str()));
		for (auto i = nutrients.begin(); i != nutrients.end(); ++i) m_selectedItem.AddElem((*i).first, winrt::to_hstring((*i).second));
		HighlightValidEntry();
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
		NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(SelectedItem().Name(), SelectedItem().Amount());
		ClickItem.BasketIndex(index);
		ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
		// attach nutri input
		for (int i = 0; i < SelectedItem().Elems().Size(); ++i) {
			ClickItem.AddElem(SelectedItem().Elems().GetAt(i).Nutrient(), SelectedItem().Elems().GetAt(i).Amount());
		}
		main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);
		UpdateLocalBlueprints();
		ResetEntryBG();
		AddItemDialog().Hide();
	}

	void AddItemControl::CustomClickHandler(IInspectable const& sender, Controls::ContentDialogButtonClickEventArgs const&)
	{
		SearchBar().Text(L"");
		ResetEntryBG();
		m_customClick = true;
	}

	void AddItemControl::AddItemCancelClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
	{
		SearchBar().Text(L"");
		ResetEntryBG();
	}

	void AddItemControl::DefaultDialogClosedClickHandler(IInspectable const& sender, Controls::ContentDialogClosedEventArgs const&)
	{
		if (m_customClick == true) {
			m_customClick = false;
			AddCustomItemDialog().ShowAsync();
		}
	}

	void AddItemControl::CustomDialogClosedClickHandler(IInspectable const& sender, Controls::ContentDialogClosedEventArgs const&)
	{
		if (m_customAdd == true) {
			m_customAdd = false;
		}
		else {
			AddItemDialog().ShowAsync();
		}
	}

	void AddItemControl::AddCustomClickHandler(IInspectable const& sender, Controls::ContentDialogButtonClickEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		int index = main->BodyList().SelectedIndex();
		NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(CustomName().Text(), CustomAmount().Text());
		ClickItem.BasketIndex(index);
		ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
		// attach nutri input
		ClickItem.AddElem(L"Fat", CustomFat().Text());
		ClickItem.AddElem(L"Sugar", CustomSugar().Text());
		ClickItem.AddElem(L"Carbs", CustomCarbs().Text());
		main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);
		m_customAdd = true;
	}

	void AddItemControl::AddCustomCancelClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
	{
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

	void AddItemControl::UpdateLocalBlueprints()
	{
		
	}
}
