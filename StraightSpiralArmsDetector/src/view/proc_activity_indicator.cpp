#include "proc_activity_indicator.hpp"

wxActivityIndicator* CreateActivityIndicator(
    wxWindow* parent,
    wxSize size,
    wxPoint pos
)
{
    if (pos == wxDefaultPosition)
    {
        pos.x = parent->GetSize().GetWidth() / 2;
        pos.y = parent->GetSize().GetHeight() / 2;

        pos.x -= size.GetWidth() / 2;
        pos.y -= size.GetHeight() - size.GetHeight() / 4;
    }

    return new wxActivityIndicator(parent, -1, pos, size);
}