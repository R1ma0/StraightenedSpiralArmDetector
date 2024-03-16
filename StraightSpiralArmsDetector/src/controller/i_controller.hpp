#ifndef I_CONTROLLER_H
#define I_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class IController
{
public:
    virtual void SetView(wxWindow*) = 0;
};

#endif
