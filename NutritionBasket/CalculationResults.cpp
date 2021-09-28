#include "pch.h"
#include "CalculationResults.h"
#include "CalculationControl.h"
#include "MainPage.h"
#if __has_include("CalculationResults.g.cpp")
#include "CalculationResults.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	CalculationResults::CalculationResults()
	{
		InitializeComponent();
	}

	void CalculationResults::OpenCalculationResultsDialog() {
		AverageResults();
		MyDialog().ShowAsync();
	}

	// Takes average of basket and returns item representing results.
	// Assume a basket is always selected.
	NutritionBasket::BluePrint CalculationResults::AverageResults() {
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());

		// Update Title of Dialog based off of DaysInput
		hstring days = main->MyCalculationControl().Days();
		if (days.size() == 0) return m_results; // return empty-initialized m_results
		else m_results.Elems().Clear();
		std::string title;
		if(stoi(to_string((days)))==1) title = "Average Daily Nutrition, for " + to_string(days) + " Day";
		else title = "Average Daily Nutrition, for " + to_string(days) + " Days";
		Controls::TextBlock thing;
		thing.Text(to_hstring(title));
		MyDialog().Title(thing);

		// Populate Amount
		double amount = 0;
		auto basket = main->BodyViewModel().BasketViews().GetAt(main->BodyList().SelectedIndex()).Basket();
		for (int i = 0; i < basket.Size(); ++i) {
			amount += stod(to_string(basket.GetAt(i).BluePrint().Amount()));
		}
		m_results.Amount(to_hstring(amount / stod(to_string(days))));
		Weight().Text(to_hstring("Weight : " + to_string(m_results.Amount())+"g"));

		//Populate Elems
		std::map<hstring, double> nutriMap;
		for (int i = 0; i < basket.Size(); ++i) {
			for (int j = 0; j < basket.GetAt(i).BluePrint().Elems().Size(); ++j) {
				hstring name = basket.GetAt(i).BluePrint().Elems().GetAt(j).Nutrient();
				double amt = stod(to_string(basket.GetAt(i).BluePrint().Elems().GetAt(j).Amount()));
				if (nutriMap.find(name) != nutriMap.end()) {
					amt += nutriMap.find(name)->second;
				}
				nutriMap.insert_or_assign(name, amt);
			}
		}
		for (auto it = nutriMap.begin(); it != nutriMap.end(); ++it) {
			nutriMap.insert_or_assign(it->first, round((it->second)/stod(to_string(days))*1000)/1000);
			m_results.AddElem(it->first, to_hstring(it->second));
		}
		auto s = m_results.Elems().Size();
		return m_results;
	}
	void CalculationResults::CalculationResultsClosedHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogClosedEventArgs const&) {
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->MyCalculationControl().Days(L"");
	}
}
