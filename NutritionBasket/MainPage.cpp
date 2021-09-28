#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "App.h"
#include "Parsing.h"
#include "LocalIngredients.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace winrt::NutritionBasket::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();

		// Load blueprints and rebuild layout
		std::string storedBluePrints;
		auto processOp{ Storage::ReadStorageAsync(&storedBluePrints) };
		while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
		Parsing::LoadBluePrintData(&storedBluePrints, &m_localBluePrints);

		//Rebuild layout
		std::string storedLayout;
		auto processOp2{ Storage::GetLayoutMappingAsync(&storedLayout) };
		while (processOp2.Status() != Windows::Foundation::AsyncStatus::Completed);
		Parsing::RebuildLayout(&storedLayout, &m_localBluePrints, &m_bodyViewModel);
		if (m_bodyViewModel.BasketViews().Size() > 0) BodyList().SelectedIndex(0);
	}

	NutritionBasket::BodyViewModel MainPage::BodyViewModel() { return m_bodyViewModel; }
	NutritionBasket::BluePrintList MainPage::LocalBluePrints() { return m_localBluePrints; }

	void MainPage::NavIngredientsHandler(IInspectable const& sender, RoutedEventArgs const&) {
		this->Frame().Navigate(xaml_typename<NutritionBasket::LocalIngredients>());
	}

	void MainPage::OpenClearBasketsDialogClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MyClearBasketsControl().OpenClearBasketsDialog();
	}

	void MainPage::OpenNewBasketDialogClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MyNewBasketControl().OpenNewBasketDialog();
	}

	void MainPage::OpenSearchDialogClickHandler(IInspectable const&, RoutedEventArgs const&) {
		MyAddItemControl().OpenSearchDialog();
	}

	void MainPage::OpenDeleteBasketDialogClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MyDeleteBasketControl().OpenDeleteBasketDialog();
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
		Storage::SaveLayout();
	}

	void MainPage::BasketGotFocus(IInspectable const& sender, RoutedEventArgs const&)
	{
		// Highlight basket entry
		Controls::StackPanel panel = sender.as<Controls::StackPanel>();
		uint8_t index = panel.DataContext().as<NutritionBasket::BasketViewModel>().BasketIndex();
		BodyList().SelectedIndex(index);
	}

	void MainPage::ItemGotFocus(IInspectable const& sender, RoutedEventArgs const&)
	{
		Controls::StackPanel panel = sender.as<Controls::StackPanel>();
		// Highlight Item Entry
		uint8_t index = panel.DataContext().as<NutritionBasket::BasketItem>().ItemIndex();
		Controls::ListBox ItemList = FindListBoxAncestor(panel.as<DependencyObject>());
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
}

