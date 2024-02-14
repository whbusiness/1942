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


/*

Game Includes:

Start Screen
Instructions Screen
Level 1
Level 2
Moving NPC
Shooting NPC
Shootable Bullets
Pause Feature
Tips Feature
Boss
Healthbar
Lose Screen
Win Screen
Invincible PowerUp

*/

//Namespaces'
using namespace std;
using namespace sf;


//Variables
unsigned short int gamestate = 0;
unsigned short int score = 0;
unsigned short int hiScore;
unsigned short int a; // used in npc movement
unsigned short int c;// used in background scrolling
unsigned short int d; // used in npc movement

//Global Variables
	//Game Window Variables...
unsigned short int GameWindowX = 500;
unsigned short int GameWindowY = 500;
	sf::RenderWindow TheGameWindow(sf::VideoMode(GameWindowX,GameWindowY),"1942",sf::Style::Titlebar); //sf::Style::Fullscreen || sf::Style::Titlebar, Fullscreen is not suitable

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
	
	/*Textures */ sf::Texture Screen, OneHealthBar, TwoHealthBar, ThirdHealthBar, FourthHealthBar, FifthHealthBar, PowerUp, PowerUp2, Bullet, Bullet2, EnemyBullet, EnemyBullet2, Screen2, Plane, EnemyPlane, BossEnemyPlane, EnemyPlane2, EnemyPlane3, EnemyPlane4,  CharacterIconTip1, CharacterTip2, CharacterTip3;

	// clock used for timing
	Clock clock;

	//Making a HelpImage1 Sprite
	Sprite HelpImage1;

	//Timer for Tips
	Time HelpTimeTotal;
	float HelpTimeRemaining = 6.0; // Timer starts at 6 seconds

	//Timer for PowerUp
	Time PowerUpTimeTotal;
	float PowerUpTimeRemaining = 10.0; // Timer starts at 10 seconds

	//Timer for Level2
	Time Level2TimeTotal;
	float Level2TimeRemaining = 3.0; // Timer starts at 3 seconds

	//BossText Timer
	Time BossTextTimeTotal;
	float BossTextTimeRemaining = 3.0; // Timer starts at 3 seconds

	//Level 1 background Image Variables, Level1 Background
	float ScreenCurrentScaleX = 1.0f,ScreenCurrentScaleY = 1.0f;
	float ScreenWidth,ScreenHeight;
	sf::Vector2f ScreenLocation(0,-500);

	//PowerUp background Image Variables, Level1 Background
	float PowerUpCurrentScaleX = 0.2f,PowerUpCurrentScaleY = 0.15f;
	float PowerUpWidth,PowerUpHeight, PowerUpSpeed = 0.4f;
	sf::Vector2f PowerUpLocation(200,0);

	//PowerUp2 background Image Variables, Level1 Background
	float PowerUp2CurrentScaleX = 0.2f,PowerUp2CurrentScaleY = 0.15f;
	float PowerUp2Speed = 0.4f;
	sf::Vector2f PowerUp2Location(200,0);

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

	//Boss Enemy Plane 1 Image Variables
	float BossEnemyPlaneCurrentScaleX = 0.28f,BossEnemyPlaneCurrentScaleY = 0.28f;
	float BossEnemyPlaneWidth,BossEnemyPlaneHeight, BossEnemyPlaneSpeed = 0.5;
	sf::Vector2f BossEnemyPlaneLocation(490,200);

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
	float CharacterIconTip1CurrentScaleX = 0.2f,CharacterIconTip1CurrentScaleY = 0.2f;
	float CharacterIconTip1Width,CharacterIconTip1Height;
	sf::Vector2f CharacterIconTip1Location(50,390);

	//Tip 2 Image Variables
	float CharacterTip2CurrentScaleX = 0.2f,CharacterTip2CurrentScaleY = 0.2f;
	float CharacterTip2Width,CharacterTip2Height;
	sf::Vector2f CharacterTip2Location(50,390);

	//Tip 3 Image Variables
	float CharacterTip3CurrentScaleX = 0.2f,CharacterTip3CurrentScaleY = 0.2f;
	float CharacterTip3Width,CharacterTip3Height;
	sf::Vector2f CharacterTip3Location(50,390);

	//Font Variables
	Font font;
	font.loadFromFile("Assets/BAUHS93.ttf");

	//Score  Variables
    Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(Color::White);
	scoreText.setString("Score: ");
	scoreText.setPosition(55,475);

	//Level2 Text  Variables
    Text Level2Text;
	Level2Text.setFont(font);
	Level2Text.setCharacterSize(70);
	Level2Text.setFillColor(Color::Black);
	Level2Text.setString("Level 2");
	Level2Text.setPosition(160,150);

	Level2Text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//Boss Text  Variables
    Text BossText;
	BossText.setFont(font);
	BossText.setCharacterSize(70);
	BossText.setFillColor(Color::Black);
	BossText.setString("Boss Level");
	BossText.setPosition(100,150);

	BossText.setStyle(sf::Text::Bold | sf::Text::Underlined);


	//HiScore Variables
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(18);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setString("HiScore: ");
	hiScoreText.setPosition(300,475);

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

		//PowerUp Image Variables
	if (!PowerUp.loadFromFile("Assets/PowerUp.png"))
		{
		std::cout << "PowerUp has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite PowerUpSprite(PowerUp);
	PowerUpSprite.setScale(sf::Vector2f(PowerUpCurrentScaleX,PowerUpCurrentScaleY));
	PowerUpWidth = PowerUpSprite.getGlobalBounds().width;
	PowerUpHeight = PowerUpSprite.getGlobalBounds().height;
	
	PowerUpSprite.setPosition(PowerUpLocation.x,PowerUpLocation.y);

	//PowerUp2 Image Variables
	if (!PowerUp2.loadFromFile("Assets/PowerUp2.png"))
		{
		std::cout << "PowerUp2 has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite PowerUp2Sprite(PowerUp2);
	PowerUp2Sprite.setScale(sf::Vector2f(PowerUp2CurrentScaleX,PowerUp2CurrentScaleY));	
	PowerUp2Sprite.setPosition(PowerUp2Location.x,PowerUp2Location.y);

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

		//Enemy Plane 1 Image Variables
	if (!BossEnemyPlane.loadFromFile("Assets/BossEnemyPlane.png"))
		{
		std::cout << "Boss Enemy Plane 1 has not loaded" << "\n";
		system("pause");
		}

	//Declares the image within the code, Allowing me to call to it
	sf::Sprite BossEnemyPlaneSprite(BossEnemyPlane);
	BossEnemyPlaneSprite.setScale(sf::Vector2f(BossEnemyPlaneCurrentScaleX,BossEnemyPlaneCurrentScaleY));
	BossEnemyPlaneWidth = BossEnemyPlaneSprite.getGlobalBounds().width;
	BossEnemyPlaneHeight = BossEnemyPlaneSprite.getGlobalBounds().height;

		
	BossEnemyPlaneSprite.setPosition(BossEnemyPlaneLocation.x,BossEnemyPlaneLocation.y);

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

	//Full Health Bar Image Variables
	float OneHealthBarCurrentScaleX = 0.81f,OneHealthBarCurrentScaleY = 0.5f;
	sf::Vector2f OneHealthBarLocation(48,-115);

		//Enemy Bullet Image Variables
	if (!OneHealthBar.loadFromFile("Assets/FullHealthBar.png")) //The "Enemy Plane" Image...
		{
		std::cout << "FullHealthBar has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite OneHealthBarImage(OneHealthBar);
	OneHealthBarImage.setScale(sf::Vector2f(OneHealthBarCurrentScaleX,OneHealthBarCurrentScaleY));		
	OneHealthBarImage.setPosition(OneHealthBarLocation.x,OneHealthBarLocation.y);

		//Full Health Bar Image Variables
	float TwoHealthBarCurrentScaleX = 0.81f,TwoHealthBarCurrentScaleY = 0.5f;
	sf::Vector2f TwoHealthBarLocation(48,-115);

	//4th Health Bar Image Variables
	if (!TwoHealthBar.loadFromFile("Assets/4thHealthBar.png")) //The "Enemy Plane" Image...
		{
		std::cout << "4thHealthBar has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite TwoHealthBarImage(TwoHealthBar);
	TwoHealthBarImage.setScale(sf::Vector2f(TwoHealthBarCurrentScaleX,TwoHealthBarCurrentScaleY));		
	TwoHealthBarImage.setPosition(TwoHealthBarLocation.x,TwoHealthBarLocation.y);

	//Full Health Bar Image Variables
	float ThirdHealthBarCurrentScaleX = 0.81f,ThirdHealthBarCurrentScaleY = 0.5f;
	sf::Vector2f ThirdHealthBarLocation(48,-115);

		//Enemy Bullet Image Variables
	if (!ThirdHealthBar.loadFromFile("Assets/3rdHealthBar.png")) //The "Enemy Plane" Image...
		{
		std::cout << "3rdHealthBar has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite ThirdHealthBarImage(ThirdHealthBar);
	ThirdHealthBarImage.setScale(sf::Vector2f(ThirdHealthBarCurrentScaleX,ThirdHealthBarCurrentScaleY));		
	ThirdHealthBarImage.setPosition(ThirdHealthBarLocation.x,ThirdHealthBarLocation.y);

		//Full Health Bar Image Variables
	float FourthHealthBarCurrentScaleX = 0.81f,FourthHealthBarCurrentScaleY = 0.5f;
	sf::Vector2f FourthHealthBarLocation(48,-115);

			//Enemy Bullet Image Variables
	if (!FourthHealthBar.loadFromFile("Assets/2ndHealthBar.png")) //The "Enemy Plane" Image...
		{
		std::cout << "2ndHealthBar has not loaded" << "\n";
		system("pause");
		}
	//Declares the image within the code, Allowing me to call to it
	sf::Sprite FourthHealthBarImage(FourthHealthBar);
	FourthHealthBarImage.setScale(sf::Vector2f(FourthHealthBarCurrentScaleX,FourthHealthBarCurrentScaleY));		
	FourthHealthBarImage.setPosition(FourthHealthBarLocation.x,FourthHealthBarLocation.y);


	//Rotate enemy plane so that it is correctly angled in the direction it is travelling
	EnemyPlaneSprite.setRotation(90);
	EnemyPlane2Sprite.setRotation(90);
	EnemyPlane3Sprite.setRotation(270);
	BossEnemyPlaneSprite.setRotation(270);

	//Boolean functions for later use
	bool restart = false;
	bool showlevel = false;
	bool paused = false;
	bool move1 = true;
	bool move2 = false;
	bool move3 = false;
	bool move4 = false;
	bool Level2 = false;
	bool move11 = false;
	bool move12 = false;
	bool move13 = false;
	bool move14 = false;
	bool move15 = false;
	bool move16 = false;
	bool move17 = false;
	bool move18 = false;
	bool DisplayTip = false;
	bool TipLoop = false;
	bool PowerUpLoop = false;
	bool showpowerup = false;
	bool dontshowplanes;
	bool dontshowplanes2;
	bool dontshowplanes3;
	bool dontshowplanes4;
	bool dontshowbossplane;
	bool cantmouseclick = false;
	bool isinvincible = false;
	bool cantbeshot = false;
	bool cancontact = false;
	bool dontshow = false;
	bool PowerUpMoving = false;
	bool PowerUp2Moving = false;
	bool showpowerup2 = false;
	bool dontshow2 = false;
	bool cancontact2 = false;
	bool showfullhealth = false;
	bool show2ndhealth = false;
	bool show3rdhealth = false;
	bool show4thhealth = false;
	bool showtext = false;
	bool Level2Textcanshow = false;
	bool DrawLevel2Text = false;
	bool showBosstext = false;
	bool BossTextcanshow = false;
	bool DrawBossText = false;

	//When game is first run show the start screen
	if (gamestate == 0)
	{
	TheGameWindow.clear();
	StartScreenMethod();
	TheGameWindow.display();
	}		

	PlaneSprite.setColor(Color::White);
	BossEnemyPlaneSprite.setColor(Color::Yellow);
	EnemyPlaneSprite.setColor(Color::Blue);
	EnemyPlane2Sprite.setColor(Color::Red);
	EnemyPlane3Sprite.setColor(Color::Red);
	EnemyPlane4Sprite.setColor(Color::Magenta);

	//L is your bullet, K is enemy bullets, U is enemybullet2
	unsigned short int L = 1;
	unsigned short int K = 1;
	unsigned short int U = 1;

	unsigned short int health = 400;

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
					dontshowbossplane = false;
					showlevel = true;//Show level graphics

					if(L==1)//If you are not shooting bullet is off screen
					{
						BulletLocation.x = 800;
						BulletLocation.y = 800;
						BulletSprite.setPosition(BulletLocation.x,BulletLocation.y);
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
					if(EnemyPlane3Location.x<30)
					{
						dontshowplanes3 = false;
					}
					if(EnemyPlane3Location.x>421)
					{
						dontshowplanes3 = false;
					}
					if(BossEnemyPlaneLocation.x<370)
					{
						dontshowbossplane = true;
					}
					if(BossEnemyPlaneLocation.x<40)
					{
						dontshowbossplane = false;
					}
					if(BossEnemyPlaneLocation.x>371)
					{
						dontshowbossplane = false;
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
					if(EnemyPlane2Location.x>240)
					{
						if(EnemyPlane2Location.x<241)
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
					if(EnemyPlane3Location.x>240)
					{
						if(EnemyPlane3Location.x<241)
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
					if(BossEnemyPlaneLocation.x>120)
					{
						if(BossEnemyPlaneLocation.x<121)
						{	
						K=6;
						EnemyBulletLocation.x = BossEnemyPlaneLocation.x;
						EnemyBulletLocation.y = BossEnemyPlaneLocation.y;
						BulletsFired.play();
					}
					}
					if(BossEnemyPlaneLocation.x>200)
					{
						if(BossEnemyPlaneLocation.x<201)
						{	
						U=6;
						EnemyBullet2Location.x = BossEnemyPlaneLocation.x;
						EnemyBullet2Location.y = BossEnemyPlaneLocation.y;
						BulletsFired.play();
					}
					}
					if(BossEnemyPlaneLocation.x>300)
					{
						if(BossEnemyPlaneLocation.x<301)
						{		
						U=6;
						EnemyBullet2Location.x = BossEnemyPlaneLocation.x;
						EnemyBullet2Location.y = BossEnemyPlaneLocation.y;
						BulletsFired.play();
					}
					}

					if(BossEnemyPlaneLocation.x>360)
					{
						if(BossEnemyPlaneLocation.x<361)
						{		
						U=6;
						EnemyBullet2Location.x = BossEnemyPlaneLocation.x;
						EnemyBullet2Location.y = BossEnemyPlaneLocation.y;
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
					if(EnemyPlane4Location.y>450)
					{
						if(EnemyPlane4Location.y<451)
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
							dontshow2 = true;
						}
					if (move4)
					{
						if(dontshow2)
							{
							showpowerup2 = true;
							cancontact2 = true;
							PowerUp2Moving = true;
							}
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
							Level2Textcanshow = true;
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
							EnemyPlane3Location.x = 0 + 500;
							}
							EnemyPlane3Sprite.setPosition(EnemyPlane3Location.x,EnemyPlane3Location.y);
						}

						if (move11)
						{
							if(Level2Textcanshow)
							{
							showtext = true;
							}
							EnemyPlaneSprite.setPosition(15,50);
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							if((BulletSprite.getGlobalBounds().intersects(EnemyPlaneSprite.getGlobalBounds())))
							{
							score = score+100;
							move11 = false;
							EnemyPlaneLocation.x = -60;
							EnemyPlaneLocation.y = 50;
							EnemyPlaneSprite.setPosition(EnemyPlaneLocation.x,EnemyPlaneLocation.y);
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
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
								dontshow = true;
							}
						}

						if(PowerUpMoving)
						{
							PowerUpLocation.y = PowerUpLocation.y + PowerUpSpeed;
							if (PowerUpLocation.y > 500)
							{
							PowerUpMoving = false;
							dontshow = false;
							cancontact = false;
							PowerUpLocation.x = 1000;
							PowerUpLocation.y = 1000;
							}
							PowerUpSprite.setPosition(PowerUpLocation.x,PowerUpLocation.y);
						}

						if(PowerUp2Moving)
						{
							PowerUp2Location.y = PowerUp2Location.y + PowerUp2Speed;
							if (PowerUp2Location.y > 500)
							{
							PowerUp2Moving = false;
							dontshow2 = false;
							cancontact2 = false;
							PowerUp2Location.x = 1000;
							PowerUp2Location.y = 1000;
							}
							PowerUp2Sprite.setPosition(PowerUp2Location.x,PowerUp2Location.y);
						}


						if (move14)
						{
							if(dontshow)
							{
							showpowerup = true;
							cancontact = true;
							PowerUpMoving = true;
							}
							
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
						}
						if(move17)
						{
							if(dontshow)
							{
							showpowerup = true;
							cancontact = true;
							PowerUpMoving = true;
							}
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
							BossTextcanshow = true;
							move18 = true;
							//gamestate = 10;
						}		
						if (move18)
						{
						if((BulletSprite.getGlobalBounds().intersects(BossEnemyPlaneSprite.getGlobalBounds())))
						{
							health = health - 100;
							if(health==0)
							{
							BossEnemyPlaneLocation.x = 520;
							BossEnemyPlaneLocation.y = 150;
							BossEnemyPlaneSprite.setPosition(520,150);
							BossEnemyPlaneSprite.setPosition(BossEnemyPlaneLocation.x,BossEnemyPlaneLocation.y);
							move18 = false;
							score = score+100;
							gamestate = 10;
							}
							BulletLocation.x=700;
							BulletLocation.y=700;
							L=1;
						}
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
							EnemyPlane3Location.x = 0 + 500;
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
							EnemyPlane3Location.x = 0 + 500;
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
						if(move18)
						{
							BossEnemyPlaneLocation.x = BossEnemyPlaneLocation.x - BossEnemyPlaneSpeed;
							if (BossEnemyPlaneLocation.x < -100)
							{
							BossEnemyPlaneLocation.x = 0 + 500;
							}
							BossEnemyPlaneSprite.setPosition(BossEnemyPlaneLocation.x,BossEnemyPlaneLocation.y);
						}

						if(move18)
						{
							if(health==400)
							{
								showfullhealth = true;
							}
							if(health==300)
							{
								showfullhealth=false;
								show2ndhealth = true;
							}
							if(health==200)
							{
								show2ndhealth = false;
								show3rdhealth = true;
							}
							if(health==100)
							{
								show3rdhealth = false;
								show4thhealth = true;
							}
						}

						//Level 1 Background scrolling code
						if(c == 0)
						{
						if(ScreenLocation.y < 0)
							{
								ScreenLocation.y = ScreenLocation.y+0.15f;
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
								Screen2Location.y = Screen2Location.y+0.15f;
							}
						if(Screen2Location.y > 0)
							{

								Screen2Location.y = -500;
							}
						Screen2Image.setPosition(Screen2Location.x,Screen2Location.y);
						}

						if(cancontact)
							{
						if((PlaneSprite.getGlobalBounds().intersects(PowerUpSprite.getGlobalBounds())))
						{
							showpowerup = false;
							PowerUpLocation.x = 1000;
							PowerUpLocation.y = 1000;
							isinvincible = true;
							cancontact = false;
							dontshow = false;
						}
							}
						if(cancontact2)
							{
						if((PlaneSprite.getGlobalBounds().intersects(PowerUp2Sprite.getGlobalBounds())))
						{
							score = score +1000;
							showpowerup2 = false;
							PowerUp2Location.x = 1000;
							PowerUp2Location.y = 1000;
							cancontact2 = false;
							dontshow2 = false;
						}
							}



						if(L==8)//When space is pressed
						{
							
							if(BulletLocation.y < 500)
							{
								cantmouseclick = true;
								BulletLocation.y = BulletLocation.y-2.5f; // Move the bullet up gradually whilst less than 500y
							}
							if(BulletLocation.y < -65)//If fully off screen reset bullet position off screen and allow user to shoot again
							{
								L = 1;
								cantmouseclick = false;
							}
							BulletSprite.setPosition(BulletLocation.x,BulletLocation.y);
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

						if(!cantbeshot)
						{
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
						if((PlaneSprite.getGlobalBounds().intersects(BossEnemyPlaneSprite.getGlobalBounds())))
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
						}
						// score becomes high score if score is more than the current high score
						if (score >= hiScore)
						{
						hiScore = score;
						} 	
						if (restart)//Restart is true when backspace pressed. Resets all image locations and begins game from 1st movement (level 1).
						{
							showtext = false;
							Level2Textcanshow = false;
							DrawLevel2Text = false;
							showBosstext = false;
							BossTextcanshow = false;
							DrawBossText = false;
							showfullhealth = false;
							show2ndhealth = false;
							show3rdhealth = false;
							show4thhealth = false;
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
							isinvincible = false;
							PowerUpMoving = false;
							PowerUp2Moving = false;
							showpowerup2 = false;
							PowerUp2Location.x = 200;
							PowerUp2Location.y = 0;
							cancontact2 = false;
							dontshow2 = false;
							cantbeshot = false;
							cancontact = false;
							dontshow = false;
							PowerUpTimeRemaining = 10;
							Level2TimeRemaining = 3;
							BossTextTimeRemaining = 3;
							showpowerup = false;
							PowerUpLocation.x = 200;
							PowerUpLocation.y = 0;
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
							BossEnemyPlaneLocation.x = 490;
							BossEnemyPlaneLocation.y = 150;
							BossEnemyPlaneSprite.setPosition(BossEnemyPlaneLocation.x,BossEnemyPlaneLocation.y);
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
							move18 = false;
							health = 400;
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

				if (BossTextcanshow)//True when collision with powerup. applies invincibility for 3 seconds.
			{
				BossTextTimeRemaining -= dt.asSeconds();
				if (BossTextTimeRemaining <= 0.0)
				{
					BossTextcanshow = false;
					showBosstext = false;
					DrawBossText = false;
				}
				if (BossTextTimeRemaining >0.0)
				{
					DrawBossText = true;
				}	
			}	
				if (Level2Textcanshow)//True when collision with powerup. applies invincibility for 3 seconds.
			{
				Level2TimeRemaining -= dt.asSeconds();
				if (Level2TimeRemaining <= 0.0)
				{
					Level2Textcanshow = false;
					showtext = false;
					DrawLevel2Text = false;
				}
				if (Level2TimeRemaining >0.0)
				{
					DrawLevel2Text = true;
				}	
				}
				if(DrawBossText)
				{
				TheGameWindow.draw(BossText);
				}
				if(DrawLevel2Text)
				{
				TheGameWindow.draw(Level2Text);
				}
				TheGameWindow.draw(scoreText);
				TheGameWindow.draw(hiScoreText);
				TheGameWindow.draw(PlaneSprite);
				TheGameWindow.draw(BulletSprite);
				if(showpowerup)
				{
				TheGameWindow.draw(PowerUpSprite);
				}
				if(showpowerup2)
				{
				TheGameWindow.draw(PowerUp2Sprite);
				}
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
				if(dontshowbossplane)
				{
				TheGameWindow.draw(BossEnemyPlaneSprite);
				}
				if(showfullhealth)
				{
				TheGameWindow.draw(OneHealthBarImage);
				}
				if(show2ndhealth)
				{
				TheGameWindow.draw(TwoHealthBarImage);
				}
				if(show3rdhealth)
				{
				TheGameWindow.draw(ThirdHealthBarImage);
				}
				if(show4thhealth)
				{
				TheGameWindow.draw(FourthHealthBarImage);
				}
		
				
			if (isinvincible)//True when collision with powerup. applies invincibility for 3 seconds.
			{
				showpowerup = false;
				PlaneSprite.setColor(Color::Green);
				PowerUpTimeRemaining -= dt.asSeconds();
				if (PowerUpTimeRemaining <= 0.0)
				{
					showpowerup = false;
					isinvincible = false;
					cantbeshot = false;					
				}
				if (PowerUpTimeRemaining >0.0)
				{
					showpowerup = false;
					cantbeshot = true;
				}	
			}	
			if(!isinvincible)
			{
			PlaneSprite.setColor(Color::White);
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
						unsigned short int Tips;
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

