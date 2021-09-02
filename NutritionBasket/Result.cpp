#include "pch.h"
#include "Result.h"
#if __has_include("Result.g.cpp")
#include "Result.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    Result::Result(winrt::hstring name, winrt::hstring fdcid)
    {
        m_name = name;
        m_Fdcid = fdcid;
    }

    winrt::hstring Result::Name() {
        return m_name;
    }

    void Result::Name(winrt::hstring const& value) {
        if (m_name != value)
        {
            m_name = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::hstring Result::Fdcid() {
        return m_Fdcid;
    }

    void Result::Fdcid(winrt::hstring const& value) {
        if (m_Fdcid != value)
        {
            m_Fdcid = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Fdcid" });
        }
    }

    winrt::event_token Result::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void Result::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
