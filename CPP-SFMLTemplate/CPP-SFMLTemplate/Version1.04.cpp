//1942 Game Assignment, made by William Hunt
//Header Files
#include <sstream>
#include <iostream>//input output header file
#include <SFML/Graphics.hpp>//graphics header file
#include <fstream> //file input/output
#include <SFML/Audio.hpp>//audio header file

//Namespaces'
using namespace std;
using namespace sf;

int gamestate = 0;
int score = 0;
int hiScore;
//Global Variables
	//Game Window Variables...

	sf::Vector2f TheGameWindow_CurrentDimensions(500,500);
	sf::Vector2f TheGameWindow_PerspectiveDimensions(500,500);
	sf::RenderWindow TheGameWindow(sf::VideoMode(TheGameWindow_CurrentDimensions.x,TheGameWindow_CurrentDimensions.y),"1942",sf::Style::Titlebar); //sf::Style::Fullscreen || sf::Style::Titlebar


//Main
int main()
{
	TheGameWindow.setMouseCursorVisible(false); //Mouse Cursor is now invisible

//Local Variables
	//Event Variables
	sf::Event event;

	/*Textures */ sf::Texture Screen, Plane, Bullet, StartScreen, PauseScreen, LoseScreen, EnemyPlane;

	//Screen Image Variables
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,0);

	//Lose Image Variables
	float LoseScreenCurrentScaleX = 1.0f,LoseScreenCurrentScaleY = 1.0f;
	float LoseScreenWidth,LoseScreenHeight;
	sf::Vector2f LoseScreenLocation(0,0);

	//Pause Image Variables
	float PauseScreenCurrentScaleX = 1.0f,PauseScreenCurrentScaleY = 1.0f;
	float PauseScreenWidth,PauseScreenHeight;
	sf::Vector2f PauseScreenLocation(0,0);

	//Start Screen Image Variables
	float StartScreenCurrentScaleX = 1.0f,StartScreenCurrentScaleY = 1.0f;
	float StartScreenWidth,StartScreenHeight;
	sf::Vector2f StartScreenLocation(0,0);

	//Bullet Image Variables
	float BulletCurrentScaleX = 1.0f,BulletCurrentScaleY = 1.0f;
	float BulletWidth,BulletHeight;
	sf::Vector2f BulletLocation(0,0);

	//Plane Image Variables
	float PlaneCurrentScaleX = 0.22f,PlaneCurrentScaleY = 0.22f;
	float PlaneWidth,PlaneHeight;
	sf::Vector2f PlaneLocation(220,350);

	//Enemy Plane Image Variables
	float EnemyPlaneCurrentScaleX = 0.22f,EnemyPlaneCurrentScaleY = 0.22f;
	float EnemyPlaneWidth,EnemyPlaneHeight;
	sf::Vector2f EnemyPlaneLocation(100,150);

	//Font Variables
	Font font;
	font.loadFromFile("Assets/BAUHS93.ttf");

	//Score  Variables
    Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(22);
	scoreText.setFillColor(Color::White);
	scoreText.setString("Score: ");
	scoreText.setPosition(10, 470);

	//HiScore Variables
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(22);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setString("Hiscore: ");
	hiScoreText.setPosition(350,470);

	//Loading the hiscore from hiscore.txt in the hiscoredata folder
	std::ifstream hiScoreLoadFILE("hiscoredata/HiScores.txt");
	if (hiScoreLoadFILE.is_open())
	{
		hiScoreLoadFILE >> hiScore;
		hiScoreLoadFILE.close();
	}

	//Instructions Image Variables
	if (!Screen.loadFromFile("Assets/Screen.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite ScreenImage(Screen);
	ScreenImage.setScale(sf::Vector2f(ScreenCurrentScaleX,ScreenCurrentScaleY));
	ScreenWidth = ScreenImage.getGlobalBounds().width;
	ScreenHeight = ScreenImage.getGlobalBounds().height;
	
	ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);

	//Instructions Image Variables
	if (!PauseScreen.loadFromFile("Assets/PauseScreen.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite PauseScreenImage(PauseScreen);
	PauseScreenImage.setScale(sf::Vector2f(PauseScreenCurrentScaleX,PauseScreenCurrentScaleY));
	PauseScreenWidth = PauseScreenImage.getGlobalBounds().width;
	PauseScreenHeight = PauseScreenImage.getGlobalBounds().height;
	
	PauseScreenImage.setPosition(PauseScreenLocation.x,PauseScreenLocation.y);

	//Start Screen Image Variables
	if (!StartScreen.loadFromFile("Assets/StartScreen.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite StartScreenImage(StartScreen);
	StartScreenImage.setScale(sf::Vector2f(StartScreenCurrentScaleX,StartScreenCurrentScaleY));
	StartScreenWidth = StartScreenImage.getGlobalBounds().width;
	StartScreenHeight = StartScreenImage.getGlobalBounds().height;
	
	StartScreenImage.setPosition(StartScreenLocation.x,StartScreenLocation.y);

	//Lose Screen Image Variables
	if (!LoseScreen.loadFromFile("Assets/LoseScreen.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite LoseScreenImage(LoseScreen);
	LoseScreenImage.setScale(sf::Vector2f(LoseScreenCurrentScaleX,LoseScreenCurrentScaleY));
	LoseScreenWidth = LoseScreenImage.getGlobalBounds().width;
	LoseScreenHeight = LoseScreenImage.getGlobalBounds().height;
	
	LoseScreenImage.setPosition(LoseScreenLocation.x,LoseScreenLocation.y);

	//Player (plane) Image Variables
	if (!Plane.loadFromFile("Assets/Plane.png")) //The "Player" Image...
		{
		std::cout << "plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite PlaneSprite(Plane);
	PlaneSprite.setScale(sf::Vector2f(PlaneCurrentScaleX,PlaneCurrentScaleY));
	PlaneWidth = PlaneSprite.getGlobalBounds().width;
	PlaneHeight = PlaneSprite.getGlobalBounds().height;

	PlaneLocation.y = TheGameWindow_CurrentDimensions.y - PlaneHeight;
			
	PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

	//Enemy Plane Image Variables
	if (!EnemyPlane.loadFromFile("Assets/EnemyPlane.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyPlaneSprite(EnemyPlane);
	EnemyPlaneSprite.setScale(sf::Vector2f(EnemyPlaneCurrentScaleX,EnemyPlaneCurrentScaleY));
	EnemyPlaneWidth = EnemyPlaneSprite.getGlobalBounds().width;
	EnemyPlaneHeight = EnemyPlaneSprite.getGlobalBounds().height;

	EnemyPlaneLocation.y = TheGameWindow_CurrentDimensions.y - EnemyPlaneHeight;
		
	EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

	if (!Bullet.loadFromFile("Assets/Bullet.png")) //The "StartScreen" Image...
		{
		std::cout << "Bullet has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite BulletSprite(Bullet);
	BulletSprite.setScale(sf::Vector2f(BulletCurrentScaleX,BulletCurrentScaleY));
	BulletWidth = BulletSprite.getGlobalBounds().width;
	BulletHeight = BulletSprite.getGlobalBounds().height;

	BulletLocation.y = TheGameWindow_CurrentDimensions.y - BulletHeight;
		
	BulletSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

	if (gamestate == 0)
	{
		TheGameWindow.draw(StartScreenImage);
		TheGameWindow.display();
	}

while (TheGameWindow.isOpen()) 
			{
				while (TheGameWindow.pollEvent(event))
				{
				if (event.type == sf::Event::Closed || event.key.code == 36)//esc key)
					{
					//This code means that if the x on the window is used or the ESC key the game window will close. 
					 TheGameWindow.close();
					}
				else if (event.type == sf::Event::KeyPressed) 
					//else if key pressed
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //Enter Key, Game Starts
						{
							cout << "Game Has Started";
							gamestate = 1;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
						{
							gamestate = 2;
						}
						if(gamestate == 3)
						{
							//Add backspace press later for restart of game
						}
						if(gamestate == 1)
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
						{
							//std::cout << "w" ;
							if(PlaneLocation.y <= -10)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaneLocation.y = PlaneLocation.y - 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							//std::cout << "a" ;
							if(PlaneLocation.x == -15)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaneLocation.x = PlaneLocation.x - 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							//std::cout << "s" ;
							if(PlaneLocation.y >= 425)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaneLocation.y = PlaneLocation.y + 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							//ADD FIRING MECHANISM, Does not work
							int a = 0;
							while (a<=4)
							{
								cout << "Hello";
								BulletLocation.y = BulletLocation.y - 20;
								a++;
							}
							if (a>4)
							{
								cout << "Goodbye";
								BulletLocation.y = PlaneLocation.y;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
						{
							//std::cout << "d" ;
							if(PlaneLocation.x >= 400)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaneLocation.x = PlaneLocation.x + 5;
							}
						}
						PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						BulletSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
					}
				}
				}
				if(gamestate == 1)
				{
					if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						gamestate = 3;
					}
					if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						EnemyPlaneSprite.setPosition(800,800);
					}
				TheGameWindow.clear();
				TheGameWindow.draw(ScreenImage);
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(EnemyPlaneSprite);
				TheGameWindow.draw(BulletSprite);
				TheGameWindow.display();
				}
				if (gamestate == 2)
				{
				TheGameWindow.clear();
				TheGameWindow.draw(PauseScreenImage);
				TheGameWindow.display();
				}
				if (gamestate == 3)
				{
				TheGameWindow.clear();
				TheGameWindow.draw(LoseScreenImage);
				TheGameWindow.display();
				}
			}
			return 0;
		}