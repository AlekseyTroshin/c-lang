#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Fild
{

private:
	Vector2f m_Position;
	Vector2f m_Size;
	RectangleShape m_Shape;
public:
	Fild(float sizeX, float sizeY, float positionX, float positionY);
	FloatRect getPosition();
	FloatRect getSize();
	RectangleShape getShape();

};