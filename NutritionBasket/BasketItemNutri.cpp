#include "pch.h"
#include "BasketItemNutri.h"
#if __has_include("BasketItemNutri.g.cpp")
#include "BasketItemNutri.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BasketItemNutri::BasketItemNutri()
    {
        m_elems = winrt::single_threaded_observable_vector<NutritionBasket::BasketItemNutriElem>();
    }

    winrt::hstring BasketItemNutri::Amount()
    {
        return m_amt;
    }

    void BasketItemNutri::Amount(winrt::hstring const& value)
    {
        if (m_amt != value)
        {
            m_amt = value;
            // Call Nutri(updated values);
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Amount" });
        }
    }

    void BasketItemNutri::AddElem(winrt::hstring name, winrt::hstring quantity)
    {
        m_elems.Append(winrt::make<NutritionBasket::implementation::BasketItemNutriElem>(name, quantity));
        m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Elems" });
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> BasketItemNutri::Elems()
    {
        return m_elems;
    }

    winrt::event_token BasketItemNutri::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void BasketItemNutri::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
