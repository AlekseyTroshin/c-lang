#include "Player.h"

Player::Player()
	: 	m_Speed(START_SPEED),
		m_Health(START_HEALTH),
		m_MaxHealth(START_HEALTH),
		m_Texture("graphics/player.png"),
		m_Sprite(m_Texture)
{
	// Связываем текстуру со спрайтом
	// !!Обратите внимание на это место!!
	// m_Texture.loadFromFile();
	// Устанавливаем начало спрайта в центр
	// для плавного вращения
	m_Sprite.setOrigin({25, 25});
}

void Player::spawn(
			IntRect arena,
			Vector2f resolution,
			int tileSize
			)
{
	// Размещаем игрового персонажа в центре арены
	m_Position.x = arena.size.x / 2;
	m_Position.y = arena.size.y / 2;
	// Копируем детали арены в m_Arena
	m_Arena.position.x = arena.position.x;
	m_Arena.size.x = arena.size.x;
	m_Arena.position.y = arena.position.y;
	m_Arena.size.y = arena.size.y;
	// Запоминаем размер плиток на этой арене
	m_TileSize = tileSize;
	// Сохраняем разрешение для последующего использования
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return m_LastHit;
}


bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds()
		- m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else
	{
		
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation().asDegrees();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}
	
	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}
	
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	
	if (m_LeftPressed)
	{	
		m_Position.x -= m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	// Удерживаем игрового персонажа на арене
	if (m_Position.x > m_Arena.size.x - m_TileSize)
	{
		m_Position.x = m_Arena.size.x - m_TileSize;
	}
	if (m_Position.x < m_Arena.position.x + m_TileSize)
	{	
		m_Position.x = m_Arena.position.x + m_TileSize;
	}
	if (m_Position.y > m_Arena.size.y - m_TileSize)
	{	
		m_Position.y = m_Arena.size.y - m_TileSize;
	}
	if (m_Position.y < m_Arena.position.y + m_TileSize)
	{	
		m_Position.y = m_Arena.position.y + m_TileSize;
	}

	// Вычисляем, под каким углом повернут персонаж
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	m_Sprite.setRotation(degrees(angle));
}

void Player::upgradeSpeed()
{
	// Увеличение скорости на 20 %
	m_Speed += (START_SPEED * .2);
}
void Player::upgradeHealth()
{
	// Увеличение максимального здоровья на 20 %
	m_MaxHealth += (START_HEALTH * .2);
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// Но не больше максимального
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}




