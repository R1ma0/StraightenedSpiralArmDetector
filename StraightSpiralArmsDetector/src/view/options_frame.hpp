#ifndef OPTIONS_FRAME_H
#define OPTIONS_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/propgrid/propgrid.h>
#include "../controller/i_controller.hpp"
#include "../controller/options_frame_controller.hpp"

#ifndef CastOFC
#define CastOFC dynamic_cast<OptionsFrameController*>(controller)
#endif

class OptionsFrame : public wxDialog
{
private:
	IController* controller;
	wxPropertyGrid* propertyGrid;
	void CreateControls();
	void AppendOptions();
public:
	OptionsFrame(IController*);
};

#endif