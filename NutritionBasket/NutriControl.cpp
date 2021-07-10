#include "pch.h"
#include "NutriControl.h"
#include "MainPage.h"
#if __has_include("NutriControl.g.cpp")
#include "NutriControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    NutriControl::NutriControl() {
        InitializeComponent();
    }

    Windows::UI::Xaml::DependencyProperty NutriControl::m_basketItemProperty =
        Windows::UI::Xaml::DependencyProperty::Register(
            L"BasketItem",
            winrt::xaml_typename<NutritionBasket::BasketItem>(),
            winrt::xaml_typename<NutritionBasket::NutriControl>(),
            Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"default label"), Windows::UI::Xaml::PropertyChangedCallback{ &NutriControl::OnBasketItemChanged } }
    );

    void NutriControl::OnBasketItemChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& /* e */)
    {
        if (NutritionBasket::NutriControl theControl{ d.try_as<NutritionBasket::NutriControl>() })
        {
            // Call members of the projected type via theControl.

            NutritionBasket::implementation::NutriControl* ptr{ winrt::get_self<NutritionBasket::implementation::NutriControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }
}
