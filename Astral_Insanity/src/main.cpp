#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <windows.h>
#include <sstream> 
#include <SFML/Audio.hpp>
#include <SFML/Audio/Export.hpp>
#include <SFML/Audio/SoundSource.hpp>

// Adds sf in front of everything to reference the library
using namespace sf;

sf::SoundBuffer buffer;
sf::Sound sound;

Texture playerSpriteTexture, backgroundTexture, policeSpriteTexture, playerShootingTexture, powerupChestTexture, backgroundMenuTexture, buttonMenuTexture, armySpriteTexture, armyShootingTexture, policeShootingTexure;
Sprite backgroundSprite;
Font font;
Text scoreText, healthText, gameOverText, startMenuText, highscoreMenuText, weblinkMenuText, exitMenuText, gameCountDownTimer, bulletsAvailableCounter, enemyBoatsLeft, nameInputOutput;

String nameInput;
// Used for Main Menu
Texture startButtonMenuTexture, highscoreButtonMenuTexture, weblinkButtonMenuTexture, exitButtonMenuTexture, optionsButtonMenuTexture, mouseMenuTexture;
Sprite backgroundMenuSprite, startButtonMenuSprite, highscoreButtonMenuSprite, weblinkButtonMenuSprite, exitButtonMenuSprite, optionsButtonMenuSprite, mouseMenuSprite;
RectangleShape startButtonMenuRect, highscoreButtonMenuRect, weblinkButtonMenuRect, exitButtonMenuRect, optionsButtonMenuRect;



bool key[29];

// Used for the gameSystem
int sysPolice = 0, sysArmy = 0, sysLevel = 0;
float sysSpeed = 50.0f;

// Booleans to limit movement
bool leftNotAllowed = false, rightNotAllowed = false, levelComplete = false, highscoreChanged = false, newLevel = false, newGame = false, hasLoadPauseBeenCalled = false, isControllerButtonPressed = false;

// Have the load methods been called
bool hasLoadStartBeenCalled = false, hasLoadMenuBeenCalled = false, hasGameOverBeenCalled = false, hasHighscoresBeenCalled = false, hasCompleteBeenCalled = false, hasOpitionsBeenCalled = false;
bool hasCountDownBeenCalled = false, userHasNoHealth = false;

// Used to hold user information
int userScore = 0, userHealth = 0, userBullets = 0, userRemaingBoats = 0;

// Used for player ship
RectangleShape playerSpriteRectangle;
Sprite playerShootingSprite[30], playerSprite;
bool playerShootingSpriteAvailable[30], playerShootingSpriteActive[30];

// Used to detect if player has pressed buttons
bool isSpacePressed = false;

// Used for police boats
Sprite policeBoatSprite[30], policeBoatShootingSprite[30];
RectangleShape policeBoatRectangle[30];
int policeBoatHealth[30];
bool hasPlayerShootingSpriteHitPoliceBoat[30], isPoliceBulletActive[30];

// Used for army boats
Sprite armyBoatSprite[30], armyBoatShootingSprite[30];
RectangleShape armyBoatRectangle[30];
int armyBoatHealth[30];
bool hasPlayerShootingSpriteHitArmyBoat[30], isArmyBulletActive[30];

// Used for power ups
Sprite powerupChestSprite;
RectangleShape powerupChestRectangle;

// Used for game over screen
Text exitGame;
Texture gameOverTexture, confirmTexture, enterNameTexture;
Sprite gameOverSprite, confirmSprite, enterNameSprite;
RectangleShape confirmRectangle;

// Used for highscores screen
Texture highscoresTexture, returnTexture, namescoreTexture;
Sprite highscoresSprite, returnSprite, namescoreSprite;
RectangleShape returnRectangle;
String names[20];
int scores[20];
Text displayNames[20], displayScores[20];

// Used for level complete screen
Texture completeMessageTexture, completeNextTexture, completeExitTexture;
Sprite completeMessage, completeNext, completeExit;
RectangleShape completeNextRectangle, completeExitRectangle;

// Used for the pause screen
Texture pauseResumeTexture, pauseExitTexture;
Sprite pauseResumeSprite, pauseExitSprite;
RectangleShape pauseResumeRectangle, pauseExitRectangle;

// Used for the options screen
Texture fourOptionTexture, eightOptionTexture, fullOptionTexture, returnOptionTexture;
Sprite fourOptionSprite, eightOptionSprite, fullOptionSprite, returnOptionSprite;
RectangleShape fourOptionRectangle, eightOptionRectangle, fullOptionRectangle, returnOptionRectangle;

// Method which gholds the different gamestates
enum class GameStates
{
	STATE_START = 1,
	STATE_MENU = 2,
	STATE_PAUSE = 3,
	STATE_OPITIONS = 4,
	STATE_HIGHSCORES = 5,
	STATE_GAMEOVER = 6,
	STATE_COMPLETE = 7,
};

