#ifndef APP_MAIN_WINDOW_CONTROLLER_H
#define APP_MAIN_WINDOW_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../model/processed_image.hpp"
#include "../model/converters.hpp"

class AppMainWindowController : public IController
{
private:
    wxFrame *view;
    ProcessedImage *procImage;
public:
    AppMainWindowController();
    ~AppMainWindowController();
    wxBitmap GetBitmapImage();
    bool LoadImage(const std::string path);
    bool SaveImage(const std::string path);
    void SetView(wxFrame *);
};

#endif
