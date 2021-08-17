#include "pch.h"
#include "Result.h"
#if __has_include("Result.g.cpp")
#include "Result.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    Result::Result(winrt::hstring name)
    {
        m_name = name;
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

    winrt::event_token Result::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void Result::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
