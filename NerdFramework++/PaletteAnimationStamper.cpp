#include "PaletteAnimationStamper.h"

PaletteAnimationStamper::PaletteAnimationStamper(std::vector<PaletteImageStamper*> frames, int framesPerSecond, Palette<Color4>* defaultPalette) :
	_frames(frames),
	_timer(),
	PaletteStamper(defaultPalette)
{
	_timer.tickNow();
	setFPS(framesPerSecond);
}
PaletteAnimationStamper::PaletteAnimationStamper(std::vector<PaletteImageStamper*> frames, double secondsPerFrame, Palette<Color4>* defaultPalette) :
	_frames(frames),
	_timer(),
	PaletteStamper(defaultPalette)
{
	_timer.tickNow();
	setFPS(secondsPerFrame);
}

int PaletteAnimationStamper::getFPS() {
	return _framesPerSecond;
}
void PaletteAnimationStamper::setFPS(int framesPerSecond) {
	_framesPerSecond = framesPerSecond;
	_secondsPerFrame = 1.0 / framesPerSecond;
}
void PaletteAnimationStamper::setFPS(double secondsPerFrame) {
	_secondsPerFrame = secondsPerFrame;
	_framesPerSecond = (int)(1.0 / secondsPerFrame + 0.01);
}

void PaletteAnimationStamper::play(std::chrono::steady_clock::time_point timepoint, int loops) {
	_timer.tickTo(timepoint);
	_loops = loops;
}
void PaletteAnimationStamper::play(int loops) {
	_timer.tickNow();
	_loops = loops;
}

void PaletteAnimationStamper::update() {
	int frameNum = (int)(_timer.tock() / _secondsPerFrame);
	int completedLoops = frameNum / _loops;
	if (_loops == -1 || completedLoops < _loops)
		_frameIndex = frameNum % _frames.size();
	else
		_frameIndex = _frames.size() - 1;
}

void PaletteAnimationStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds) {
	_frames[_frameIndex]->draw(palette, screen, bounds);
}
void PaletteAnimationStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds) {
	_frames[_frameIndex]->draw(palette, renderer, bounds);
}
void PaletteAnimationStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(palette, screen, bounds, flipOptions, scaleType);
}
void PaletteAnimationStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(palette, renderer, bounds, flipOptions, scaleType);
}
void PaletteAnimationStamper::draw(const Palette<Color4>& palette, Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(palette, screen, bounds, degrees, origin, flipOptions, scaleType);
}
void PaletteAnimationStamper::draw(const Palette<Color4>& palette, SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(palette, renderer, bounds, degrees, origin, flipOptions, scaleType);
}