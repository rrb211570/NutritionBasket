#pragma once
#include "App.xaml.g.h"
#include "pch.h"

namespace winrt::NutritionBasket::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
        void OnLeavingBackground(IInspectable const&, Windows::ApplicationModel::LeavingBackgroundEventArgs const&);
        void OnEnteredBackground(IInspectable const&, Windows::ApplicationModel::EnteredBackgroundEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);
    };
}
