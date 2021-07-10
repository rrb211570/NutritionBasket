#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "AddItemControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl>
    {
        AddItemControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void AddItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void NewItemCancelClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl, implementation::AddItemControl>
    {
    };
}
