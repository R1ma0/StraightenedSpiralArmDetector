#include "app_main_window_controller.hpp"

AppMainWindowController::AppMainWindowController()
{
}

void AppMainWindowController::SetView(wxFrame *view)
{
    uncastedView = view;
    dynamic_cast<AppMainWindow *>(uncastedView)->AllowSavingImage(true);
}

void AppMainWindowController::Display()
{
    std::cout << "123" << std::endl;
}
