#pragma once
#include "BluePrint.h"
#include "BluePrintList.g.h"

namespace winrt::NutritionBasket::implementation
{
    struct BluePrintList : BluePrintListT<BluePrintList>
    {
        BluePrintList();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BluePrint> BluePrints();

    private:
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::BluePrint> m_bluePrints;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct BluePrintList : BluePrintListT<BluePrintList, implementation::BluePrintList>
    {
    };
}
