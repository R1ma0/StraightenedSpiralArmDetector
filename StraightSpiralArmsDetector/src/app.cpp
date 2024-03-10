#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "controller/i_controller.hpp"
#include "controller/app_main_window_controller.hpp"
#include "controller/bitmap_control_panel_controller.hpp"
#include "controller/detectorator_control_panel_controller.hpp"
#include "view/app_main_window.hpp"
#include "view/bitmap_control_panel.hpp"
#include "view/detectorator_control_panel.hpp"

class App : public wxApp
{
public:
	bool OnInit() override;
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    AppMainWindowController *mainController = new AppMainWindowController();
	AppMainWindow *mainWindow = new AppMainWindow(
	    "Straight Spiral Arms Detector", 
        mainController
    );
    mainController->SetView(mainWindow);

    BitmapControlPanelController *bcpController = \
        new BitmapControlPanelController(
        mainWindow->GetBufferedBitmap(),
        mainController->GetProcessedImage()
    );
    BitmapControlPanel *bcp = new BitmapControlPanel(mainWindow, bcpController);
    bcpController->SetView(bcp);

    DetectoratorControlPanelController *dcpController = \
        new DetectoratorControlPanelController(
        mainWindow->GetBufferedBitmap(),
        mainController->GetProcessedImage()
    );
    DetectoratorControlPanel *dcp = new DetectoratorControlPanel(
        mainWindow, 
        dcpController
    );
    dcpController->SetView(dcp);

    mainWindow->SetBitmapControlPanel(bcp);
    mainWindow->SetDetectoratorControlPanel(dcp);

	mainWindow->SetSize(mainWindow->FromDIP(wxSize(1024, 768)));
	mainWindow->Show(true);

	return true;
}
