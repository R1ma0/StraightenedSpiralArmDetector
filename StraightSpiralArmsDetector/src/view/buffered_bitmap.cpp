#include "buffered_bitmap.hpp"

BufferedBitmap::BufferedBitmap(
    wxWindow* parent, wxWindowID id, const wxBitmap& bitmap,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = 0
) : wxScrolled<wxWindow>(
    parent, id, pos, size,
    wxFULL_REPAINT_ON_RESIZE | wxVSCROLL | wxHSCROLL | style
)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &BufferedBitmap::OnPaint, this);
    this->SetBitmap(bitmap);
}

void BufferedBitmap::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    DoPrepareDC(dc);
    gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        gc->SetInterpolationQuality(wxINTERPOLATION_NONE);
        const wxSize bmpSize = GetScaledBitmapSize();
        const wxPoint bmpCenter = GetScaledBitmapCenter();

        gc->DrawBitmap(
            bitmap,
            gc->FromDIP(bmpCenter.x), gc->FromDIP(bmpCenter.y), 
            gc->FromDIP(bmpSize.GetWidth()), gc->FromDIP(bmpSize.GetHeight())
        );

        delete gc;
    }
}

void BufferedBitmap::SetBitmap(const wxBitmap& bitmap)
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

wxPoint BufferedBitmap::GetScaledBitmapCenter() const
{
    const wxSize drawSize = ToDIP(GetVirtualSize());
    const wxSize bmpSize = GetScaledBitmapSize();

    const double x = (drawSize.GetWidth() - bmpSize.GetWidth()) / 2.0;
    const double y = (drawSize.GetHeight() - bmpSize.GetHeight()) / 2.0;

    return wxPoint(x, y);
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
