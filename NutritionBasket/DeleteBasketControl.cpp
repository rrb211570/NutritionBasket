#include "pch.h"
#include "DeleteBasketControl.h"
#include "MainPage.h"
#if __has_include("DeleteBasketControl.g.cpp")
#include "DeleteBasketControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	DeleteBasketControl::DeleteBasketControl()
	{
		InitializeComponent();
	}

	int32_t DeleteBasketControl::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void DeleteBasketControl::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}

	void DeleteBasketControl::DeleteColClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		for (int i = main->BodyList().SelectedIndex() + 1; i < main->BodyViewModel().BasketViews().Size(); ++i) {
			NutritionBasket::BasketViewModel it = main->BodyViewModel().BasketViews().GetAt(i);
			it.BasketIndex(it.BasketIndex() - 1);
		}
		main->BodyViewModel().BasketViews().RemoveAt(main->BodyList().SelectedIndex());
	}

	void DeleteBasketControl::DeleteColCancelClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->ClosePopUps();
	}
}