#pragma once

#include "BodyViewModel.g.h"
#include "BasketViewModel.h"

namespace winrt::NutritionBasket::implementation
{
    struct BodyViewModel : BodyViewModelT<BodyViewModel>
    {
        BodyViewModel();

        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketViewModel> BasketViews();

    private:
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketViewModel> m_basketViews;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BodyViewModel : BodyViewModelT<BodyViewModel, implementation::BodyViewModel>
    {
    };
}