// Method which moves the bullets
void moveTheBullets(Vector2f upMovement, float dt) {
	// If bullet is active then
	if (playerShootingSpriteActive[0]) {
		// Move bullet
		playerShootingSprite[0].move(upMovement*sysSpeed*dt);
		// If bullet is off screen then
		if (playerShootingSprite[0].getPosition().y < -20.0f) {
			// Reset bullet posotion
			playerShootingSprite[0].setPosition(-10.0f, -10.0f);
			// Make bullet available
			playerShootingSpriteAvailable[0] = true;
			// Add one to user bullets 
			userBullets += 1;
			// Deactivate bullet
			playerShootingSpriteActive[0] = false;
		}
	}

	if (playerShootingSpriteActive[1]) {
		playerShootingSprite[1].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[1].getPosition().y < -20.0f) {
			playerShootingSprite[1].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[1] = true;
			userBullets += 1;
			playerShootingSpriteActive[1] = false;
		}
	}

	if (playerShootingSpriteActive[2]) {
		playerShootingSprite[2].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[2].getPosition().y < -20.0f) {
			playerShootingSprite[2].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[2] = true;
			userBullets += 1;
			playerShootingSpriteActive[2] = false;
		}
	}

	if (playerShootingSpriteActive[3]) {
		playerShootingSprite[3].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[3].getPosition().y < -20.0f) {
			playerShootingSprite[3].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[3] = true;
			userBullets += 1;
			playerShootingSpriteActive[3] = false;
		}
	}

	if (playerShootingSpriteActive[4]) {
		playerShootingSprite[4].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[4].getPosition().y < -20.0f) {
			playerShootingSprite[4].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[4] = true;
			userBullets += 1;
			playerShootingSpriteActive[4] = false;
		}
	}

	if (playerShootingSpriteActive[5]) {
		playerShootingSprite[5].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[5].getPosition().y < -20.0f) {
			playerShootingSprite[5].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[5] = true;
			userBullets += 1;
			playerShootingSpriteActive[5] = false;
		}
	}

	if (playerShootingSpriteActive[6]) {
		playerShootingSprite[6].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[6].getPosition().y < -20.0f) {
			playerShootingSprite[6].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[6] = true;
			userBullets += 1;
			playerShootingSpriteActive[6] = false;
		}
	}

	if (playerShootingSpriteActive[7]) {
		playerShootingSprite[7].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[7].getPosition().y < -20.0f) {
			playerShootingSprite[7].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[7] = true;
			userBullets += 1;
			playerShootingSpriteActive[7] = false;
		}
	}

	if (playerShootingSpriteActive[8]) {
		playerShootingSprite[8].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[8].getPosition().y < -20.0f) {
			playerShootingSprite[8].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[8] = true;
			userBullets += 1;
			playerShootingSpriteActive[8] = false;
		}
	}

	if (playerShootingSpriteActive[9]) {
		playerShootingSprite[9].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[9].getPosition().y < -20.0f) {
			playerShootingSprite[9].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[9] = true;
			userBullets += 1;
			playerShootingSpriteActive[9] = false;
		}
	}

	if (playerShootingSpriteActive[10]) {
		playerShootingSprite[10].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[10].getPosition().y < -20.0f) {
			playerShootingSprite[10].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[10] = true;
			userBullets += 1;
			playerShootingSpriteActive[10] = false;
		}
	}

	if (playerShootingSpriteActive[11]) {
		playerShootingSprite[11].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[11].getPosition().y < -20.0f) {
			playerShootingSprite[11].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[11] = true;
			userBullets += 1;
			playerShootingSpriteActive[11] = false;
		}
	}

	if (playerShootingSpriteActive[12]) {
		playerShootingSprite[12].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[12].getPosition().y < -20.0f) {
			playerShootingSprite[12].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[12] = true;
			userBullets += 1;
			playerShootingSpriteActive[12] = false;
		}
	}

	if (playerShootingSpriteActive[13]) {
		playerShootingSprite[13].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[13].getPosition().y < -20.0f) {
			playerShootingSprite[13].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[13] = true;
			userBullets += 1;
			playerShootingSpriteActive[13] = false;
		}
	}

	if (playerShootingSpriteActive[14]) {
		playerShootingSprite[14].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[14].getPosition().y < -20.0f) {
			playerShootingSprite[14].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[14] = true;
			userBullets += 1;
			playerShootingSpriteActive[14] = false;
		}
	}

	if (playerShootingSpriteActive[15]) {
		playerShootingSprite[15].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[15].getPosition().y < -20.0f) {
			playerShootingSprite[15].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[15] = true;
			userBullets += 1;
			playerShootingSpriteActive[15] = false;
		}
	}

	if (playerShootingSpriteActive[16]) {
		playerShootingSprite[16].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[16].getPosition().y < -20.0f) {
			playerShootingSprite[16].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[16] = true;
			userBullets += 1;
			playerShootingSpriteActive[16] = false;
		}
	}

	if (playerShootingSpriteActive[17]) {
		playerShootingSprite[17].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[17].getPosition().y < -20.0f) {
			playerShootingSprite[17].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[17] = true;
			userBullets += 1;
			playerShootingSpriteActive[17] = false;
		}
	}

	if (playerShootingSpriteActive[18]) {
		playerShootingSprite[18].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[18].getPosition().y < -20.0f) {
			playerShootingSprite[18].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[18] = true;
			userBullets += 1;
			playerShootingSpriteActive[18] = false;
		}
	}

	if (playerShootingSpriteActive[19]) {
		playerShootingSprite[19].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[19].getPosition().y < -20.0f) {
			playerShootingSprite[19].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[19] = true;
			userBullets += 1;
			playerShootingSpriteActive[19] = false;
		}
	}

	if (playerShootingSpriteActive[20]) {
		playerShootingSprite[20].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[20].getPosition().y < -20.0f) {
			playerShootingSprite[20].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[20] = true;
			userBullets += 1;
			playerShootingSpriteActive[20] = false;
		}
	}

	if (playerShootingSpriteActive[21]) {
		playerShootingSprite[21].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[21].getPosition().y < -20.0f) {
			playerShootingSprite[21].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[21] = true;
			userBullets += 1;
			playerShootingSpriteActive[21] = false;
		}
	}

	if (playerShootingSpriteActive[22]) {
		playerShootingSprite[22].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[22].getPosition().y < -20.0f) {
			playerShootingSprite[22].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[22] = true;
			userBullets += 1;
			playerShootingSpriteActive[22] = false;
		}
	}

	if (playerShootingSpriteActive[23]) {
		playerShootingSprite[23].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[23].getPosition().y < -20.0f) {
			playerShootingSprite[23].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[23] = true;
			userBullets += 1;
			playerShootingSpriteActive[23] = false;
		}
	}

	if (playerShootingSpriteActive[24]) {
		playerShootingSprite[24].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[24].getPosition().y < -20.0f) {
			playerShootingSprite[24].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[24] = true;
			userBullets += 1;
			playerShootingSpriteActive[24] = false;
		}
	}

	if (playerShootingSpriteActive[25]) {
		playerShootingSprite[25].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[25].getPosition().y < -20.0f) {
			playerShootingSprite[25].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[25] = true;
			userBullets += 1;
			playerShootingSpriteActive[25] = false;
		}
	}

	if (playerShootingSpriteActive[26]) {
		playerShootingSprite[26].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[26].getPosition().y < -20.0f) {
			playerShootingSprite[26].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[26] = true;
			userBullets += 1;
			playerShootingSpriteActive[26] = false;
		}
	}

	if (playerShootingSpriteActive[27]) {
		playerShootingSprite[27].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[27].getPosition().y < -20.0f) {
			playerShootingSprite[27].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[27] = true;
			userBullets += 1;
			playerShootingSpriteActive[27] = false;
		}
	}

	if (playerShootingSpriteActive[28]) {
		playerShootingSprite[28].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[28].getPosition().y < -20.0f) {
			playerShootingSprite[28].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[28] = true;
			userBullets += 1;
			playerShootingSpriteActive[28] = false;
		}
	}

	if (playerShootingSpriteActive[29]) {
		playerShootingSprite[29].move(upMovement*sysSpeed*dt);
		if (playerShootingSprite[29].getPosition().y < -20.0f) {
			playerShootingSprite[29].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[29] = true;
			userBullets += 1;
			playerShootingSpriteActive[29] = false;
		}
	}
}

// Method which displays various user values on the interface
void setupStartTexts() {
	scoreText.setFont(font);
	scoreText.setString("SCORE: " + std::to_string(userScore));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::Black);
	scoreText.setStyle(Text::Bold | Text::Underlined);
	scoreText.setPosition(200.0f, 0.0f);

	healthText.setFont(font);
	healthText.setString("HEALTH: " + std::to_string(userHealth));
	healthText.setCharacterSize(24);
	healthText.setFillColor(Color::Black);
	healthText.setStyle(Text::Bold | Text::Underlined);
	healthText.setPosition(10.0f, 0.0f);

	gameCountDownTimer.setFont(font);
	gameCountDownTimer.setString("Level " + std::to_string(sysLevel));
	gameCountDownTimer.setCharacterSize(30);
	gameCountDownTimer.setFillColor(Color::Black);
	gameCountDownTimer.setStyle(Text::Bold | Text::Underlined);
	gameCountDownTimer.setPosition(150.0f, 150.0f);

	bulletsAvailableCounter.setFont(font);
	bulletsAvailableCounter.setString("BULLETS: 30/30");
	bulletsAvailableCounter.setCharacterSize(24);
	bulletsAvailableCounter.setFillColor(Color::Black);
	bulletsAvailableCounter.setStyle(Text::Bold | Text::Underlined);
	bulletsAvailableCounter.setPosition(10.0f, 360.0f);

	enemyBoatsLeft.setFont(font);
	enemyBoatsLeft.setString("REMAIN: " + std::to_string(userRemaingBoats));
	enemyBoatsLeft.setCharacterSize(24);
	enemyBoatsLeft.setFillColor(Color::Black);
	enemyBoatsLeft.setStyle(Text::Bold | Text::Underlined);
	enemyBoatsLeft.setPosition(220.0f, 360.0f);
}

void LoadComplete(int winX, int winY) {
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!completeMessageTexture.loadFromFile("res/img/congrats.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!completeNextTexture.loadFromFile("res/img/next.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!completeExitTexture.loadFromFile("res/img/exit.png")) {
		throw std::invalid_argument("Loading error with background!");
	}

	completeMessage.setPosition((winX / 4), (winY / 16));
	completeNext.setPosition((winX / 4), (winY /2));
	completeExit.setPosition((winX / 4), (winY / 8) + (winY / 2));
}

void LoadPause(int winX, int winY) {
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!pauseResumeTexture.loadFromFile("res/img/resume.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!pauseExitTexture.loadFromFile("res/img/EXIT.png")) {
		throw std::invalid_argument("Loading error with background!");
	}

	pauseResumeSprite.setPosition((winX / 4), (winY / 4) + (winY / 8));

	pauseExitSprite.setPosition((winX / 4), (winY / 2));
}

