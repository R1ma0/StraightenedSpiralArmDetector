#ifndef PROCESSED_PARAMETERS_H
#define PROCESSED_PARAMETERS_H

#include "aliases.h"

namespace processed_parameters_namespace
{
	class ProcessedParameters
	{
	private:
		float min;
		float max;
		float step;
	public:
		uint getIterRange();
		float getMin();
		float getMax();
		float getStep();
		void setMin(float);
		void setMax(float);
		void setStep(float);
	};
}

#endif
