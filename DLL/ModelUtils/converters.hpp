#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <opencv2/opencv.hpp>
#include <wx/image.h>
#include "model_utils.hpp"

wxImage SSAD_MODEL_UTILS_API MatToWxImage(cv::Mat*);

#endif
