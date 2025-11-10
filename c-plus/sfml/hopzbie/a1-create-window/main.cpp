#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode({800, 600}), "Title");

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

		window.display();
	}

	return 0;
}