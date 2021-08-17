#pragma once

#include "Result.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct Result : ResultT<Result>
    {
        Result() = delete;
        Result(winrt::hstring name);

        winrt::hstring Name();
        void Result::Name(winrt::hstring const& value);

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

    private:
        winrt::hstring m_name;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct Result : ResultT<Result, implementation::Result>
    {
    };
}
