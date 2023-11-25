#include "app_main_window_controller.hpp"

AppMainWindowController::AppMainWindowController()
{
    std::cout << "Created controller" << std::endl;;
}

void AppMainWindowController::SetView(wxFrame *view)
{
    uncastedView = view;
    std::cout << "View is set" << std::endl;
    castedView = dynamic_cast<AppMainWindow *>(view);
    castedView->AllowSavingImage(true);
}
