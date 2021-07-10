#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "DeleteBasketControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct DeleteBasketControl : DeleteBasketControlT<DeleteBasketControl>
    {
        DeleteBasketControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void DeleteColClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void DeleteColCancelClickHandler(Windows::Foundation::IInspectable const& local_flyout, Windows::UI::Xaml::RoutedEventArgs const&);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct DeleteBasketControl : DeleteBasketControlT<DeleteBasketControl, implementation::DeleteBasketControl>
    {
    };
}
