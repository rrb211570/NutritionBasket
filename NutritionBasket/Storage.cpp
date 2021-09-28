#include "pch.h"
#include "Storage.h"
#include "Mainpage.h"
#include <cmath>
#include <winrt/Windows.UI.Core.h>

using namespace winrt;
using namespace NutritionBasket::implementation;
using namespace Windows::UI::Xaml;
namespace Storage {

	void SetAliveFlag(boolean val) {
		Windows::Storage::ApplicationDataContainer localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
		boolean aliveFlagVal = val;
		localSettings.Values().Insert(L"aliveFlag", box_value(aliveFlagVal));
	}

	void SetChangeFlag(boolean val) {
		Windows::Storage::ApplicationDataContainer localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
		boolean changeFlagVal = val;
		localSettings.Values().Insert(L"changeFlag", box_value(changeFlagVal));
	}

	boolean GetAliveFlag() {
		Windows::Storage::ApplicationDataContainer localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
		return unbox_value<boolean>(localSettings.Values().Lookup(L"aliveFlag"));
	}

	boolean GetChangeFlag() {
		Windows::Storage::ApplicationDataContainer localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
		return unbox_value<boolean>(localSettings.Values().Lookup(L"changeFlag"));
	}

	Windows::Foundation::IAsyncAction ReadStorageAsync(std::string* data) {
		co_await resume_background();
		Windows::Storage::StorageFolder storageFolder =
			Windows::Storage::ApplicationData::Current().LocalFolder();
		Windows::Storage::StorageFile storageFile = co_await storageFolder.CreateFileAsync(L"StoredBlueprints.txt", Windows::Storage::CreationCollisionOption::OpenIfExists);
		hstring myData = co_await Windows::Storage::FileIO::ReadTextAsync(storageFile);
		data->append(to_string(myData.c_str()));
	}

	Windows::Foundation::IAsyncAction SaveNewItemAsync(NutritionBasket::BluePrint* NewItem) {
		co_await resume_background();
		Windows::Storage::StorageFolder storageFolder =
			Windows::Storage::ApplicationData::Current().LocalFolder();
		Windows::Storage::StorageFile storageFile =
			co_await storageFolder.GetFileAsync(L"StoredBlueprints.txt");
		std::string entry = "\"" + to_string(NewItem->Name()) + "\"" + "," + to_string(NewItem->Amount());
		for (uint8_t i = 0; i < NewItem->Elems().Size(); ++i) entry.append(",\"" + to_string(NewItem->Elems().GetAt(i).Nutrient()) + "\"," + to_string(NewItem->Elems().GetAt(i).Amount()));
		entry.append("\n");
		co_await Windows::Storage::FileIO::AppendTextAsync(storageFile, to_hstring(entry));
	}

	void SaveLayout() {
		std::string layout;
		Storage::GetLayout(&layout);
		auto processOp{ Storage::SaveLayoutAsync(&layout) };
		while (processOp.Status() != Windows::Foundation::AsyncStatus::Completed);
	}

	void GetLayout(std::string* layout) {
		MainPage* main = get_self<MainPage>(Window::Current().Content().try_as<Controls::Frame>().Content().try_as<NutritionBasket::MainPage>());
		int baskets = main->BodyViewModel().BasketViews().Size();
		for (int i = 0; i < baskets; ++i) {
			layout->append(to_string(main->BodyViewModel().BasketViews().GetAt(i).Name()));
			int items = main->BodyViewModel().BasketViews().GetAt(i).Basket().Size();
			for (int j = 0; j < items; ++j) {
				layout->append("\n" + to_string(main->BodyViewModel().BasketViews().GetAt(i).Basket().GetAt(j).BluePrint().Name()) + "\n" + to_string(main->BodyViewModel().BasketViews().GetAt(i).Basket().GetAt(j).BluePrint().Amount()));
			}
			layout->append("\n\n");
		}
		layout->append("\n");
	}

	// Unused right now
	Windows::Foundation::IAsyncAction AutoSaveLayoutAsync() {
		apartment_context ui_thread;
		while (GetAliveFlag()) {
			co_await resume_after(std::chrono::seconds(3)); // runs every 3 seconds
			if (GetChangeFlag()) {
				co_await ui_thread;
				std::string layout;
				GetLayout(&layout);
				Windows::Storage::StorageFolder storageFolder =
					Windows::Storage::ApplicationData::Current().LocalFolder();
				Windows::Storage::StorageFile storageFile =
					co_await storageFolder.CreateFileAsync(L"StoredLayout.txt", Windows::Storage::CreationCollisionOption::OpenIfExists);
				co_await Windows::Storage::FileIO::WriteTextAsync(storageFile, to_hstring(layout));
				SetChangeFlag(false);
				co_await winrt::resume_background();
			}
		}
	}

	Windows::Foundation::IAsyncAction SaveLayoutAsync(std::string* layout) {
		co_await resume_background();
		Windows::Storage::StorageFolder storageFolder =
			Windows::Storage::ApplicationData::Current().LocalFolder();
		Windows::Storage::StorageFile storageFile =
			co_await storageFolder.CreateFileAsync(L"StoredLayout.txt", Windows::Storage::CreationCollisionOption::OpenIfExists);
		co_await Windows::Storage::FileIO::WriteTextAsync(storageFile, to_hstring(*layout));
	}

	Windows::Foundation::IAsyncAction GetLayoutMappingAsync(std::string* layout) {
		co_await resume_background();
		Windows::Storage::StorageFolder storageFolder =
			Windows::Storage::ApplicationData::Current().LocalFolder();
		Windows::Storage::StorageFile storageFile = co_await storageFolder.CreateFileAsync(L"StoredLayout.txt", Windows::Storage::CreationCollisionOption::OpenIfExists);
		hstring myData = co_await Windows::Storage::FileIO::ReadTextAsync(storageFile);
		layout->append(to_string(myData));
	}

	Windows::Foundation::IAsyncAction Test_CollectResponseAsync(std::string* resp) {
		co_await resume_background();
		Windows::Storage::StorageFolder storageFolder =
			Windows::Storage::ApplicationData::Current().LocalFolder();
		Windows::Storage::StorageFile storageFile =
			co_await storageFolder.CreateFileAsync(L"Test_CollectResponse.txt", Windows::Storage::CreationCollisionOption::OpenIfExists);
		co_await Windows::Storage::FileIO::WriteTextAsync(storageFile, to_hstring(*resp));
	}
}