void LoadOpitions(int winX, int winY) {
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!fourOptionTexture.loadFromFile("res/img/four.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!eightOptionTexture.loadFromFile("res/img/eight.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!fullOptionTexture.loadFromFile("res/img/full.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!returnOptionTexture.loadFromFile("res/img/return.png")) {
		throw std::invalid_argument("Loading error with background!");
	}

	fourOptionSprite.setPosition((winX / 4), (winY / 4));

	eightOptionSprite.setPosition((winX / 4), (winY / 2) - (winY / 8));

	fullOptionSprite.setPosition((winX / 4), (winY / 2));

	returnOptionSprite.setPosition((winX / 4), (winY / 2) + (winY / 8));
}

void LoadHighscores(int winX, int winY) {
	std::cout << "LoadHS" << std::endl;
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!font.loadFromFile("res/fonts/Treamd.ttf")) {
		throw std::invalid_argument("Loading error with font!");
	}
	if (!highscoresTexture.loadFromFile("res/img/high.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}
	if (!returnTexture.loadFromFile("res/img/return.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}
	if (!namescoreTexture.loadFromFile("res/img/namescore.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}
	/*
	names[0] = "Sam";
	names[1] = "John";
	names[2] = "Mark";
	names[3] = "Neil";
	names[4] = "CalumT";

	scores[0] = 1;
	scores[1] = 2;
	scores[2] = 7;
	scores[3] = 4;
	scores[4] = 5;
	*/
	int temp;
	String tempName;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20 - 1; j++)
		{
			if (scores[j] > scores[j + 1])
			{
				//we need to swap
				temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;

				tempName = names[j];
				names[j] = names[j + 1];
				names[j + 1] = tempName;
			}
		}
	}

	std::reverse(std::begin(scores), std::end(scores));
	std::reverse(std::begin(names), std::end(names));

	for (int i = 0; i < 5; i++) {
		displayNames[i].setFont(font);
		displayNames[i].setString(names[i]);
		displayNames[i].setCharacterSize(30);
		displayNames[i].setFillColor(Color::Black);
		displayNames[i].setPosition((winX / 4), (winY / 4) + (winY / 16) + (i * 35));

		displayScores[i].setFont(font);
		displayScores[i].setString(std::to_string(scores[i]));
		displayScores[i].setCharacterSize(30);
		displayScores[i].setFillColor(Color::Black);
		displayScores[i].setPosition((winX / 2) + (winX / 16), (winY / 4) + (winY / 16) + (i * 35));

		//std::cout << " " << scores[i] << std::endl;
	}

	highscoresSprite.setPosition((winX/4), (winY/16));
	namescoreSprite.setPosition((winX/4), (winY/8) + (winY / 16));
	returnSprite.setPosition((winX/4), (winY/8) + (winY/4) + (winY/2));
}

void LoadMenu(int winX, int winY) {
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}
	if (!buttonMenuTexture.loadFromFile("res/img/enemy.png")) {
		throw std::invalid_argument("Loading error with menu start button!");
	}
	if (!font.loadFromFile("res/fonts/Treamd.ttf")) {
		throw std::invalid_argument("Loading error with font!");
	}
	if (!startButtonMenuTexture.loadFromFile("res/img/start.png")) {
		throw std::invalid_argument("Loading error with button tex!");
	}
	if (!mouseMenuTexture.loadFromFile("res/img/smallbullet1.png")) {
		throw std::invalid_argument("Loading error with button tex!");
	}
	if (!highscoreButtonMenuTexture.loadFromFile("res/img/high.png")) {
		throw std::invalid_argument("Loading error with  button tex!");
	}
	if (!weblinkButtonMenuTexture.loadFromFile("res/img/web.png")) {
		throw std::invalid_argument("Loading error with  button tex!");
	}
	if (!exitButtonMenuTexture.loadFromFile("res/img/EXIT.png")) {
		throw std::invalid_argument("Loading error with  button tex!");
	}
	if (!optionsButtonMenuTexture.loadFromFile("res/img/options.png")) {
		throw std::invalid_argument("Loading error with  button tex!");
	}

	// Set position and the scale of all the sprite buttons
	startButtonMenuSprite.setPosition((winX/2) - (winX/4), (winY / 2) - (winY / 4));
	
	highscoreButtonMenuSprite.setPosition((winX/2) - (winX/4), (winY / 2) - (winY / 8));

	weblinkButtonMenuSprite.setPosition((winX/2) - (winX/4), (winY / 2));

	optionsButtonMenuSprite.setPosition((winX / 4), (winY / 2) + (winY / 8));

	exitButtonMenuSprite.setPosition((winX/2) - (winX/4), (winY / 2) + (winY / 4));

	mouseMenuSprite.setPosition((winX / 2), (winY / 2));

	if (!buffer.loadFromFile("res/music/boat.wav")) {
		std::cout << "Error 404" << std::endl;
	}
	else { std::cout << "Loadedppp" << std::endl; }
	sound.setBuffer(buffer);
	sound.play();
}

void LoadGameOver(int winX, int winY) {
	if (!backgroundMenuTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}

	if (!font.loadFromFile("res/fonts/Treamd.ttf")) {
		throw std::invalid_argument("Loading error with font!");
	}

	if (!gameOverTexture.loadFromFile("res/img/gameover.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}
	if (!confirmTexture.loadFromFile("res/img/confirm.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}
	if (!enterNameTexture.loadFromFile("res/img/name.png")) {
		throw std::invalid_argument("Loading error with pic!");
	}

	for (int i = 0; i < 29; i++) {
		key[i] = false;
	}
	
	nameInputOutput.setFont(font);
	nameInputOutput.setString("");
	nameInputOutput.setCharacterSize(30);
	nameInputOutput.setFillColor(Color::Black);
	nameInputOutput.setStyle(Text::Bold | Text::Underlined);

	gameOverSprite.setPosition((winX /4), (winY / 8));
	enterNameSprite.setPosition((winX / 4), (winY / 4));
	confirmSprite.setPosition((winX / 4), (winY / 2) + (winY / 4));
	nameInputOutput.setPosition((winX / 4) + (winX / 8), (winY / 2));
}

void LoadStart() {
	if (!playerSpriteTexture.loadFromFile("res/img/pirate.png")) {
		throw std::invalid_argument("Loading error with sprite!");
	}

	if (!backgroundTexture.loadFromFile("res/img/background1.png")) {
		throw std::invalid_argument("Loading error with background!");
	}

	if (!policeSpriteTexture.loadFromFile("res/img/police.png")) {
		throw std::invalid_argument("Loading error with poliz!");
	}

	if (!armySpriteTexture.loadFromFile("res/img/army1.png")) {
		throw std::invalid_argument("Loading error with army!");
	}
	if (!armyShootingTexture.loadFromFile("res/img/armybullet.png")) {
		throw std::invalid_argument("Loading error with army!");
	}
	if (!policeShootingTexure.loadFromFile("res/img/policebullet.png")) {
		throw std::invalid_argument("Loading error with army!");
	}
	if (!playerShootingTexture.loadFromFile("res/img/smallbullet1.png")) {
		throw std::invalid_argument("Loading error with gunfire!");
	}

	if (!powerupChestTexture.loadFromFile("res/img/chest1.png")) {
		throw std::invalid_argument("Loading error with chest!");
	}

	if (!font.loadFromFile("res/fonts/Treamd.ttf")) {
		throw std::invalid_argument("Loading error with font!");
	}

	// Set the start position of the user sprite
	playerSprite.setPosition(130.0f, 300.0f);
	playerSpriteRectangle.setPosition(130.0f, 300.0f);
	playerSpriteRectangle.setSize(Vector2f(41.0f, 50.0f));

	float startingDistancesY[100];
	for (int i = 0; i < 100; i++) {
		startingDistancesY[i] = 100.0f + (i*60.0f);
	}

	float startingDistancesX[6] = { 32.0f, 82.0f, 134.0f, 186.0f, 238.0f, 290.0f, };
	
	srand(time(0));
	// Setup police boat
	for (int i = 0; i < sysPolice; i++) {
		int x = rand() % 5;
		int y = rand() % sysPolice * 2;
		policeBoatSprite[i].setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));
		policeBoatRectangle[i].setSize(Vector2f(41.0f, 50.0f));
		policeBoatRectangle[i].setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));
		policeBoatHealth[i] = 0;
	}

	// Setup army boats
	for (int i = 0; i < sysArmy; i++) {
		int x = rand() % 5;
		int y = rand() % sysArmy * 2;
		armyBoatSprite[i].setPosition(startingDistancesX[x], -(startingDistancesY[y]));
		//std::cout << "Army Boat deployed at: " << startingDistancesX[x] << " -" << startingDistancesY[y] << std::endl;
		armyBoatRectangle[i].setSize(Vector2f(41.0f, 50.0f));
		armyBoatRectangle[i].setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));
		armyBoatHealth[i] = 0;
	}

	// Set the position to off the players bullets of screen
	for (int i = 0; i < 30; i++) {
		playerShootingSprite[i].setPosition(-10.0f, -10.0f);
		playerShootingSpriteAvailable[i] = true;
	}

	for (int i = 0; i < sysPolice; i++) {
		policeBoatShootingSprite[i].setPosition(-1300.0f, -10.0f);
		isPoliceBulletActive[i] = false;
	}

	for (int i = 0; i < sysArmy; i++) {
		armyBoatShootingSprite[i].setPosition(-1300.0f, -10.0f);
		isArmyBulletActive[i] = false;
	}

	int x = rand() % 5;
	int y = rand() % sysArmy * 2;

	powerupChestSprite.setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));
	powerupChestRectangle.setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));
	powerupChestRectangle.setSize(Vector2f(50.0f, 50.0f));

	// Variables that reset each round
	if (newGame) {
		userHealth = 100;
		newGame = false;
		userScore = 0;
		userHasNoHealth = false;
		newLevel = true;
	}
	userBullets = 30;
	for (int i = 0; i < 30; i++) {
		// Reset all player bullets
		playerShootingSpriteAvailable[i] = true;
		playerShootingSpriteActive[i] = false;
	}

	// Setup game texts
	setupStartTexts();
}

