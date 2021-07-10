#pragma once

#include "BasketItem.g.h"
#include "BasketItemNutri.h"

namespace winrt::NutritionBasket::implementation
{
    struct BasketItem : BasketItemT<BasketItem>
    {
        BasketItem() = delete;
        BasketItem(winrt::hstring name);

        winrt::hstring Name();
        NutritionBasket::BasketItemNutri Nutrition();
        uint8_t ItemIndex();
        uint8_t BasketIndex();

        void BasketItem::Name(winrt::hstring const& value);
        void ItemIndex(uint8_t i);
        void BasketIndex(uint8_t i);
        
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_name;
        uint8_t m_itemIndex;
        uint8_t m_basketIndex;
        NutritionBasket::BasketItemNutri m_basketItemNutri;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BasketItem : BasketItemT<BasketItem, implementation::BasketItem>
    {
    };
}
