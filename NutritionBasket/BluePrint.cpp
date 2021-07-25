#include "pch.h"
#include "BluePrint.h"
#if __has_include("BluePrint.g.cpp")
#include "BluePrint.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BluePrint::BluePrint()
    {
        m_elems = winrt::single_threaded_observable_vector<NutritionBasket::BasketItemNutriElem>();
    }

    winrt::hstring BluePrint::Name()
    {
        return m_name;
    }

    winrt::hstring BluePrint::Amount()
    {
        return m_amt;
    }

    void BluePrint::Name(winrt::hstring const& value)
    {
        if (m_name != value)
        {
            m_name = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    void BluePrint::Amount(winrt::hstring const& value)
    {
        if (m_amt != value)
        {
            m_amt = value;
            // Call Nutri(updated values);
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Amount" });
        }
    }

    void BluePrint::AddElem(winrt::hstring name, winrt::hstring quantity)
    {
        m_elems.Append(winrt::make<NutritionBasket::implementation::BasketItemNutriElem>(name, quantity));
        m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Elems" });
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItemNutriElem> BluePrint::Elems()
    {
        return m_elems;
    }

    winrt::event_token BluePrint::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void BluePrint::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
