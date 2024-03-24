#include "app_main_window.hpp"

AMW::AMW(
    const wxString& title, IController* controller
) : wxFrame(
    nullptr, wxID_ANY, title
)
{
    this->controller = controller;

    CreateControls();
    BindEventHandlers();
    AllowSavingImage(false);
}

AMW::~AMW()
{
    delete bitmap;
    delete saveImg;
}

void AMW::CreateControls()
{
    auto menuFile = new wxMenu();
    auto loadImg = new wxMenuItem(
        menuFile, 
        ID_LOAD_IMG, 
        _("Upload image\tCtrl-O"), 
        _("Upload an image for processing")
    );
    saveImg = new wxMenuItem(
        menuFile, 
        ID_SAVE_IMG, 
        _("Save image\tCtrl-S"),        
        _("Save the processed image")
    );
    menuFile->Append(loadImg);
    menuFile->Append(saveImg);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto menuView = new wxMenu();
    auto zoomInItem = new wxMenuItem(
        menuView, 
        ID_ZOOM_IN, 
        _("Zoom in\tCtrl-+"),
        _("Increase the size of the image in the preview window")
    );
    auto zoomOutItem = new wxMenuItem(
        menuView,
        ID_ZOOM_OUT, 
        _("Zoom out\tCtrl--"),
        _("Reduce the image size in the preview window")
    );
    menuView->Append(zoomInItem);
    menuView->Append(zoomOutItem);

    auto menuProcessing = new wxMenu();
    auto openRotateScaleDialog = new wxMenuItem(
        menuProcessing, 
        ID_ROTATE_SCALE, 
        _("Rotation and stretching\tAlt-R"),
        _("Open the image rotation and stretching window")
    );
    auto skeletonizationMenu = new wxMenu();
    auto adaptiveZhangSuenMethod = new wxMenuItem(
        skeletonizationMenu, 
        ID_OPEN_AZSM, 
        _("Adaptive Zhang-Suen"),
        _("Use Zhang-Suen`s adaptive skeletonisation method")
    );
    auto useMuiltipleProcessing = new wxMenuItem(
        menuProcessing,
        ID_USE_MULT_PROC,
        _("Multi-image processing"),
        _("Processing of several images with specified parameters")
    );
    skeletonizationMenu->Append(adaptiveZhangSuenMethod);
    menuProcessing->Append(openRotateScaleDialog);
    menuProcessing->AppendSubMenu(
        skeletonizationMenu, 
        _("Skeletonisation algorithms")
    );
    menuProcessing->AppendSeparator();
    menuProcessing->Append(useMuiltipleProcessing);

    auto toolsMenu = new wxMenu();
    auto openOtionsWindow = new wxMenuItem(
        toolsMenu,
        ID_OPEN_OPTIONS,
        _("Options..."),
        _("Open the options window to configure the programme")
    );
    toolsMenu->Append(openOtionsWindow);
    
    auto menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _("File"));
    menuBar->Append(menuView, _("View"));
    menuBar->Append(menuProcessing, _("Processing"));
    menuBar->Append(toolsMenu, _("Tools"));
    SetMenuBar(menuBar);
    
    CreateStatusBar();

    bitmap = new BufferedBitmap(
        this, 
        wxID_ANY, 
        wxBitmap(wxSize(1, 1)), 
        wxDefaultPosition, 
        FromDIP(wxSize(1, 1)), 0
    );

    sizerMain = new wxBoxSizer(wxHORIZONTAL);
    sizerMain->Add(bitmap, 1, wxEXPAND | wxALL, FromDIP(1));

    this->SetSizerAndFit(sizerMain);
}

void AMW::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AMW::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AMW::OnSaveImg, this, ID_SAVE_IMG);
    Bind(wxEVT_MENU, &AMW::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &AMW::OnRotateScale, this, ID_ROTATE_SCALE);
    Bind(wxEVT_MENU, &AMW::OnImageZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_MENU, &AMW::OnImageZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_MENU, &AMW::OnUseAZSMethod, this, ID_OPEN_AZSM);
    Bind(wxEVT_MENU, &AMW::OnUseMultipleProcessing, this, ID_USE_MULT_PROC);
    Bind(wxEVT_MENU, &AMW::OnOpenOptionsFrame, this, ID_OPEN_OPTIONS);
}

void AMW::OnOpenOptionsFrame(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->OpenOptionsFrame();
}

void AMW::OnUseMultipleProcessing(wxCommandEvent& WXUNUSED(event))
{
    
}

void AMW::OnUseAZSMethod(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->OpenAZSMethodFrame(bitmap);
}

void AMW::OnRotateScale(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->OpenRotateScaleFrame(bitmap);
}

void AMW::OnImageZoomIn(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->ZoomInBitmap(bitmap);
}

void AMW::OnImageZoomOut(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->ZoomOutBitmap(bitmap);
}

void AMW::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void AMW::OnLoadImg(wxCommandEvent& WXUNUSED(event))
{
    bool isImageNotLoaded = CastAMWC->LoadImage();

    if (isImageNotLoaded)
    {
        wxMessageBox(
            _("Image opening error!"), 
            _("Error"), 
            wxOK | wxICON_ERROR
        );
        return;
    }

    AllowSavingImage(true);
}

void AMW::OnSaveImg(wxCommandEvent& WXUNUSED(event))
{
    bool isImageSaved = CastAMWC->SaveImage();

    if (!isImageSaved)
    {
        wxMessageBox(
            _("Image saving error!"), 
            _("Error"), 
            wxOK | wxICON_ERROR
        );
        return;
    }
}

void AMW::AllowSavingImage(bool state)
{
    saveImg->Enable(state);
}

void AMW::UpdateBitmap(wxBitmap bmp)
{
    bitmap->SetBitmap(bmp);
    this->Layout();
}
