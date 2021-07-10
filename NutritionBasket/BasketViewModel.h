#pragma once

#include "BasketViewModel.g.h"
#include "BasketItem.h"

namespace winrt::NutritionBasket::implementation
{
    struct BasketViewModel : BasketViewModelT<BasketViewModel>
    {
        BasketViewModel();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItem> Basket();
        uint8_t BasketIndex();
        winrt::hstring Name();
        void BasketViewModel::Name(winrt::hstring name);
        void BasketIndex(uint8_t i);

    private:
        uint8_t m_index;
        winrt::hstring m_name;
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItem> m_basket;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BasketViewModel : BasketViewModelT<BasketViewModel, implementation::BasketViewModel>
    {
    };
}
