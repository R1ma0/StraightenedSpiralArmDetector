#ifndef AZS_MP_TASK_H
#define AZS_MP_TASK_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include <vector>
#include <filesystem>
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen_types.hpp"
#include "../model/src_files_handler.hpp"

struct AZSTask
{
	cv::Mat img;
	AdaptiveZhangSuenParameters params;
	std::string pathToSave;
};

typedef std::vector<AZSTask> AZSTasks;

AZSTasks* CreateSetOfTasks(SrcFilesData*, wxString, AZSParametersRanges);
std::string GetPathToSave(
    std::string, 
    std::string, 
    std::string,
    std::string
);
std::string ParamsSeqToStr(AdaptiveZhangSuenParameters*);

#endif