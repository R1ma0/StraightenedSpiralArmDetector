#pragma once

#ifdef _SSAD_UI_UTILS_EXPORTS
#define SSAD_UI_UTILS_API __declspec(dllexport)
#else
#define SSAD_UI_UTILS_API __declspec(dllimport)
#endif