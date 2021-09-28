#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "SearchUSDAControl.g.h"
#include "BluePrintList.h"
#include "BluePrint.h"
#include "Result.h"
#include "USDA_API.h"

namespace winrt::NutritionBasket::implementation
{
    struct SearchUSDAControl : SearchUSDAControlT<SearchUSDAControl>
    {
        SearchUSDAControl();
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::Result> USDAResults();
        void ResetVisibilities();

        void SearchUSDAClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void USDAPrevClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void USDANextClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void HandleSearch(int velocity);
        Windows::Foundation::IAsyncAction SearchCoRoutine(int inputPageNumber);
        void Searching();
        void ReturnedUSDAResults();
        void UpdateNavigationBtns();
        void SelectUSDAItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
    private:
        Windows::Foundation::Collections::IObservableVector<NutritionBasket::Result> m_USDAResults;
        USDA_API m_USDA_API;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct SearchUSDAControl : SearchUSDAControlT<SearchUSDAControl, implementation::SearchUSDAControl>
    {
    };
}
