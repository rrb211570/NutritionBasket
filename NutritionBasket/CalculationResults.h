#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "BluePrint.h"
#include "CalculationResults.g.h"

using namespace winrt;
namespace winrt::NutritionBasket::implementation
{
    struct CalculationResults : CalculationResultsT<CalculationResults>
    {
        CalculationResults();

        void OpenCalculationResultsDialog();
        NutritionBasket::BluePrint AverageResults();
        void CalculationResultsClosedHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogClosedEventArgs const&);
    private:
        NutritionBasket::BluePrint m_results;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct CalculationResults : CalculationResultsT<CalculationResults, implementation::CalculationResults>
    {
    };
}
