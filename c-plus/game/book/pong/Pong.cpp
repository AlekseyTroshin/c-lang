#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


#include "Bat.h"
#include "Ball.h"

using namespace std;

int main()
{

	// Создаем объект VideoMode
	VideoMode vm({1920, 1080});

	// Создаем и открываем окно для игры в полноэкранном режиме
	RenderWindow window(vm, "Pong");
	int score = 0;
	int lives = 3;

	// Создаем ракетку в нижней центральной части экрана
	Bat bat(1920 / 2, 1080 - 20);

	// Создаем мяч
	Ball ball(1920 / 2, 0);

	// Крутой ретрошрифт
	Font font("./fonts/DS-DIGIT.ttf");

	// Мы добавим мяч в следующей главе
	// Создаем текстовый объект HUD
	Text hud(font);

	// Делаем его большим и красивым
	hud.setCharacterSize(75);

	// Выбираем цвет
	hud.setFillColor(Color::White);
	hud.setPosition({20, 20});

	// Таймер для управления временем
	Clock clock;
	float targetFPS = 30.0f;
	float frameTime = 1.0f / targetFPS;

	while (window.isOpen())
	{
		Time dt = clock.restart();
		float deltaTime = dt.asSeconds();

		if (deltaTime < frameTime)
		{
			sleep (seconds(frameTime - deltaTime));
			deltaTime = frameTime;
		}


		if (auto event = window.pollEvent())
		{
			if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->scancode == Keyboard::Scan::Escape)
				{
					window.close();	
				}

				if (keyPressed->scancode == Keyboard::Scan::Left)
				{
					bat.moveLeft();
				}
				else
				{
					bat.stopLeft();
				}

				if (keyPressed->scancode == Keyboard::Scan::Right)
				{
					bat.moveRight();
				}
				else
				{
					bat.stopRight();
				}
			}
		}
		/*
		Обработка ввода игрока
		**************************************
		**************************************
		**************************************
		*/
		
		/*
		Отрисовка ракетки, мяча и HUD
		*/
		bat.update(deltaTime);
		ball.update(deltaTime);

		stringstream stst;
		stst << "Score:" << score << " Lives:" << lives;
		hud.setString(stst.str());

		// Обработка столкновения мяча с нижней границей экрана
		if (ball.getPosition().position.y > window.getSize().y)
		{
			// Смена направления движения мяча
			ball.reboundBottom();
			// Уменьшение количества жизней
			lives--;
			// Проверка оставшегося количества жизней
			if (lives < 1) {
				// Сброс счета
				score = 0;
				// Сброс жизней
				lives = 3;
			}
		}

		// Обработка столкновения мяча с верхней границей экрана
		if (ball.getPosition().position.y < 0)
		{
			ball.reboundBatOrTop();
			// Добавление одного очка к счету игрока
			score++;
		}

		// Обработка столкновения мяча с боковыми границами экрана
		if (ball.getPosition().position.x < 0 ||
			ball.getPosition().position.x + ball.getPosition().size.x > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Мяч столкнулся с ракеткой?
		if (ball.getPosition().findIntersection(bat.getPosition()))
		{
			// Обнаружение столкновения, изменение направления движения мяча
			// и добавление одного очка к счету
			ball.reboundBatOrTop();
		}

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}