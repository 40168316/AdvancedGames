#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <windows.h>

// Adds sf in front of everything to reference the library
using namespace sf;

Texture playerSpriteTexture, backgroundTexture, enemySpriteTexture, playerShootingTexture, powerupChestTexture, backgroundMenuTexture, buttonMenuTexture;
Sprite playerSprite, backgroundSprite, backgroundMenuSprite, startButtonMenuSprite, highscoreButtonMenuSprite, weblinkButtonMenuSprite, exitButtonMenuSprite, powerupChestSprite;
Font font;
Text scoreText, healthText, gameOverText, startMenuText, highscoreMenuText, weblinkMenuText, exitMenuText, gameCountDownTimer, bulletsAvailableCounter;

bool leftNotAllowed = false;
bool rightNotAllowed = false;
bool powerupObtained = false;
bool enemyShipHide = false;

// Havethe load methods been called
bool hasLoadStartBeenCalled = false, hasLoadMenuBeenCalled = false, hasCountDownBeenCalled = false;

// Used to hold user information
int userScore = 0, userHealth = 10, userBullets = 30;

// Used for player ship
Sprite playerShootingSprite[30];
bool playerShootingSpriteAvailable[30], playerShootingSpriteActive[30];

// Used to detect if player has pressed buttons
bool isSpacePressed = false;

// Used for police boats
Sprite policeBoatSprite[30];
RectangleShape policeBoatRectangle[30];
int policeBoatHealth[30];
bool hasPlayerShootingSpriteHitPoliceBoat[30];


// Method which gholds the different gamestates
enum class GameStates
{
	STATE_START = 1,
	STATE_MENU = 2,
	STATE_OPTIONS = 3,
	STATE_LEVEL = 4,
	STATE_HIGHSCORES = 5,
};