void UpdateGameOver() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	if (nameInput.getSize() < 6) {
		if (!key[0] && (Keyboard::isKeyPressed(Keyboard::Space))) {
			std::cout << "Space" << std::endl;
			nameInput += " ";
			key[0] = true;
		}
		if (!key[1] && (Keyboard::isKeyPressed(Keyboard::A))) {
			std::cout << "A" << std::endl;
			nameInput += "A";
			key[1] = true;
		}
		if (!key[2] && (Keyboard::isKeyPressed(Keyboard::B))) {
			std::cout << "B" << std::endl;
			nameInput += "B";
			key[2] = true;
		}
		if (!key[3] && (Keyboard::isKeyPressed(Keyboard::C))) {
			std::cout << "C" << std::endl;
			nameInput += "C";
			key[3] = true;
		}
		if (!key[4] && (Keyboard::isKeyPressed(Keyboard::D))) {
			std::cout << "D" << std::endl;
			nameInput += "D";
			key[4] = true;
		}
		if (!key[5] && (Keyboard::isKeyPressed(Keyboard::E))) {
			std::cout << "E" << std::endl;
			nameInput += "E";
			key[5] = true;
		}
		if (!key[6] && (Keyboard::isKeyPressed(Keyboard::F))) {
			std::cout << "F" << std::endl;
			nameInput += "F";
			key[6] = true;
		}
		if (!key[7] && (Keyboard::isKeyPressed(Keyboard::G))) {
			std::cout << "G" << std::endl;
			nameInput += "G";
			key[7] = true;
		}
		if (!key[8] && (Keyboard::isKeyPressed(Keyboard::H))) {
			std::cout << "H" << std::endl;
			nameInput += "H";
			key[8] = true;
		}
		if (!key[9] && (Keyboard::isKeyPressed(Keyboard::I))) {
			std::cout << "I" << std::endl;
			nameInput += "I";
			key[9] = true;
		}
		if (!key[10] && (Keyboard::isKeyPressed(Keyboard::J))) {
			std::cout << "J" << std::endl;
			nameInput += "J";
			key[10] = true;
		}
		if (!key[11] && (Keyboard::isKeyPressed(Keyboard::K))) {
			std::cout << "K" << std::endl;
			nameInput += "K";
			key[11] = true;
		}
		if (!key[12] && (Keyboard::isKeyPressed(Keyboard::L))) {
			std::cout << "L" << std::endl;
			nameInput += "L";
			key[12] = true;
		}
		if (!key[13] && (Keyboard::isKeyPressed(Keyboard::M))) {
			std::cout << "M" << std::endl;
			nameInput += "M";
			key[13] = true;
		}
		if (!key[14] && (Keyboard::isKeyPressed(Keyboard::N))) {
			std::cout << "N" << std::endl;
			nameInput += "N";
			key[14] = true;
		}
		if (!key[15] && (Keyboard::isKeyPressed(Keyboard::O))) {
			std::cout << "O" << std::endl;
			nameInput += "O";
			key[15] = true;
		}
		if (!key[16] && (Keyboard::isKeyPressed(Keyboard::P))) {
			std::cout << "P" << std::endl;
			nameInput += "P";
			key[16] = true;
		}
		if (!key[17] && (Keyboard::isKeyPressed(Keyboard::Q))) {
			std::cout << "Q" << std::endl;
			nameInput += "Q";
			key[17] = true;
		}
		if (!key[18] && (Keyboard::isKeyPressed(Keyboard::R))) {
			std::cout << "R" << std::endl;
			nameInput += "R";
			key[18] = true;
		}
		if (!key[19] && (Keyboard::isKeyPressed(Keyboard::S))) {
			std::cout << "S" << std::endl;
			nameInput += "S";
			key[19] = true;
		}
		if (!key[20] && (Keyboard::isKeyPressed(Keyboard::T))) {
			std::cout << "T" << std::endl;
			nameInput += "T";
			key[20] = true;
		}
		if (!key[21] && (Keyboard::isKeyPressed(Keyboard::U))) {
			std::cout << "U" << std::endl;
			nameInput += "U";
			key[21] = true;
		}
		if (!key[22] && (Keyboard::isKeyPressed(Keyboard::V))) {
			std::cout << "V" << std::endl;
			nameInput += "V";
			key[22] = true;
		}
		if (!key[23] && (Keyboard::isKeyPressed(Keyboard::W))) {
			std::cout << "W" << std::endl;
			nameInput += "W";
			key[23] = true;
		}
		if (!key[24] && (Keyboard::isKeyPressed(Keyboard::X))) {
			std::cout << "X" << std::endl;
			nameInput += "X";
			key[24] = true;
		}
		if (!key[25] && (Keyboard::isKeyPressed(Keyboard::Y))) {
			std::cout << "Y" << std::endl;
			nameInput += "Y";
			key[25] = true;
		}
		if (!key[26] && (Keyboard::isKeyPressed(Keyboard::Z))) {
			std::cout << "Z" << std::endl;
			nameInput += "Z";
			key[26] = true;
		}
	}

	// If name enter contains a character allow removal
	if (nameInput.getSize() > 0) {
		if (!key[27] && (Keyboard::isKeyPressed(Keyboard::BackSpace))) {
			std::cout << "Back" << std::endl;
			nameInput.erase(nameInput.getSize() - 1, 1);
			key[27] = true;
		}
		if (!key[28] && (Keyboard::isKeyPressed(Keyboard::Delete))) {
			std::cout << "Back" << std::endl;
			nameInput.erase(nameInput.getSize() - 1, 1);
			key[28] = true;
		}
	}

	// Output the inputted string
	nameInputOutput.setString(nameInput);

	// If keys are not pressed then update boolean
	if (!Keyboard::isKeyPressed(Keyboard::Space)) {
		key[0] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::A)) {
		key[1] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::B)) {
		key[2] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::C)) {
		key[3] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::D)) {
		key[4] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::E)) {
		key[5] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::F)) {
		key[6] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::G)) {
		key[7] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::H)) {
		key[8] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::I)) {
		key[9] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::J)) {
		key[10] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::K)) {
		key[11] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::L)) {
		key[12] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::M)) {
		key[13] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::N)) {
		key[14] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::O)) {
		key[15] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::P)) {
		key[16] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Q)) {
		key[17] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::R)) {
		key[18] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::S)) {
		key[19] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::T)) {
		key[20] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::U)) {
		key[21] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::V)) {
		key[22] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::W)) {
		key[23] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::X)) {
		key[24] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Y)) {
		key[25] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Z)) {
		key[26] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::BackSpace)) {
		key[27] = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Delete)) {
		key[28] = false;
	}
}

