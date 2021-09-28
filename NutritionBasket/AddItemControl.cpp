#include "pch.h"
#include "AddItemControl.h"
#include "MainPage.h"
#if __has_include("AddItemControl.g.cpp")
#include "AddItemControl.g.cpp"
#endif
constexpr boolean validEntryFlag = true;
constexpr boolean unknownEntryFlag = false;

using namespace winrt;
using namespace Windows::UI::Xaml;
namespace winrt::NutritionBasket::implementation
{
	AddItemControl::AddItemControl() { InitializeComponent(); }

	NutritionBasket::BluePrintList AddItemControl::LocalSearchList() { return m_localSearchList; }
	NutritionBasket::BluePrint AddItemControl::SelectedItem() { return m_selectedItem; }
	hstring AddItemControl::SearchBarText() { return SearchBar().Text(); }

	void AddItemControl::SearchBarText(hstring s) { SearchBar().Text(s); }
	void AddItemControl::SetSelectedItem(NutritionBasket::BluePrint item) { m_selectedItem = item; }
	void AddItemControl::HideSearchResults() { SearchResults().Visibility(Visibility::Collapsed); }

	void AddItemControl::OpenSearchDialog()
	{
		SearchResults().Visibility(Visibility::Collapsed);
		MySearchUSDAControl().ResetVisibilities();
		m_selectedItem = NULL;
		UpdateSearchBarUX(unknownEntryFlag);
		AddItemButton().IsEnabled(false);
		AddSelectedItem().Visibility(Visibility::Collapsed);
		AmountInputError().Visibility(Visibility::Collapsed);
		AddItemDialog().ShowAsync();
	}

	void AddItemControl::SearchBarEntryHandler(IInspectable const&, Controls::TextChangedEventArgs const&)
	{
		NoLocalResults().Visibility(Visibility::Collapsed);
		MySearchUSDAControl().ResetVisibilities();
		hstring entryName = SearchBar().Text();
		if (m_selectedItem == NULL) {
			UpdateSearchBarUX(unknownEntryFlag);
			AddSelectedItem().Visibility(Visibility::Collapsed);
		}
		if (m_selectedItem != NULL && m_selectedItem.Name() != entryName) {
			m_selectedItem = NULL;
			UpdateSearchBarUX(unknownEntryFlag);
			AddSelectedItem().Visibility(Visibility::Collapsed);
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
		for (uint8_t i = 0; i < main->LocalBluePrints().BluePrints().Size(); ++i) {
			hstring bluePrintName = main->LocalBluePrints().BluePrints().GetAt(i).Name();
			char lowerBluePrintName[100];
			char lowerEntryName[100];
			strcpy_s(lowerBluePrintName, 100, to_string(bluePrintName).c_str());
			strcpy_s(lowerEntryName, 100, to_string(entryName).c_str());
			Util::LowerCase(lowerBluePrintName);
			Util::LowerCase(lowerEntryName);
			if (strstr(lowerBluePrintName, lowerEntryName) != NULL) {
				m_localSearchList.BluePrints().Append(main->LocalBluePrints().BluePrints().GetAt(i));
			}
			if (m_localSearchList.BluePrints().Size() == 5) break;
		}
		if (m_localSearchList.BluePrints().Size() == 0) NoLocalResults().Visibility(Visibility::Visible);
	}

	void AddItemControl::SelectItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		SearchBar().Text(sender.as<Controls::Button>().Content().as<hstring>());
		SearchResults().Visibility(Visibility::Collapsed);
		// update selected item
		m_selectedItem = sender.as<Controls::Button>().DataContext().as<NutritionBasket::BluePrint>();
		UpdateSearchBarUX(validEntryFlag);
		AmountInput().Text(L"");
		AmountInputError().Visibility(Visibility::Collapsed);
		AddSelectedItem().Visibility(Visibility::Visible);
	}

