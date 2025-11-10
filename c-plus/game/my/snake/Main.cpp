#include <SFML/Graphics.hpp>

#include "Fild.h"

using namespace std;

int main()
{

	VideoMode vm({1920, 1080});
	RenderWindow window(vm, "SnakE");

	Fild fild(500, 500, 300, 300);


	Clock clock;
	float targetFps = 30.0f;
	float frameTime = 1.0f / targetFps;

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
			}


			window.clear();

			window.draw(fild.getShape());

			window.display();
		}

	}


	return 0;

}