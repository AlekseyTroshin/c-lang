#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <sstream>
#include "mission.h"
#include <locale>


using namespace std;
using namespace sf;

// View moveMap(float time);

class Player {
public:
	float x, y = 0;
public:
	float dx, dy, speed = 0, width, height;
	int dir = 0, w = 0, h = 0, playerScore = 0, health = 0;
	bool life = true, isMove, isSelect;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	FloatRect size;

	Player(String F, int X, int Y, float W, float H) 
		: texture(), sprite(texture)
	{
		health = 100;
		life = true, isMove = false, isSelect = false;
		File = F;
		w = W;
		h = H;
		image.loadFromFile(filesystem::path("images/" + File));
		image.createMaskFromColor(Color(0, 0, 255));
		texture.loadFromImage(image);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect({0, 0}, {w, h}));
		width = texture.getSize().x;
		height = texture.getSize().y;
		sprite.setOrigin({w / 2.0f, h / 2.0f});
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition({x, y});
		interactionWithMap();

		if (health <= 0)
		{
			life = false;
		}
	}

	float getPlayerCoordinateX()
	{
		return x;
	}

	float getPlayerCoordinateY()
	{
		return y;
	}

	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}
					if (dy < 0)
					{
						y = i * 32 + 32;
					}
					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (TileMap[i][j] == 's')
				{
					playerScore++;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'f')
				{
					health -= 40;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'h')
				{
					health += 20;
					TileMap[i][j] = ' ';
				}
			}
		}

	}

};

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
    RenderWindow window(VideoMode({1366, 768}), "SFML Window");
    view.setSize({640, 480});

    Font font;
	if (!font.openFromFile("font/CyrilicOld.TTF")) {
	    return 200;
	}
    Text text(font, "", 20);
	text.setCharacterSize(20);
	text.setFillColor(Color::Black);

    Image map_image;
    map_image.loadFromFile("images/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map(map);

    Image map_image1;
    map_image1.loadFromFile("images/heroArrow.jpg");
    Texture map1;
    map1.loadFromImage(map_image1);
    Sprite s_map1(map1);


    Image quest_image;
    quest_image.loadFromFile("images/missionbg.jpg");
    quest_image.createMaskFromColor(Color({0, 0, 0}));
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest(quest_texture);
    s_quest.setTextureRect(IntRect({0, 0}, {340, 510}));
    s_quest.setScale({0.6f, 0.6f});

    Player p("heroForRotate.jpg", 50, 50, 136, 76);

    

    bool showMissionText = true;

    float CurrentFrame = 0;

    Clock clock;
    float targetFPS = 20.0f;
    float frameTime = 1.0f / targetFPS;

    int heroSpeed = 120;
    int heroDeltaTime = 5;

    Clock gameTimeClock;
    int gameTime = 0;
    float createObjectForMapTimer = 0;

    bool isMove = false;
    float dX = 0;
    float dY = 0;

    int tempX = 0;
    int tempY = 0;
    float distance = 0;

    while (window.isOpen()) {
    	Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);
        // cout << pixelPos.x << endl;
        // cout << pos.x << endl;


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

                if (keyPressed->scancode == Keyboard::Scan::Tab)
                {
                	switch (showMissionText)
                	{
                	case true:
                		{
                			ostringstream playerHealthString;
                			playerHealthString << p.health;
                			ostringstream task;
                			task << getTextMission(getCurrentMission(p.getPlayerCoordinateX()));
                			std::string str = "Здоровье: " + playerHealthString.str() + "\n" + task.str();
							text.setString(sf::String::fromUtf8(str.begin(), str.end()));
                			showMissionText = false;
                			break;
                		}
                	case false:
                		{
                			text.setString("");
                			showMissionText = true;
                			break;
                		}
                	}
                }
            }

            if (auto* mouseEvent = event->getIf<Event::MouseButtonPressed>()) 
            {
	    		if (mouseEvent->button == Mouse::Button::Left) 
	    		{
	        		if (p.sprite.getGlobalBounds().contains({pos.x, pos.y}))
	        		{


	        			p.sprite.setColor(Color::Green);
	        			p.isSelect = true;
	        			// dX = pos.x - p.sprite.getPosition().x;
	        			// dY = pos.y - p.sprite.getPosition().y;
	        			// isMove = true;
	        		}
	        	}
	        }

	        if (p.isSelect) 
	        {
	        	if (auto* mouseEvent = event->getIf<Event::MouseButtonPressed>()) 
	            {
		    		if (mouseEvent->button == Mouse::Button::Right) 
		    		{

		        		p.isMove = true;
		        		p.isSelect = false;
		        		p.sprite.setColor(Color::White);
		        		tempX = pos.x - ((int)p.width / 2);
		        		tempY = pos.y - ((int)p.height / 2);

        				
		        	}
		        }
	        }

	        // if (auto* mouseEvent = event->getIf<Event::MouseButtonReleased>()) {
	    	// 	if (mouseEvent->button == Mouse::Button::Left) {
	        // 		isMove = false;
	        // 		p.sprite.setColor(Color::White);
	        // 	}
	        // }
        }

        if (p.isMove)
        {
        	distance = sqrt((tempX - p.x) * (tempX - p.x) + (tempY - p.y) * (tempY - p.y));
			cout << " | w " << p.width << " | h " << p.height << " | tx " << tempX << " | ty " << tempY  << endl;
        	if (distance > 2)
        	{
        		p.x += (3 * (tempX - p.x)) / distance;
        		p.y += (3 * (tempY - p.y)) / distance;
        		float dX = pos.x - p.x - ((int)p.width / 2);
				float dY = pos.y - p.y - ((int)p.height / 2);
				float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
				std::cout << rotation << "\n";
				p.sprite.setRotation(degrees(rotation));
        	}
        	else
        	{
        		p.isMove = false;
        		cout << "priehali" << endl;
        	}
        }



        // if (isMove)
        // {
        // 	p.sprite.setColor(Color::Green);
        // 	p.x = pos.x - dX;
        // 	p.y = pos.y - dY;
        // }

        



        if (p.life)
        {
        	gameTime = gameTimeClock.getElapsedTime().asSeconds();
        }

    	float deltaTime = clock.restart().asSeconds();

		if (deltaTime < frameTime)
    	{
    		sleep(sf::seconds(frameTime - deltaTime));
    		deltaTime = frameTime;
    	}


    	if (p.life == true)
    	{
	        if (
	        		Keyboard::isKeyPressed(Keyboard::Key::Left)
	        	)
	        {
	        	p.dir = 1;
	        	p.speed = heroSpeed;
	        	CurrentFrame += deltaTime * heroDeltaTime;
	        	if (CurrentFrame > 3) CurrentFrame -= 3;
	        	p.sprite.setTextureRect(IntRect({96 * int(CurrentFrame), 96}, {96, 96}));
	        }

	        if (
	        		Keyboard::isKeyPressed(Keyboard::Key::Right)
	        	)
	        {
	        	p.dir = 0;
	        	p.speed = heroSpeed;
	        	CurrentFrame += deltaTime * heroDeltaTime;
	        	if (CurrentFrame > 3) CurrentFrame -= 3;
	        	p.sprite.setTextureRect(IntRect({96 * int(CurrentFrame), 192}, {96, 96}));
	        }

	        if (
	        		Keyboard::isKeyPressed(Keyboard::Key::Up)
	        	)
	        {
	        	p.dir = 3;
	        	p.speed = heroSpeed;
	        	CurrentFrame += deltaTime * heroDeltaTime;
	        	if (CurrentFrame > 3) CurrentFrame -= 3;
	        	p.sprite.setTextureRect(IntRect({96 * int(CurrentFrame), 288}, {96, 96}));
	        }

	        if (
	        		Keyboard::isKeyPressed(Keyboard::Key::Down)
	        	)
	        {
	        	p.dir = 2;
	        	p.speed = heroSpeed;
	        	CurrentFrame += deltaTime * heroDeltaTime;
	        	if (CurrentFrame > 3) CurrentFrame -= 3;
	        	p.sprite.setTextureRect(IntRect({96 * int(CurrentFrame), 0}, {96, 96}));
	        }
        }

        // getPlayerCoordinateForView(
    	// 	p.getPlayerCoordinateX(),
    	// 	p.getPlayerCoordinateY()
    	// );


        Vector2i localPosition = Mouse::getPosition(window);
        // cout << "1 x  " << localPosition.x << " 1 y  " << localPosition.y << "\n";
        // cout << "2 x  " << window.getSize().x << " 2 y  " << window.getSize().y << "\n";
        

        if ( localPosition.x > window.getSize().x / 2 + 100 )
        {
        	view.move( Vector2f(130 * deltaTime, 0) );
        }
        if ( localPosition.y > window.getSize().y / 2 + 100 )
        {
        	view.move( Vector2f(0, 130 * deltaTime) );
        }

        if ( localPosition.x < window.getSize().x / 2 - 100 )
        {
        	view.move( Vector2f( -(130.0f * deltaTime), 0) );
        }
        if ( localPosition.y < window.getSize().y / 2 - 100 )
        {
        	view.move( Vector2f(0, -(130.0f * deltaTime)) );
        }


        createObjectForMapTimer += deltaTime;
        // cout << "3 " << createObjectForMapTimer << endl;
        if ( createObjectForMapTimer > 10 ) 
        {
        	randomMapGenerate();
        	createObjectForMapTimer = 0;
        }


        p.update(deltaTime);

        window.setView(view);
        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
        {
        	for (int j = 0; j < WIDTH_MAP; j++) 
    		{
    			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect({0, 0}, {32, 32}));
    			if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect({32, 0}, {32, 32}));
    			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect({64, 0}, {32, 32}));
    			if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect({96, 0}, {32, 32}));
    			if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect({128, 0}, {32, 32}));

    			s_map.setPosition({j * 32.0f, i * 32.0f});

    			window.draw(s_map);
    		}
		}

		if (!showMissionText) 
		{
			text.setPosition({view.getCenter().x + 125, view.getCenter().y - 130});
			s_quest.setPosition({view.getCenter().x + 115, view.getCenter().y - 130});
			window.draw(s_quest);
			window.draw(text);
		}

        window.draw(p.sprite);

        window.display();
    }
    
    return 0;
}