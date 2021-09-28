#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "NewBasketControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct NewBasketControl : NewBasketControlT<NewBasketControl>
    {
        NewBasketControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void OpenNewBasketDialog();
        void NewColClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void NewColCancelClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct NewBasketControl : NewBasketControlT<NewBasketControl, implementation::NewBasketControl>
    {
    };
}
