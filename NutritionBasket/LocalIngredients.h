#pragma once

#include "LocalIngredients.g.h"
#include "BluePrintList.h"

namespace winrt::NutritionBasket::implementation
{
    struct LocalIngredients : LocalIngredientsT<LocalIngredients>
    {
        LocalIngredients();
        NutritionBasket::BluePrintList BluePrintList();

        void NavBasketsHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
    private:
        NutritionBasket::BluePrintList m_localBluePrints;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct LocalIngredients : LocalIngredientsT<LocalIngredients, implementation::LocalIngredients>
    {
    };
}
