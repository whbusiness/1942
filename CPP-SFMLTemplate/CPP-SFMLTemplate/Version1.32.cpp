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

//Variables
int gamestate = 0;
int score = 0;
int hiScore;
int health = 100;
int a;
int o;
int j;
int c;
int d;
//Global Variables
	//Game Window Variables...
	sf::Vector2f TheGameWindow_CurrentDimensions(500,500);
	sf::Vector2f TheGameWindow_PerspectiveDimensions(500,500);
	sf::RenderWindow TheGameWindow(sf::VideoMode(TheGameWindow_CurrentDimensions.x,TheGameWindow_CurrentDimensions.y),"1942",sf::Style::Titlebar); //sf::Style::Fullscreen || sf::Style::Titlebar

	//Creating Textures and Sprites for Methods
	sf::Texture StartTexture, InstructionsScreenTexture, WinTexture, LoseTexture;
	sf::Sprite StartSprite, InstructionsScreenSprite, WinSprite, LoseSprite;
	

//Methods
void StartScreenMethod();
void InstructionsMethod();
void PauseMethod();
void WinMethod();
void LoseMethod();

//Main
int main()
{
	
		TheGameWindow.setMouseCursorVisible(false); //Mouse Cursor is now invisible
//Local Variables
	//Event Variables
	sf::Event event;
	
	/*Textures */ sf::Texture Screen, Bullet, EnemyBullet, Screen2, Plane, EnemyPlane, EnemyPlane2, EnemyPlane3, EnemyPlane4,  CharacterIconTip1, CharacterTip2, CharacterTip3;

	// clock used for timing
	Clock clock;

	//Making a HelpImage1 Sprite
	Sprite HelpImage1;

	//Timer for Tips
	Time HelpTimeTotal;
	float HelpTimeRemaining = 6.0; // Timer starts at 6 seconds


	//Screen Image Variables, Level1 Background
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,-500);

	//Screen Image Variables, Level2 Background
	float Screen2CurrentScaleX = 1.0f,Screen2CurrentScaleY = 1.0f;
	float Screen2Width,Screen2Height;
	sf::Vector2f Screen2Location(0,-500);

	//Plane Image Variables
	float PlaneCurrentScaleX = 0.15f,PlaneCurrentScaleY = 0.15f;
	float PlaneWidth,PlaneHeight;
	sf::Vector2f PlaneLocation(220,200);

	//Enemy Plane 1 Image Variables
	float EnemyPlaneCurrentScaleX = 0.15f,EnemyPlaneCurrentScaleY = 0.15f;
	float EnemyPlaneWidth,EnemyPlaneHeight, EnemyPlaneSpeed = 0.12;
	sf::Vector2f EnemyPlaneLocation(15,50);

	//Enemy Plane 2 Image Variables
	float EnemyPlane2CurrentScaleX = 0.15f,EnemyPlane2CurrentScaleY = 0.15f;
	float EnemyPlane2Width,EnemyPlane2Height, EnemyPlane2Speed = 0.12;
	sf::Vector2f EnemyPlane2Location(-60,150);

	//Enemy Plane 3 Image Variables
	float EnemyPlane3CurrentScaleX = 0.15f,EnemyPlane3CurrentScaleY = 0.15f;
	float EnemyPlane3Width,EnemyPlane3Height, EnemyPlane3Speed = 0.12;
	sf::Vector2f EnemyPlane3Location(550,250);

	//Enemy Plane 4 Image Variables
	float EnemyPlane4CurrentScaleX = 0.15f,EnemyPlane4CurrentScaleY = 0.15f;
	float EnemyPlane4Width,EnemyPlane4Height, EnemyPlane4Speed = 0.12;
	sf::Vector2f EnemyPlane4Location(400,550);

	//Tip 1 Image Variables
	float CharacterIconTip1CurrentScaleX = 0.25f,CharacterIconTip1CurrentScaleY = 0.25f;
	float CharacterIconTip1Width,CharacterIconTip1Height;
	sf::Vector2f CharacterIconTip1Location(0,350);

	//Tip 2 Image Variables
	float CharacterTip2CurrentScaleX = 0.25f,CharacterTip2CurrentScaleY = 0.25f;
	float CharacterTip2Width,CharacterTip2Height;
	sf::Vector2f CharacterTip2Location(0,350);

	//Tip 3 Image Variables
	float CharacterTip3CurrentScaleX = 0.25f,CharacterTip3CurrentScaleY = 0.25f;
	float CharacterTip3Width,CharacterTip3Height;
	sf::Vector2f CharacterTip3Location(0,350);

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
	hiScoreText.setString("HiScore: ");
	hiScoreText.setPosition(320,470);

		//Win Sound
	SoundBuffer WinSound;
	WinSound.loadFromFile("Sounds/WinSound.wav");
	Sound WonSound;
	WonSound.setBuffer(WinSound);

			//Loss Sound
	SoundBuffer LossSound;
	LossSound.loadFromFile("Sounds/LossSound.wav");
	Sound LoseSound;
	LoseSound.setBuffer(LossSound);

	//BulletFired sound
	SoundBuffer BulletFired;
	BulletFired.loadFromFile("Sounds/BulletFired.wav");
	Sound BulletsFired;
	BulletsFired.setBuffer(BulletFired);


	//Loading the hiscore from hiscore.txt in the hiscoredata folder
	std::ifstream hiScoreLoadFILE("hiscoredata/HiScores.txt");
	if (hiScoreLoadFILE.is_open())
	{
		hiScoreLoadFILE >> hiScore;
		hiScoreLoadFILE.close();
	}

	//Level 1 Image Variables
	if (!Screen.loadFromFile("Assets/Screen.png"))
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

	//Level 2 Image Variables
	if (!Screen2.loadFromFile("Assets/Screen2.png"))
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

	//Player (plane) Image Variables
	if (!Plane.loadFromFile("Assets/Plane.png"))
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

	//Enemy Plane 1 Image Variables
	if (!EnemyPlane.loadFromFile("Assets/EnemyPlane.png"))
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

	//Enemy Plane 2 Image Variables
	if (!EnemyPlane2.loadFromFile("Assets/EnemyPlane2.png"))
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

	//Enemy Plane 3 Image Variables
	if (!EnemyPlane3.loadFromFile("Assets/EnemyPlane3.png"))
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

	//Enemy Plane 4 Image Variables
	if (!EnemyPlane4.loadFromFile("Assets/EnemyPlane4.png"))
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

	//Tip 1 Image Variables
	if (!CharacterIconTip1.loadFromFile("Assets/CharacterTip1.png")) //The "CharacterIcon" Image...
		{
		std::cout << "CharacterTip1 has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite CharacterIconTip1Image(CharacterIconTip1);
	CharacterIconTip1Image.setScale(sf::Vector2f(CharacterIconTip1CurrentScaleX,CharacterIconTip1CurrentScaleY));
	CharacterIconTip1Width = CharacterIconTip1Image.getGlobalBounds().width;
	CharacterIconTip1Height = CharacterIconTip1Image.getGlobalBounds().height;
	
	CharacterIconTip1Image.setPosition(CharacterIconTip1Location.x,CharacterIconTip1Location.y);

	//Tip 2 Image Variables
	if (!CharacterTip2.loadFromFile("Assets/CharacterTip2.png")) //The "CharacterIcon" Image...
		{
		std::cout << "CharacterTip2 has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite CharacterTip2Image(CharacterTip2);
	CharacterTip2Image.setScale(sf::Vector2f(CharacterTip2CurrentScaleX,CharacterTip2CurrentScaleY));
	CharacterTip2Width = CharacterTip2Image.getGlobalBounds().width;
	CharacterTip2Height = CharacterTip2Image.getGlobalBounds().height;
	
	CharacterTip2Image.setPosition(CharacterTip2Location.x,CharacterTip2Location.y);

	//Tip 3 Image Variables
	if (!CharacterTip3.loadFromFile("Assets/CharacterTip3.png")) //The "CharacterIcon" Image...
		{
		std::cout << "CharacterTip3 has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite CharacterTip3Image(CharacterTip3);
	CharacterTip3Image.setScale(sf::Vector2f(CharacterTip3CurrentScaleX,CharacterTip3CurrentScaleY));
	CharacterTip3Width = CharacterTip3Image.getGlobalBounds().width;
	CharacterTip3Height = CharacterTip3Image.getGlobalBounds().height;
	
	CharacterTip3Image.setPosition(CharacterTip3Location.x,CharacterTip3Location.y);

	
	//Bullet Image Variables
	float BulletCurrentScaleX = 0.15f,BulletCurrentScaleY = 0.15f;
	float BulletWidth,BulletHeight;
	sf::Vector2f BulletLocation(PlaneLocation.x+25,PlaneLocation.y-20);

	//Bullet Image Variables
	if (!Bullet.loadFromFile("Assets/Bullet.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite BulletSprite(Bullet);
	BulletSprite.setScale(sf::Vector2f(BulletCurrentScaleX,BulletCurrentScaleY));
	BulletWidth = BulletSprite.getGlobalBounds().width;
	BulletHeight = BulletSprite.getGlobalBounds().height;

		
	BulletSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

	//Enemy Bullet Image Variables
	float EnemyBulletCurrentScaleX = 0.15f,EnemyBulletCurrentScaleY = 0.15f;
	float EnemyBulletWidth,EnemyBulletHeight;
	sf::Vector2f EnemyBulletLocation(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

	//Enemy Bullet Image Variables
	if (!EnemyBullet.loadFromFile("Assets/EnemyBullet.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Plane has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyBulletSprite(EnemyBullet);
	EnemyBulletSprite.setScale(sf::Vector2f(EnemyBulletCurrentScaleX,EnemyBulletCurrentScaleY));
	EnemyBulletWidth = EnemyBulletSprite.getGlobalBounds().width;
	EnemyBulletHeight = EnemyBulletSprite.getGlobalBounds().height;

		
	EnemyBulletSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);


	//Rotate enemy plane so that it is correctly angled in the direction it is travelling
	EnemyPlaneSprite.setRotation(90);
	EnemyPlane2Sprite.setRotation(90);
	EnemyPlane3Sprite.setRotation(270);

	//Boolean functions for later use
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
	bool DisplayTip = false;
	bool TipLoop = false;

	//When game is first run show the start screen
	if (gamestate == 0)
	{
	TheGameWindow.clear();
	StartScreenMethod();
	TheGameWindow.display();
	}		

	int L = 1;
	int K = 1;

	//Setting the bullet and enemy bullet to the correct plane locations.
	BulletSprite.setPosition(PlaneLocation.x+25,PlaneLocation.y-20);
	EnemyBulletSprite.setPosition(EnemyPlaneLocation.x+25,EnemyPlaneLocation.y-20);

//When the game is running
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
							if(gamestate != 3) //If you haven't lost you can press enter to make gamestate 1.
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
						if(gamestate == 1 || gamestate == 10 || gamestate == 3)
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						{
							showlevel = true;
							gamestate = 1;
							restart = true;	
						}
						}
						if(gamestate == 1) // If game is playing character can move with wasd or arrow keys
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
						{
							PlaneLocation.y = PlaneLocation.y - 7;
							if (PlaneLocation.y < -100)
								{
									PlaneLocation.y = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);							
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
						{
							DisplayTip = true;
							TipLoop = true;
							HelpTimeRemaining = 3.0;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							PlaneLocation.x = PlaneLocation.x - 7;
							if (PlaneLocation.x < -100)
								{
									PlaneLocation.x = 600 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							PlaneLocation.y = PlaneLocation.y + 7;
							if (PlaneLocation.y > 500)
								{
									PlaneLocation.y = -20 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(L!=8)//When fired L is 8, when bullet goes off screen L is 1 so you can fire again
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//Fire bullet when space is pressed
						{
							cout<< "SHOOT";
							L = 8;
							BulletLocation.x = PlaneLocation.x+25;
							BulletLocation.y = PlaneLocation.y-20;
							BulletsFired.play();
						}
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
						{
							PlaneLocation.x = PlaneLocation.x + 7;
							if (PlaneLocation.x > TheGameWindow_CurrentDimensions.x)
								{
									PlaneLocation.x = 0 - PlaneWidth;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))//If I is pressed show instructions screen
						{
							gamestate = 5;
						}
						PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))//If P is pressed pause game and show Pause Text
						{
							gamestate = 6;
						}
						}
					}
				}
				if(gamestate == 1)//If game is playing
				{
					showlevel = true;

					if(L!=8)//If you are not shooting bullet is off screen
					{
						BulletSprite.setPosition(-100,-100);
					}
					if(K!=6)//If npc are not shooting bullet is off screen
					{
						EnemyBulletSprite.setPosition(-180,-180);
					}	

					//Setting Enemy Firing Points

					if(EnemyPlaneLocation.x>100)
					{
						if(EnemyPlaneLocation.x<100.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlaneLocation.x;
						EnemyBulletLocation.y = EnemyPlaneLocation.y;
						BulletsFired.play();
					}
					}

					if(EnemyPlaneLocation.x>250)
					{
						if(EnemyPlaneLocation.x<250.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlaneLocation.x;
						EnemyBulletLocation.y = EnemyPlaneLocation.y;
						BulletsFired.play();						
					}
					}


					if(EnemyPlaneLocation.x>400)
					{
						if(EnemyPlaneLocation.x<400.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlaneLocation.x;
						EnemyBulletLocation.y = EnemyPlaneLocation.y;
						BulletsFired.play();						
					}
					}

					if(EnemyPlane2Location.x>100)
					{
						if(EnemyPlane2Location.x<100.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane2Location.x;
						EnemyBulletLocation.y = EnemyPlane2Location.y;
						BulletsFired.play();						
					}
					}

					if(EnemyPlane2Location.x>250)
					{
						if(EnemyPlane2Location.x<250.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane2Location.x;
						EnemyBulletLocation.y = EnemyPlane2Location.y;
						BulletsFired.play();						
					}
					}


					if(EnemyPlane2Location.x>400)
					{
						if(EnemyPlane2Location.x<400.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane2Location.x;
						EnemyBulletLocation.y = EnemyPlane2Location.y;
						BulletsFired.play();
					}
					}
					if(EnemyPlane3Location.x>100)
					{
						if(EnemyPlane3Location.x<100.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane3Location.x;
						EnemyBulletLocation.y = EnemyPlane3Location.y;
						BulletsFired.play();
					}
					}

					if(EnemyPlane3Location.x>250)
					{
						if(EnemyPlane3Location.x<250.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane3Location.x;
						EnemyBulletLocation.y = EnemyPlane3Location.y;
						BulletsFired.play();
					}
					}


					if(EnemyPlane3Location.x>400)
					{
						if(EnemyPlane3Location.x<400.1)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane3Location.x;
						EnemyBulletLocation.y = EnemyPlane3Location.y;
						BulletsFired.play();
					}
					}
					if(EnemyPlane4Location.y>100)
					{
						if(EnemyPlane4Location.y<100.1)
						{						
						K=12;
						EnemyBulletLocation.x = EnemyPlane4Location.x;
						EnemyBulletLocation.y = EnemyPlane4Location.y;
						BulletsFired.play();
					}
					}

					if(EnemyPlane4Location.y>250)
					{
						if(EnemyPlane4Location.y<250.1)
						{						
						K=12;
						EnemyBulletLocation.x = EnemyPlane4Location.x;
						EnemyBulletLocation.y = EnemyPlane4Location.y;
						BulletsFired.play();
					}
					}


					if(EnemyPlane4Location.y>400)
					{
						if(EnemyPlane4Location.y<400.1)
						{						
						K=12;
						EnemyBulletLocation.x = EnemyPlane4Location.x;
						EnemyBulletLocation.y = EnemyPlane4Location.y;
						BulletsFired.play();
					}
					}

					if(move1)
					{
					if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneSprite.setPosition(-11000, -11000);
						move2 = true;
						score = score+100;
					}
					}
					if(move2)
					{
					if((BulletSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
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
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
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
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
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
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
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
							if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
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
							if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
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
							if((BulletSprite.getGlobalBounds().intersects(EnemyPlane4Sprite.getGlobalBounds())))
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
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
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
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
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

						//ADD CODE FOR BULLETS

						if(L==8)
						{
							//BulletLocation.x = PlaneLocation.x;
							//BulletLocation.y = PlaneLocation.y;
							if(BulletLocation.y < TheGameWindow_CurrentDimensions.y)
							{
								BulletLocation.y = BulletLocation.y-0.6;
							}
							if(BulletLocation.y < -65)
							{
								L = 1;
								BulletSprite.setPosition(PlaneLocation.x+25,PlaneLocation.y-20);
								BulletLocation.x = PlaneLocation.x+25;
								BulletLocation.y = PlaneLocation.y-20;
							}
							BulletSprite.setPosition(BulletLocation.x,BulletLocation.y);
						}

						if(K==6)
						{
							//BulletLocation.x = PlaneLocation.x;
							//BulletLocation.y = PlaneLocation.y;
							if(EnemyBulletLocation.y < 500)
							{
								EnemyBulletLocation.y = EnemyBulletLocation.y+0.6;
							}
							if(EnemyBulletLocation.y > 500)
							{
								K = 1;
								EnemyBulletSprite.setPosition(EnemyPlaneLocation.x+25,EnemyPlaneLocation.y-20);
								EnemyBulletLocation.x = EnemyPlaneLocation.x+25;
								EnemyBulletLocation.y = EnemyPlaneLocation.y-20;
							}
							EnemyBulletSprite.setPosition(EnemyBulletLocation.x,EnemyBulletLocation.y);
						}

						if(K==12)
						{
							EnemyBulletSprite.setRotation(90);
							//BulletLocation.x = PlaneLocation.x;
							//BulletLocation.y = PlaneLocation.y;
							if(EnemyBulletLocation.x < 500)
							{
								EnemyBulletLocation.x = EnemyBulletLocation.x-0.6;
							}
							if(EnemyBulletLocation.x < 0)
							{
								K = 1;
								EnemyBulletSprite.setRotation(0);
								EnemyBulletSprite.setPosition(EnemyPlaneLocation.x+25,EnemyPlaneLocation.y-20);
								EnemyBulletLocation.x = EnemyPlaneLocation.x+25;
								EnemyBulletLocation.y = EnemyPlaneLocation.y-20;
							}
							EnemyBulletSprite.setPosition(EnemyBulletLocation.x,EnemyBulletLocation.y);
						}

						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						if((PlaneSprite.getGlobalBounds().intersects(EnemyPlane4Sprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						if((EnemyBulletSprite.getGlobalBounds().intersects(PlaneSprite.getGlobalBounds())))
						{
							gamestate = 3;
						}

						if (score >= hiScore)
						{
						hiScore = score;
						} 	

						if (restart)
						{
							K = 1;
							EnemyBulletSprite.setRotation(0);
							score = 0;
							gamestate = 1;
							c = 0;
							a = 0;
							d = 0;
							showlevel = true;
							move1 = true;
							EnemyBulletLocation.x = -100;
							EnemyBulletLocation.y = -100;
							BulletLocation.x = -180;
							BulletLocation.y = -180;
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
				WonSound.play();
				showlevel = false;
				TheGameWindow.clear();
				WinMethod();
				TheGameWindow.display();
				std::ofstream OutputhiScoreLoadFILE("hiscoredata/HiScores.txt");
				OutputhiScoreLoadFILE << hiScore;
				OutputhiScoreLoadFILE.close();					
				}
				if(gamestate == 3)
				{
				LoseSound.play();
				showlevel = false;
				TheGameWindow.clear();							
				LoseMethod();
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
				Time dt = clock.restart();
				TheGameWindow.clear();
				if(c==0)
				{
					TheGameWindow.draw(ScreenImage);
				}
				if(c==1)
				{
					TheGameWindow.draw(Screen2Image);
				}
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(BulletSprite);
				TheGameWindow.draw(EnemyBulletSprite);
				TheGameWindow.draw(EnemyPlaneSprite);
				TheGameWindow.draw(EnemyPlane2Sprite);
				TheGameWindow.draw(EnemyPlane3Sprite);
				TheGameWindow.draw(EnemyPlane4Sprite);
			if (DisplayTip)
			{
				HelpTimeRemaining -= dt.asSeconds();
				if (HelpTimeRemaining <= 0.0)
				{
					cout << "TIME IS 0";
					DisplayTip = false;
				}
				if (HelpTimeRemaining >0.0)
				{
					if(TipLoop)
					{
						int Tips;
						Tips = ((rand() % 3));
						switch (Tips)
						{
						case 0: 
							HelpImage1 = CharacterIconTip1Image;
							break;
						case 1: 
							HelpImage1 = CharacterTip2Image;
							break;
						case 2: 
							HelpImage1 = CharacterTip3Image;
							break;
						}
						TipLoop = false;
				}
					TheGameWindow.draw(HelpImage1);
			}	
		}
				TheGameWindow.display();	
				}
				if(gamestate==6)
				{
					showlevel = false;
					PauseMethod();
					TheGameWindow.display();
				}
				if (gamestate == 5)
				{
				showlevel = false;
				TheGameWindow.clear();
				InstructionsMethod();
				TheGameWindow.display();
				}
			}
			return 0;
		}

void StartScreenMethod()
{
	if (!StartTexture.loadFromFile("Assets/StartScreen.png")) //The "Background" Image...
		{
		cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
		system("pause");
		}
	StartSprite.setTexture(StartTexture);

	TheGameWindow.draw(StartSprite);
}


void InstructionsMethod()
{
	if (!InstructionsScreenTexture.loadFromFile("Assets/Instructions.png")) //The "Background" Image...
		{
		cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
		system("pause");
		}
	InstructionsScreenSprite.setTexture(InstructionsScreenTexture);

	TheGameWindow.draw(InstructionsScreenSprite);
}

void PauseMethod()
{
	
	//Font Variables
	Font font;
	font.loadFromFile("Assets/BAUHS93.ttf");

	
	Text PausedText;
	PausedText.setFont(font);
	PausedText.setCharacterSize(80);
	PausedText.setFillColor(Color::Black);
	PausedText.setString("PAUSED");
	PausedText.setPosition(120,180);

	TheGameWindow.draw(PausedText);

}

void WinMethod()
{
	if (!WinTexture.loadFromFile("Assets/WinScreen.png")) //The "Background" Image...
		{
		cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
		system("pause");
		}
	WinSprite.setTexture(WinTexture);

	TheGameWindow.draw(WinSprite);
}

void LoseMethod()
{
	if (!LoseTexture.loadFromFile("Assets/LoseScreen.png")) //The "Background" Image...
		{
		cout << "Error 1: Loading The Game Image(s) Failed. Make Sure ALL Images Are 8-bit-RGBA Images..." << "\n";
		system("pause");
		}
	LoseSprite.setTexture(LoseTexture);

	TheGameWindow.draw(LoseSprite);
}