// Method which moves the bullets
void moveTheBullets(Vector2f upMovement, float dt) {
	// If bullet is active then
	if (playerShootingSpriteActive[0]) {
		// Move bullet
		playerShootingSprite[0].move(upMovement*20.0f*dt);
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
		playerShootingSprite[1].move(upMovement*20.0f*dt);
		if (playerShootingSprite[1].getPosition().y < -20.0f) {
			playerShootingSprite[1].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[1] = true;
			userBullets += 1;
			playerShootingSpriteActive[1] = false;
		}
	}

	if (playerShootingSpriteActive[2]) {
		playerShootingSprite[2].move(upMovement*20.0f*dt);
		if (playerShootingSprite[2].getPosition().y < -20.0f) {
			playerShootingSprite[2].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[2] = true;
			userBullets += 1;
			playerShootingSpriteActive[2] = false;
		}
	}

	if (playerShootingSpriteActive[3]) {
		playerShootingSprite[3].move(upMovement*20.0f*dt);
		if (playerShootingSprite[3].getPosition().y < -20.0f) {
			playerShootingSprite[3].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[3] = true;
			userBullets += 1;
			playerShootingSpriteActive[3] = false;
		}
	}

	if (playerShootingSpriteActive[4]) {
		playerShootingSprite[4].move(upMovement*20.0f*dt);
		if (playerShootingSprite[4].getPosition().y < -20.0f) {
			playerShootingSprite[4].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[4] = true;
			userBullets += 1;
			playerShootingSpriteActive[4] = false;
		}
	}

	if (playerShootingSpriteActive[5]) {
		playerShootingSprite[5].move(upMovement*20.0f*dt);
		if (playerShootingSprite[5].getPosition().y < -20.0f) {
			playerShootingSprite[5].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[5] = true;
			userBullets += 1;
			playerShootingSpriteActive[5] = false;
		}
	}

	if (playerShootingSpriteActive[6]) {
		playerShootingSprite[6].move(upMovement*20.0f*dt);
		if (playerShootingSprite[6].getPosition().y < -20.0f) {
			playerShootingSprite[6].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[6] = true;
			userBullets += 1;
			playerShootingSpriteActive[6] = false;
		}
	}

	if (playerShootingSpriteActive[7]) {
		playerShootingSprite[7].move(upMovement*20.0f*dt);
		if (playerShootingSprite[7].getPosition().y < -20.0f) {
			playerShootingSprite[7].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[7] = true;
			userBullets += 1;
			playerShootingSpriteActive[7] = false;
		}
	}

	if (playerShootingSpriteActive[8]) {
		playerShootingSprite[8].move(upMovement*20.0f*dt);
		if (playerShootingSprite[8].getPosition().y < -20.0f) {
			playerShootingSprite[8].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[8] = true;
			userBullets += 1;
			playerShootingSpriteActive[8] = false;
		}
	}

	if (playerShootingSpriteActive[9]) {
		playerShootingSprite[9].move(upMovement*20.0f*dt);
		if (playerShootingSprite[9].getPosition().y < -20.0f) {
			playerShootingSprite[9].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[9] = true;
			userBullets += 1;
			playerShootingSpriteActive[9] = false;
		}
	}

	if (playerShootingSpriteActive[10]) {
		playerShootingSprite[10].move(upMovement*20.0f*dt);
		if (playerShootingSprite[10].getPosition().y < -20.0f) {
			playerShootingSprite[10].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[10] = true;
			userBullets += 1;
			playerShootingSpriteActive[10] = false;
		}
	}

	if (playerShootingSpriteActive[11]) {
		playerShootingSprite[11].move(upMovement*20.0f*dt);
		if (playerShootingSprite[11].getPosition().y < -20.0f) {
			playerShootingSprite[11].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[11] = true;
			userBullets += 1;
			playerShootingSpriteActive[11] = false;
		}
	}

	if (playerShootingSpriteActive[12]) {
		playerShootingSprite[12].move(upMovement*20.0f*dt);
		if (playerShootingSprite[12].getPosition().y < -20.0f) {
			playerShootingSprite[12].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[12] = true;
			userBullets += 1;
			playerShootingSpriteActive[12] = false;
		}
	}

	if (playerShootingSpriteActive[13]) {
		playerShootingSprite[13].move(upMovement*20.0f*dt);
		if (playerShootingSprite[13].getPosition().y < -20.0f) {
			playerShootingSprite[13].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[13] = true;
			userBullets += 1;
			playerShootingSpriteActive[13] = false;
		}
	}

	if (playerShootingSpriteActive[14]) {
		playerShootingSprite[14].move(upMovement*20.0f*dt);
		if (playerShootingSprite[14].getPosition().y < -20.0f) {
			playerShootingSprite[14].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[14] = true;
			userBullets += 1;
			playerShootingSpriteActive[14] = false;
		}
	}

	if (playerShootingSpriteActive[15]) {
		playerShootingSprite[15].move(upMovement*20.0f*dt);
		if (playerShootingSprite[15].getPosition().y < -20.0f) {
			playerShootingSprite[15].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[15] = true;
			userBullets += 1;
			playerShootingSpriteActive[15] = false;
		}
	}

	if (playerShootingSpriteActive[16]) {
		playerShootingSprite[16].move(upMovement*20.0f*dt);
		if (playerShootingSprite[16].getPosition().y < -20.0f) {
			playerShootingSprite[16].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[16] = true;
			userBullets += 1;
			playerShootingSpriteActive[16] = false;
		}
	}

	if (playerShootingSpriteActive[17]) {
		playerShootingSprite[17].move(upMovement*20.0f*dt);
		if (playerShootingSprite[17].getPosition().y < -20.0f) {
			playerShootingSprite[17].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[17] = true;
			userBullets += 1;
			playerShootingSpriteActive[17] = false;
		}
	}

	if (playerShootingSpriteActive[18]) {
		playerShootingSprite[18].move(upMovement*20.0f*dt);
		if (playerShootingSprite[18].getPosition().y < -20.0f) {
			playerShootingSprite[18].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[18] = true;
			userBullets += 1;
			playerShootingSpriteActive[18] = false;
		}
	}

	if (playerShootingSpriteActive[19]) {
		playerShootingSprite[19].move(upMovement*20.0f*dt);
		if (playerShootingSprite[19].getPosition().y < -20.0f) {
			playerShootingSprite[19].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[19] = true;
			userBullets += 1;
			playerShootingSpriteActive[19] = false;
		}
	}

	if (playerShootingSpriteActive[20]) {
		playerShootingSprite[20].move(upMovement*20.0f*dt);
		if (playerShootingSprite[20].getPosition().y < -20.0f) {
			playerShootingSprite[20].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[20] = true;
			userBullets += 1;
			playerShootingSpriteActive[20] = false;
		}
	}

	if (playerShootingSpriteActive[21]) {
		playerShootingSprite[21].move(upMovement*20.0f*dt);
		if (playerShootingSprite[21].getPosition().y < -20.0f) {
			playerShootingSprite[21].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[21] = true;
			userBullets += 1;
			playerShootingSpriteActive[21] = false;
		}
	}

	if (playerShootingSpriteActive[22]) {
		playerShootingSprite[22].move(upMovement*20.0f*dt);
		if (playerShootingSprite[22].getPosition().y < -20.0f) {
			playerShootingSprite[22].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[22] = true;
			userBullets += 1;
			playerShootingSpriteActive[22] = false;
		}
	}

	if (playerShootingSpriteActive[23]) {
		playerShootingSprite[23].move(upMovement*20.0f*dt);
		if (playerShootingSprite[23].getPosition().y < -20.0f) {
			playerShootingSprite[23].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[23] = true;
			userBullets += 1;
			playerShootingSpriteActive[23] = false;
		}
	}

	if (playerShootingSpriteActive[24]) {
		playerShootingSprite[24].move(upMovement*20.0f*dt);
		if (playerShootingSprite[24].getPosition().y < -20.0f) {
			playerShootingSprite[24].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[24] = true;
			userBullets += 1;
			playerShootingSpriteActive[24] = false;
		}
	}

	if (playerShootingSpriteActive[25]) {
		playerShootingSprite[25].move(upMovement*20.0f*dt);
		if (playerShootingSprite[25].getPosition().y < -20.0f) {
			playerShootingSprite[25].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[25] = true;
			userBullets += 1;
			playerShootingSpriteActive[25] = false;
		}
	}

	if (playerShootingSpriteActive[26]) {
		playerShootingSprite[26].move(upMovement*20.0f*dt);
		if (playerShootingSprite[26].getPosition().y < -20.0f) {
			playerShootingSprite[26].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[26] = true;
			userBullets += 1;
			playerShootingSpriteActive[26] = false;
		}
	}

	if (playerShootingSpriteActive[27]) {
		playerShootingSprite[27].move(upMovement*20.0f*dt);
		if (playerShootingSprite[27].getPosition().y < -20.0f) {
			playerShootingSprite[27].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[27] = true;
			userBullets += 1;
			playerShootingSpriteActive[27] = false;
		}
	}

	if (playerShootingSpriteActive[28]) {
		playerShootingSprite[28].move(upMovement*20.0f*dt);
		if (playerShootingSprite[28].getPosition().y < -20.0f) {
			playerShootingSprite[28].setPosition(-10.0f, -10.0f);
			playerShootingSpriteAvailable[28] = true;
			userBullets += 1;
			playerShootingSpriteActive[28] = false;
		}
	}

	if (playerShootingSpriteActive[29]) {
		playerShootingSprite[29].move(upMovement*20.0f*dt);
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

	healthText.setFont(font);
	healthText.setString("HEALTH: " + std::to_string(userHealth));
	healthText.setCharacterSize(24);
	healthText.setFillColor(Color::Black);
	healthText.setStyle(Text::Bold | Text::Underlined);
	healthText.setPosition(150.0f, 0.0f);

	gameOverText.setFont(font);
	gameOverText.setString("GAME OVER!!!!!");
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(Color::Black);
	gameOverText.setStyle(Text::Bold | Text::Underlined);
	gameOverText.setPosition(150.0f, 150.0f);

	gameCountDownTimer.setFont(font);
	gameCountDownTimer.setString("READY!");
	gameCountDownTimer.setCharacterSize(40);
	gameCountDownTimer.setFillColor(Color::Black);
	gameCountDownTimer.setStyle(Text::Bold | Text::Underlined);
	gameCountDownTimer.setPosition(150.0f, 150.0f);

	bulletsAvailableCounter.setFont(font);
	bulletsAvailableCounter.setString("BULLETS: 30/30");
	bulletsAvailableCounter.setCharacterSize(24);
	bulletsAvailableCounter.setFillColor(Color::Black);
	bulletsAvailableCounter.setStyle(Text::Bold | Text::Underlined);
	bulletsAvailableCounter.setPosition(0.0f, 360.0f);
}

void setupMenuTexts(int winX, int winY) {
	startMenuText.setFont(font);
	startMenuText.setString("START GAME");
	startMenuText.setCharacterSize(24);
	startMenuText.setFillColor(Color::Black);
	startMenuText.setStyle(Text::Bold | Text::Underlined);
	startMenuText.setPosition(winX/2, 100.0f);

	highscoreMenuText.setFont(font);
	highscoreMenuText.setString("HIGHSCORES");
	highscoreMenuText.setCharacterSize(24);
	highscoreMenuText.setFillColor(Color::Black);
	highscoreMenuText.setStyle(Text::Bold | Text::Underlined);
	highscoreMenuText.setPosition(winX / 2, 150.0f);

	weblinkMenuText.setFont(font);
	weblinkMenuText.setString("WEBLINK");
	weblinkMenuText.setCharacterSize(24);
	weblinkMenuText.setFillColor(Color::Black);
	weblinkMenuText.setStyle(Text::Bold | Text::Underlined);
	weblinkMenuText.setPosition(winX / 2, 200.0f);

	exitMenuText.setFont(font);
	exitMenuText.setString("LEAVE GAME");
	exitMenuText.setCharacterSize(24);
	exitMenuText.setFillColor(Color::Black);
	exitMenuText.setStyle(Text::Bold | Text::Underlined);
	exitMenuText.setPosition(winX / 2, 250.0f);
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

	// Set position and the scale of all the sprite buttons
	startButtonMenuSprite.setPosition((winX/2)-10.0f, 100.0f);
	startButtonMenuSprite.scale(4.0f, 0.9f);

	highscoreButtonMenuSprite.setPosition((winX / 2) - 10.0f, 150.0f);
	highscoreButtonMenuSprite.scale(4.0f, 0.9f);

	weblinkButtonMenuSprite.setPosition((winX / 2) - 10.0f, 200.0f);
	weblinkButtonMenuSprite.scale(4.0f, 0.9f);

	exitButtonMenuSprite.setPosition((winX / 2) - 10.0f, 250.0f);
	exitButtonMenuSprite.scale(4.0f, 0.9f);

	setupMenuTexts(winX, winY);
}

// Load method which loads all the files required
void LoadStart() {
  if (!playerSpriteTexture.loadFromFile("res/img/pirate.png")) {
    throw std::invalid_argument("Loading error with sprite!");
  }

  if (!backgroundTexture.loadFromFile("res/img/background1.png")) {
	  throw std::invalid_argument("Loading error with background!");
  }

  if (!enemySpriteTexture.loadFromFile("res/img/police.png")) {
	  throw std::invalid_argument("Loading error with enemy!");
  }

  if (!playerShootingTexture.loadFromFile("res/img/smallbullet.png")) {
	  throw std::invalid_argument("Loading error with gunfire!");
  }

  if (!powerupChestTexture.loadFromFile("res/img/chest.png")) {
	  throw std::invalid_argument("Loading error with chest!");
  }

  if(!font.loadFromFile("res/fonts/Treamd.ttf")) {
	  throw std::invalid_argument("Loading error with font!");
  }

  // Set the start position of the user sprite
  playerSprite.setPosition(130.0f, 300.0f);
  //playerSprite.setScale(1.1f, 1.1f);

  powerupChestSprite.setPosition(160.0f, 5.0f);

  float startingDistancesY[50];
  for (int i = 0; i < 50; i++) {
	  startingDistancesY[i] = 100.0f + (i*60.0f);
	  std::cout << startingDistancesY[i] << std::endl;
  }

  float startingDistancesX[6] = { 30.0f, 82.0f, 134.0f, 186.0f, 238.0f, 290.0f, };

  // Setup police boat
  for (int i = 0; i < 30; i++) {
	  int x = rand() % 5;
	  int y = rand() % 50;
	  policeBoatSprite[i].setPosition(startingDistancesX[x],- (startingDistancesY[y]));
	  policeBoatRectangle[i].setSize(Vector2f(41.0f, 50.0f));
	  policeBoatRectangle[i].setPosition(Vector2f(startingDistancesX[x], -(startingDistancesY[y])));

  }
  
  // Set the position to off the players bullets of screen
  for (int i = 0; i < 30; i++) {
	  playerShootingSprite[i].setPosition(-10.0f, -10.0f);
	  playerShootingSpriteAvailable[i] = true;
  }

  // Setup game texts
  setupStartTexts();
}


void UpdateMenu() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
}

