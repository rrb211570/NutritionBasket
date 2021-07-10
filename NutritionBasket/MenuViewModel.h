#pragma once

#include "MenuViewModel.g.h"
#include "MenuItem.h"

namespace winrt::NutritionBasket::implementation
{
    struct MenuViewModel : MenuViewModelT<MenuViewModel>
    {
        MenuViewModel();

        Windows::Foundation::Collections::IObservableVector<NutritionBasket::MenuItem> Options();

    private:
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::MenuItem> m_options;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct MenuViewModel : MenuViewModelT<MenuViewModel, implementation::MenuViewModel>
    {
    };
}
