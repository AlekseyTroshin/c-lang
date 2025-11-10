#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode({800, 600}), "Title");

	RectangleShape rectangle({400.f, 200.f});

	//	set origin
	rectangle.setOrigin({200.f, 100.f});
	rectangle.setPosition({400.f, 300.f});
	rectangle.setOutlineThickness(10.f);
	rectangle.setOutlineColor(Color(255, 170, 0));

	//	transformation
	// rectangle.setPosition({200, 100});
	rectangle.setRotation(degrees(30.f));
	// rectangle.setScale({1.5f, 1.f});

	// color & outline
	rectangle.setFillColor(Color(255, 213, 128));



	while (window.isOpen())
	{
		if (std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(Color(127, 127, 127));

		window.draw(rectangle);

		window.display();
	}

	return 0;
}