#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Microsoft.UI.Xaml.Media.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
		NutritionBasket::BasketViewModel MainView = winrt::make<NutritionBasket::implementation::BasketViewModel>();
		MainView.BasketIndex(0);
		MainView.Name(L"Day 1");
		m_bodyViewModel.BasketViews().Append(MainView);
		NutritionBasket::BasketViewModel SecondView = winrt::make<NutritionBasket::implementation::BasketViewModel>();
		SecondView.BasketIndex(1);
		SecondView.Name(L"Day 2");
		m_bodyViewModel.BasketViews().Append(SecondView);

		NutritionBasket::BasketItem MainItem = winrt::make<NutritionBasket::implementation::BasketItem>(L"Main Instantiation", L"30g");
		MainItem.ItemIndex(0);
		MainItem.BasketIndex(0);
		MainItem.AddElem(L"Fat", L"1g");
		MainItem.AddElem(L"Sugar", L"200g");
		MainItem.AddElem(L"Carb", L"47850g");
		MainView.Basket().Append(MainItem);

		NutritionBasket::BasketItem SecondItem = winrt::make<NutritionBasket::implementation::BasketItem>(L"Second Instantiation", L"30g");
		SecondItem.ItemIndex(0);
		SecondItem.BasketIndex(1);
		SecondItem.AddElem(L"Fat", L"1g");
		SecondItem.AddElem(L"Sugar", L"200g");
		SecondItem.AddElem(L"Carb", L"47850g");
		SecondView.Basket().Append(SecondItem);
	}

	void MainPage::MenuClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
	}

	void MainPage::DeleteItemClickHandler(IInspectable const& sender, RoutedEventArgs const&)
	{
		// delete associated item
		NutritionBasket::BasketViewModel curBasket = BodyViewModel().BasketViews().GetAt(BodyList().SelectedIndex());
		Controls::ListBox ItemList = MainPage::FindListBoxAncestor(sender.as<DependencyObject>());
		for (int i = ItemList.SelectedIndex() + 1; i < curBasket.Basket().Size(); ++i) {
			NutritionBasket::BasketItem it = curBasket.Basket().GetAt(i);
			it.ItemIndex(it.ItemIndex() - 1);
		}
		curBasket.Basket().RemoveAt(ItemList.SelectedIndex());
	}

	void MainPage::AvgOptClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
	}

	void MainPage::AvgClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
	}

	void MainPage::BasketGotFocus(IInspectable const& sender, RoutedEventArgs const&)
	{
		// Highlight basket entry
		Controls::StackPanel panel = sender.as<Controls::StackPanel>();
		uint8_t index = panel.DataContext().as<winrt::NutritionBasket::BasketViewModel>().BasketIndex();
		BodyList().SelectedIndex(index);
	}

	void MainPage::ItemGotFocus(IInspectable const& sender, RoutedEventArgs const&)
	{
		Controls::StackPanel panel = sender.as<Controls::StackPanel>();
		// Highlight Item Entry
		uint8_t index = panel.DataContext().as<winrt::NutritionBasket::BasketItem>().ItemIndex();
		Controls::ListBox ItemList = MainPage::FindListBoxAncestor(panel.as<DependencyObject>());
		ItemList.SelectedIndex(index);
	}

	Controls::ListBox MainPage::FindListBoxAncestor(DependencyObject panel) {
		if (panel == NULL) return NULL;
		if (panel.try_as<Controls::ListBox>() != NULL) return panel.as<Controls::ListBox>();
		return FindListBoxAncestor(Media::VisualTreeHelper::GetParent(panel));
	}

	Controls::TextBox MainPage::FindNameInput(DependencyObject panel) {
		if (panel == NULL) return NULL;
		panel = Media::VisualTreeHelper::GetParent(panel);
		if (panel == NULL) return NULL;
		panel = Media::VisualTreeHelper::GetChild(panel, 0);
		if (panel == NULL) return NULL;
		panel = Media::VisualTreeHelper::GetChild(panel, 1);
		if (panel.try_as<Controls::TextBox>() != NULL) return panel.as<Controls::TextBox>();
		return NULL;
	}

	void MainPage::ClosePopUps() {
		auto popups = Media::VisualTreeHelper::GetOpenPopups(Window::Current());
		for (int i = 0; i < popups.Size(); i++)
		{
			auto popup = popups.GetAt(i);
			auto name = get_class_name(popup);
			if (get_class_name(popup) == L"Windows.UI.Xaml.Controls.Primitives.Popup")
			{
				popup.IsOpen(false);
			}
		}
	}

	NutritionBasket::BodyViewModel MainPage::BodyViewModel()
	{
		return m_bodyViewModel;
	}

	NutritionBasket::MenuViewModel MainPage::MenuViewModel()
	{
		return m_menuViewModel;
	}
}
