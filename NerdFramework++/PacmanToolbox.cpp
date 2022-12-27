#include "PacmanToolbox.h"

PacmanToolbox::PacmanToolbox()
{
	Color4 black(0, 0, 0, 0);
	Color4 red(252, 0, 0);
	Color4 brown(216, 144, 85);
	Color4 pink(252, 180, 255);
	Color4 cyan(0, 252, 255);
	Color4 blue(72, 180, 255);
	Color4 orange(252, 180, 85);
	Color4 yellow(252, 252, 0);
	Color4 indigo(36, 36, 255);
	Color4 green(0, 252, 0);
	Color4 teal(72, 180, 170);
	Color4 salmon(252, 180, 170);
	Color4 white(252, 252, 255);
	this->palettes = {
		{ { Color4::none, black, black, black } },		// 0
		{ { Color4::none, indigo, black, salmon } },	// 1 frightened1
		{ { Color4::none, white, brown, red } },		// 2 frightened2
		{ { Color4::none, yellow, pink, cyan } },		// 3
		{ { Color4::none, black, black, black } },		// 4
		{ { Color4::none, red, indigo, white } },		// 5 blinky
		{ { Color4::none, cyan, indigo, white } },		// 6 inky
		{ { Color4::none, yellow, red, indigo } },		// 7
		{ { Color4::none, salmon, indigo, green } },	// 8
		{ { Color4::none, brown, green, orange } },		// 9
		{ { Color4::none, black, indigo, white } },		// 10 eyes
		{ { Color4::none, red, salmon, white } },		// 11
		{ { Color4::none, salmon, black, white } },		// 12
		{ { Color4::none, red, white, green } },		// 13
		{ { Color4::none, white, blue, yellow } },		// 14
		{ { Color4::none, indigo, black, salmon } },	// 15
		{ { Color4::none, salmon, indigo, white } },	// 16
		{ { Color4::none, pink, indigo, white } },		// 17 pinky
		{ { Color4::none, orange, indigo, white } },	// 18 clyde
		{ { Color4::none, white, green, red } },		// 19
		{ { Color4::none, white, green, teal } },		// 20
		{ { Color4::none, indigo, black, salmon } },	// 21
		{ { Color4::none, white, black, salmon } },		// 22
	};
}
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
	delete ghostLegsAnim1;
	delete ghostLegsAnim2;
}