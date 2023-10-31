#ifndef BUFFERED_BITMAP_HPP
#define BUFFERED_BITMAP_HPP

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/affinematrix2d.h>

class BufferedBitmap : public wxScrolled<wxWindow>
{
private:
    wxBitmap bitmap;
    wxGraphicsContext *gc;
    wxSize GetScaledBitmapSize() const;
    wxPoint GetScaledBitmapCenter() const;
    wxPoint GetBitmapCenterPosition() const;
    const double ZOOM_FACTOR = 2.0;
    wxDouble angleRotationRadians = 0.0;
    int zoomLevel = 0;
    void CenterAfterZoom(wxPoint, wxPoint);
    void CenterAndSetSize(const double);
public:
    BufferedBitmap(
        wxWindow *, wxWindowID, const wxBitmap &, const wxPoint &, 
        const wxSize &, long
    );
    double GetZoomMultiplier() const;
    wxDouble GetAngleRotationRadians() const;
    bool Save(wxString);
    void SetAngleRotationRadians(wxDouble);
    void SetBitmap(const wxBitmap &);
    void OnPaint(wxPaintEvent &);
    void ZoomInBitmap();
    void ZoomOutBitmap();
};

#endif // BUFFERED_BITMAP_HPP
