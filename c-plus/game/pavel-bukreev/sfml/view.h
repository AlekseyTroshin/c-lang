#include <SFML/Graphics.hpp>
using namespace sf;

View view(FloatRect({0, 0}, {640, 480}));

View getPlayerCoordinateForView(float x, float y)
{
	float tempX = x, tempY = y;

	if (x < 320) tempX = 320;
	if (y < 240) tempY = 240;
	if (y > 554) tempY = 554;

	view.setCenter({tempX, tempY});
	return view;
}




