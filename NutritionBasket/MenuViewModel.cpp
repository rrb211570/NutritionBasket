#include "pch.h"
#include "MenuViewModel.h"
#if __has_include("MenuViewModel.g.cpp")
#include "MenuViewModel.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    MenuViewModel::MenuViewModel()
    {
        m_options = winrt::single_threaded_observable_vector<NutritionBasket::MenuItem>();
        m_options.Append(winrt::make<NutritionBasket::implementation::MenuItem>(L"Baskets"));
        m_options.Append(winrt::make<NutritionBasket::implementation::MenuItem>(L"Local Ingredients"));
        m_options.Append(winrt::make<NutritionBasket::implementation::MenuItem>(L"Trends"));
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::MenuItem> MenuViewModel::Options()
    {
        return m_options;
    }
}
