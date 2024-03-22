#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "controller/app_main_window_controller.hpp"
#include "view/app_main_window.hpp"
#include "model/app_utils/configurator.hpp"

class App : public wxApp
{
private:
	Configurator* appConfigurator;
	AppMainWindow* amw;
	AppMainWindowController* amwc;
public:
	App();
	~App();
	virtual bool OnInit() override;
};

wxIMPLEMENT_APP(App);

#endif