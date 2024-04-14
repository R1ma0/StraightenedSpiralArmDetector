#ifndef PROC_ACTIVITY_INDICATOR
#define PROC_ACTIVITY_INDICATOR

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/activityindicator.h>

wxActivityIndicator* CreateActivityIndicator(
	wxWindow*,
	wxSize,
	wxPoint = wxDefaultPosition
);

#endif