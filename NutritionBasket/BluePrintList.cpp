#include "pch.h"
#include "BluePrintList.h"
#if __has_include("BluePrintList.g.cpp")
#include "BluePrintList.g.cpp"
#endif

namespace winrt::NutritionBasket::implementation
{
    BluePrintList::BluePrintList()
    {
        m_bluePrints = winrt::single_threaded_observable_vector<NutritionBasket::BluePrint>();
    }

    Windows::Foundation::Collections::IObservableVector<NutritionBasket::BluePrint> BluePrintList::BluePrints()
    {
        return m_bluePrints;
    }
}
