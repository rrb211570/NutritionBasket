#include "pch.h"
#include "BasketItemNutriElem.h"
#if __has_include("BasketItemNutriElem.g.cpp")
#include "BasketItemNutriElem.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BasketItemNutriElem::BasketItemNutriElem(winrt::hstring nutrient, winrt::hstring amount)
    {
        m_nutrient = nutrient;
        m_amount = amount;
    }

    winrt::hstring BasketItemNutriElem::Nutrient()
    {
        return m_nutrient;
    }

    winrt::hstring BasketItemNutriElem::Amount()
    {
        return m_amount;
    }

    void BasketItemNutriElem::Nutrient(winrt::hstring const& value)
    {
        if (m_nutrient != value)
        {
            m_nutrient = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Nutrient" });
        }
    }

    void BasketItemNutriElem::Amount(winrt::hstring const& value)
    {
        if (m_amount != value)
        {
            m_amount = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Amount" });
        }
    }

    winrt::event_token BasketItemNutriElem::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void BasketItemNutriElem::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
