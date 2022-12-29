#pragma once

#include "PaletteImageStamper.h"
#include "Timer.h"

class PaletteAnimationStamper : public PaletteStamper {
private:
	const std::vector<PaletteImageStamper*> _frames;

	int _framesPerSecond;
	double _secondsPerFrame;

	Timer _timer;
	int _loops;

	size_t _frameIndex;
public:
	PaletteAnimationStamper(std::vector<PaletteImageStamper*> frames, int framesPerSecond, Palette<Color4>* defaultPalette = nullptr);
	PaletteAnimationStamper(std::vector<PaletteImageStamper*> frames, double secondsPerFrame, Palette<Color4>* defaultPalette = nullptr);

	int getFPS();
	void setFPS(int framesPerSecond);
	void setFPS(double secondsPerFrame);

	void play(std::chrono::steady_clock::time_point timepoint, int loops = -1);
	void play(int loops = -1);

	void update();

	void draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds);
	void draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds);
	void draw(Image4& screen, const Rect2<double>& bounds);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
};

