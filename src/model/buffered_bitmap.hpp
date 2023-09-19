#ifndef BUFFERED_BITMAP_HPP
#define BUFFERED_BITMAP_HPP

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class BufferedBitmap : public wxScrolled<wxWindow>
{
private:
    wxBitmap bitmap;
    const double ZOOM_FACTOR = 1.1;
    int zoomLevel = 0;
    double GetZoomMultiplier() const;
public:
    BufferedBitmap(
        wxWindow *, wxWindowID, const wxBitmap &, const wxPoint &, 
        const wxSize &, long
    );
    wxSize GetScaledBitmapSize() const;
    void SetBitmap(const wxBitmap &);
    void OnPaint(wxPaintEvent &);
};

#endif // BUFFERED_BITMAP_HPP
