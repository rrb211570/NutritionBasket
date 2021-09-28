#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "AddCustomControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct AddCustomControl : AddCustomControlT<AddCustomControl>
    {
        AddCustomControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct AddCustomControl : AddCustomControlT<AddCustomControl, implementation::AddCustomControl>
    {
    };
}
