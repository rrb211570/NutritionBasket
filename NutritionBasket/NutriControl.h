#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "NutriControl.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct NutriControl : NutriControlT<NutriControl>
    {
        NutriControl();

        NutritionBasket::BasketItem BasketItem()
        {
            return winrt::unbox_value<NutritionBasket::BasketItem>(GetValue(m_basketItemProperty));
        }

        void BasketItem(NutritionBasket::BasketItem const& value)
        {
            SetValue(m_basketItemProperty, winrt::box_value(value));
        }

        static Windows::UI::Xaml::DependencyProperty BasketItemProperty() { return m_basketItemProperty; }

        static void OnBasketItemChanged(Windows::UI::Xaml::DependencyObject const&, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);

    private:
        static Windows::UI::Xaml::DependencyProperty m_basketItemProperty;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct NutriControl : NutriControlT<NutriControl, implementation::NutriControl>
    {
    };
}
