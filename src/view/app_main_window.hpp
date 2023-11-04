#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/numdlg.h>
#include <wx/slider.h>
#include <wx/event.h>
#include <opencv2/opencv.hpp>
#include "ids_of_controls.hpp"
#include "buffered_bitmap.hpp"
#include "detectorator_control_panel.hpp"
#include "bitmap_control_panel.hpp"
#include "../model/processed_image.hpp"

class AppMainWindow : public wxFrame
{
private:
    BufferedBitmap *bitmap;
    ProcessedImage *procImage;
    wxPanel *mainPanel;
    wxMenuItem *saveImg;
    wxImage MatToWxImage(cv::Mat);
    void UpdateBitmapImage();
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void OnSaveImg(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
    void AllowSavingImage(bool);
public:
    AppMainWindow(const wxString &);
    ~AppMainWindow();
    wxPanel *GetMainPanel();
};

#endif
