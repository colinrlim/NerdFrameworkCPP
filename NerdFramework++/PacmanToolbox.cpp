#include "PacmanToolbox.h"

PacmanToolbox::PacmanToolbox() :
	tileBatch(nullptr),
	ghostUpMaster(nullptr),
	ghostDownMaster(nullptr),
	ghostLeftMaster(nullptr),
	ghostRightMaster(nullptr),
	ghostFrightMaster(nullptr),
	ghostLegsMaster1(nullptr),
	ghostLegsMaster2(nullptr),
	ghostLegsMaster3(nullptr),
	ghostLegsMaster4(nullptr)
{ }
PacmanToolbox::~PacmanToolbox() {
	delete tileBatch;

	delete ghostUpMaster;
	delete ghostDownMaster;
	delete ghostLeftMaster;
	delete ghostRightMaster;
	delete ghostFrightMaster;
	delete ghostLegsMaster1;
	delete ghostLegsMaster2;
	delete ghostLegsMaster3;
	delete ghostLegsMaster4;
}