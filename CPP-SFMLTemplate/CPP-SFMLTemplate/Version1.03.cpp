//1942 Game Assignment, made by William Hunt
//Header Files
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream> //file input/output
#include <SFML/Audio.hpp>

//Namespaces'
using namespace std;
using namespace sf;

int gamestate = 0;

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

	sf::Texture Screen, Plane, Bullet, StartScreen, PauseScreen;

	//Screen Image Variables
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,0);

	//Screen Image Variables
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

	//Instructions Image Variables
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


	//Instructions Image Variables
	if (!Plane.loadFromFile("Assets/Plane.png")) //The "StartScreen" Image...
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
						if ((event.key.code == 58)) //Enter Key, Game Starts
						{
							cout << "Game Has Started";
							gamestate = 1;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
						{
							gamestate = 2;
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
				TheGameWindow.clear();
				TheGameWindow.draw(ScreenImage);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(BulletSprite);
				TheGameWindow.display();
				}
				if (gamestate == 2)
				{
				TheGameWindow.clear();
				TheGameWindow.draw(PauseScreenImage);
				TheGameWindow.display();
				}
			}
			return 0;
		}
