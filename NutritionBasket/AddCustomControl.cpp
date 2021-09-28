#include "pch.h"
#include "AddCustomControl.h"
#if __has_include("AddCustomControl.g.cpp")
#include "AddCustomControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    AddCustomControl::AddCustomControl()
    {
        InitializeComponent();
    }

    int32_t AddCustomControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AddCustomControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AddCustomControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
