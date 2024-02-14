//1942 Game Assignment, made by William Hunt

//Header Files
#include <sstream>
#include <iostream>//input output header file
#include <SFML/Graphics.hpp>//graphics header file
#include <fstream> //file input/output
#include <SFML/Audio.hpp>//audio header file

/*
gamestate 0 = Original State when game is started
gamestate 1 = Playing state
gamestate 3 = Lose state
gamestate 5 = Instructions state
gamestate 6 = Pause state
gamestate 10 = Win State
*/

//Namespaces'
using namespace std;
using namespace sf;

//Variables
int gamestate = 0;
int score = 0;
int hiScore;
int a; // used in npc movement
int c;// used in background scrolling
int d; // used in npc movement
//Global Variables
	//Game Window Variables...
	sf::Vector2f TheGameWindow_CurrentDimensions(500,500);
	sf::Vector2f TheGameWindow_PerspectiveDimensions(500,500);
	sf::RenderWindow TheGameWindow(sf::VideoMode(TheGameWindow_CurrentDimensions.x,TheGameWindow_CurrentDimensions.y),"1942",sf::Style::Titlebar); //sf::Style::Fullscreen || sf::Style::Titlebar, Fullscreen is not suitable

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
	
	/*Textures */ sf::Texture Screen, Bullet, Bullet2, EnemyBullet, EnemyBullet2, Screen2, Plane, EnemyPlane, EnemyPlane2, EnemyPlane3, EnemyPlane4,  CharacterIconTip1, CharacterTip2, CharacterTip3;

	// clock used for timing
	Clock clock;

	//Making a HelpImage1 Sprite
	Sprite HelpImage1;

	//Timer for Tips
	Time HelpTimeTotal;
	float HelpTimeRemaining = 6.0; // Timer starts at 6 seconds


	//Level 1 background Image Variables, Level1 Background
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,-500);

	//Level 2 background Image Variables, Level2 Background
	float Screen2CurrentScaleX = 1.0f,Screen2CurrentScaleY = 1.0f;
	float Screen2Width,Screen2Height;
	sf::Vector2f Screen2Location(0,-500);

	//Plane Image Variables
	float PlaneCurrentScaleX = 0.15f,PlaneCurrentScaleY = 0.15f;
	float PlaneWidth,PlaneHeight;
	sf::Vector2f PlaneLocation(220,200);

	//Enemy Plane 1 Image Variables
	float EnemyPlaneCurrentScaleX = 0.15f,EnemyPlaneCurrentScaleY = 0.15f;
	float EnemyPlaneWidth,EnemyPlaneHeight, EnemyPlaneSpeed = 0.5;
	sf::Vector2f EnemyPlaneLocation(40,50);

	//Enemy Plane 2 Image Variables
	float EnemyPlane2CurrentScaleX = 0.15f,EnemyPlane2CurrentScaleY = 0.15f;
	float EnemyPlane2Width,EnemyPlane2Height, EnemyPlane2Speed = 0.5;
	sf::Vector2f EnemyPlane2Location(40,150);

	//Enemy Plane 3 Image Variables
	float EnemyPlane3CurrentScaleX = 0.15f,EnemyPlane3CurrentScaleY = 0.15f;
	float EnemyPlane3Width,EnemyPlane3Height, EnemyPlane3Speed = 0.5;
	sf::Vector2f EnemyPlane3Location(490,250);

	//Enemy Plane 4 Image Variables
	float EnemyPlane4CurrentScaleX = 0.15f,EnemyPlane4CurrentScaleY = 0.15f;
	float EnemyPlane4Width,EnemyPlane4Height, EnemyPlane4Speed = 0.5;
	sf::Vector2f EnemyPlane4Location(360,540);

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
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(Color::White);
	scoreText.setString("Score: ");
	scoreText.setPosition(60, 480);

	//HiScore Variables
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(18);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setString("HiScore: ");
	hiScoreText.setPosition(300,480);

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
		std::cout << "Screen 1 has not loaded" << "\n";
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
		std::cout << "Screen 2 has not loaded" << "\n";
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
		std::cout << "Enemy Plane 1 has not loaded" << "\n";
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
		std::cout << "Enemy Plane 2 has not loaded" << "\n";
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
		std::cout << "Enemy Plane 3 has not loaded" << "\n";
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
		std::cout << "Enemy Plane 4 has not loaded" << "\n";
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
		std::cout << "Bullet has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite BulletSprite(Bullet);
	BulletSprite.setScale(sf::Vector2f(BulletCurrentScaleX,BulletCurrentScaleY));
	BulletWidth = BulletSprite.getGlobalBounds().width;
	BulletHeight = BulletSprite.getGlobalBounds().height;

		
	BulletSprite.setPosition(PlaneLocation.x,PlaneLocation.y);

		//Bullet Image Variables
	float Bullet2CurrentScaleX = 0.15f,Bullet2CurrentScaleY = 0.15f;
	float Bullet2Width,Bullet2Height;
	sf::Vector2f Bullet2Location(PlaneLocation.x+25,PlaneLocation.y-20);

	//Bullet Image Variables
	if (!Bullet2.loadFromFile("Assets/Bullet2.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Bullet has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite Bullet2Sprite(Bullet2);
	Bullet2Sprite.setScale(sf::Vector2f(Bullet2CurrentScaleX,Bullet2CurrentScaleY));
	Bullet2Width = Bullet2Sprite.getGlobalBounds().width;
	Bullet2Height = Bullet2Sprite.getGlobalBounds().height;

		
	Bullet2Sprite.setPosition(PlaneLocation.x,PlaneLocation.y);

	//Enemy Bullet Image Variables
	float EnemyBulletCurrentScaleX = 0.15f,EnemyBulletCurrentScaleY = 0.15f;
	float EnemyBulletWidth,EnemyBulletHeight;
	sf::Vector2f EnemyBulletLocation(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

	//Enemy Bullet Image Variables
	if (!EnemyBullet.loadFromFile("Assets/EnemyBullet.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Bullet has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyBulletSprite(EnemyBullet);
	EnemyBulletSprite.setScale(sf::Vector2f(EnemyBulletCurrentScaleX,EnemyBulletCurrentScaleY));
	EnemyBulletWidth = EnemyBulletSprite.getGlobalBounds().width;
	EnemyBulletHeight = EnemyBulletSprite.getGlobalBounds().height;

		
	EnemyBulletSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);

		//Enemy Bullet Image Variables
	float EnemyBullet2CurrentScaleX = 0.15f,EnemyBullet2CurrentScaleY = 0.15f;
	float EnemyBullet2Width,EnemyBullet2Height;
	sf::Vector2f EnemyBullet2Location(EnemyPlane3Location.x,EnemyPlane3Location.y);

	//Enemy Bullet Image Variables
	if (!EnemyBullet2.loadFromFile("Assets/EnemyBullet2.png")) //The "Enemy Plane" Image...
		{
		std::cout << "Enemy Bullet has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite EnemyBullet2Sprite(EnemyBullet2);
	EnemyBullet2Sprite.setScale(sf::Vector2f(EnemyBullet2CurrentScaleX,EnemyBullet2CurrentScaleY));
	EnemyBullet2Width = EnemyBullet2Sprite.getGlobalBounds().width;
	EnemyBullet2Height = EnemyBullet2Sprite.getGlobalBounds().height;

		
	EnemyBullet2Sprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);


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
	bool dontshowplanes;
	bool dontshowplanes2;
	bool dontshowplanes3;
	bool dontshowplanes4;
	bool cantmouseclick = false;


	//When game is first run show the start screen
	if (gamestate == 0)
	{
	TheGameWindow.clear();
	StartScreenMethod();
	TheGameWindow.display();
	}		

	//L is your bullet, K is enemy bullets, U is enemybullet2
	int L = 1;
	int K = 1;
	int U = 1;
	int T = 1;

	//Setting the bullet and enemy bullet to the correct plane locations.
	BulletSprite.setPosition(PlaneLocation.x+25,PlaneLocation.y-20);
	EnemyBulletSprite.setPosition(EnemyPlaneLocation.x+25,EnemyPlaneLocation.y-20);

//When the game is running
while (TheGameWindow.isOpen()) 
			{
				TheGameWindow.setFramerateLimit(120);
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
						if(gamestate == 1 || gamestate == 10 || gamestate == 3)//If game is playing, you won, or you lost
						{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))//restart game
						{
							showlevel = true;
							gamestate = 1;
							restart = true;	
						}
						}
						if(gamestate == 1) // If game is playing character can move with wasd or arrow keys
						{
							if(T!=8)
							{
							if(L==8)
							{
								if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//Fire bullet when space is pressed
									{
										cout<< "SHOOT";
										T = 8;
										Bullet2Location.x = PlaneLocation.x+25;
										Bullet2Location.y = PlaneLocation.y-20;
										BulletsFired.play();
									}
							}
							}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
						{
							if(PlaneLocation.y>0)
							{
							PlaneLocation.y = PlaneLocation.y - 5;
							}				
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
						{
							DisplayTip = true;
							TipLoop = true;
							HelpTimeRemaining = 3.0;
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) 
						{
							PlaneLocation.x = PlaneLocation.x - 5;
							if (PlaneLocation.x < 41)
								{
									PlaneLocation.x = 380;
								}
								PlaneSprite.setPosition(PlaneLocation.x,PlaneLocation.y);
						}
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							if(PlaneLocation.y<450)
							{
							PlaneLocation.y = PlaneLocation.y + 5;
							}
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
							PlaneLocation.x = PlaneLocation.x + 5;
							if (PlaneLocation.x > 380)
								{
									PlaneLocation.x = 40;
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
					if(!cantmouseclick)
					{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					L=8;
					cout << L;
					BulletLocation.x = PlaneLocation.x+25;
					BulletLocation.y = PlaneLocation.y-20;
					BulletsFired.play();
				}
					}
				}
				if(gamestate == 1)//If game is playing
				{
					dontshowplanes = false;
					dontshowplanes2 = false;
					dontshowplanes3 = false;
					dontshowplanes4 = false;
					showlevel = true;//Show level graphics

					if(L==1)//If you are not shooting bullet is off screen
					{
						BulletLocation.x = 800;
						BulletLocation.y = 800;
						BulletSprite.setPosition(BulletLocation.x,BulletLocation.y);
						cantmouseclick = false;
					}
					if(T==1)//If you are not shooting bullet is off screen
					{
						Bullet2Location.x = 800;
						Bullet2Location.y = 800;
						Bullet2Sprite.setPosition(Bullet2Location.x,Bullet2Location.y);
						cantmouseclick = false;
					}
					if(K==1)//If npc are not shooting bullet is off screen
					{
						EnemyBulletLocation.x = 800;
						EnemyBulletLocation.y = 800;
						EnemyBulletSprite.setPosition(EnemyBulletLocation.x,EnemyBulletLocation.y);
					}
					if(U==1)//If npc are not shooting bullet is off screen
					{
						EnemyBullet2Location.x = 900;
						EnemyBullet2Location.y = 900;
						EnemyBullet2Sprite.setPosition(EnemyBullet2Location.x,EnemyBullet2Location.y);
					}	
					//Setting Enemy Firing Points

					if(EnemyPlaneLocation.x<94)
					{
						dontshowplanes = false;
					}
					if(EnemyPlaneLocation.x>95)
					{
						dontshowplanes = true;
					}
					if(EnemyPlaneLocation.x>450)
					{
						dontshowplanes = false;
					}
					if(EnemyPlane2Location.x<94)
					{
						dontshowplanes2 = false;
					}
					if(EnemyPlane2Location.x>95)
					{
						dontshowplanes2 = true;
					}
					if(EnemyPlane2Location.x>450)
					{
						dontshowplanes2 = false;
					}
					if(EnemyPlane3Location.x<420)
					{
						dontshowplanes3 = true;
					}
					if(EnemyPlane3Location.x<101)
					{
						dontshowplanes3 = false;
					}
					if(EnemyPlane3Location.x>421)
					{
						dontshowplanes3 = false;
					}
					if(EnemyPlane4Location.y<500)
					{
						dontshowplanes4 = true;
					}
					if(EnemyPlane4Location.x<0)
					{
						dontshowplanes4 = false;
					}

					if(EnemyPlaneLocation.x>150)
					{
						if(EnemyPlaneLocation.x<151)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlaneLocation.x;
						EnemyBulletLocation.y = EnemyPlaneLocation.y;
						BulletsFired.play();
					}
					}
					
					if(EnemyPlaneLocation.x>330)
					{
						if(EnemyPlaneLocation.x<331)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlaneLocation.x;
						EnemyBulletLocation.y = EnemyPlaneLocation.y;
						BulletsFired.play();						
					}
					}

					if(EnemyPlane2Location.x>150)
					{
						if(EnemyPlane2Location.x<151)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane2Location.x;
						EnemyBulletLocation.y = EnemyPlane2Location.y;
						BulletsFired.play();
					}
					}
					
					if(EnemyPlane2Location.x>330)
					{
						if(EnemyPlane2Location.x<331)
						{						
						K=6;
						EnemyBulletLocation.x = EnemyPlane2Location.x;
						EnemyBulletLocation.y = EnemyPlane2Location.y;
						BulletsFired.play();						
					}
					}
					if(EnemyPlane3Location.x>180)
					{
						if(EnemyPlane3Location.x<181)
						{	
						U=6;
						EnemyBullet2Location.x = EnemyPlane3Location.x;
						EnemyBullet2Location.y = EnemyPlane3Location.y;
						BulletsFired.play();
					}
					}


					if(EnemyPlane3Location.x>340)
					{
						if(EnemyPlane3Location.x<341)
						{		
						U=6;
						EnemyBullet2Location.x = EnemyPlane3Location.x;
						EnemyBullet2Location.y = EnemyPlane3Location.y;
						BulletsFired.play();
					}
					}
					if(EnemyPlane4Location.y>150)
					{
						if(EnemyPlane4Location.y<151)
						{						
						K=12;
						EnemyBulletLocation.x = EnemyPlane4Location.x;
						EnemyBulletLocation.y = EnemyPlane4Location.y;
						BulletsFired.play();
					}
					}
					if(EnemyPlane4Location.y>320)
					{
						if(EnemyPlane4Location.y<321)
						{	
							K=12;
							EnemyBulletLocation.x = EnemyPlane4Location.x;
							EnemyBulletLocation.y = EnemyPlane4Location.y;
						}
					}

					if(EnemyPlane4Location.y>150)
					{
						if(EnemyPlane4Location.y<151)
						{						
						U=12;
						EnemyBullet2Location.x = EnemyPlane4Location.x+20;
						EnemyBullet2Location.y = EnemyPlane4Location.y;
						BulletsFired.play();
					}
					}

					//Enemy movement code, If bullet hits the plane within that movement go on to the next movement.

					if(move1)
					{
					if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneSprite.setPosition(-11000, -11000);
						BulletLocation.x=700;
						BulletLocation.y=700;
						L=1;
						move2 = true;
						score = score+100;
					}
					if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneSprite.setPosition(-11000, -11000);
						Bullet2Location.x=700;
						Bullet2Location.y=700;
						T=1;
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
						BulletLocation.x=700;
						BulletLocation.y=700;
						L=1;
						move2 = false;
						move3 = true;
						move16 = true;
						score = score+100;
					}
					if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
					{
						cout << "Hit";
						move1 = false;
						EnemyPlaneLocation.x = -60;
						EnemyPlaneLocation.y = 50;
						EnemyPlane2Location.x = -60;
						EnemyPlane2Location.y = 150;
						EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
						Bullet2Location.x=700;
						Bullet2Location.y=700;
						T=1;
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
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							a++;
							score = score+100;
							move16 = false;							
						}
						if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane2Sprite.getGlobalBounds())))
						{
							EnemyPlane2Location.x = -60;
							EnemyPlane2Location.y = 150;
							EnemyPlane2Sprite.setPosition(-60,150);
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
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
							a++;
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							score = score+100;
							move3 = false;							
						}
						if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(-60,50);
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							a++;
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
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
							move4=true;
						}
					if (move4)
					{
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;
							EnemyPlane3Location.y = 150;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							score = score+100;
							move4 = false;
							move11 = true;
							c = 1;
						}
						if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;
							EnemyPlane3Location.y = 150;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
							score = score+100;
							move4 = false;
							move11 = true;
							c = 1;
						}
					}						
						if (move1)
						{
							EnemyPlaneLocation.x = EnemyPlaneLocation.x + EnemyPlaneSpeed;
							if (EnemyPlaneLocation.x > 520)
							{
							EnemyPlaneLocation.x = 40;
							}
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
						}
						if (move2)
						{
							EnemyPlane2Location.x = EnemyPlane2Location.x + EnemyPlane2Speed;
							if (EnemyPlane2Location.x > 520)
							{
							EnemyPlane2Location.x = 40;
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
							EnemyPlane3Location.x = EnemyPlane3Location.x - EnemyPlane3Speed;
							if (EnemyPlane3Location.x < -100)
							{
							EnemyPlane3Location.x = 0 + TheGameWindow_CurrentDimensions.x;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}

						if (move11)
						{
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
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							move12 = true;
							}
							if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
							{
							score = score+100;
							move10 = false;
							move11 = false;
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
							move12 = true;
							}
						}
						if(move12)
						{
							if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
							{
								EnemyPlane3Location.x = 550;
								EnemyPlane3Location.y = 250;
								EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
								BulletLocation.x=700;
								BulletLocation.y=700;
								L=1;
								move12 = false;
								move13 = true;
								score = score+100;
							}
							if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
							{
								EnemyPlane3Location.x = 550;
								EnemyPlane3Location.y = 250;
								EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
								Bullet2Location.x=700;
								Bullet2Location.y=700;
								T=1;
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
								BulletLocation.x=700;
								BulletLocation.y=700;
								L=1;
								move13=false;
								move14 = true;
								move17 = true;
								score = score+100;
							}
							if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane4Sprite.getGlobalBounds())))
							{
								EnemyPlane4Location.x = 400;
								EnemyPlane4Location.y = 550;
								EnemyPlane4Sprite.setPosition(EnemyPlane4Location.x,EnemyPlane4Location.y);
								Bullet2Location.x=700;
								Bullet2Location.y=700;
								T=1;
								move13=false;
								move14 = true;
								move17 = true;
								score = score+100;
							}
						}
						if (move14)
						{
						if((BulletSprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;;
							EnemyPlane3Location.y = 250;
							EnemyPlane3Sprite.setPosition(550,250);
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							d++;
							score = score+100;
							move14 = false;
						}
						if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlane3Sprite.getGlobalBounds())))
						{
							EnemyPlane3Location.x = 550;;
							EnemyPlane3Location.y = 250;
							EnemyPlane3Sprite.setPosition(550,250);
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
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
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							d++;
							score = score+100;
							move17 = false;
						}
						if((Bullet2Sprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
						{
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(-60,50);
							Bullet2Location.x=700;
							Bullet2Location.y=700;
							T=1;
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

						//Level 1 Background scrolling code
						if(c == 0)
						{
						if(ScreenLocation.y < 0)
							{
								ScreenLocation.y = ScreenLocation.y+0.15;
							}
						if(ScreenLocation.y > 0)
							{

								ScreenLocation.y = -500;
							}
						ScreenImage.setPosition(ScreenLocation.x,ScreenLocation.y);
						}
						//Level 2 Background scrolling code
						if(c == 1)
						{
						if(Screen2Location.y < 0)
							{
								Screen2Location.y = Screen2Location.y+0.15;
							}
						if(Screen2Location.y > 0)
							{

								Screen2Location.y = -500;
							}
						Screen2Image.setPosition(Screen2Location.x,Screen2Location.y);
						}

						if(L==8)//When space is pressed
						{
							
							if(BulletLocation.y < TheGameWindow_CurrentDimensions.y)
							{
								cantmouseclick = true;
								BulletLocation.y = BulletLocation.y-2.5; // Move the bullet up gradually whilst less than 500y
							}
							if(BulletLocation.y < -65)//If fully off screen reset bullet position off screen and allow user to shoot again
							{
								L = 1;
								cantmouseclick = false;
							}
							BulletSprite.setPosition(BulletLocation.x,BulletLocation.y);
						}

						if(T==8)//When space is pressed
						{
							
							if(Bullet2Location.y < TheGameWindow_CurrentDimensions.y)
							{
								cantmouseclick = true;
								Bullet2Location.y = Bullet2Location.y-2.5; // Move the bullet up gradually whilst less than 500y
							}
							if(Bullet2Location.y < -65)//If fully off screen reset bullet position off screen and allow user to shoot again
							{
								T = 1;
								cantmouseclick = false;
							}
							Bullet2Sprite.setPosition(Bullet2Location.x,Bullet2Location.y);
						}

						if(K==6)//Enemy shooting function
						{
							EnemyBulletSprite.setRotation(0);
							if(EnemyBulletLocation.y < 600)
							{
								EnemyBulletLocation.y = EnemyBulletLocation.y+2; //Move enemy bullet up gradually whilst less than 500y
							}
							if(EnemyBulletLocation.y > 500) // reset enemy bullet location
							{
								K = 1;
							}
							EnemyBulletSprite.setPosition(EnemyBulletLocation.x,EnemyBulletLocation.y);
						}

						if(K==12)//Enemy Shooting Function for bullet on x axis
						{
							EnemyBulletSprite.setRotation(90);
							if(EnemyBulletLocation.x < 600)
							{
								EnemyBulletLocation.x = EnemyBulletLocation.x-2; // Move enemy bullet across the screen whilst its less than 500x
							}
							if(EnemyBulletLocation.x < 0) // reset enemy bullet location
							{
								K = 1;
							}
							EnemyBulletSprite.setPosition(EnemyBulletLocation.x,EnemyBulletLocation.y);
						}
						if(U==6)//Enemy shooting function
						{
							EnemyBullet2Sprite.setRotation(0);
							if(EnemyBullet2Location.y < 600)
							{
								EnemyBullet2Location.y = EnemyBullet2Location.y+2; //Move enemy bullet down gradually whilst less than 500y
							}
							if(EnemyBullet2Location.y > 500) // reset enemy bullet location
							{
								U = 1;
							}
							EnemyBullet2Sprite.setPosition(EnemyBullet2Location.x,EnemyBullet2Location.y);
						}
						if(U==12)//Enemy shooting function
						{
							EnemyBullet2Sprite.setRotation(0);
							if(EnemyBullet2Location.y < 600)
							{
								EnemyBullet2Location.y = EnemyBullet2Location.y+2; //Move enemy bullet down gradually whilst less than 500y
							}
							if(EnemyBullet2Location.y > 500) // reset enemy bullet location
							{
								U = 1;
							}
							EnemyBullet2Sprite.setPosition(EnemyBullet2Location.x,EnemyBullet2Location.y);
						}

						//If player (plane) collides with any of the enemy planes you lose
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
						//If enemy bullet collides with player (plane) you lose
						if((EnemyBullet2Sprite.getGlobalBounds().intersects(PlaneSprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						//If enemy bullet collides with player (plane) you lose
						if((EnemyBulletSprite.getGlobalBounds().intersects(PlaneSprite.getGlobalBounds())))
						{
							gamestate = 3;
						}
						// score becomes high score if score is more than the current high score
						if (score >= hiScore)
						{
						hiScore = score;
						} 	

						if (restart)//Restart is true when backspace pressed. Resets all image locations and begins game from 1st movement (level 1).
						{
							cantmouseclick = false;
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
							EnemyBullet2Location.x = -300;
							EnemyBullet2Location.y = -300;
							BulletLocation.x = -180;
							BulletLocation.y = -180;
							EnemyPlaneLocation.x = 40;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							EnemyPlane2Location.x = 40;
							EnemyPlane2Location.y = 150;
							EnemyPlane2Sprite.setPosition(EnemyPlane2Location.x,EnemyPlane2Location.y);
							EnemyPlane3Location.x = 490;
							EnemyPlane3Location.y = 250;
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
							EnemyPlane4Location.x = 360;
							EnemyPlane4Location.y = 540;
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
				if(gamestate == 10)//If won, play win sound, draw win screen and output the high score data into the text file.
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
				if(gamestate == 3)//If Lost, play lose sound, draw lose screen and output the high score data into the text file.
				{
				showlevel = false;
				TheGameWindow.clear();
				LoseMethod();
				LoseSound.play();
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
				}//end of gamestate == 1
				if(showlevel) // showlevel is true when gamestate == 1 (game is playing)
				{
				Time dt = clock.restart();
				TheGameWindow.clear();
				if(c==0)
				{
					TheGameWindow.draw(ScreenImage);//Level 1 screen
				}
				if(c==1)
				{
					TheGameWindow.draw(Screen2Image);//Level 2 screen
				}
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(BulletSprite);
				TheGameWindow.draw(Bullet2Sprite);
				TheGameWindow.draw(EnemyBulletSprite);
				TheGameWindow.draw(EnemyBullet2Sprite);
				if(dontshowplanes)
				{
				TheGameWindow.draw(EnemyPlaneSprite);
				}
				if(dontshowplanes2)
				{
				TheGameWindow.draw(EnemyPlane2Sprite);
				}
				if(dontshowplanes3)
				{
				TheGameWindow.draw(EnemyPlane3Sprite);
				}
				if(dontshowplanes4)
				{
				TheGameWindow.draw(EnemyPlane4Sprite);
				}
				
			if (DisplayTip)//True when h is pressed. Shows a random tip for 3 seconds then goes off screen.
			{
				HelpTimeRemaining -= dt.asSeconds();
				if (HelpTimeRemaining <= 0.0)
				{
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
				TheGameWindow.display(); // Display all images
				} // end of showlevel
				if(gamestate==6)//Pause state. When P is pressed show pause text
				{
					showlevel = false;
					PauseMethod();
					TheGameWindow.display();
				}
				if (gamestate == 5)//Instruction state. When I is pressed show Instructions image
				{
				showlevel = false;
				TheGameWindow.clear();
				InstructionsMethod();
				TheGameWindow.display();
				}
			}
			return 0;
		}

void StartScreenMethod() // StartScreen Method, Create image and draw it
{
	if (!StartTexture.loadFromFile("Assets/StartScreen.png"))
		{
		cout << "StartScreen not loaded" << "\n";
		system("pause");
		}
	StartSprite.setTexture(StartTexture);

	TheGameWindow.draw(StartSprite);
}


void InstructionsMethod()// Instructions Method, Create image and draw it
{
	if (!InstructionsScreenTexture.loadFromFile("Assets/Instructions.png")) 
		{
		cout << "Instructions not loaded" << "\n";
		system("pause");
		}
	InstructionsScreenSprite.setTexture(InstructionsScreenTexture);

	TheGameWindow.draw(InstructionsScreenSprite);
}

void PauseMethod()// Pause Method, Create text and draw it
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

void WinMethod()// Win Method, Create image and draw it
{
	if (!WinTexture.loadFromFile("Assets/WinScreen.png"))
		{
		cout << "WinScreen not loaded" << "\n";
		system("pause");
		}
	WinSprite.setTexture(WinTexture);

	TheGameWindow.draw(WinSprite);
}

void LoseMethod()// Lose Method, Create image and draw it
{
	if (!LoseTexture.loadFromFile("Assets/LoseScreen.png"))
		{
		cout << "LoseScreen not loaded" << "\n";
		system("pause");
		}
	LoseSprite.setTexture(LoseTexture);

	TheGameWindow.draw(LoseSprite);
}



