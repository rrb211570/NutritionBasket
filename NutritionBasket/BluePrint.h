#pragma once

#include "BluePrint.g.h"
#include "BasketItemNutriElem.h"

namespace winrt::NutritionBasket::implementation
{
    struct BluePrint : BluePrintT<BluePrint>
    {
        BluePrint();

        winrt::hstring Name();
        winrt::hstring Amount();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> Elems();
        void BluePrint::Name(winrt::hstring const& value);
        void BluePrint::Amount(winrt::hstring const& value);
        void BluePrint::AddElem(winrt::hstring name, winrt::hstring quantity);

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_name;
        winrt::hstring m_amt;
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> m_elems;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BluePrint : BluePrintT<BluePrint, implementation::BluePrint>
    {
    };
}
