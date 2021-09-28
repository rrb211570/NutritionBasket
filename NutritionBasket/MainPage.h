#pragma once

#include "MainPage.g.h"
#include "DeleteBasketControl.h"
#include "AddItemControl.h"
#include "BodyViewModel.h"
#include "Storage.h"
#include "Util.h"
#include "Parsing.h"

namespace winrt::NutritionBasket::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        NutritionBasket::BodyViewModel BodyViewModel();
        NutritionBasket::BluePrintList LocalBluePrints();

        // Page Navigation
        void NavIngredientsHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);

        // MainPage Functions
        void OpenClearBasketsDialogClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void OpenNewBasketDialogClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void OpenSearchDialogClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void OpenDeleteBasketDialogClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void DeleteItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);

        void BasketGotFocus(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void ItemGotFocus(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::UI::Xaml::Controls::ListBox FindListBoxAncestor(DependencyObject panel);
        winrt::Windows::UI::Xaml::Controls::TextBox FindNameInput(DependencyObject panel);
        void ClosePopUps();
    private:
        NutritionBasket::BodyViewModel m_bodyViewModel;
        NutritionBasket::BluePrintList m_localBluePrints;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
