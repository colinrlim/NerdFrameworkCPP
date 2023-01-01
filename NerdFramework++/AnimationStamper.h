#pragma once

#include "ImageStamper.h"
#include "Stamper.h"
#include "Timer.h"

class AnimationStamper : public Stamper {
private:
	const std::vector<ImageStamper*> _frames;

	int _framesPerSecond;
	double _secondsPerFrame;

	Timer _timer;
	int _loops;

	size_t _frameIndex;
public:
	AnimationStamper(std::vector<ImageStamper*> frames, int framesPerSecond);
	AnimationStamper(std::vector<ImageStamper*> frames, double secondsPerFrame);

	int getFPS();
	void setFPS(int framesPerSecond);
	void setFPS(double secondsPerFrame);

	void play(std::chrono::steady_clock::time_point timepoint, int loops = -1);
	void play(int loops = -1);

	void update();

	void draw(Image4& screen, const Rect2<double>& bounds);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds);
	void draw(Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType);
	void draw(Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType);
	void draw(SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType);
};

