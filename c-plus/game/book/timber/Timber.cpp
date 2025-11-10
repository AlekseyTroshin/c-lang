#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
vector<Sprite> branches;

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

float random_int(std::mt19937& gen, int min, int max, int plus = 0) 
{
	static uniform_int_distribution<int> dist;
    return dist(gen, uniform_int_distribution<int>::param_type(min, max)) + plus;
}

float random_float(mt19937& gen, float min, float max, float plus = 0.0f) 
{
	static uniform_real_distribution<float> dist;
    return dist(gen, uniform_real_distribution<float>::param_type(min, max)) + plus;
}

int main()
{

	VideoMode vm = VideoMode({1920, 1080});
	RenderWindow window(vm, "Timber!");

	// Шрифт
	Font font("./fonts/KOMIKAP_.ttf");
	Text messageText(font);
	Text scoreText(font);

	messageText.setFont(font);
	scoreText.setFont(font);

	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();

	messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});

	scoreText.setPosition({20, 20});


	//Ветки
	Texture textureBranch("graphics/branch.png");
	vector<Sprite> branches(NUM_BRANCHES, Sprite(textureBranch));

	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setPosition({-2000, -2000});

		branches[i].setOrigin({220, 20});
	}


	//Счёт
	int score = 0;
	

	// Рандомные числа
	random_device rd;
	mt19937 gen(rd());

	int playerScore {0};
	char playerInitial {'J'};
	float valuePi {3.141f};
	bool isAlive {true};

	// Фон
	Texture textureBackground;
	int textureBackgroundErr = textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground(textureBackground);
	spriteBackground.setPosition({0, 0});

	// Дерево
	const float TREE_HORIZONTAL_POSITION = 810;
	const float TREE_VERTICAL_POSITION = 0;
	Texture textureTree;
	int textureTreeErr = textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree(textureTree);
	spriteTree.setPosition({TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION});

	// Пчела
	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture textureBee;
	int textureBeeErr = textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee(textureBee);
	spriteBee.setPosition({-300, 800});

	// Облако
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Texture textureCloud;
	int textureCloudErr = textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1(textureCloud);
	Sprite spriteCloud2(textureCloud);
	Sprite spriteCloud3(textureCloud);
	spriteCloud1.setPosition({-300, 0});
	spriteCloud2.setPosition({-300, 250});
	spriteCloud3.setPosition({-300, 500});

	Clock clock;
	float targetFPS = 30.0f;
	float frameTime = 1.0f / targetFPS;
	float totalTime = 0.0f;

	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition({(1920 / 2) - timeBarStartWidth / 2, 980});

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool paused = true;

	Texture texturePlayer;
	int texturePlayerErr = texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer(texturePlayer);
	spritePlayer.setPosition({580, 720});

	side playerSide = side::LEFT;

	Texture textureRIP;
	int textureRIPErr = textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP(textureRIP);
	spriteRIP.setPosition({2000, 860});

	Texture textureAxe;
	int textureAxeErr = textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe(textureAxe);
	spriteAxe.setPosition({2000, 830});

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	Texture textureLog;
	int textureLogErr = textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog(textureLog);
	spriteLog.setPosition({810, 720});

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop(chopBuffer);
	chop.setVolume(20.f);
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death(deathBuffer);
	death.setVolume(5.f);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime(ootBuffer);
	outOfTime.setVolume(10.f);

	while (window.isOpen())
	{

		Time dt = clock.restart();
		float deltaTime = dt.asSeconds();

		totalTime += deltaTime;

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

				if (keyPressed->scancode == Keyboard::Scan::P)
				{
					paused = true;
					messageText.setString("Put enter");
				}

				if (keyPressed->scancode == Keyboard::Scan::Enter)
				{
					paused = false;
					messageText.setString("");

					score = 0;
					timeRemaining = 6;

					for (int i = 1; i < NUM_BRANCHES; i++)
					{
						branchPositions[i] = side::NONE;
					}

					spriteRIP.setPosition({675, 2000});

					spritePlayer.setPosition({580, 720});

					spriteAxe.setPosition({700, 830});

					acceptInput = true;
				}

				if (acceptInput)
				{
					if (keyPressed->scancode == Keyboard::Scan::Right)
					{
						playerSide = side::RIGHT;

						score++;

						timeRemaining += (2 / score) + .35;

						spriteAxe.setPosition({AXE_POSITION_RIGHT, spriteAxe.getPosition().y});
						spritePlayer.setPosition({1200, 720});

						updateBranches(score);

						spriteLog.setPosition({810, 720});
						logSpeedX = -5000;
						logActive = true;

						acceptInput = false;

						chop.play();
					}

					if (keyPressed->scancode == Keyboard::Scan::Left)
					{
						playerSide = side::LEFT;

						score++;

						timeRemaining += (2 / score) + .35;

						spriteAxe.setPosition({AXE_POSITION_LEFT, spriteAxe.getPosition().y});
						spritePlayer.setPosition({580, 720});

						updateBranches(score);

						spriteLog.setPosition({810, 720});
						logSpeedX = 5000;
						logActive = true;

						acceptInput = false;

						chop.play();
					}
				}
			}

			if (const auto* keyReleased = event->getIf<Event::KeyReleased>())
			{
				if (keyReleased->scancode == Keyboard::Scan::Right && !paused)
				{
					acceptInput = true;
					spriteAxe.setPosition({2000, spriteAxe.getPosition().y});
				}
				if (keyReleased->scancode == Keyboard::Scan::Left && !paused)
				{
					acceptInput = true;
					spriteAxe.setPosition({2000, spriteAxe.getPosition().y});
				}
			}
		}

		if (!paused)
		{
			timeRemaining -= frameTime;
			
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				paused = true;

				messageText.setString("Time OUT !");

				outOfTime.play();
			}

			if (!beeActive)
			{
				beeSpeed = random_float(gen, 0.0f, 100.0f, 150.0f);
				beeSpeed = beeSpeed * frameTime;

				float height = random_float(gen, 0.0f, 400.0f, 200.0f);
				spriteBee.setPosition({2000, height});
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition({
					spriteBee.getPosition().x - beeSpeed,
					spriteBee.getPosition().y
				});

				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}

			if (!cloud1Active)
			{
				cloud1Speed = random_float(gen, 50.0f, 100.0f);
				cloud1Speed = cloud1Speed * frameTime;

				float height = random_float(gen, 0.0f, 150.0f);
				spriteCloud1.setPosition({-300, height});
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition({
					spriteCloud1.getPosition().x + cloud1Speed,
					spriteCloud1.getPosition().y
				});

				if (spriteCloud1.getPosition().x > 1920)
				{
					cloud1Active = false;
				}
			}

			if (!cloud2Active)
			{
				cloud2Speed = random_float(gen, 50.0f, 200.0f);
				cloud2Speed = cloud2Speed * frameTime;

				float height = random_float(gen, 0.0f, 300.0f, -150);
				spriteCloud2.setPosition({-300, height});
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition({
					spriteCloud2.getPosition().x + cloud2Speed,
					spriteCloud2.getPosition().y
				});

				if (spriteCloud2.getPosition().x > 1920)
				{
					cloud2Active = false;
				}
			}

			if (!cloud3Active)
			{
				cloud3Speed = random_float(gen, 50.0f, 250.0f);
				cloud3Speed = cloud3Speed * frameTime;

				float height = random_float(gen, 0.0f, 450.0f, -150);
				spriteCloud3.setPosition({-200, height});
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition({
					spriteCloud3.getPosition().x + cloud3Speed,
					spriteCloud3.getPosition().y
				});

				if (spriteCloud3.getPosition().x > 1920)
				{
					cloud3Active = false;
				}
			}

			stringstream stst;
			stst << "Score = " << score;
			scoreText.setString(stst.str());
			
			for (int i = 0; i < NUM_BRANCHES; i++) 
			{
				float height = i * 150;

				if (branchPositions[i] == side::LEFT)
				{
					branches[i].setPosition({610, height});

					branches[i].setRotation(degrees(180));
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition({1330, height});

					branches[i].setRotation(degrees(0));
				}
				else 
				{
					branches[i].setPosition({3000, height});
				}
			}

			if (logActive)
			{
				spriteLog.setPosition({
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				});

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					logActive = false;
					spriteLog.setPosition({810, 720});
				}
			}

			if (branchPositions[5] == playerSide)
			{
				paused = true;
				acceptInput = false;

				spriteRIP.setPosition({525, 760});

				spritePlayer.setPosition({2000, 660});

				spriteAxe.setPosition({3000, 760});

				messageText.setString("CRUSHED!");

				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(Vector2f({textRect.size.x / 2.0f, 
					textRect.size.y / 2.0f}));

				messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});

				death.play();
			}
		}


		window.clear();

		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		window.draw(spriteTree);

		
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);

		window.draw(spriteBee);

		window.draw(scoreText);
		window.draw(timeBar);
		window.draw(messageText);

		window.display();
	}

	return 0;

}

void updateBranches(int seed)
{
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}






