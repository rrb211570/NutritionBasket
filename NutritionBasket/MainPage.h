﻿#pragma once

#include "MainPage.g.h"
#include "DeleteBasketControl.h"
#include "AddItemControl.h"
#include "BodyViewModel.h"
#include "MenuViewModel.h"

namespace winrt::NutritionBasket::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        NutritionBasket::BodyViewModel BodyViewModel();
        NutritionBasket::MenuViewModel MenuViewModel();
        NutritionBasket::BluePrintList LocalBluePrints();

        void MenuClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void DeleteItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void AvgOptClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        void AvgClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);

        void BasketGotFocus(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void ItemGotFocus(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::UI::Xaml::Controls::ListBox FindListBoxAncestor(DependencyObject panel);
        winrt::Windows::UI::Xaml::Controls::TextBox FindNameInput(DependencyObject panel);
        void ClosePopUps();

        void LowerCase(char * arr);

    private:
        NutritionBasket::MenuViewModel m_menuViewModel;
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
