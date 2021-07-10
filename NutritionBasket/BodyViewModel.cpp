#include "pch.h"
#include "BodyViewModel.h"
#if __has_include("BodyViewModel.g.cpp")
#include "BodyViewModel.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BodyViewModel::BodyViewModel()
    {
        m_basketViews = winrt::single_threaded_observable_vector<NutritionBasket::BasketViewModel>();
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::BasketViewModel> BodyViewModel::BasketViews()
    {
        return m_basketViews;
    }
}
