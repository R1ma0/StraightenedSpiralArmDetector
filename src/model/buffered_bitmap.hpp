#ifndef BUFFERED_BITMAP_HPP
#define BUFFERED_BITMAP_HPP

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class BufferedBitmap : public wxScrolled<wxWindow>
{
private:
    wxBitmap bitmap;
    const double ZOOM_FACTOR = 2.0;
    int zoomLevel = 0;
    wxSize GetScaledBitmapSize() const;
    wxPoint GetBitmapCenterPosition() const;
    void CenterAfterZoom(wxPoint, wxPoint);
    void CenterAndSetSize(const double);
public:
    BufferedBitmap(
        wxWindow *, wxWindowID, const wxBitmap &, const wxPoint &, 
        const wxSize &, long
    );
    double GetZoomMultiplier() const;
    void SetBitmap(const wxBitmap &);
    void OnPaint(wxPaintEvent &);
    void ZoomInBitmap();
    void ZoomOutBitmap();
};

#endif // BUFFERED_BITMAP_HPP
