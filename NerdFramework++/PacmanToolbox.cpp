#include "PacmanToolbox.h"

PacmanToolbox::PacmanToolbox() :
	tileBatcher(nullptr),
	ghostUpStamper(nullptr),
	ghostDownStamper(nullptr),
	ghostLeftStamper(nullptr),
	ghostRightStamper(nullptr),
	ghostFrightStamper(nullptr),
	ghostLegsStamper1(nullptr),
	ghostLegsStamper2(nullptr),
	ghostLegsStamper3(nullptr),
	ghostLegsStamper4(nullptr)
{ }
PacmanToolbox::~PacmanToolbox() {
	delete tileBatcher;

	delete ghostUpStamper;
	delete ghostDownStamper;
	delete ghostLeftStamper;
	delete ghostRightStamper;
	delete ghostFrightStamper;
	delete ghostLegsStamper1;
	delete ghostLegsStamper2;
	delete ghostLegsStamper3;
	delete ghostLegsStamper4;
}