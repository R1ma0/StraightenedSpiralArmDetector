#include "app_main_window.hpp"

AWM::AWM
(
    const wxString& title, IController* controller
) : wxFrame
(
    nullptr, wxID_ANY, title
)
{
    mainController = controller;

    CreateControls();
    BindEventHandlers();
    AllowSavingImage(false);
}

AWM::~AWM()
{
    delete bitmap;
    delete saveImg;
}

void AWM::CreateControls()
{
    auto menuFile = new wxMenu();
    auto loadImg = new wxMenuItem(
        menuFile, 
        ID_LOAD_IMG, 
        wxT("Load Image\tCtrl-O"), 
        wxT("Opening and loading an image for processing")
    );
    saveImg = new wxMenuItem(
        menuFile, 
        ID_SAVE_IMG, 
        wxT("Save Image\tCtrl-S"),        
        wxT("Saving processed image")
    );
    menuFile->Append(loadImg);
    menuFile->Append(saveImg);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto menuView = new wxMenu();
    auto zoomInItem = new wxMenuItem(
        menuView, 
        ID_ZOOM_IN, 
        wxT("Zoom In\tCtrl-+"),
        wxT("Increase the size of the image in the preview window")
    );
    auto zoomOutItem = new wxMenuItem(
        menuView,
        ID_ZOOM_OUT, 
        wxT("Zoom Out\tCtrl--"),
        wxT("Reduce the size of the image in the preview window")
    );
    menuView->Append(zoomInItem);
    menuView->Append(zoomOutItem);

    auto menuProcessing = new wxMenu();
    auto openRotateScaleDialog = new wxMenuItem(
        menuProcessing, 
        ID_ROTATE_SCALE, 
        wxT("Rotate and Scale\tAlt-R"),
        wxT("Opens a window for rotating and scaling the image")
    );
    auto skeletonizationMenu = new wxMenu();
    auto adaptiveZhangSuenMethod = new wxMenuItem(
        skeletonizationMenu, 
        ID_OPEN_AZSM, 
        wxT("Adaptive Zhang Suen"),
        wxT("Configure and use Adaptive Zhang Suen skeletonization method")
    );
    auto useMuiltipleProcessing = new wxMenuItem(
        menuProcessing,
        ID_USE_MULT_PROC,
        wxT("Multiple processing"),
        wxT("Processing multiple images with specified parameters")
    );
    skeletonizationMenu->Append(adaptiveZhangSuenMethod);
    menuProcessing->Append(openRotateScaleDialog);
    menuProcessing->AppendSubMenu(
        skeletonizationMenu, 
        wxT("Skeletonization Methods")
    );
    menuProcessing->AppendSeparator();
    menuProcessing->Append(useMuiltipleProcessing);

    auto menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("File"));
    menuBar->Append(menuView, wxT("View"));
    menuBar->Append(menuProcessing, wxT("Processing"));
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

void AWM::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AWM::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AWM::OnSaveImg, this, ID_SAVE_IMG);
    Bind(wxEVT_MENU, &AWM::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &AWM::OnRotateScale, this, ID_ROTATE_SCALE);
    Bind(wxEVT_MENU, &AWM::OnImageZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_MENU, &AWM::OnImageZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_MENU, &AWM::OnUseAZSMethod, this, ID_OPEN_AZSM);
    Bind(wxEVT_MENU, &AWM::OnUseMultipleProcessing, this, ID_USE_MULT_PROC);
}

void AWM::OnUseMultipleProcessing(wxCommandEvent& WXUNUSED(event))
{
    
}

void AWM::OnUseAZSMethod(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->OpenAZSMethodFrame(bitmap);
}

void AWM::OnRotateScale(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->OpenRotateScaleFrame(bitmap);
}

void AWM::OnImageZoomIn(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->ZoomInBitmap(bitmap);
}

void AWM::OnImageZoomOut(wxCommandEvent& WXUNUSED(event))
{
    CastAMWC->ZoomOutBitmap(bitmap);
}

void AWM::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void AWM::OnLoadImg(wxCommandEvent& WXUNUSED(event))
{
    bool isImageNotLoaded = CastAMWC->LoadImage();

    if (isImageNotLoaded)
    {
        wxMessageBox("Failed to open image", "Error", wxOK | wxICON_ERROR);
        return;
    }

    AllowSavingImage(true);
}

void AWM::OnSaveImg(wxCommandEvent& WXUNUSED(event))
{
    bool isImageSaved = CastAMWC->SaveImage();

    if (!isImageSaved)
    {
        wxMessageBox("Failed to save image", "Error", wxOK | wxICON_ERROR);
        return;
    }
}

void AWM::AllowSavingImage(bool state)
{
    saveImg->Enable(state);
}

void AWM::UpdateBitmap(wxBitmap bmp)
{
    bitmap->SetBitmap(bmp);
    this->Layout();
}