void UpdateMenu() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	Vector2f move;

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -2.0f) {
		move.x--;
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 4.0f) {
		move.x++;
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -8.0f) {
		move.y--;
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 84.0f) {
		move.y++;
	}
	mouseMenuSprite.move(move*100.0f*dt);
	std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
}

void UpdateOpitions() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
}

void UpdatePause() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
}

void UpdateComplete() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
}

void UpdateHighscores() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
}

// Update method which stores a clock and handles the movement of the default user sprite - called while window is open
void UpdateStart() {
  // Create clocks
  static sf::Clock clock;
  static sf::Clock gameClock;

  // If a new level has begun then reset clocks as they are on a seprate thread
  if (newLevel) {
	  clock.restart().Zero;
	  gameClock.restart().Zero;
	  newLevel = false;
  }
  float dt = clock.restart().asSeconds();
  float gameTime = gameClock.getElapsedTime().asSeconds();

  Vector2f move;
  Vector2f downMovement;
  Vector2f upMovement;

  // Once the game has been going for 5 seconds, hide label
  if (gameTime > 0.5f) {
	  gameCountDownTimer.setString("");
  }

  // Set the downMovement for enemy ships
  downMovement.y++;

  // Set the upMovement for gun fire
  upMovement.y--;

  // If keys are pressed then move users sprite
  if (!leftNotAllowed) {
	  if (Keyboard::isKeyPressed(Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -2.0f) {
		  move.x--;
	  }
  }
  if (!rightNotAllowed) {
	  if (Keyboard::isKeyPressed(Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 4.0f) {
		  move.x++;
	  }
  }
  // Update player movement
  playerSprite.move(move*100.0f*dt);
  playerSpriteRectangle.move(move*100.0f*dt);

  // If space is not currently pressed
  if (isSpacePressed == false) {
	  // If space is pressed 
	  if (Keyboard::isKeyPressed(Keyboard::Space)) {
		  // Set boolean to true
		  isSpacePressed = true;
		  // For all bullets
		  for (int i = 0; i < 30; i++) {
			  // If bullet is avaiable - default true
			  if (playerShootingSpriteAvailable[i] == true)
			  {
				  // Set bullet to active
				  playerShootingSpriteActive[i] = true;
				  // Set position to boat
				  playerShootingSprite[i].setPosition((playerSprite.getPosition().x) + 20.0f, (playerSprite.getPosition().y) - 20.0f);
				  // Set bullet to not available
				  playerShootingSpriteAvailable[i] = false;
				  // Lower the users bullet count
				  userBullets -= 1;
				  // break as bullet has been selected
				  break;
			  }
		  }
	  }
  }

	// If space bar is realised - set to false
	if (!Keyboard::isKeyPressed(Keyboard::Space)) {
		isSpacePressed = false;
	}

	// If space is not currently pressed
	if (isControllerButtonPressed == false) {
		// If space is pressed 
		if (sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
			// Set boolean to true
			isControllerButtonPressed = true;
			// For all bullets
			for (int i = 0; i < 30; i++) {
				// If bullet is avaiable - default true
				if (playerShootingSpriteAvailable[i] == true)
				{
					// Set bullet to active
					playerShootingSpriteActive[i] = true;
					// Set position to boat
					playerShootingSprite[i].setPosition((playerSprite.getPosition().x) + 20.0f, (playerSprite.getPosition().y) - 20.0f);
					// Set bullet to not available
					playerShootingSpriteAvailable[i] = false;
					// Lower the users bullet count
					userBullets -= 1;
					// break as bullet has been selected
					break;
				}
			}
		}
	}

	// If space bar is realised - set to false
	if (!sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
		isControllerButtonPressed = false;
	}

	/*
	if (!sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
		isSpacePressed = false;
		isControllerButtonPressed
	}
	*/

	// Method which updates the bullets position
	moveTheBullets(upMovement, dt);

	// For loop which moves the police boats
	for (int i = 0; i < sysPolice; i++) {
		if (policeBoatSprite[i].getPosition().x > 29.0f) {
			policeBoatSprite[i].move(Vector2f(0.0f, sysSpeed*dt));
			//std::cout << policeBoatSprite[1].getPosition().y << std::endl;
			policeBoatRectangle[i].move(Vector2f(0.0f, sysSpeed*dt));
		}
	}  

	// For loop which moves the army boats
	for (int i = 0; i < sysArmy; i++) {
		armyBoatSprite[i].move(downMovement*sysSpeed*dt);
		armyBoatRectangle[i].move(downMovement*sysSpeed*dt);
	}

  // Move the powerup chest down the screen
  powerupChestSprite.move(downMovement*sysSpeed*dt);
  powerupChestRectangle.move(downMovement*sysSpeed*dt);

  // Double for loop - one boats and other for bullets
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < sysPolice; j++){
			// If the police boat contains the bullet then
			if (policeBoatRectangle[j].getGlobalBounds().contains(playerShootingSprite[i].getPosition())) {
				// Deducted 5 health
				policeBoatHealth[j] -= 5;
				// Reset bullet posotion
				playerShootingSprite[i].setPosition(-10.0f, -10.0f);
				// Make bullet available
				playerShootingSpriteAvailable[i] = true;
				// Add one to user bullets 
				userBullets += 1;
				// Deactivate bullet
				playerShootingSpriteActive[i] = false;
				// Award user some score
				userScore += 1;
				// If boat has been hit by 4 bullets
				if (policeBoatHealth[j] < -18) {
					// Reset position
					policeBoatSprite[j].setPosition(-500.0f, -200.0f);
					// Reset rectangle
					policeBoatRectangle[j].setPosition(-500.0f, -200.0f);
					// Lower counter
					userRemaingBoats -= 1;
					// Print
					std::cout << "Police boat destroyed!"<< j << std::endl;
					// Award user score
					userScore += 10;
					// Break for loop - goto allows double break and skips to label
					goto enloop;
				}
			}
		}
	}
 
enloop:

	// Double for loop - one boats and other for bullets
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < sysArmy; j++) {
			// If the police boat contains the bullet then
			if (armyBoatRectangle[j].getGlobalBounds().contains(playerShootingSprite[i].getPosition())) {
				// Deducted 5 health
				armyBoatHealth[j] -= 5;
				// Reset bullet posotion
				playerShootingSprite[i].setPosition(-10.0f, -10.0f);
				// Make bullet available
				playerShootingSpriteAvailable[i] = true;
				// Add one to user bullets 
				userBullets += 1;
				// Deactivate bullet
				playerShootingSpriteActive[i] = false;
				// Award user some score
				userScore += 1;
				// If boat has been hit by 6 bullets
				if (armyBoatHealth[j] < -28) {
					// Reset position
					armyBoatSprite[j].setPosition(-400.0f, -200.0f);
					// Reset rectangle
					armyBoatRectangle[j].setPosition(-400.0f, -200.0f);
					// Print
					std::cout << "Army boat destroyed!" << std::endl;
					// Lower counter
					userRemaingBoats -= 1;
					// Award user score
					userScore += 10;
					// Break for loop - goto allows double break and skips to label
					goto enloop1;
				}
			}
		}
	}

