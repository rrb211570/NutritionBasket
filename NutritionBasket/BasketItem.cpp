#include "pch.h"
#include "BasketItem.h"
#if __has_include("BasketItem.g.cpp")
#include "BasketItem.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BasketItem::BasketItem()
    {
        m_bluePrint = winrt::make<NutritionBasket::implementation::BluePrint>();
    }

    NutritionBasket::BluePrint BasketItem::BluePrint() {
        return m_bluePrint;
    }

    uint8_t BasketItem::ItemIndex() {
        return m_itemIndex;
    }

    uint8_t BasketItem::BasketIndex() {
        return m_basketIndex;
    }

    void BasketItem::UpdateBluePrint(NutritionBasket::BluePrint print) {
        m_bluePrint = print;
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
