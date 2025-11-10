#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <locale>

#include "view.h"
#include "map.h"


using namespace std;
using namespace sf;


int main()
{

	RenderWindow window(VideoMode({600, 400}), "SFML Window");
	view.setSize({200, 120});

	Clock clock;
	float targetFPS = 5.0f;
	float frameTime = 1.0f / targetFPS;
	int countA = 0, countB = 0;

	Clock gameClock;
	bool gameRunning = true;

	int TileBitX = 20;
	int TileBitY = 20;
	RectangleShape tile(Vector2f(TileBitX, TileBitY));
	tile.setFillColor(Color::White);
	Vector2u windowSize = window.getSize();

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		if (deltaTime < frameTime)
		{
			sleep (seconds(frameTime - deltaTime));
			deltaTime = frameTime;
		}

		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f windowPos = window.mapPixelToCoords(mousePos);


		bool atLeftEdge = mousePos.x <= 10;
		bool atRightEdge = mousePos.x >= 600 - 10;
		bool atTopEdge = mousePos.y <= 10;
		bool atBottomEdge = mousePos.y >= 400 - 10;

		// cout << " --  " << mousePos.x << " - " << mousePos.y << " - " 
		// 	<< windowSize.x << " - " << windowSize.y << endl;

		cout << " --  " << mousePos.x << " - "  << mousePos.y << " - "  
			<< atLeftEdge << " - " << atRightEdge << " - " 
			<< atTopEdge << " - " << atBottomEdge << endl;

		if (auto event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->scancode == Keyboard::Scan::Escape)
				{
					window.close();	
				}
			}
		}

		
		window.clear();


		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0')
				{
					tile.setPosition(Vector2f(j * TileBitX, i * TileBitY));
					window.draw(tile);
				}

			}
		}

		window.display();

	}

}













