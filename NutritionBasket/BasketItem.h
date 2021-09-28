#pragma once

#include "BasketItem.g.h"
#include "BluePrint.h"

namespace winrt::NutritionBasket::implementation
{
    struct BasketItem : BasketItemT<BasketItem>
    {
        BasketItem();

        NutritionBasket::BluePrint BluePrint();
        uint8_t ItemIndex();
        uint8_t BasketIndex();
        void UpdateBluePrint(NutritionBasket::BluePrint print);
        void ItemIndex(uint8_t i);
        void BasketIndex(uint8_t i);
        
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        NutritionBasket::BluePrint m_bluePrint;
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
