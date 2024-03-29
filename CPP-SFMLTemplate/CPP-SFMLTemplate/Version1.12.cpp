//1942 Game Assignment, made by William Hunt
//Header Files
#include <sstream>
#include <iostream>//input output header file
#include <SFML/Graphics.hpp>//graphics header file
#include <fstream> //file input/output
#include <SFML/Audio.hpp>//audio header file
#include "Bullet.h"
#include <vector>

//Namespaces'
using namespace std;
using namespace sf;

int gamestate = 0;
int score = 0;
int hiScore;
int health = 100;
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

	/*Textures */ sf::Texture Screen, Plane, StartScreen, PauseScreen, InstructionsScreen, LoseScreen, EnemyPlane, EnemyPlane2, EnemyPlane3;

	int PlaneSpawn;
	int o = 0;

	//Screen Image Variables
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,-500);

	//Instructions Image Variables
	float InstructionsScreenCurrentScaleX = 1.0f,InstructionsScreenCurrentScaleY = 1.0f;
	float InstructionsScreenWidth,InstructionsScreenHeight;
	sf::Vector2f InstructionsScreenLocation(0,0);

	//Lose Image Variables
	float LoseScreenCurrentScaleX = 1.0f,LoseScreenCurrentScaleY = 1.0f;
	float LoseScreenWidth,LoseScreenHeight;
	sf::Vector2f LoseScreenLocation(0,0);

	//Start Screen Image Variables
	float StartScreenCurrentScaleX = 1.0f,StartScreenCurrentScaleY = 1.0f;
	float StartScreenWidth,StartScreenHeight;
	sf::Vector2f StartScreenLocation(0,0);

	//Pause Screen Image Variables
	float PauseScreenCurrentScaleX = 1.0f,PauseScreenCurrentScaleY = 1.0f;
	float PauseScreenWidth,PauseScreenHeight;
	sf::Vector2f PauseScreenLocation(0,0);

	//Plane Image Variables
	float PlaneCurrentScaleX = 0.15f,PlaneCurrentScaleY = 0.15f;
	float PlaneWidth,PlaneHeight;
	sf::Vector2f PlaneLocation(220,200);

	//Enemy Plane Image Variables
	float EnemyPlaneCurrentScaleX = 0.15f,EnemyPlaneCurrentScaleY = 0.15f;
	float EnemyPlaneWidth,EnemyPlaneHeight, EnemyPlaneSpeed = 0.065;
	sf::Vector2f EnemyPlaneLocation(15,50);

	//Enemy Plane Image Variables
	float EnemyPlane2CurrentScaleX = 0.15f,EnemyPlane2CurrentScaleY = 0.15f;
	float EnemyPlane2Width,EnemyPlane2Height, EnemyPlane2Speed = 0.065;
	sf::Vector2f EnemyPlane2Location(-60,150);

	//Enemy Plane Image Variables
	float EnemyPlane3CurrentScaleX = 0.15f,EnemyPlane3CurrentScaleY = 0.15f;
	float EnemyPlane3Width,EnemyPlane3Height, EnemyPlane3Speed = 0.065;
	sf::Vector2f EnemyPlane3Location(560,50);

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

	Text PausedText;
	PausedText.setFont(font);
	PausedText.setCharacterSize(80);
	PausedText.setFillColor(Color::Black);
	PausedText.setString("PAUSED");
	PausedText.setPosition(120,200);


	//HiScore Variables
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(22);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setString("HiScore: ");
	hiScoreText.setPosition(320,470);

	//Loading the hiscore from hiscore.txt in the hiscoredata folder
	std::ifstream hiScoreLoadFILE("hiscoredata/HiScores.txt");
	if (hiScoreLoadFILE.is_open())
	{
		hiScoreLoadFILE >> hiScore;
		hiScoreLoadFILE.close();
	}

	//Background Image Variables
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
	if (!InstructionsScreen.loadFromFile("Assets/Instructions.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite InstructionsScreenImage(InstructionsScreen);
	InstructionsScreenImage.setScale(sf::Vector2f(InstructionsScreenCurrentScaleX,InstructionsScreenCurrentScaleY));
	InstructionsScreenWidth = InstructionsScreenImage.getGlobalBounds().width;
	InstructionsScreenHeight = InstructionsScreenImage.getGlobalBounds().height;
	
	InstructionsScreenImage.setPosition(InstructionsScreenLocation.x,InstructionsScreenLocation.y);

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
	if (!LoseScreen.loadFromFile("Assets/LoseScreen.png")) //The "LoseScreen" Image...
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

		
	EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

	//Enemy Plane2 Image Variables
	if (!EnemyPlane2.loadFromFile("Assets/EnemyPlane2.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyPlane2Sprite(EnemyPlane2);
	EnemyPlane2Sprite.setScale(sf::Vector2f(EnemyPlane2CurrentScaleX,EnemyPlane2CurrentScaleY));
	EnemyPlane2Width = EnemyPlane2Sprite.getGlobalBounds().width;
	EnemyPlane2Height = EnemyPlane2Sprite.getGlobalBounds().height;

		
	EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);

	//Enemy Plane3 Image Variables
	if (!EnemyPlane3.loadFromFile("Assets/EnemyPlane3.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyPlane3Sprite(EnemyPlane3);
	EnemyPlane3Sprite.setScale(sf::Vector2f(EnemyPlane3CurrentScaleX,EnemyPlane3CurrentScaleY));
	EnemyPlane3Width = EnemyPlane3Sprite.getGlobalBounds().width;
	EnemyPlane3Height = EnemyPlane3Sprite.getGlobalBounds().height;

		
	EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);

	//Rotate enemy plane so that it is correctly angled in the direction it is travelling
	EnemyPlaneSprite.setRotation(90);
	EnemyPlane2Sprite.setRotation(90);
	EnemyPlane3Sprite.setRotation(270);

	bool restart = false;
	bool showlevel = false;
	bool paused = false;
	bool move1 = true;
	bool move2 = false;
	bool move3 = false;
	bool move4 = false;


	if (gamestate == 0)
	{
	TheGameWindow.clear();
	TheGameWindow.draw(StartScreenImage);
	TheGameWindow.display();
	}

		
	std::vector<Bullet> bulletVector;
	bool isfiring = false;

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
							paused = false;
						}			
						if(gamestate == 1)
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						{
							restart = true;				
						}
						}
						if(gamestate == 3)//if lose state
						{
							if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
							{
								cout << "Backspace pressed";
								gamestate = 1;
								showlevel = true;
								restart = true;
							}
						}
						if(gamestate == 1)
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
						{
							//std::cout << "w" ;
							PlaneLocation.y = PlaneLocation.y - 5;
							if (PlaneLocation.y < -100)
								{
									PlaneLocation.y = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
							
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							//std::cout << "a" ;
							PlaneLocation.x = PlaneLocation.x - 5;
							if (PlaneLocation.x < -100)
								{
									PlaneLocation.x = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							//std::cout << "s" ;
							PlaneLocation.y = PlaneLocation.y + 5;
							if (PlaneLocation.y > 500)
								{
									PlaneLocation.y = -20 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							isfiring = true;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
						{
							//std::cout << "d" ;
							PlaneLocation.x = PlaneLocation.x + 5;
							if (PlaneLocation.x > TheGameWindow_CurrentDimensions.x)
								{
									PlaneLocation.x = 0 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
						{
							gamestate = 5;
						}
						PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
						{
							gamestate = 6;
						}
						}
					}
				}
				

				if(gamestate == 1)
				{
					/*if (isfiring == true)
				{
					Bullet newBullet(sf::Vector2f(50, 5));
					newBullet.setPos(sf::Vector2f(PlaneLocation.x, PlaneLocation.y));
					bulletVector.push_back(newBullet);
					isfiring = false;
					cout << "Hello";
				}

				for(int i=0; i < bulletVector.size(); i++) {
					bulletVector[i].draw(TheGameWindow);
					bulletVector[i].fire(3);
				}
				*/
					showlevel = true;
					if(move1)
					{
					if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneSprite.setPosition(-11000, -11000);
						move2 = true;
					}
					}
					if(move2)
					{
					if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneLocation.x = -60;
						EnemyPlaneLocation.y = 50;
						EnemyPlane2Location.x = -60;
						EnemyPlane2Location.y = 150;
						move2 = false;
						move3 = true;
					}
					}
					if(move3)
					{

						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
						{
							EnemyPlane2Location.x = -60;
							EnemyPlane2Location.y = 150;
							//move3 = false;
							a++;

						}
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							//move4 = true;
							a++;
						}
						if(a > 2)
						{
							cout << "MOVE3 WORKED!!";
							move4 = true;
						}


					}
						
						if (move1)
						{
							EnemyPlaneLocation.x = EnemyPlaneLocation.x + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.x > 600)
							{
							EnemyPlaneLocation.x = 0 - EnemyPlaneWidth;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
						}

						if (move2)
						{
							EnemyPlane2Location.x = EnemyPlane2Location.x + EnemyPlane2Speed;
							if (EnemyPlane2Location.x > 600)
							{
							EnemyPlane2Location.x = 0 - EnemyPlane2Width;
							}
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
						}

						if(move3)
						{

							EnemyPlaneLocation.x = EnemyPlaneLocation.x + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.x > 600)
							{
							EnemyPlaneLocation.x = 0 - EnemyPlaneWidth;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

							EnemyPlane2Location.x = EnemyPlane2Location.x + EnemyPlane2Speed;
							if (EnemyPlane2Location.x > 600)
							{
							EnemyPlane2Location.x = 0 - EnemyPlane2Width;
							}
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
						}

						if(move4)
						{
							EnemyPlane3Location.x = EnemyPlane3Location.x - EnemyPlane3Speed;
							if (EnemyPlane3Location.x < -100)
							{
							EnemyPlane3Location.x = 0 - TheGameWindow_CurrentDimensions.x;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}
							// ADD IF STATEMENT, IF ENEMY PLANE DIES SPAWN A NEW PLANE, HAVE 3 OVERALL PLANES, RESPAWN THEM WHEN THEY DIE.
			
							/*EnemyPlaneLocation.y = EnemyPlaneLocation.y + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.y > 550)
							{
							EnemyPlaneLocation.y = 0 - EnemyPlaneHeight;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);*/
							
									//end of for loop
					//Background scroller
						if(ScreenLocation.y < 0)
							{
								ScreenLocation.y = ScreenLocation.y+0.01;
							}
						if(ScreenLocation.y > 0)
							{

								ScreenLocation.y = -500;
							}
						ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);

						if (restart)
						{
							health = 100;
							PlaneLocation.x = 220;
							PlaneLocation.y = 200;
							PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
							ScreenLocation.x = 0;
							ScreenLocation.y = -500;
							ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);
							EnemyPlaneLocation.x = 15;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							restart = false;
						}


				std::stringstream hiscorE;
				hiscorE << "High Score: " << hiScore;
				hiScoreText.setString(hiscorE.str());
				std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
				OutputhiScoreLoadFILE << hiScore;
				OutputhiScoreLoadFILE.close();
				
				}
				if(showlevel)
				{
				TheGameWindow.clear();
				TheGameWindow.draw(ScreenImage);
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(EnemyPlaneSprite);
				TheGameWindow.draw(EnemyPlane2Sprite);
				TheGameWindow.display();	
				}

				if(gamestate==6)
				{
					showlevel = false;
					TheGameWindow.draw(PausedText);
					TheGameWindow.display();
				}

				if (gamestate == 3)
				{
				showlevel = false;
				TheGameWindow.clear();
				TheGameWindow.draw(LoseScreenImage);
				TheGameWindow.display();
				}
				if (gamestate == 5)
				{
				showlevel = false;
				TheGameWindow.clear();
				TheGameWindow.draw(InstructionsScreenImage);
				TheGameWindow.display();
				}
			}
			return 0;
		}
