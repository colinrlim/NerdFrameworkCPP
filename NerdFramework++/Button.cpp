#include "Button.h"

Button::Button(const UDim2& position, const UDim2& size) :
	UIObject(position, size),
	onLeftUp([](int x, int y)->void {}),
	onLeftDown([](int x, int y)->void {}),
	onLeftClick([](int x, int y)->void {}),
	onRightUp([](int x, int y)->void {}),
	onRightDown([](int x, int y)->void {}),
	onRightClick([](int x, int y)->void {})
{ }