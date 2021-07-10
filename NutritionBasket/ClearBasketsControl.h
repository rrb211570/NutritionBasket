#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "ClearBasketsControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct ClearBasketsControl : ClearBasketsControlT<ClearBasketsControl>
    {
        ClearBasketsControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void ClearClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const&);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct ClearBasketsControl : ClearBasketsControlT<ClearBasketsControl, implementation::ClearBasketsControl>
    {
    };
}