enloop1:

	// Code for collision between bullet and powerup sprite
	for (int i = 0; i < 30; i++) {
		if (powerupChestRectangle.getGlobalBounds().contains(playerShootingSprite[i].getPosition())) {
			std::cout << "Powerup obtained!" << std::endl;
			powerupChestSprite.setPosition(-90.0f, -90.0f);
			powerupChestRectangle.setPosition(-90.0f, -90.0f);
			userHealth += 25;
			playerShootingSprite[i].setPosition(Vector2f(-10.0f, -10.0f));
		}
	}

	// If player collides with powerup
	if (playerSpriteRectangle.getGlobalBounds().intersects(powerupChestRectangle.getGlobalBounds())) {
		powerupChestSprite.setPosition(-90.0f, -90.0f);
		powerupChestRectangle.setPosition(-90.0f, -90.0f);
		userHealth += 10;
	}

  // If the police boats get off screen
  for (int i = 0; i < sysPolice; i++) {
	  if (policeBoatSprite[i].getPosition().y > 400.0f && policeBoatSprite[i].getPosition().x > 29.0f)
	  {
		  // Print
		  std::cout << "The convoy has been hit!!! -10 Health!" << std::endl;
		  // Lower users health
		  userHealth -= 10;
		  // Reset boat position
		  policeBoatSprite[i].setPosition(-70.0f, -10.0f);
		  // Reset rectangle
		  policeBoatRectangle[i].setPosition(-70.0f, -10.0f);
		  // Lower counter
		  userRemaingBoats -= 1;
	  }
  }

  // If the army boats get off screen
  for (int i = 0; i < sysArmy; i++) {
	  if (armyBoatSprite[i].getPosition().y > 400.0f && armyBoatSprite[i].getPosition().x > 29.0f)
	  {
		  // Print
		  std::cout << "The convoy has been hit!!! -20 Health!" << std::endl;
		  // Lower users health
		  userHealth -= 20;
		  // Reset boat position
		  armyBoatSprite[i].setPosition(-70.0f, -10.0f);
		  // Reset rectangle
		  armyBoatRectangle[i].setPosition(-70.0f, -10.0f);
		  // Lower counter
		  userRemaingBoats -= 1;
	  }
  }

  // If a police boat and player boat direct hit - for all police boats
  for (int i = 0; i < sysPolice; i++) {
	  // If the police boat contains player boat then - 20 is added as the midpoint
	  if (policeBoatRectangle[i].getGlobalBounds().contains(playerSprite.getPosition()+Vector2f(20.0f, 0.0f))) {
		  // Print
		  std::cout << "Direct hit! -50 Helath! 3333" << std::endl;
		  // Lower users health
		  userHealth -= 50;
		  // Reset boat position
		  policeBoatSprite[i].setPosition(-50.0f, -10.0f);
		  // Reset rectangle
		  policeBoatRectangle[i].setPosition(-10.0f, -10.0f);
		  // Lower counter
		  userRemaingBoats -= 1;
	  }
  }

  // If a army boat and player boat direct hit - for all police boats
  for (int i = 0; i < sysArmy; i++) {
	  // If the army boat contains player boat then - 20 is added as the midpoint
	  if (armyBoatRectangle[i].getGlobalBounds().contains(playerSprite.getPosition() + Vector2f(20.0f, 0.0f))) {
		  // Print
		  std::cout << "Direct hit! -50 Helath! 4444 " << std::endl;
		  // Lower users health
		  userHealth -= 50;
		  // Reset boat position
		  armyBoatSprite[i].setPosition(-50.0f, -10.0f);
		  // Reset rectangle
		  armyBoatRectangle[i].setPosition(-10.0f, -10.0f);
		  // Lower counter
		  userRemaingBoats -= 1;
	  }
  }

  // Random array of possible starting positions
  float arr[9] = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f };
  // Reset random gen

  // For all police bullets
  for (int i = 0; i < sysPolice; i++) {
	  // If bullet isnt active
	  if (!isPoliceBulletActive[i]) {
		  // Get random number
		  int starto = rand() % 8;
		  // If police boat is great than random number on y axis and in play
		  if (policeBoatSprite[i].getPosition().y > arr[starto] && policeBoatSprite[i].getPosition().x > 10.0f) {
			  // Set the bullet to fire from the boat
			  policeBoatShootingSprite[i].setPosition(Vector2f((policeBoatSprite[i].getPosition().x) + 18.0f, (policeBoatSprite[i].getPosition().y) + 50.0f));
			  // Set bullet to active
			  isPoliceBulletActive[i] = true;
		  }
	  }
	  // If bullet is active
	  else
	  {
		  // Update
		  policeBoatShootingSprite[i].move(downMovement*150.0f*dt);
	  }
  }

  // For all army bullets
  for (int i = 0; i < sysArmy; i++) {
	  // If bullet isnt active
	  if (!isArmyBulletActive[i]) {
		  // Get random number
		  int starto = rand() % 8;
		  // If police boat is great than random number on y axis and in play
		  if (armyBoatSprite[i].getPosition().y > arr[starto] && armyBoatSprite[i].getPosition().x > 10.0f) {
			  // Set the bullet to fire from the boat
			  armyBoatShootingSprite[i].setPosition(Vector2f((armyBoatSprite[i].getPosition().x) + 18.0f, (armyBoatSprite[i].getPosition().y) + 50.0f));
			  // Set bullet to active
			  isArmyBulletActive[i] = true;
		  }
	  }
	  // If bullet is active
	  else
	  {
		  // Update
		  armyBoatShootingSprite[i].move(downMovement*150.0f*dt);
	  }
  }

  // For all policebullets
  for (int i = 0; i < sysPolice; i++) {
	  // If police bullets hit player boat then
	  if (playerSpriteRectangle.getGlobalBounds().contains(policeBoatShootingSprite[i].getPosition()+(Vector2f(0.0f, 20.0f)))) {
		  // Print
		  std::cout << "Boat hit" << std::endl;
		  // Lower userHealth by 10
		  userHealth -= 10;
		  // Hide missile
		  policeBoatShootingSprite[i].setPosition(Vector2f(-10.0f, -10.0f));
	  }
  }

  // For all army bullets
  for (int i = 0; i < sysArmy; i++) {
	  // If police bullets hit player boat then
	  if (playerSpriteRectangle.getGlobalBounds().contains(armyBoatShootingSprite[i].getPosition() + (Vector2f(0.0f, 20.0f)))) {
		  // Print
		  std::cout << "Boat hit" << std::endl;
		  // Lower userHealth by 10
		  userHealth -= 10;
		  // Hide missile
		  armyBoatShootingSprite[i].setPosition(Vector2f(-10.0f, -10.0f));
	  }
  }

  std::stringstream stream;
  stream << "SCORE: " << userScore;

  // Update various labels
  scoreText.setString(stream.str());
  healthText.setString("HEALTH: " + std::to_string(userHealth));
  bulletsAvailableCounter.setString("BULLETS: " + std::to_string(userBullets) + "/30");
  enemyBoatsLeft.setString("REMAIN: " + std::to_string(userRemaingBoats));
  
  // If statement limiting the player to go to far left
  if (playerSprite.getPosition().x < 25.0f) {
	  std::cout << "To far left";
	  leftNotAllowed = true;
  }
  else {
	  leftNotAllowed = false;
  }

  // If statement limiting the player from going to far right
  if (playerSprite.getPosition().x > 330.0f) {
	  std::cout << "To far right";
	  rightNotAllowed = true;
  }
  else {
	  rightNotAllowed = false;
  }

  if (userHealth <= 1) {
	  userHasNoHealth = true;
  }

  if (userRemaingBoats == 0){
	  levelComplete = true;
  }
}

void RenderPause(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	window.draw(pauseExitSprite);
	window.draw(pauseResumeSprite);
}

// Render method for the complete screen
void RenderComplete(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	window.draw(completeMessage);
	window.draw(completeNext);
	window.draw(completeExit);
}

// Render method for the complete screen
void RenderOpitions(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	window.draw(fourOptionSprite);
	window.draw(eightOptionSprite);
	window.draw(fullOptionSprite);
	window.draw(returnOptionSprite);
}

