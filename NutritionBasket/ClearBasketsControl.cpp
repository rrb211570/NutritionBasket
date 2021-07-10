#include "pch.h"
#include "ClearBasketsControl.h"
#include "MainPage.h"
#if __has_include("ClearBasketsControl.g.cpp")
#include "ClearBasketsControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    ClearBasketsControl::ClearBasketsControl()
    {
        InitializeComponent();
    }

    int32_t ClearBasketsControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ClearBasketsControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ClearBasketsControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        MyDialog().ShowAsync();
    }

    void ClearBasketsControl::ClearClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
    {
        MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
        main->BodyViewModel().BasketViews().Clear();
        main->ClosePopUps();
    }
}
