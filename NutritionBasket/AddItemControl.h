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

        void OpenSearchDialogHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void SearchBarEntryHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);

        void SelectItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void SearchUSDAClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void USDAPrevClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void USDANextClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);

        void AddItemClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const&);
        void CustomClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const&);
        void AddItemCancelClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const&);

        void DefaultDialogClosedClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogClosedEventArgs  const&);
        void CustomDialogClosedClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogClosedEventArgs  const&);
        void AddCustomClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const&);
        void AddCustomCancelClickHandler(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const&);

        void HighlightValidEntry();
        void ResetEntryBG();
        
    private:
        NutritionBasket::BluePrintList m_localSearchList;
        NutritionBasket::BluePrint m_selectedItem;
        boolean m_customClick;
        boolean m_customAdd;
    };
}

namespace winrt::NutritionBasket::factory_implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl, implementation::AddItemControl>
    {
    };
}
