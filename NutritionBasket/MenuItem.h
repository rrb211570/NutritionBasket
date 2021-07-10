#pragma once

#include "MenuItem.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct MenuItem : MenuItemT<MenuItem>
    {
        MenuItem() = delete;
        MenuItem(winrt::hstring const& name);

        winrt::hstring Name();
        void Name(winrt::hstring const& value);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_name;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct MenuItem : MenuItemT<MenuItem, implementation::MenuItem>
    {
    };
}
