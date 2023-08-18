#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include "detectorator.h"
#include "aliases.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	dsg::Detectorator detectorator;

	//detectorator.readImg("../../m51.png");
					
	// Processing image
	detectorator.setImgCompressPercentage(20);
	detectorator.setBinaryThreshValue(190);
	detectorator.setGaussConst(-3);
	detectorator.setGaussBlockSize(250);
			
	detectorator.execute();
					
	// Writing image
	//detectorator.writeImg("../../m51_proc.png");					

	return 0;
}
