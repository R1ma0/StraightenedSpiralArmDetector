#include "azsm_frame_controller.hpp"

AZSMFC::AZSMFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;

    gbsOldValue = GBS_SPIN_DEFAULT_VALUE;
}

AZSMFC::~AZSMFC()
{
    delete bitmap;
    delete procImage;
    delete activityIndicator;
    delete computeThread;
}

void AZSMFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMFC::CreateActivityIndicator()
{
    wxSize size = wxSize(100, 100);
    wxPoint pos;

    pos.x = view->GetSize().GetWidth() / 2;
    pos.y = view->GetSize().GetHeight() / 2;

    pos.x -= size.GetWidth() / 2;
    pos.y -= size.GetHeight() - size.GetHeight() / 4;

    activityIndicator = new wxActivityIndicator(view, -1, pos, size);
}

void AZSMFC::RunDetectorator()
{
    float binaryThresh = (float)CastAZSMCF->GetBinaryThresh();
    float gaussConst = (float)CastAZSMCF->GetGaussConst();
    float compressPercentage = (float)CastAZSMCF->GetCompressPercentage();
    int gaussBlockSize = CastAZSMCF->GetGaussBlockSize();

    AdaptiveZhangSuenParameters azsmParams{
        binaryThresh, gaussConst, compressPercentage, gaussBlockSize
    };

    CreateActivityIndicator();
    activityIndicator->Start();
    activityIndicator->Show();

    EnableDialogComponents(false);

    computeThread = new std::thread{ &AZSMFC::Compute, this, azsmParams, activityIndicator };
    computeThread->detach();
}

void AZSMFC::Compute(AdaptiveZhangSuenParameters azsmParams, wxActivityIndicator* actInd)
{   
    AdaptiveZhangSuenMethod* azsm = new AdaptiveZhangSuenMethod();
    cv::Mat img = procImage->GetProcessedImage();
    cv::Mat dst;
    cv::cvtColor(img, dst, cv::COLOR_RGB2GRAY);

    img = azsm->execute(dst, azsmParams);

    // If the dialog has been closed up to this point, the program will close
    // TO DO: fix that!

    procImage->SetProcessedImage(img);
    cv::cvtColor(img, dst, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(&dst)));

    actInd->Stop();
    actInd->Hide();
    EnableDialogComponents(true);

    delete azsm;
}

void AZSMFC::EnableDialogComponents(bool state)
{
    CastAZSMCF->SetEnableComponents(state);
}

int AZSMFC::CheckGBSValue(int value)
{
    int newValue = value;

    if (value % 2 == 0)
    {
        if (value - gbsOldValue > 0) { newValue = value + 1; }
        if (value - gbsOldValue < 0) { newValue = value - 1; }
    }

    gbsOldValue = newValue;

    return newValue;
}
