#pragma once

#include "BasketItemNutri.g.h"
#include "BasketItemNutriElem.h"
#include "Item.h"

namespace winrt::NutritionBasket::implementation
{

    struct BasketItemNutri : BasketItemNutriT<BasketItemNutri>
    {
        BasketItemNutri();

        winrt::hstring Amount();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> Elems();
        void BasketItemNutri::Amount(winrt::hstring const& value);
        void BasketItemNutri::AddElem(winrt::hstring name, winrt::hstring quantity);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_amt;
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> m_elems;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BasketItemNutri : BasketItemNutriT<BasketItemNutri, implementation::BasketItemNutri>
    {
    };
}
