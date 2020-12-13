#include "stdafx.h"
#include "rgb_hsv.h"

#define SHIFT_INTERVAL 200

float color[4] = { 1.0f, 1.0f, 0, 1.0f };
static int lastColorShift;

void shiftColorHue()
{
	color[3] = 1.0f; 

	if ((Com_Milliseconds() - lastColorShift) > SHIFT_INTERVAL)
	{
		lastColorShift = Com_Milliseconds();

		rgb _color;
		_color.r = color[0];
		_color.g = color[1];
		_color.b = color[2];

		hsv _hsv = rgb2hsv(_color);

		_hsv.h++;
		_hsv.s = 1.0f;

		_color = hsv2rgb(_hsv);

		color[0] = _color.r;
		color[1] = _color.g;
		color[2] = _color.b;
	}
}