#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "../resource.h"
#include "configurator.hpp"
#include "controller/app_main_window_controller.hpp"
#include "view/app_main_window.hpp"
#include "model/i18n/i18n.hpp"
#include "model/constants.hpp"

class App : public wxApp
{
private:
	wxLocale* locale;
	Configurator* appConfigurator;
	I18N* i18n;
	AppMainWindow* amw;
	AppMainWindowController* amwc;
	wxStandardPaths* standardPaths;
public:
	App();
	~App();
	virtual bool OnInit() override;
	void ShowLangStatusMessage();
};

wxIMPLEMENT_APP(App);

#endif