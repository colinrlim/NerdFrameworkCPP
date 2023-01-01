#include "shooter.h"
#include "PaletteImageStamper.h"

void launchShooter() {
	PaletteImage enemy1_idle(3, 3, std::vector<uint8_t>{
		0,0,0,
		0,1,0,
		0,1,0,
	});
	PaletteImage enemy1_left(3, 3, std::vector<uint8_t>{
		0,0,0,
		1,0,0,
		0,1,0,
	});
	PaletteImage enemy1_right(3, 3, std::vector<uint8_t>{
		0,0,0,
		0,0,1,
		0,1,0,
	});

	PaletteImage player(3, 3, std::vector<uint8_t>{
		0,0,0,
		0,1,0,
		0,1,0,
	});
}