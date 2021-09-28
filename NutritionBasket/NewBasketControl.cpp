#include "pch.h"
#include "NewBasketControl.h"
#include "MainPage.h"
#if __has_include("NewBasketControl.g.cpp")
#include "NewBasketControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    NewBasketControl::NewBasketControl()
    {
        InitializeComponent();
    }

    int32_t NewBasketControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void NewBasketControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

	void NewBasketControl::OpenNewBasketDialog()
	{
		MyDialog().ShowAsync();
	}

	void NewBasketControl::NewColClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		NutritionBasket::BasketViewModel NewView = winrt::make<NutritionBasket::implementation::BasketViewModel>();
		NewView.BasketIndex(main->BodyViewModel().BasketViews().Size());
		//Update NewView.Name()
		NewView.Name(BasketTitle().Text());
		main->BodyViewModel().BasketViews().Append(NewView);
		Storage::SaveLayout();
		BasketTitle().Text(L"");
		main->ClosePopUps();
	}

	void NewBasketControl::NewColCancelClickHandler(IInspectable const&, Controls::ContentDialogButtonClickEventArgs const&)
	{
		BasketTitle().Text(L"");
	}
}
