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

//Global Variables
	//Game Window Variables...

	sf::Vector2f TheGameWindow_CurrentDimensions(500,500);
	sf::Vector2f TheGameWindow_PerspectiveDimensions(500,500);
	sf::RenderWindow TheGameWindow(sf::VideoMode(TheGameWindow_CurrentDimensions.x,TheGameWindow_CurrentDimensions.y),"Bouncing Ball Game",sf::Style::Titlebar); //sf::Style::Fullscreen || sf::Style::Titlebar


//Main
int main()
{
	TheGameWindow.setMouseCursorVisible(false); //Mouse Cursor is now invisible

//Local Variables
	//Event Variables
	sf::Event event;

	sf::Texture Screen, PlaceHolderForPlane;

	//Screen Image Variables
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,0);

	//PlaceHolderForPlane Image Variables
	float PlaceHolderForPlaneCurrentScaleX = 0.22f,PlaceHolderForPlaneCurrentScaleY = 0.22f;
	float PlaceHolderForPlaneWidth,PlaceHolderForPlaneHeight;
	sf::Vector2f PlaceHolderForPlaneLocation(220,350);

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
	if (!PlaceHolderForPlane.loadFromFile("Assets/PlaceHolderForPlane.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite PlaceHolderForPlaneSprite(PlaceHolderForPlane);
	PlaceHolderForPlaneSprite.setScale(sf::Vector2f(PlaceHolderForPlaneCurrentScaleX,PlaceHolderForPlaneCurrentScaleY));
	PlaceHolderForPlaneWidth = PlaceHolderForPlaneSprite.getGlobalBounds().width;
	PlaceHolderForPlaneHeight = PlaceHolderForPlaneSprite.getGlobalBounds().height;

	PlaceHolderForPlaneLocation.y = TheGameWindow_CurrentDimensions.y - PlaceHolderForPlaneHeight;
		
	PlaceHolderForPlaneSprite.setPosition(PlaceHolderForPlaneLocation.x,PlaceHolderForPlaneLocation.y);

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
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
						{
							//std::cout << "w" ;
							if(PlaceHolderForPlaneLocation.y <= -10)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaceHolderForPlaneLocation.y = PlaceHolderForPlaneLocation.y - 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							//std::cout << "a" ;
							if(PlaceHolderForPlaneLocation.x == -15)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaceHolderForPlaneLocation.x = PlaceHolderForPlaneLocation.x - 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							//std::cout << "s" ;
							if(PlaceHolderForPlaneLocation.y >= 430)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaceHolderForPlaneLocation.y = PlaceHolderForPlaneLocation.y + 5;
							}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
						{
							//std::cout << "d" ;
							if(PlaceHolderForPlaneLocation.x >= 422)
							{
								//cout << "This action is not permitted";
							}
							else {
								PlaceHolderForPlaneLocation.x = PlaceHolderForPlaneLocation.x + 5;
							}
						}
						PlaceHolderForPlaneSprite.setPosition(PlaceHolderForPlaneLocation.x,PlaceHolderForPlaneLocation.y);
					}
				}
				TheGameWindow.clear();
				TheGameWindow.draw(ScreenImage);
				TheGameWindow.draw(PlaceHolderForPlaneSprite);
				TheGameWindow.display();
			}
			return 0;
		}