// Update method which stores a clock and handles the movement of the default user sprite - called while window is open
void UpdateStart() {
  static sf::Clock clock;
  static sf::Clock gameClock;
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
	  if (Keyboard::isKeyPressed(Keyboard::Left)) {
		  move.x--;
		  //std::cout << "left";
	  }
  }
  if (!rightNotAllowed) {
	  if (Keyboard::isKeyPressed(Keyboard::Right)) {
		  move.x++;
		  //std::cout << "right";
	  }
  }
  playerSprite.move(move*100.f*dt);

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
				  playerShootingSprite[i].setPosition((playerSprite.getPosition().x) + 18.0f, (playerSprite.getPosition().y) - 20.0f);
				  // Print bullet
				  std::cout << i << std::endl;
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

	// Method which updates the bullets position
	moveTheBullets(upMovement, dt);

	for (int i = 0; i < 30; i++) {
		policeBoatSprite[i].move(downMovement*25.0f*dt);
		policeBoatRectangle[i].move(downMovement*25.0f*dt);
	}  

  // Move the powerup chest down the screen
  powerupChestSprite.move(downMovement*50.0f*dt);
  
  // Double for loop - one boats and other for bullets
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++){
			// If the police boat contains the bullet then
			if (policeBoatRectangle[j].getGlobalBounds().contains(playerShootingSprite[i].getPosition())) {
				// Set bool to true
				//hasPlayerShootingSpriteHitPoliceBoat[0] = true;
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
				// Print 
				std::cout << policeBoatHealth[j] << " I am under attack" << std::endl;
				// If boat has been hit by 4 bullets
				if (policeBoatHealth[j] < -18) {
					// Reset position
					policeBoatSprite[j].setPosition(-50.0f, -10.0f);
					// Reset rectangle
					policeBoatRectangle[j].setPosition(-10.0f, -10.0f);
					// Print
					std::cout << "Police boat destroyed "<< j << std::endl;
					// Award user score
					userScore += 10;
					// Break for loop - goto allows double break and skips to label
					goto enloop;
				}
			}
		}
	}
 
	enloop:
  // Code for collision between bullet and powerup sprite
  if (playerShootingSprite[0].getPosition().x >= powerupChestSprite.getPosition().x && playerShootingSprite[0].getPosition().x <= (powerupChestSprite.getPosition().x) + 41 &&
	  playerShootingSprite[0].getPosition().y >= powerupChestSprite.getPosition().y && playerShootingSprite[0].getPosition().y <= (powerupChestSprite.getPosition().y) + 41) {
	  std::cout << "collision. OBTAINED";
	  powerupChestSprite.setPosition(0.0f, 0.0f);
	  powerupObtained = true;
	  userHealth+=5;
  }

  // Code for collision between player ship and powerup sprite
  if (playerSprite.getPosition().x >= powerupChestSprite.getPosition().x && playerSprite.getPosition().x <= (powerupChestSprite.getPosition().x) + 41 &&
	  playerSprite.getPosition().y >= powerupChestSprite.getPosition().y && playerSprite.getPosition().y <= (powerupChestSprite.getPosition().y) + 41) {
	  std::cout << "collision. POWERUP";
	  powerupChestSprite.setPosition(0.0f, 0.0f);
	  powerupObtained = true;
	  userHealth += 5;
  }

  /*
  // Code collision between enemy ship and player ship
  if (playerSprite.getPosition().x >= enemySprite.getPosition().x && playerSprite.getPosition().x <= (enemySprite.getPosition().x) + 41 &&
	  playerSprite.getPosition().y >= enemySprite.getPosition().y && playerSprite.getPosition().y <= (enemySprite.getPosition().y) + 41) {
	  std::cout << "collision. BOAT HIT";
	  userHealth -= 10;
	  enemyShipHide = true;
  }
  */

  // Update various labels
  scoreText.setString("SCORE: " + std::to_string(userScore));
  healthText.setString("HEALTH: " + std::to_string(userHealth));
  bulletsAvailableCounter.setString("BULLETS: " + std::to_string(userBullets) + " /30");

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
}

