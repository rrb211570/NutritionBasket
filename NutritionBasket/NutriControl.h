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

        NutritionBasket::BluePrint BluePrint()
        {
            return winrt::unbox_value<NutritionBasket::BluePrint>(GetValue(m_bluePrintProperty));
        }

        void BluePrint(NutritionBasket::BluePrint const& value) { SetValue(m_bluePrintProperty, winrt::box_value(value)); }

        static Windows::UI::Xaml::DependencyProperty BluePrintProperty() { return m_bluePrintProperty; }
        static void OnBluePrintChanged(Windows::UI::Xaml::DependencyObject const&, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);

    private:
        static Windows::UI::Xaml::DependencyProperty m_bluePrintProperty;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct NutriControl : NutriControlT<NutriControl, implementation::NutriControl>
    {
    };
}