// Render method for the highscores screen
void RenderHighscores(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	window.draw(highscoresSprite);
	window.draw(namescoreSprite);
	window.draw(returnSprite);

	for (int i = 0; i < 5; i++) {
		window.draw(displayNames[i]);
		window.draw(displayScores[i]);
	}
}

// Render method for the menu screen
void RenderMenu(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	// Draw all the button values
	window.draw(startButtonMenuSprite);
	window.draw(highscoreButtonMenuSprite);
	window.draw(weblinkButtonMenuSprite);
	window.draw(exitButtonMenuSprite);
	window.draw(optionsButtonMenuSprite);
	window.draw(mouseMenuSprite);
}

// Render method for game over screen
void RenderGameOver(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	window.draw(gameOverSprite);
	window.draw(enterNameSprite);
	window.draw(confirmSprite);
	window.draw(nameInputOutput);
}

// Render method for the start screen
void RenderStart(RenderWindow &window) { 
	window.draw(backgroundMenuSprite);
	window.draw(playerSprite);
	for (int i = 0; i < sysPolice; i++) {
		window.draw(policeBoatSprite[i]);
		window.draw(policeBoatShootingSprite[i]);
	}
	for (int i = 0; i < sysArmy; i++) {
		window.draw(armyBoatSprite[i]);
		window.draw(armyBoatShootingSprite[i]);
	}
	for (int i = 0; i < 30; i++) {
		window.draw(playerShootingSprite[i]);
	}
	window.draw(powerupChestSprite);
	window.draw(enemyBoatsLeft);
	window.draw(scoreText);
	window.draw(healthText);
	window.draw(bulletsAvailableCounter);
	window.draw(gameCountDownTimer);
}

