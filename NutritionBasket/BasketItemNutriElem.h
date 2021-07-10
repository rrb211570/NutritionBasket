#pragma once

#include "BasketItemNutriElem.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct BasketItemNutriElem : BasketItemNutriElemT<BasketItemNutriElem>
    {
        BasketItemNutriElem() = delete;
        BasketItemNutriElem(winrt::hstring nutrient, winrt::hstring amount);

        winrt::hstring Nutrient();
        winrt::hstring Amount();
        void BasketItemNutriElem::Nutrient(winrt::hstring const& value);
        void BasketItemNutriElem::Amount(winrt::hstring const& value);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_nutrient;
        winrt::hstring m_amount;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BasketItemNutriElem : BasketItemNutriElemT<BasketItemNutriElem, implementation::BasketItemNutriElem>
    {
    };
}
