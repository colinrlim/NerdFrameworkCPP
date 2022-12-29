#pragma once

#include "UIObject.h"

class Button : public UIObject
{
public:
	std::function<void(int x, int y)> onLeftUp;
	std::function<void(int x, int y)> onLeftDown;
	std::function<void(int x, int y)> onLeftClick;

	std::function<void(int x, int y)> onRightUp;
	std::function<void(int x, int y)> onRightDown;
	std::function<void(int x, int y)> onRightClick;

	Button(const UDim2& position, const UDim2& size);
};

