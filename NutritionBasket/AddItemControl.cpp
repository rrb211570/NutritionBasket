#include "pch.h"
#include "AddItemControl.h"
#include "MainPage.h"
#if __has_include("AddItemControl.g.cpp")
#include "AddItemControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
    AddItemControl::AddItemControl()
    {
        InitializeComponent();
    }

	int32_t AddItemControl::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void AddItemControl::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}

	void AddItemControl::AddItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		int index = main->BodyList().SelectedIndex();
		// attach name input
		Controls::TextBox name_input = main->FindNameInput(sender.as<DependencyObject>());
		NutritionBasket::BasketItem ClickItem = winrt::make<NutritionBasket::implementation::BasketItem>(name_input.Text());
		name_input.Text(L"");
		ClickItem.BasketIndex(index);
		ClickItem.ItemIndex(main->BodyViewModel().BasketViews().GetAt(index).Basket().Size());
		NutritionBasket::BasketItemNutri ItemNutri = ClickItem.Nutrition();
		// attach nutri input

		ItemNutri.Amount(L"125g");
		ItemNutri.AddElem(L"Fat", L"10g");
		ItemNutri.AddElem(L"Sugar", L"20g");
		ItemNutri.AddElem(L"Carb", L"30g");
		main->BodyViewModel().BasketViews().GetAt(index).Basket().Append(ClickItem);
		main->ClosePopUps();
	}

	void AddItemControl::NewItemCancelClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		main->ClosePopUps();
	}
}
