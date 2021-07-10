﻿#include "pch.h"
#include "BasketItem.h"
#if __has_include("BasketItem.g.cpp")
#include "BasketItem.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BasketItem::BasketItem(winrt::hstring name)
    {
        m_name = name;
    }

    winrt::hstring BasketItem::Name()
    {
        return m_name;
    }

    NutritionBasket::BasketItemNutri BasketItem::Nutrition(){
        return m_basketItemNutri;
    }

    uint8_t BasketItem::ItemIndex() {
        return m_itemIndex;
    }

    uint8_t BasketItem::BasketIndex() {
        return m_basketIndex;
    }

    void BasketItem::Name(winrt::hstring const& value)
    {
        if (m_name != value)
        {
            m_name = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    void BasketItem::ItemIndex(uint8_t i) {
        m_itemIndex = i;
    }

    void BasketItem::BasketIndex(uint8_t i) {
        m_basketIndex = i;
    }

    winrt::event_token BasketItem::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void BasketItem::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}