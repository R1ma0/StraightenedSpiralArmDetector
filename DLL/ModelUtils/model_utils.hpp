#pragma once

#ifdef _SSAD_MODEL_UTILS_EXPORTS
#define SSAD_MODEL_UTILS_API __declspec(dllexport)
#else
#define SSAD_MODEL_UTILS_API __declspec(dllimport)
#endif