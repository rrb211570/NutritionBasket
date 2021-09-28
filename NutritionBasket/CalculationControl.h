#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "CalculationControl.g.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
namespace winrt::NutritionBasket::implementation
{
    struct CalculationControl : CalculationControlT<CalculationControl>
    {
        CalculationControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);
        hstring Days();
        void Days(hstring s);

        void DaysChangedHandler(Windows::Foundation::IInspectable const&, Controls::TextChangedEventArgs const&);
        void AvgClickHandler(Windows::Foundation::IInspectable const&, RoutedEventArgs const&);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct CalculationControl : CalculationControlT<CalculationControl, implementation::CalculationControl>
    {
    };
}
