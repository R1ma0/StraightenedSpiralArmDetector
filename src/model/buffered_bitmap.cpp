#include "buffered_bitmap.hpp"

BufferedBitmap::BufferedBitmap(
    wxWindow *parent, wxWindowID id, const wxBitmap &bitmap, 
    const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
    long style=0
) : wxScrolled<wxWindow>(
    parent, id, pos, size, 
    wxFULL_REPAINT_ON_RESIZE | wxVSCROLL | wxHSCROLL | style
)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &BufferedBitmap::OnPaint, this);
    this->SetBitmap(bitmap);
}

void BufferedBitmap::OnPaint([[maybe_unused]] wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    DoPrepareDC(dc);
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        const wxSize drawSize = ToDIP(GetVirtualSize());
        const wxSize bmpSize = GetScaledBitmapSize();

        const double w = bmpSize.GetWidth();
        const double h = bmpSize.GetHeight();

        const double x = (drawSize.GetWidth() - w) / 2.0;
        const double y = (drawSize.GetHeight() - h) / 2.0;

        gc->DrawBitmap(
            bitmap,
            gc->FromDIP(x), gc->FromDIP(y), 
            gc->FromDIP(w), gc->FromDIP(h)
        );

        delete gc;
    }
}

void BufferedBitmap::SetBitmap(const wxBitmap &bitmap)
{
    this->bitmap = bitmap;
    
    SetScrollRate(FromDIP(10), FromDIP(10));
    SetVirtualSize(FromDIP(GetScaledBitmapSize()));

    this->Refresh();
}

wxSize BufferedBitmap::GetScaledBitmapSize() const
{
    const wxSize bmpSize = bitmap.GetSize();
    const double zoom = GetZoomMultiplier();

    return wxSize(bmpSize.GetWidth() * zoom, bmpSize.GetHeight() * zoom);
}

double BufferedBitmap::GetZoomMultiplier() const
{
    return pow(ZOOM_FACTOR, zoomLevel);
}

wxPoint BufferedBitmap::GetBitmapCenterPosition() const
{
    return CalcUnscrolledPosition(
        wxPoint(
            GetClientSize().GetWidth() / 2,
            GetClientSize().GetHeight() / 2
        )
    );
}

void BufferedBitmap::CenterAndSetSize(const double zoomFactor)
{
    auto centerPos = GetBitmapCenterPosition();
    CenterAfterZoom(centerPos, centerPos * zoomFactor);
    SetVirtualSize(FromDIP(GetScaledBitmapSize()));
    this->Refresh();
}

void BufferedBitmap::ZoomInBitmap()
{
    zoomLevel++;
    CenterAndSetSize(ZOOM_FACTOR);
}

void BufferedBitmap::ZoomOutBitmap()
{
    zoomLevel--;
    CenterAndSetSize(1.0 / ZOOM_FACTOR);
}

void BufferedBitmap::CenterAfterZoom(wxPoint prevCenter, wxPoint currCenter)
{
    wxPoint pixelsPerUnit;

    GetScrollPixelsPerUnit(&pixelsPerUnit.x, &pixelsPerUnit.y);
    const auto delta = currCenter - prevCenter;
    const auto destX = GetViewStart().x + delta.x / pixelsPerUnit.x;
    const auto destY = GetViewStart().y + delta.y / pixelsPerUnit.y;

    Scroll(destX, destY);
}