// Main method which runs everything
int main() {
	// Set the gamestate the the default start
  GameStates gameState = GameStates::STATE_MENU;
  // Set the window and its size
  RenderWindow window(VideoMode(400, 400), "Pirates of the Firth of Forth!", Style::Default);
 
  int winX = window.getSize().x;
  int winY = window.getSize().y;
  int scaleR = 1;

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed){
        window.close();
      }
    }
	// If escape is pressed close window
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

	switch (gameState) {
		// Main Menu
		case GameStates::STATE_MENU:
			// If load has not been called then
			if (!hasLoadMenuBeenCalled) {
				// Call the load method
				try {
					LoadMenu(winX, winY);
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				hasLoadMenuBeenCalled = true;
			}

			// Bind all the sprites to textures
			backgroundMenuSprite.setTexture(backgroundMenuTexture);
			startButtonMenuSprite.setTexture(startButtonMenuTexture);
			highscoreButtonMenuSprite.setTexture(highscoreButtonMenuTexture);
			weblinkButtonMenuSprite.setTexture(weblinkButtonMenuTexture);
			exitButtonMenuSprite.setTexture(exitButtonMenuTexture);
			optionsButtonMenuSprite.setTexture(optionsButtonMenuTexture);
			mouseMenuSprite.setTexture(mouseMenuTexture);

			// Pos x = 100, y = 100
			startButtonMenuRect.setPosition((winX / 2) - (winX / 4), (winY / 2) - (winY / 4));
			startButtonMenuRect.setSize(Vector2f((winX / 2), (winY / 8)));

			// Pos x = 100, y = 150
			highscoreButtonMenuRect.setPosition((winX / 2) - (winX / 4), (winY / 2) - (winY / 8));
			highscoreButtonMenuRect.setSize(Vector2f((winX / 2), (winY / 8)));

			// Pos x = 100, y = 200
			weblinkButtonMenuRect.setPosition((winX / 2) - (winX / 4), (winY / 2));
			weblinkButtonMenuRect.setSize(Vector2f((winX / 2), (winY / 8)));

			optionsButtonMenuRect.setPosition((winX / 2) - (winX / 4), (winY / 2) + (winY / 8));
			optionsButtonMenuRect.setSize(Vector2f((winX / 2), (winY / 8)));

			// Pos x = 100, y = 250
			exitButtonMenuRect.setPosition((winX / 2) - (winX / 4), (winY / 2) + (winY / 4));
			exitButtonMenuRect.setSize(Vector2f((winX / 2), (winY / 8)));

			if (sf::Joystick::isConnected(0))
			{
				// joystick number 0 is connected
				//std::cout << "Controller" << std::endl;
				float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
				float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
				//std::cout << x << std::endl;
			}

			// Code for start button pressed
			if(Mouse::isButtonPressed(Mouse::Left) && startButtonMenuRect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
			{
				std::cout << "Start button pressed" << std::endl;
				hasCountDownBeenCalled = false;
				hasLoadStartBeenCalled = false;
				sysLevel = 1;
				newGame = true;
				gameState = GameStates::STATE_START;
			}

			// Code for highscores button pressed
			if (Mouse::isButtonPressed(Mouse::Left) && highscoreButtonMenuRect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "Highscores button pressed" << std::endl;
				//hasHighscoresBeenCalled = false;
				gameState = GameStates::STATE_HIGHSCORES;
			}

			// Code for weblink button pressed
			if (Mouse::isButtonPressed(Mouse::Left) && weblinkButtonMenuRect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "Weblink button pressed" << std::endl;
				ShellExecute(NULL, "open", "http://www.calumtempleton.com",
					NULL, NULL, SW_SHOWNORMAL);
			}

			// Code for weblink button pressed
			if (Mouse::isButtonPressed(Mouse::Left) && optionsButtonMenuRect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "Options button pressed" << std::endl;
				Sleep(300);
				gameState = GameStates::STATE_OPITIONS;
			}

			// Code for exit button pressed
			if (Mouse::isButtonPressed(Mouse::Left) && exitButtonMenuRect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "Exit button pressed" << std::endl;
				window.close();
			}

			window.clear();
			UpdateMenu();
			RenderMenu(window);
			window.display();

			break;
		case GameStates::STATE_PAUSE:
			// If load has not been called then
			if (!hasLoadPauseBeenCalled) {
				// Call the load method
				try {
					LoadPause(winX, winY);
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				hasLoadPauseBeenCalled = true;
			}

			pauseResumeSprite.setTexture(pauseResumeTexture);
			pauseExitSprite.setTexture(pauseExitTexture);

			pauseResumeRectangle.setPosition((winX / 4), (winY / 4) + (winY / 8));
			pauseResumeRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			pauseExitRectangle.setPosition((winX / 4), (winY / 2));
			pauseExitRectangle.setSize(Vector2f((winX / 2), (winY / 8)));


			// If return rectangle is clicked on 
			if (Mouse::isButtonPressed(Mouse::Left) && pauseResumeSprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				// Return user to main menu
				newLevel = true;
				gameState = GameStates::STATE_START;
			}

			// If return rectangle is clicked on 
			if (Mouse::isButtonPressed(Mouse::Left) && pauseExitSprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				// Return user to main menu
				gameState = GameStates::STATE_MENU;
			}

			window.clear();
			UpdatePause();
			RenderPause(window);
			window.display();

			break;
		// Case for starting the game
		case GameStates::STATE_START:
			// If the load method for the start screen hasnt been called
			if (!hasLoadStartBeenCalled) {
				try {
					// If user is on level one set values.... else different values
					if (sysLevel == 1) {
						sysPolice = 5;
						sysSpeed = 20.0f;
						sysArmy = 2;
						userRemaingBoats = sysPolice+sysArmy;
					}
					else if (sysLevel == 2) {
						sysPolice = 10;
						sysSpeed = 25.0f;
						sysArmy = 4;
						userRemaingBoats = sysPolice + sysArmy;
					}
					else if (sysLevel == 3) {
						sysPolice = 15;
						sysSpeed = 30.0f;
						sysArmy = 8;
						userRemaingBoats = sysPolice + sysArmy;
					}
					else if (sysLevel == 4) {
						sysPolice = 20;
						sysSpeed = 35.0f;
						sysArmy = 12;
						userRemaingBoats = sysPolice + sysArmy;
					}
					else if (sysLevel == 5) {
						sysPolice = 25;
						sysSpeed = 40.0f;
						sysArmy = 18;
						userRemaingBoats = sysPolice + sysArmy;
					}
					// Load the start method
					LoadStart();
				}
				// Catch with error
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				// Set load boolean to true
				hasLoadStartBeenCalled = true;
			}

			// Set the various textures
			backgroundMenuSprite.setTexture(backgroundTexture);
			playerSprite.setTexture(playerSpriteTexture);
			powerupChestSprite.setTexture(powerupChestTexture);

			backgroundSprite.setPosition(winX, winY);
	
			// For the various objects - boats and bullets set the textures
			for (int i = 0; i < 30; i++) {
				playerShootingSprite[i].setTexture(playerShootingTexture);
				policeBoatSprite[i].setTexture(policeSpriteTexture);
				armyBoatSprite[i].setTexture(armySpriteTexture);
				policeBoatShootingSprite[i].setTexture(policeShootingTexure);
				armyBoatShootingSprite[i].setTexture(armyShootingTexture);
			}

			// If the game countdown has not been called
			if (!hasCountDownBeenCalled) {
				// Rednder the game but dont call update
				window.clear();
				RenderStart(window);
				window.display();
				// Get the game to sleep to simulate a countdown
				Sleep(1000);
				// Set the bool to true;
				hasCountDownBeenCalled = true;
			}
			// If countdown has been called
			else 
			{
				// Set the game message to go
				gameCountDownTimer.setString("   GO!");
				// If the user has more than 0 health
				if (!userHasNoHealth) {
					// Start the game and get it going
					window.clear();
					UpdateStart();
					RenderStart(window);
					window.display();
				}
				// Else change game states to game over
				else 
				{
					gameState = GameStates::STATE_GAMEOVER;
				}
			}

			if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Key::P)) {
				std::cout << "P" << std::endl;
				Sleep(200);
				gameState = GameStates::STATE_PAUSE;
			}

			// If levelcomplete bool is true
			if (levelComplete) {
				// Change game states to level complete
				gameState = GameStates::STATE_COMPLETE;
			}
			break;
		// Case for highscore screen 
		case GameStates::STATE_HIGHSCORES:
			// If highscores hasnt been called or there has been a change
			if (!hasHighscoresBeenCalled || highscoreChanged == true) {
				try {
					// Load highscores
					LoadHighscores(winX, winY);
					// Set change to false as change has been loaded
					highscoreChanged = false;
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				// Set bool to true
				hasHighscoresBeenCalled = true;
			}

			// Show content
			window.clear();
			UpdateHighscores();
			RenderHighscores(window);
			window.display();

			// Bind textures to sprites
			highscoresSprite.setTexture(highscoresTexture);
			namescoreSprite.setTexture(namescoreTexture);
			returnSprite.setTexture(returnTexture);

			// Set position of return rectangle
			returnRectangle.setPosition((winX / 4), (winY / 8) + (winY / 4) + (winY / 2));
			returnRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			// If return rectangle is clicked on 
			if (Mouse::isButtonPressed(Mouse::Left) && returnRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				// Return user to main menu
				nameInput = "";
				gameState = GameStates::STATE_MENU;
			}
			break;
		// Case for game over
		case GameStates::STATE_GAMEOVER:
			// If game over hasnt been called
			if (!hasGameOverBeenCalled) {
				try {
					// Call game over
					LoadGameOver(winX, winY);
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				// Set bool to true
				hasGameOverBeenCalled = true;
			}

			// Display content
			window.clear();
			UpdateGameOver();
			RenderGameOver(window);
			window.display();

			// Set textures to sprites
			backgroundMenuSprite.setTexture(backgroundMenuTexture);
			gameOverSprite.setTexture(gameOverTexture);
			confirmSprite.setTexture(confirmTexture);
			enterNameSprite.setTexture(enterNameTexture);

			// Set position of confirmRectangle
			confirmRectangle.setPosition((winX / 4), (winY / 2) + (winY / 4));
			confirmRectangle.setSize(Vector2f((winX / 2), (winY / 8)));
			
			// If confirm rectangle is pressed
			if (Mouse::isButtonPressed(Mouse::Left) && confirmRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				//userHasNoHealth = false;
				//userHealth = 100;
				// For 20
				for (int i = 0; i < 20; i++) {
					// Get next avaiable place in array
					if (scores[i] == 0) {
						// Add user name and user score
						scores[i] = userScore;
						names[i] = nameInput;
						// Set bool to true
						highscoreChanged = true;
						break;
					}
				}
				// Go back to main menu
				gameState = GameStates::STATE_MENU;
			}
			
			break;
		case GameStates::STATE_COMPLETE:
			newLevel = true;
			if (!hasCompleteBeenCalled) {
				// Call the load method
				try {
					LoadComplete(winX, winY);
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				hasCompleteBeenCalled = true;
			}

			completeMessage.setTexture(completeMessageTexture);
			completeNext.setTexture(completeNextTexture);
			completeExit.setTexture(completeExitTexture);

			completeNextRectangle.setPosition((winX / 4), (winY / 2));
			completeNextRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			completeExitRectangle.setPosition((winX / 4), (winY / 8) + (winY / 2));
			completeExitRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			if (Mouse::isButtonPressed(Mouse::Left) && completeNextRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				hasCountDownBeenCalled = false;
				hasLoadStartBeenCalled = false;
				levelComplete = false;
				sysLevel += 1;
				gameState = GameStates::STATE_START;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && completeExitRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				userHasNoHealth = false;
				userHealth = 100;
				Sleep(200);
				gameState = GameStates::STATE_MENU;
			}

			window.clear();
			UpdateComplete();
			RenderComplete(window);
			window.display();
			break;
		case GameStates::STATE_OPITIONS:
			if (!hasOpitionsBeenCalled) {
				// Call the load method
				try {
					LoadOpitions(winX, winY);
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				hasOpitionsBeenCalled = true;
			}

			fourOptionSprite.setTexture(fourOptionTexture);
			eightOptionSprite.setTexture(eightOptionTexture);
			fullOptionSprite.setTexture(fullOptionTexture);
			returnOptionSprite.setTexture(returnOptionTexture);

			fourOptionRectangle.setPosition((winX / 4), (winY / 4));
			fourOptionRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			eightOptionRectangle.setPosition((winX / 4), (winY / 2) - (winY / 8));
			eightOptionRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			fullOptionRectangle.setPosition((winX / 4), (winY / 2));
			fullOptionRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			returnOptionRectangle.setPosition((winX / 4), (winY / 2) + (winY / 8));
			returnOptionRectangle.setSize(Vector2f((winX / 2), (winY / 8)));

			if (Mouse::isButtonPressed(Mouse::Left) && fourOptionRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "four" << std::endl;
				window.create(VideoMode(400, 400), "Pirates of the Firth of Forth!");
				winX = 400;
				winY = 400;
				LoadOpitions(winX, winY);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && eightOptionRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "eight" << std::endl;
				window.create(VideoMode(800, 800), "Pirates of the Firth of Forth!");
				scaleR = 2;
				backgroundMenuSprite.setScale(scaleR, scaleR);
				winX = 800;
				winY = 800;
				LoadOpitions(winX, winY);

			}

			if (Mouse::isButtonPressed(Mouse::Left) && fullOptionRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "full" << std::endl;
				backgroundMenuSprite.setScale(4.8f, 2.7f);
				window.create(VideoMode(1920.0f, 1080.0f), "Pirates of the Firth of Forth!", Style::Fullscreen);	
			}

			if (Mouse::isButtonPressed(Mouse::Left) && returnOptionRectangle.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
				std::cout << "Ret" << std::endl;
				Sleep(200);
				gameState = GameStates::STATE_MENU;
			}

			window.clear();
			UpdateOpitions();
			RenderOpitions(window);
			window.display();
	}
  }

  return 0;
}