#include "pch.h"
#include "SearchUSDAControl.h"
#include "MainPage.h"
#if __has_include("SearchUSDAControl.g.cpp")
#include "SearchUSDAControl.g.cpp"
#endif
constexpr boolean validEntryFlag = true;
constexpr boolean unknownEntryFlag = false;

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	SearchUSDAControl::SearchUSDAControl()
	{
		InitializeComponent();
		m_USDAResults = single_threaded_observable_vector<NutritionBasket::Result>();
		m_USDA_API = USDA_API();
	}

	Windows::Foundation::Collections::IObservableVector<NutritionBasket::Result> SearchUSDAControl::USDAResults() {
		return m_USDAResults;
	}

	void SearchUSDAControl::ResetVisibilities() {
		searchUSDA().Visibility(Visibility::Visible);
		USDASearchResults().Visibility(Visibility::Collapsed);
	}

	void SearchUSDAControl::SearchUSDAClickHandler(IInspectable const&, RoutedEventArgs const&) { HandleSearch(0); }
	void SearchUSDAControl::USDAPrevClickHandler(IInspectable const&, RoutedEventArgs const&) { HandleSearch(-1); }
	void SearchUSDAControl::USDANextClickHandler(IInspectable const&, RoutedEventArgs const&) { HandleSearch(1); }

	void SearchUSDAControl::HandleSearch(int velocity) {
		Searching();
		m_USDAResults.Clear();

		USDASuccess().Visibility(Visibility::Collapsed);
		USDAEmpty().Visibility(Visibility::Collapsed);
		USDAError().Visibility(Visibility::Collapsed);

		if (velocity == 0) auto processOp{ SearchCoRoutine(1) }; // "origin"
		else if (velocity == -1) auto processOp{ SearchCoRoutine(m_USDA_API.GetCurrentPage() - 1) }; // "move left"
		else if (velocity == 1) auto processOp{ SearchCoRoutine(m_USDA_API.GetCurrentPage() + 1) };// "move right"
	}

	Windows::Foundation::IAsyncAction SearchUSDAControl::SearchCoRoutine(int inputPageNumber) {

		apartment_context ui_thread; // makes nested co-routine work, no idea why...
		co_await resume_after(std::chrono::milliseconds(1)); // allows "Search USDA" to change to "Searching..."
		co_await ui_thread;
		NutritionBasket::implementation::MainPage* main = get_self<NutritionBasket::implementation::MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		std::map<hstring, int> names = m_USDA_API.Search(main->MyAddItemControl().SearchBarText(), inputPageNumber); //nested co-routine

		// if(names.network error) USDAError().Visibility(Visibility::Visible); return;
		for (auto entry = names.begin(); entry != names.end(); ++entry) m_USDAResults.Append
		(make<NutritionBasket::implementation::Result>(entry->first, to_hstring(entry->second)));

		searchUSDA().Visibility(Visibility::Collapsed);
		USDASearchResults().Visibility(Visibility::Visible);
		if (m_USDAResults.Size() != 0) USDASuccess().Visibility(Visibility::Visible);
		else USDAEmpty().Visibility(Visibility::Visible);
		ReturnedUSDAResults();
		UpdateNavigationBtns();
	}

	void SearchUSDAControl::Searching() {
		Controls::TextBlock thing;
		thing.Text(L"Searching...");
		searchUSDA().Content(thing);
	}

	void SearchUSDAControl::ReturnedUSDAResults() {
		Controls::TextBlock thing;
		thing.Text(L"Search USDA");
		searchUSDA().Content(thing);
	}

	void SearchUSDAControl::UpdateNavigationBtns() {
		if (m_USDA_API.GetCurrentPage() == 1) USDAPrev().IsEnabled(false);
		else USDAPrev().IsEnabled(true);
		if (m_USDA_API.GetCurrentPage() == m_USDA_API.GetLastPage()) USDANext().IsEnabled(false);
		else USDANext().IsEnabled(true);
	}

	void SearchUSDAControl::SelectUSDAItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		NutritionBasket::implementation::MainPage* main = get_self<NutritionBasket::implementation::MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->MyAddItemControl().SearchBarText(sender.as<Controls::Button>().Content().as<hstring>());
		main->MyAddItemControl().HideSearchResults();
		// update selected item
		NutritionBasket::Result entry = sender.as<Controls::Button>().DataContext().as<NutritionBasket::Result>();
		NutritionBasket::BluePrint newItem = m_USDA_API.ResponseItemNutri(std::stoi(entry.Fdcid().c_str()));
		main->MyAddItemControl().SetSelectedItem(newItem);
		main->MyAddItemControl().UpdateSearchBarUX(validEntryFlag);
	}
}
