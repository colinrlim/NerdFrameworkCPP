#include "AnimationStamper.h"

AnimationStamper::AnimationStamper(std::vector<ImageStamper*> frames, int framesPerSecond) :
	_frames(frames),
	_timer()
{
	_timer.tickNow();
	setFPS(framesPerSecond);
}
AnimationStamper::AnimationStamper(std::vector<ImageStamper*> frames, double secondsPerFrame) :
	_frames(frames),
	_timer()
{
	_timer.tickNow();
	setFPS(secondsPerFrame);
}

int AnimationStamper::getFPS() {
	return _framesPerSecond;
}
void AnimationStamper::setFPS(int framesPerSecond) {
	_framesPerSecond = framesPerSecond;
	_secondsPerFrame = 1.0 / framesPerSecond;
}
void AnimationStamper::setFPS(double secondsPerFrame) {
	_secondsPerFrame = secondsPerFrame;
	_framesPerSecond = (int)(1.0 / secondsPerFrame + 0.01);
}

void AnimationStamper::play(std::chrono::steady_clock::time_point timepoint, int loops) {
	_timer.tickTo(timepoint);
	_loops = loops;
}
void AnimationStamper::play(int loops) {
	_timer.tickNow();
	_loops = loops;
}

void AnimationStamper::update() {
	int frameNum = (int)(_timer.tock() / _secondsPerFrame);
	int completedLoops = frameNum / _loops;
	if (_loops == -1 || completedLoops < _loops)
		_frameIndex = frameNum % _frames.size();
	else
		_frameIndex = _frames.size() - 1;
}

void AnimationStamper::draw(Image4& screen, const Rect2<double>& bounds) {
	_frames[_frameIndex]->draw(screen, bounds);
}
void AnimationStamper::draw(SDL_Renderer* renderer, const Rect2<double>& bounds) {
	_frames[_frameIndex]->draw(renderer, bounds);
}
void AnimationStamper::draw(Image4& screen, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(screen, bounds, flipOptions, scaleType);
}
void AnimationStamper::draw(SDL_Renderer* renderer, const Rect2<double>& bounds, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(renderer, bounds, flipOptions, scaleType);
}
void AnimationStamper::draw(Image4& screen, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(screen, bounds, degrees, origin, flipOptions, scaleType);
}
void AnimationStamper::draw(SDL_Renderer* renderer, const Rect2<double>& bounds, double degrees, const Vector2i& origin, ImageFlipOptions flipOptions, ImageScaleType scaleType) {
	_frames[_frameIndex]->draw(renderer, bounds, degrees, origin, flipOptions, scaleType);
}