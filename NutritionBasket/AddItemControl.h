#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "AddItemControl.g.h"
#include "SearchUSDAControl.h"
#include "BluePrintList.h"
#include "BluePrint.h"
#include "Result.h"
#include "USDA_API.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
namespace winrt::NutritionBasket::implementation
{
    struct AddItemControl : AddItemControlT<AddItemControl>
    {
        AddItemControl();
        NutritionBasket::BluePrintList LocalSearchList();
        NutritionBasket::BluePrint SelectedItem();
        hstring SearchBarText();
        void SearchBarText(hstring s);
        void SetSelectedItem(NutritionBasket::BluePrint item);
        void HideSearchResults();
        void OpenSearchDialog();

        void SearchBarEntryHandler(Windows::Foundation::IInspectable const& sender, Controls::TextChangedEventArgs const& e);
        void AmountEntryHandler(Windows::Foundation::IInspectable const& sender, Controls::TextChangedEventArgs const& e);
        void SelectItemClickHandler(Windows::Foundation::IInspectable const& sender, RoutedEventArgs const&);
        void AddItemClickHandler(Windows::Foundation::IInspectable const& sender, RoutedEventArgs const&);
        void DefaultDialogClosedClickHandler(Windows::Foundation::IInspectable const& sender, Controls::ContentDialogClosedEventArgs  const&);

        void UpdateSearchBarUX(boolean state);
        void UpdateLocalBlueprints(NutritionBasket::BluePrint item);
        void RatioElems(NutritionBasket::BasketItem* Item, hstring amount);
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
