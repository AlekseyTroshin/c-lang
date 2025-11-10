#include "Fild.h"

Fild::Fild(float sizeX, float sizeY, float positionX, float positionY) : m_Size(sizeX, sizeY), m_Position(positionX, positionY)
{
	m_Shape.setSize(m_Size);
	m_Shape.setPosition(m_Position);
}

FloatRect Fild::getPosition()
{
	return m_Shape.getGlobalBounds();
}

RectangleShape Fild::getShape()
{
	return m_Shape;
}

