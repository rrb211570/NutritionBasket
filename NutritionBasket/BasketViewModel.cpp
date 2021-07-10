#include "pch.h"
#include "BasketViewModel.h"
#if __has_include("BasketViewModel.g.cpp")
#include "BasketViewModel.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BasketViewModel::BasketViewModel()
    {
        m_basket = winrt::single_threaded_observable_vector<NutritionBasket::BasketItem>();
    }

    uint8_t BasketViewModel::BasketIndex() {
        return m_index;
    }

    winrt::hstring BasketViewModel::Name() {
        return m_name;
    }

    void BasketViewModel::Name(winrt::hstring name) {
        m_name = name;
    }

    void BasketViewModel::BasketIndex(uint8_t i) {
        m_index = i;
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketItem> BasketViewModel::Basket()
    {
        return m_basket;
    }
}
