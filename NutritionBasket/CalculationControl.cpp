#include "pch.h"
#include "CalculationControl.h"
#include "MainPage.h"
#if __has_include("CalculationControl.g.cpp")
#include "CalculationControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;

namespace winrt::NutritionBasket::implementation
{
    CalculationControl::CalculationControl()
    {
        InitializeComponent();
		DaysInputError().Visibility(Visibility::Collapsed);
		AverageBtn().IsEnabled(false);
    }

	int32_t CalculationControl::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void CalculationControl::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}

	hstring CalculationControl::Days() {
		return DaysInput().Text();
	}

	void CalculationControl::Days(hstring s) {
		DaysInput().Text(s);
	}

    void CalculationControl::DaysChangedHandler(IInspectable const&, Controls::TextChangedEventArgs const&) {
		try {
			std::string numString = to_string(DaysInput().Text());
			if (numString.size() == 0) {
				DaysInputError().Visibility(Visibility::Collapsed);
				AverageBtn().IsEnabled(false);
				return;
			}
			for (int i = 0; i < numString.size(); ++i) {
				if (!isdigit(numString.at(i))) {
					numString = "s"; //aka invalid input
					break;
				}
			}
			if (std::stoi(numString) > 0) {
				DaysInputError().Visibility(Visibility::Collapsed);
				AverageBtn().IsEnabled(true);
			}
			else {
				DaysInputError().Visibility(Visibility::Visible);
				AverageBtn().IsEnabled(false);
			}
		}
		catch (std::invalid_argument const& ex) {
			// do something
			DaysInputError().Visibility(Visibility::Visible);
			AverageBtn().IsEnabled(false);
		}
    }

    void CalculationControl::AvgClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->MyCalculationResults().OpenCalculationResultsDialog();
    }
}
