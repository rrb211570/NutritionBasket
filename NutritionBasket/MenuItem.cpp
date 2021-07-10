#include "pch.h"
#include "MenuItem.h"
#if __has_include("MenuItem.g.cpp")
#include "MenuItem.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    MenuItem::MenuItem(winrt::hstring const& name) : m_name{ name }
    {
    }

    winrt::hstring MenuItem::Name()
    {
        return m_name;
    }

    void MenuItem::Name(winrt::hstring const& value)
    {
        if (m_name != value)
        {
            m_name = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::event_token MenuItem::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void MenuItem::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }
}
