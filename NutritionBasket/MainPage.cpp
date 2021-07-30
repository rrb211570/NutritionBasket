#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include "icu.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NutritionBasket::implementation
{
	MainPage::MainPage()
	{
		USDA_API tmp = USDA_API();
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

		NutritionBasket::BluePrint PreLoadedBluePrint = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint.Name(L"Apple");
		PreLoadedBluePrint.Amount(L"99g");
		PreLoadedBluePrint.AddElem(L"Fat", L"9g");
		PreLoadedBluePrint.AddElem(L"Sugar", L"2999g");
		PreLoadedBluePrint.AddElem(L"Carb", L"499999g");
		NutritionBasket::BluePrint PreLoadedBluePrint2 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint2.Name(L"Green Apple");
		PreLoadedBluePrint2.Amount(L"30g");
		PreLoadedBluePrint2.AddElem(L"Fat", L"1g");
		PreLoadedBluePrint2.AddElem(L"Sugar", L"200g");
		PreLoadedBluePrint2.AddElem(L"Carb", L"47850g");
		NutritionBasket::BluePrint PreLoadedBluePrint3 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint3.Name(L"Orange");
		PreLoadedBluePrint3.Amount(L"333g");
		PreLoadedBluePrint3.AddElem(L"Fat", L"3g");
		PreLoadedBluePrint3.AddElem(L"Sugar", L"333g");
		PreLoadedBluePrint3.AddElem(L"Carb", L"3333333g");
		NutritionBasket::BluePrint PreLoadedBluePrint4 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint4.Name(L"Orange Juice");
		PreLoadedBluePrint4.Amount(L"333g");
		PreLoadedBluePrint4.AddElem(L"Fat", L"3g");
		PreLoadedBluePrint4.AddElem(L"Sugar", L"333g");
		PreLoadedBluePrint4.AddElem(L"Carb", L"3333333g");
		NutritionBasket::BluePrint PreLoadedBluePrint5 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint5.Name(L"Chickpeas");
		PreLoadedBluePrint5.Amount(L"333g");
		PreLoadedBluePrint5.AddElem(L"Fat", L"3g");
		PreLoadedBluePrint5.AddElem(L"Sugar", L"333g");
		PreLoadedBluePrint5.AddElem(L"Carb", L"3333333g");
		NutritionBasket::BluePrint PreLoadedBluePrint6 = winrt::make<NutritionBasket::implementation::BluePrint>();
		PreLoadedBluePrint6.Name(L"Lemons");
		PreLoadedBluePrint6.Amount(L"333g");
		PreLoadedBluePrint6.AddElem(L"Fat", L"3g");
		PreLoadedBluePrint6.AddElem(L"Sugar", L"333g");
		PreLoadedBluePrint6.AddElem(L"Carb", L"3333333g");
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint);
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint2);
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint3);
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint4);
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint5);
		m_localBluePrints.BluePrints().Append(PreLoadedBluePrint6);
		
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

	NutritionBasket::BluePrintList MainPage::LocalBluePrints()
	{
		return m_localBluePrints;
	}

	void MainPage::LowerCase(char * arr)
	{
		if (arr[0] == '\0') return;
		int i = -1;
		while (arr[++i] != '\0') {
			if (arr[i] <= 'Z' && arr[i] >= 'A') arr[i] = arr[i] - ('Z' - 'z');
		}
	}
}
