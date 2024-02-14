//1942 Game Assignment, made by William Hunt
//Header Files
#include <sstream>
#include <iostream>//input output header file
#include <SFML/Graphics.hpp>//graphics header file
#include <fstream> //file input/output
#include <SFML/Audio.hpp>//audio header file

//ADD SOUND, BULLETS

//Namespaces'
using namespace std;
using namespace sf;

int gamestate = 0;
int score = 0;
int hiScore;
int health = 100;
int a;
int o;
int j;
int c;
int d;
int BulletInPlay = 1;
int BulletToBeFired;
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

	Clock clock;


	/*Textures */ sf::Texture Screen, Screen2, Plane, StartScreen, WinScreen, InstructionsScreen, LoseScreen, EnemyPlane, EnemyPlane2, EnemyPlane3, EnemyPlane4;

	//Screen Image Variables, Level1 Background
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,-500);

	//Screen Image Variables, Level1 Background
	float WinScreenCurrentScaleX = 1.0f,WinScreenCurrentScaleY = 1.0f;
	float WinScreenWidth,WinScreenHeight;
	sf::Vector2f WinScreenLocation(0,0);

	//Screen Image Variables, Level2 Background
	float Screen2CurrentScaleX = 1.0f,Screen2CurrentScaleY = 1.0f;
	float Screen2Width,Screen2Height;
	sf::Vector2f Screen2Location(0,-500);

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

	//Plane Image Variables
	float PlaneCurrentScaleX = 0.15f,PlaneCurrentScaleY = 0.15f;
	float PlaneWidth,PlaneHeight;
	sf::Vector2f PlaneLocation(220,200);

	//Enemy Plane Image Variables
	float EnemyPlaneCurrentScaleX = 0.15f,EnemyPlaneCurrentScaleY = 0.15f;
	float EnemyPlaneWidth,EnemyPlaneHeight, EnemyPlaneSpeed = 0.1;
	sf::Vector2f EnemyPlaneLocation(15,50);

	//Enemy Plane Image Variables
	float EnemyPlane2CurrentScaleX = 0.15f,EnemyPlane2CurrentScaleY = 0.15f;
	float EnemyPlane2Width,EnemyPlane2Height, EnemyPlane2Speed = 0.1;
	sf::Vector2f EnemyPlane2Location(-60,150);

	//Enemy Plane Image Variables
	float EnemyPlane3CurrentScaleX = 0.15f,EnemyPlane3CurrentScaleY = 0.15f;
	float EnemyPlane3Width,EnemyPlane3Height, EnemyPlane3Speed = 0.1;
	sf::Vector2f EnemyPlane3Location(550,250);

	//Enemy Plane Image Variables
	float EnemyPlane4CurrentScaleX = 0.15f,EnemyPlane4CurrentScaleY = 0.15f;
	float EnemyPlane4Width,EnemyPlane4Height, EnemyPlane4Speed = 0.1;
	sf::Vector2f EnemyPlane4Location(400,550);

	//Bullets array
	Sprite bulletArray[50];

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
	PausedText.setPosition(120,180);

	//HiScore Variables
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(22);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setString("HiScore: ");
	hiScoreText.setPosition(320,470);


	float scalingX;
	float scalingY;
	float BulletSpeed =10.0f;

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

	//Background Image Variables
	if (!WinScreen.loadFromFile("Assets/WinScreen.png")) //The "StartScreen" Image...
		{
		std::cout << "WinScreen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite WinScreenImage(WinScreen);
	WinScreenImage.setScale(sf::Vector2f(WinScreenCurrentScaleX,WinScreenCurrentScaleY));
	WinScreenWidth = WinScreenImage.getGlobalBounds().width;
	WinScreenHeight = WinScreenImage.getGlobalBounds().height;
	
	WinScreenImage.setPosition(WinScreenLocation.x,WinScreenLocation.y);

		//Background Image Variables
	if (!Screen2.loadFromFile("Assets/Screen2.png")) //The "StartScreen" Image...
		{
		std::cout << "Screen has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite Screen2Image(Screen2);
	Screen2Image.setScale(sf::Vector2f(Screen2CurrentScaleX,Screen2CurrentScaleY));
	Screen2Width = Screen2Image.getGlobalBounds().width;
	Screen2Height = Screen2Image.getGlobalBounds().height;
	
	Screen2Image.setPosition(Screen2Location.x,Screen2Location.y);

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

	//Enemy Plane3 Image Variables
	if (!EnemyPlane4.loadFromFile("Assets/EnemyPlane4.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyPlane4Sprite(EnemyPlane4);
	EnemyPlane4Sprite.setScale(sf::Vector2f(EnemyPlane4CurrentScaleX,EnemyPlane4CurrentScaleY));
	EnemyPlane4Width = EnemyPlane4Sprite.getGlobalBounds().width;
	EnemyPlane4Height = EnemyPlane4Sprite.getGlobalBounds().height;

		
	EnemyPlane4Sprite.setPosition(EnemyPlane4Location.x,EnemyPlane4Location.y);

	sf::Vector2f firedBulletLocation(PlaneLocation.x,PlaneLocation.y);


	//Rotate enemy plane so that it is correctly angled in the direction it is travelling
	EnemyPlaneSprite.setRotation(90);
	EnemyPlane2Sprite.setRotation(90);
	EnemyPlane3Sprite.setRotation(270);

	const int MAX_NUMBER_BULLETS = 50;

	bool restart = false;
	bool showlevel = false;
	bool paused = false;
	bool move1 = true;
	bool move2 = false;
	bool move3 = false;
	bool move4 = false;
	bool Level2 = false;
	bool move10 = false;
	bool move11 = false;
	bool move12 = false;
	bool move13 = false;
	bool move14 = false;
	bool move15 = false;
	bool move16 = false;
	bool move17 = false;

	bool isSpawnComplete = false;
	bool spacepressed = false;

	if (gamestate == 0)
	{
	TheGameWindow.clear();
	TheGameWindow.draw(StartScreenImage);
	TheGameWindow.display();
	}		
	
	//std::vector<Bullet> bulletVector;
	//bool isfiring = false;

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
						if(gamestate!=10) //If you havent won you can press enter to make gamestate 1.
						{
							if(gamestate!=3)
							{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //Enter Key, Game Starts
						{
							cout << "Enter Pressed";
							gamestate = 1;
							paused = false;
							move10 = false;
							move15 = false;
						}
						}
						}
						if(j==5)
						{
							if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //Enter Key, Game Starts
							{
							move11 = true;
							}
						}
						if(gamestate == 1 || gamestate == 10)
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						{
							showlevel = true;
							gamestate = 1;
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
							PlaneLocation.y = PlaneLocation.y - 5;
							if (PlaneLocation.y < -100)
								{
									PlaneLocation.y = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);							
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							PlaneLocation.x = PlaneLocation.x - 5;
							if (PlaneLocation.x < -100)
								{
									PlaneLocation.x = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							PlaneLocation.y = PlaneLocation.y + 5;
							if (PlaneLocation.y > 500)
								{
									PlaneLocation.y = -20 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							cout<< "Space pressed";
							spacepressed = true;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
						{
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
					Time dt = clock.restart();

					int bulletNumber = 0;

					showlevel = true;
					if(move1)
					{
					if(bulletArray[BulletToBeFired].getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds()))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneSprite.setPosition(-11000, -11000);
						BulletToBeFired=BulletToBeFired+1;
						bulletArray[BulletToBeFired].setPosition(PlaneLocation.x,PlaneLocation.y);
						firedBulletLocation.x=PlaneLocation.x;
						firedBulletLocation.y=PlaneLocation.y;
						move2 = true;
						score = score+100;
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
						EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
						move2 = false;
						move3 = true;
						move16 = true;
						score = score+100;
					}
					}
					if(move16)
					{
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
						{
							EnemyPlane2Location.x = -60;
							EnemyPlane2Location.y = 150;
							EnemyPlane2Sprite.setPosition(-60,150);
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
							//move3 = false;
							a++;
							score = score+100;
							move16 = false;							
						}
					}
					if(move3)
					{
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(-60,50);
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							//move4 = true;
							a++;
							score = score+100;
							move3 = false;							
						}
					}
						if(a==2)
						{
							a = 0;
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlane2Location.x = -60;
							EnemyPlane2Location.y = 150;
							EnemyPlaneSprite.setPosition(-11000, -11000);
							EnemyPlane2Sprite.setPosition(-10000, -10000);
							move3=false;
							move16 = false;
							//cout << "MOVE3 WORKED!!!";
							//score = score+100;
							move4=true;
						}
					if (move4)
					{
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;
							EnemyPlane3Location.y = 150;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							score = score+100;
							move4 = false;
							move11 = true;
							c = 1;
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
						}
						if(move16)
						{
							EnemyPlane2Location.x = EnemyPlane2Location.x + EnemyPlane2Speed;
							if (EnemyPlane2Location.x > 600)
							{
							EnemyPlane2Location.x = 0 - EnemyPlane2Width;
							}
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
						}
						if(move4)
						{
							//cout << "Move4 Should Happen";
							//EnemyPlane3Location.x = 200;
							//EnemyPlane3Location.y = 200;
							EnemyPlane3Location.x = EnemyPlane3Location.x - EnemyPlane3Speed;
							if (EnemyPlane3Location.x < -100)
							{
							EnemyPlane3Location.x = 0 + TheGameWindow_CurrentDimensions.x;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}
						if(c == 0)
						{
						if(ScreenLocation.y < 0)
							{
								ScreenLocation.y = ScreenLocation.y+0.01;
							}
						if(ScreenLocation.y > 0)
							{

								ScreenLocation.y = -500;
							}
						ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);
						}
						if(c == 1)
						{
						if(Screen2Location.y < 0)
							{
								Screen2Location.y = Screen2Location.y+0.01;
							}
						if(Screen2Location.y > 0)
							{

								Screen2Location.y = -500;
							}
						Screen2Image.setPosition(Screen2Location.x,Screen2Location.y);
						}
						if (move11)
						{
							//EnemyPlane3Location.x = 550;
							//EnemyPlane3Location.y = 150;
							//EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							EnemyPlaneSprite.setPosition(15,50);
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
							{
							score = score+100;
							move10 = false;
							move11 = false;
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							move12 = true;
							j = j-5;
							}
						}
						if(move12)
						{
							if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
							{
								EnemyPlane3Location.x = 550;
								EnemyPlane3Location.y = 250;
								EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
								move12 = false;
								move13 = true;
								score = score+100;
							}
						}
						if(move13)
						{
							if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane4Sprite.getGlobalBounds())))
							{
								EnemyPlane4Location.x = 400;
								EnemyPlane4Location.y = 550;
								EnemyPlane4Sprite.setPosition(EnemyPlane4Location.x,EnemyPlane4Location.y);
								move13=false;
								move14 = true;
								move17 = true;
								score = score+100;
							}
						}
						if (move14)
						{
							//cout << "HELLO";
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;;
							EnemyPlane3Location.y = 250;
							EnemyPlane3Sprite.setPosition(550,250);
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							d++;
							score = score+100;
							move14 = false;
						}
						}
						if(move17)
						{
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(-60,50);
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							d++;
							score = score+100;
							move17 = false;
						}
						}
						if(d==2)
						{
							d = 0;
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlane3Location.x = 550;
							EnemyPlane3Location.y = 150;
							EnemyPlaneSprite.setPosition(-11000, -11000);
							EnemyPlane3Sprite.setPosition(-10000, -10000);
							move14 = false;
							move17 = false;
							gamestate = 10;
						}						
						if(move11)
						{
							EnemyPlaneLocation.x = EnemyPlaneLocation.x + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.x > 600)
							{
							EnemyPlaneLocation.x = 0 - EnemyPlaneWidth;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
						}
						if(move12)
						{
							EnemyPlane3Location.x = EnemyPlane3Location.x - EnemyPlane3Speed;
							if (EnemyPlane3Location.x < -100)
							{
							EnemyPlane3Location.x = 0 + TheGameWindow_CurrentDimensions.x;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}
						if(move13)
						{
							EnemyPlane4Location.y = EnemyPlane4Location.y - EnemyPlane4Speed;
							if (EnemyPlane4Location.y < -50)
							{
							EnemyPlane4Location.y = 550;
							}
							EnemyPlane4Sprite.setPosition(EnemyPlane4Location.x,EnemyPlane4Location.y);
						}
						if(move14)
						{
							EnemyPlane3Location.x = EnemyPlane3Location.x - EnemyPlane3Speed;
							if (EnemyPlane3Location.x < -100)
							{
							EnemyPlane3Location.x = 0 + TheGameWindow_CurrentDimensions.x;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}
						if(move17)
						{
							EnemyPlaneLocation.x = EnemyPlaneLocation.x + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.x > 600)
							{
							EnemyPlaneLocation.x = 0 - EnemyPlaneWidth;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
						}
						if (score >= hiScore)
						{
						hiScore = score;
						} 

						Texture bulletTexture;
						if (!bulletTexture.loadFromFile("Assets/Bullet.png")) //The "Bullet" Image...
						{
							std::cout << "Bullet not loaded" << "\n";
							system("pause");
						}


						
						while(!isSpawnComplete)
						{
							BulletInPlay=false;
						for (int bulletNumber=0;bulletNumber<MAX_NUMBER_BULLETS;bulletNumber++) // for 0 to 50
						{
							bulletArray[bulletNumber].setTexture(bulletTexture);
						}
						/*
						for (int spawnBulletNumber=0; spawnBulletNumber<MAX_NUMBER_BULLETS; spawnBulletNumber++) // for 0 to 50
							{
							// if ballnumber is not part of spawned number print out of scope
							if (spawnBulletNumber >= BulletInPlay) // Setting Fired ball locations with row of next balls to fire.
								{
								bulletArray[BulletInPlay].setPosition(PlaneLocation.x,PlaneLocation.y);
								}					
							}*/
						}//end of !isspawncomplete
						//BulletToBeFired=BulletInPlay; // number of balltobefired after spawn*/
						isSpawnComplete = true;

						sf::Vector2f bulletArrayLocation(PlaneLocation.x,PlaneLocation.y);

						//firedBulletLocation(PlaneLocation.x,PlaneLocation.y)

						if (!BulletInPlay)
						{
							bulletArray[0].setPosition(bulletArrayLocation.x,bulletArrayLocation.y);
							//bulletArrayLocation.y.=bulletArrayLocation.y;
							BulletInPlay=true;
						}
						bulletArrayLocation.y= bulletArrayLocation.y+5;
						bulletArray[0].setPosition(bulletArrayLocation.x,bulletArrayLocation.y)
						//bulletArray[0].setPosition(firedBulletLocation.x, firedBulletLocation.y);

						/*if (MAX_NUMBER_BULLETS > BulletToBeFired) // if not reached the last ball on Max_number_balls
						{
							bulletArray[BulletToBeFired].setPosition(firedBulletLocation.x,firedBulletLocation.y);

							if(spacepressed)
							{
								//Calculate the x and y of the fired ball by taking away the scaling factor multiplied by delta time and ballspeed
								firedBulletLocation.x = (firedBulletLocation.x - (dt.asSeconds() * BulletSpeed));
								firedBulletLocation.y = (firedBulletLocation.y - (dt.asSeconds() * BulletSpeed)) * 1;

								if(firedBulletLocation.y >= TheGameWindow_CurrentDimensions.y)
								{
									bulletArray[BulletToBeFired].setPosition(firedBulletLocation.x, firedBulletLocation.y);

								}
								
							}

							bulletArray[BulletToBeFired].setPosition(firedBulletLocation.x, firedBulletLocation.y);				

						}*/





						if (restart)
						{
							score = 0;
							gamestate = 1;
							c = 0;
							a = 0;
							d = 0;
							showlevel = true;
							move1 = true;
							EnemyPlaneLocation.x = -15;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							EnemyPlane2Location.x = -60;
							EnemyPlane2Location.y = 150;
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
							EnemyPlane3Location.x = 550;
							EnemyPlane3Location.y = 250;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							EnemyPlane4Location.x = 400;
							EnemyPlane4Location.y = 550;
							EnemyPlane4Sprite.setPosition(EnemyPlane4Location.x,EnemyPlane4Location.y);
							move2 = false;
							move3 = false;
							move4 = false;
							move11 = false;
							move12 = false;
							move13 = false;
							move14 = false;
							move15 = false;
							move16 = false;
							move17 = false;
							PlaneLocation.x = 220;
							PlaneLocation.y = 200;
							PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
							ScreenLocation.x = 0;
							ScreenLocation.y = -500;
							ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);
							restart = false;
							std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
							OutputhiScoreLoadFILE << hiScore;
							OutputhiScoreLoadFILE.close();					
						}
				if(gamestate == 10)
				{
				showlevel = false;
				TheGameWindow.clear();
				TheGameWindow.draw(WinScreenImage);
				TheGameWindow.display();
				std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
				OutputhiScoreLoadFILE << hiScore;
				OutputhiScoreLoadFILE.close();					
				}
				std::stringstream hiscorE;
				hiscorE << "High Score: " << hiScore;
				hiScoreText.setString(hiscorE.str());
				std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
				OutputhiScoreLoadFILE << hiScore;
				OutputhiScoreLoadFILE.close();
				std::stringstream scorE;
				scorE << "Score: " << score;
				scoreText.setString(scorE.str());				
				}
				if(showlevel)
				{
				TheGameWindow.clear();
				if(c==0){
					TheGameWindow.draw(ScreenImage);}
				if(c==1){
					TheGameWindow.draw(Screen2Image);}
				for (int bulletNumber=0; bulletNumber<MAX_NUMBER_BULLETS;bulletNumber++)
				{
				TheGameWindow.draw(bulletArray[bulletNumber]);	
				}
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(EnemyPlaneSprite);
				TheGameWindow.draw(EnemyPlane2Sprite);
				TheGameWindow.draw(EnemyPlane3Sprite);
				TheGameWindow.draw(EnemyPlane4Sprite);
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
				std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
				OutputhiScoreLoadFILE << hiScore;
				OutputhiScoreLoadFILE.close();
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
	