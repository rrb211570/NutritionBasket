#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "AddItemControl.g.h"
#include "BluePrintList.h"
#include "BluePrint.h"

namespace winrt::NutritionBasket::implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl>
    {
        AddItemControl();
        NutritionBasket::BluePrintList LocalSearchList();
        NutritionBasket::BluePrint SelectedItem();

        void SearchBarEntryHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void ClearSearchBarHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

        void SelectItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void LocalExpandClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void SearchUSDAClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void USDAExpandClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);

        void AddItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void AddItemCancelClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
        
    private:
        NutritionBasket::BluePrintList m_localSearchList;
        NutritionBasket::BluePrint m_selectedItem;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl, implementation::AddItemControl>
    {
    };
}
