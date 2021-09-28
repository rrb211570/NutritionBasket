#include "pch.h"
#include "LocalIngredients.h"
#if __has_include("LocalIngredients.g.cpp")
#include "LocalIngredients.g.cpp"
#endif
#include "Parsing.h"
#include "Storage.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    LocalIngredients::LocalIngredients()
    {
        InitializeComponent();

        std::string storedBluePrints;
        auto processOp{ Storage::ReadStorageAsync(&storedBluePrints) };
        while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
        Parsing::LoadBluePrintData(&storedBluePrints, &m_localBluePrints);
    }

    NutritionBasket::BluePrintList LocalIngredients::BluePrintList() {
        return m_localBluePrints;
    }

    void LocalIngredients::NavBasketsHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&) {
        this->Frame().Navigate(xaml_typename<NutritionBasket::MainPage>());
    }
}
