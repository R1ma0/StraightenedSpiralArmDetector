#include "processed_parameters.h"
#include "aliases.h"

namespace processed_parameters_namespace
{
	uint ProcessedParameters::getIterRange()
	{
		return (max - min) / step;
	}

	float ProcessedParameters::getMin()
	{
		return min;
	}

	float ProcessedParameters::getMax()
	{
		return max;
	}

	float ProcessedParameters::getStep()
	{
		return step;
	}

	void ProcessedParameters::setMin(float value)
	{
		min = value;
	}

	void ProcessedParameters::setMax(float value)
	{
		max = value;
	}

	void ProcessedParameters::setStep(float value)
	{
		step = value;
	}
}
