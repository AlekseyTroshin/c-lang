#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{

	// Создаем объект VideoMode
	VideoMode vm({1920, 1080});

	// Игра всегда находится в одном из четырех состояний
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	// Начинаем с состояния GAME_OVER
	// Получаем разрешение экрана и создаем окно SFML
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().size.x;
	resolution.y = VideoMode::getDesktopMode().size.y;
	RenderWindow window(
			VideoMode::getDesktopMode(),
			"Zombie Arena"
		);

	// Создаем объект View библиотеки SFML для основного действия
	View mainView(
		sf::FloatRect(Vector2f({0, 0}), Vector2f({resolution.x, resolution.y}))
	);

	// Здесь находится наш таймер для отслеживания времени
	Clock clock;
	// Таймер для управления временем
	float targetFPS = 30.0f;
	float frameTime = 1.0f / targetFPS;

	// Сколько времени прошло в состоянии PLAYING
	Time gameTimeTotal;

	// Где находится указатель мыши относительно глобальных координат
	Vector2f mouseWorldPosition;

	// Где находится указатель мыши относительно координат на экране
	Vector2i mouseScreenPosition;

	// Создаем экземпляр класса Player
	Player player;

	// Границы арены
	IntRect arena;

	

	// Основной игровой цикл
	// while (window.isOpen())
	// {
	// 	Time dt = clock.restart();
	// 	float deltaTime = dt.asSeconds();

	// 	if (deltaTime < frameTime)
	// 	{
	// 		sleep (seconds(frameTime - deltaTime));
	// 		deltaTime = frameTime;
	// 	}

	// 	if (auto event = window.pollEvent())
	// 	{
	// 		if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
	// 		{
	// 			if (keyPressed->scancode == Keyboard::Scan::Escape)
	// 			{
	// 				window.close();	
	// 			}

	// 			// Пауза в игре во время PLAYING
	// 			if (event.key.code == Keyboard::Return && state == State::PLAYING)
	// 			{
	// 				state = State::PAUSED;
	// 			}
	// 			// Возобновление игры во время PAUSED
	// 			else if (event.key.code == Keyboard::Return && state == State::PAUSED)
	// 			{
	// 				state = State::PLAYING;
	// 				// Сброс таймера, чтобы избежать скачка кадра
	// 				clock.restart();
	// 			}
	// 			// Начало новой игры в состоянии GAME_OVER
	// 			else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
	// 			{
	// 				state = State::LEVELING_UP;
	// 			}

	// 			// Пауза в игре во время PLAYING
	// 			if (event.key.code == Keyboard::Return && state == State::PLAYING)
	// 			{
	// 				state = State::PAUSED;
	// 			}
	// 			// Возобновление игры во время PAUSED
	// 			else if (event.key.code == Keyboard::Return && state == State::PAUSED)
	// 			{
	// 				state = State::PLAYING;
	// 				// Сброс таймера, чтобы избежать скачка кадра
	// 				clock.restart();
	// 			}
	// 			// Начало новой игры в состоянии GAME_OVER
	// 			else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
	// 			{
	// 				state = State::LEVELING_UP;
	// 			}// Завершение опроса событий

	// 			// Оработка WASD во время игры
	// 			if (state == State::PLAYING)
	// 			{
	// 				// Обработка нажатия и отпускания клавиш WASD
	// 				if (Keyboard::isKeyPressed(Keyboard::W)) {
	// 					player.moveUp();
	// 				}
	// 				else
	// 				{
	// 					player.stopUp();
	// 				}
					
	// 				if (Keyboard::isKeyPressed(Keyboard::S)) {
	// 					player.moveDown();
	// 				}
	// 				else
	// 				{
	// 					player.stopDown();
	// 				}

	// 				if (Keyboard::isKeyPressed(Keyboard::A)) {
	// 					player.moveLeft();
	// 				}
	// 				else
	// 				{
	// 					player.stopLeft();
	// 				}
					
	// 				if (Keyboard::isKeyPressed(Keyboard::D)) {
	// 					player.moveRight();
	// 				}
	// 				else
	// 				{
	// 					player.stopRight();
	// 				}
	// 			}// Завершение обработки WASD во время игры

	// 			// Обработка состояния повышения уровня
	// 			if (state == State::LEVELING_UP)
	// 			{
	// 				// Обработка повышения уровня игрока
	// 				if (event.key.code == Keyboard::Num1)
	// 				{
	// 					state = State::PLAYING;
	// 				}
	// 				if (event.key.code == Keyboard::Num2)
	// 				{
	// 					state = State::PLAYING;
	// 				}
	// 				if (event.key.code == Keyboard::Num3)
	// 				{
	// 					state = State::PLAYING;
	// 				}	
	// 				if (event.key.code == Keyboard::Num4)
	// 				{
	// 					state = State::PLAYING;
	// 				}
	// 				if (event.key.code == Keyboard::Num5)
	// 				{	
	// 					state = State::PLAYING;
	// 				}
	// 				if (event.key.code == Keyboard::Num6)
	// 				{
	// 					state = State::PLAYING;
	// 				}
	// 				if (state == State::PLAYING)
	// 				{
	// 					// Подготовка уровня
	// 					// Мы изменим следующие две строки позже
	// 					arena.width = 500;
	// 					arena.height = 500;
	// 					arena.left = 0;
	// 					arena.top = 0;
	// 					// Мы изменим эту строку кода позже
	// 					int tileSize = 50;
						
	// 					// Появление игрока в центре арены
	// 					player.spawn(arena, resolution, tileSize);
	// 					// Сброс таймера, чтобы избежать скачка кадра
	// 					clock.restart();
	// 				}
	// 			}// Завершение обработки повышения уровня

	// 			/*
	// 			****************
	// 			Обновление кадра
	// 			****************
	// 			*/
				
	// 			if (state == State::PLAYING)
	// 			{
	// 				// Обновление delta time

	// 				// Обновляем общее игровое время
	// 				gameTimeTotal += deltaTime;

	// 				// Преобразуем delta time в дробь
	// 				float dtAsSeconds = deltaTime;

	// 				// Получаем текущее положение указателя мыши
	// 				mouseScreenPosition = Mouse::getPosition();

	// 				// Преобразуем положение указателя мыши в глобальные
	// 				// координаты относительно mainView
	// 				mouseWorldPosition = window.mapPixelToCoords(
	// 				Mouse::getPosition(), mainView);

	// 				// Обновляем игрового персонажа
	// 				player.update(dtAsSeconds, Mouse::getPosition());

	// 				// Сохраняем новое положение персонажа
	// 				Vector2f playerPosition(player.getCenter());

	// 				// Центрируем вид вокруг игрового персонажа
	// 				mainView.setCenter(player.getCenter());
	// 			}// Завершение обновления сцены

	// 			/*
	// 			***************
	// 			Отрисовка сцены
	// 			***************
	// 			*/
				
	// 			if (state == State::PLAYING)
	// 			{
	// 				window.clear();

	// 				// Устанавливаем mainView для отображения в окне
	// 				// и отрисовываем все элементы, связанные с ним
	// 				window.setView(mainView);

	// 				// Отрисовываем игрового персонажа
	// 				window.draw(player.getSprite());
	// 			}
	// 			if (state == State::LEVELING_UP)
	// 			{
	// 			}
	// 			if (state == State::PAUSED)
	// 			{
	// 			}
	// 			if (state == State::GAME_OVER)
	// 			{
	// 			}
	// 			window.display();
	// 		}
	// 	}

	// }// Конец игрового цикла

	return 0;
}