// Render method for the menu screen
void RenderMenu(RenderWindow &window) {
	window.draw(backgroundMenuSprite);
	// Draw all the button values
	window.draw(startButtonMenuSprite);
	window.draw(highscoreButtonMenuSprite);
	window.draw(weblinkButtonMenuSprite);
	window.draw(exitButtonMenuSprite);

	// Draw all the text values
	window.draw(startMenuText);
	window.draw(highscoreMenuText);
	window.draw(weblinkMenuText);
	window.draw(exitMenuText);
}

// Render method for the start screen
void RenderStart(RenderWindow &window) { 
	window.draw(backgroundSprite);
	window.draw(playerSprite);
	for (int i = 0; i < 30; i++) {
		window.draw(playerShootingSprite[i]);
		window.draw(policeBoatSprite[i]);
	}
	if (!powerupObtained) {
		window.draw(powerupChestSprite);
	}
	
	window.draw(scoreText);
	window.draw(healthText);
	window.draw(bulletsAvailableCounter);
	window.draw(gameCountDownTimer);
	if (userHealth <= 0) {
		window.draw(gameOverText);
	}
}

// Main method which runs everything
int main() {
	// Set the gamestate the the default start
  GameStates gameState = GameStates::STATE_MENU;
  // Set the window and its size
  RenderWindow window(VideoMode(400, 400), "Pirates of the Firth of Forth!");
 
  int winX = window.getSize().x;
  int winY = window.getSize().y;

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
		case GameStates::STATE_MENU:
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

			backgroundMenuSprite.setTexture(backgroundMenuTexture);
			startButtonMenuSprite.setTexture(buttonMenuTexture);
			highscoreButtonMenuSprite.setTexture(buttonMenuTexture);
			weblinkButtonMenuSprite.setTexture(buttonMenuTexture);
			exitButtonMenuSprite.setTexture(buttonMenuTexture);

			// Code for start button pressed
			if(Mouse::isButtonPressed(Mouse::Left) && 
				Mouse::getPosition(window).x > winX/2 && Mouse::getPosition(window).x < 350.0f && 
				(Mouse::getPosition(window).y > 100.0f && Mouse::getPosition(window).y < 150.0f)){
				std::cout << "Start button pressed" << std::endl;
				gameState = GameStates::STATE_START;
			}

			// Code for highscores button pressed
			if (Mouse::isButtonPressed(Mouse::Left) &&
				Mouse::getPosition(window).x > winX / 2 && Mouse::getPosition(window).x < 350.0f &&
				(Mouse::getPosition(window).y > 150.0f && Mouse::getPosition(window).y < 200.0f)) {
				std::cout << "Highscores button pressed" << std::endl;
			}

			// Code for weblink button pressed
			if (Mouse::isButtonPressed(Mouse::Left) &&
				Mouse::getPosition(window).x > winX / 2 && Mouse::getPosition(window).x < 350.0f &&
				(Mouse::getPosition(window).y > 200.0f && Mouse::getPosition(window).y < 250.0f)) {
				std::cout << "Weblink button pressed" << std::endl;
				ShellExecute(NULL, "open", "http://www.calumtempleton.com",
					NULL, NULL, SW_SHOWNORMAL);
			}

			// Code for exit button pressed
			if (Mouse::isButtonPressed(Mouse::Left) &&
				Mouse::getPosition(window).x > winX / 2 && Mouse::getPosition(window).x < 350.0f &&
				(Mouse::getPosition(window).y > 250.0f && Mouse::getPosition(window).y < 300.0f)) {
				std::cout << "Exit button pressed" << std::endl;
				window.close();
			}

			window.clear();
			UpdateMenu();
			RenderMenu(window);
			window.display();
			break;
		case GameStates::STATE_OPTIONS:
			break;
		case GameStates::STATE_START:
			if (!hasLoadStartBeenCalled) {
				// Call the load method
				try {
					LoadStart();
				}
				catch (const std::exception &) {
					std::cerr << "Load error" << std::endl;
					return 1;
				}
				hasLoadStartBeenCalled = true;
			}

			// Set the various textures
			backgroundSprite.setTexture(backgroundTexture);
			playerSprite.setTexture(playerSpriteTexture);
			for (int i = 0; i < 30; i++) {
				playerShootingSprite[i].setTexture(playerShootingTexture);
				policeBoatSprite[i].setTexture(enemySpriteTexture);
			}
			powerupChestSprite.setTexture(powerupChestTexture);

			if (!hasCountDownBeenCalled) {
				// Pause Game
				window.clear();
				RenderStart(window);
				window.display();
				// Count down timer
				Sleep(2000);
				hasCountDownBeenCalled = true;
			}
			else {
				// Start game
				gameCountDownTimer.setString("GO!");
				window.clear();
				UpdateStart();
				RenderStart(window);
				window.display();
			}
			break;
		case GameStates::STATE_LEVEL:
			break;
		case GameStates::STATE_HIGHSCORES:
			break;
	}
  }

  return 0;
}