	void AddItemControl::AmountEntryHandler(IInspectable const&, Controls::TextChangedEventArgs const&) {
		try {
			std::string numString = to_string(AmountInput().Text());
			if (numString.size() == 0) {
				AmountInputError().Visibility(Visibility::Collapsed);
				AddItemButton().IsEnabled(false);
				return;
			}
			for (int i = 0; i < numString.size(); ++i) {
				if (!isdigit(numString.at(i))) {
					numString = "s"; //aka invalid input
					break;
				}
			}
			if (std::stoi(numString) > 0) {
				AmountInputError().Visibility(Visibility::Collapsed);
				AddItemButton().IsEnabled(true);
			}
			else {
				AmountInputError().Visibility(Visibility::Visible);
				AddItemButton().IsEnabled(false);
			}
		}
		catch (std::invalid_argument const& ex) {
			// do something
			AmountInputError().Visibility(Visibility::Visible);
			AddItemButton().IsEnabled(false);
		}
	}

	void AddItemControl::AddItemClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		uint8_t index = main->BodyList().SelectedIndex();
		// Build up item
		NutritionBasket::BasketItem ClickItem = make<NutritionBasket::implementation::BasketItem>();
		ClickItem.BluePrint().Name(SelectedItem().Name());
		ClickItem.BluePrint().Amount(L"100");
		// update BluePrint if necessary
		UpdateLocalBlueprints(ClickItem.BluePrint());
		// Add item, w/ nutrition ratio'd by input amount
		ClickItem.BasketIndex(index);
		ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
		ClickItem.BluePrint().Amount(AmountInput().Text());
		RatioElems(&ClickItem, AmountInput().Text());

		main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);

		UpdateSearchBarUX(unknownEntryFlag);
		Storage::SaveLayout();
		AddItemDialog().Hide();
	}

	void AddItemControl::DefaultDialogClosedClickHandler(IInspectable const&, Controls::ContentDialogClosedEventArgs const&)
	{
		SearchBar().Text(L"");
		UpdateSearchBarUX(unknownEntryFlag);
	}

	void AddItemControl::UpdateSearchBarUX(boolean state)
	{
		if (state) {
			SearchBar().Style(validEntry());
			AmountInput().Text(L"");
			AddSelectedItem().Visibility(Visibility::Visible);
		}
		else {
			Controls::TextBox tmp;
			SearchBar().Style(tmp.Style());
		}
	}

	void AddItemControl::UpdateLocalBlueprints(NutritionBasket::BluePrint ItemToAdd)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		boolean found = false;
		std::string NewItemName = to_string(ItemToAdd.Name().c_str());
		for (uint8_t i = 0; i < main->LocalBluePrints().BluePrints().Size(); ++i) {
			std::string bluePrintName = to_string(main->LocalBluePrints().BluePrints().GetAt(i).Name().c_str());
			if (strcmp(bluePrintName.c_str(), NewItemName.c_str()) == 0) found = true;
		}
		if (found == false) {
			NutritionBasket::BluePrint NewItem = make<NutritionBasket::implementation::BluePrint>();
			NewItem.Name(ItemToAdd.Name());
			NewItem.Amount(ItemToAdd.Amount());
			for (uint8_t i = 0; i < SelectedItem().Elems().Size(); ++i) {
				NewItem.AddElem(SelectedItem().Elems().GetAt(i).Nutrient(), SelectedItem().Elems().GetAt(i).Amount());
			}
			main->LocalBluePrints().BluePrints().Append(NewItem);
			auto processOp{ Storage::SaveNewItemAsync(&NewItem) };
			while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
		}
	}

	void AddItemControl::RatioElems(NutritionBasket::BasketItem* Item, hstring amount) {
		double ratio = stod(to_string(amount)) / 100;
		for (uint8_t i = 0; i < SelectedItem().Elems().Size(); ++i) {
			auto f = SelectedItem().Elems().GetAt(i);
			double quantity = (round(stod(to_string(SelectedItem().Elems().GetAt(i).Amount())) * ratio * 1000)) / 1000;
			Item->BluePrint().AddElem(SelectedItem().Elems().GetAt(i).Nutrient(), to_hstring(quantity));
		}
	}
}
