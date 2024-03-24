#ifndef OPTIONS_FRAME_CONTROLLER_H
#define OPTIONS_FRAME_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../view/options_frame.hpp"
#include "../model/configurator/configurator.hpp"
#include "../model/constants.hpp"

#ifndef CastOF
#define CastOF dynamic_cast<OptionsFrame*>(view)
#endif

class OptionsFrameController : public IController
{
private:
	wxWindow* view;
	Configurator* configurator;
public:
	OptionsFrameController(Configurator*);
	wxArrayString GetLanguagesList();
	int GetWinWidth() const;
	int GetWinHeight() const;
	void SetView(wxWindow*) override;
};

#endif