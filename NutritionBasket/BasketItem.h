#pragma once

#include "BasketItem.g.h"
#include "BasketItemNutriElem.h"

namespace winrt::NutritionBasket::implementation
{
    struct BasketItem : BasketItemT<BasketItem>
    {
        BasketItem() = delete;
        BasketItem(winrt::hstring name, winrt::hstring amount);

        winrt::hstring Name();
        winrt::hstring Amount();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> Elems();
        void BasketItem::AddElem(winrt::hstring name, winrt::hstring quantity);
        void BasketItem::Amount(winrt::hstring const& value);
        uint8_t ItemIndex();
        uint8_t BasketIndex();

        void BasketItem::Name(winrt::hstring const& value);
        void ItemIndex(uint8_t i);
        void BasketIndex(uint8_t i);
        
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_name;
        winrt::hstring m_amt;
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> m_elems;
        uint8_t m_itemIndex;
        uint8_t m_basketIndex;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BasketItem : BasketItemT<BasketItem, implementation::BasketItem>
    {
    };
}
