#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <windows.h>

// Adds sf in front of everything to reference the library
using namespace sf;

Texture playerSpriteTexture, backgroundTexture, enemySpriteTexture, playerShootingTexture, powerupChestTexture, backgroundMenuTexture, buttonMenuTexture;
Sprite playerSprite, backgroundSprite, enemySprite, backgroundMenuSprite, startButtonMenuSprite, highscoreButtonMenuSprite, weblinkButtonMenuSprite, exitButtonMenuSprite;
Sprite playerShootingSprite[30], powerupChestSprite;
Font font;
Text scoreText, healthText, gameOverText, startMenuText, highscoreMenuText, weblinkMenuText, exitMenuText, gameCountDownTimer, bulletsAvailableCounter;

bool fire = false;
bool leftNotAllowed = false;
bool rightNotAllowed = false;
bool powerupObtained = false;
bool enemyShipHide = false;
bool hasLoadStartBeenCalled = false;
bool hasLoadMenuBeenCalled = false;
bool hasCountDownBeenCalled = false;
bool bulletavailable[30];
int userScore = 0;
int userHealth = 10;
int userBullets = 30;

enum class GameStates
{
	STATE_START = 1,
	STATE_MENU = 2,
	STATE_OPTIONS = 3,
	STATE_LEVEL = 4,
	STATE_HIGHSCORES = 5,
};

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

	for (int i = 0; i < 30; i++) {
		bulletavailable[i] = true;
	}
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
  playerSprite.setScale(1.1f, 1.1f);

  enemySprite.setPosition(120.f, 5.0f);
  powerupChestSprite.setPosition(160.0f, 5.0f);

  for (int i = 0; i < 30; i++) {
	  playerShootingSprite[i].setPosition(0.0f, -10.0f);
  }

  setupStartTexts();
}

// Method which checks if the there is a bullet avaiable
bool isTheNextBulletAvailable(int i) {
	// If bullet is out of view
	if (playerShootingSprite[i].getPosition().y < 0.0f) {
		// Reset bullet availability to true
		 return bulletavailable[i] = true;
	}
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
	  }
  }
  if (!rightNotAllowed) {
	  if (Keyboard::isKeyPressed(Keyboard::Right)) {
		  move.x++;
	  }
  }
  playerSprite.move(move*300.0f*dt);

  // If space is pressed set fire to true
  if (Keyboard::isKeyPressed(Keyboard::Space)) {
	  fire = true;
	  for (int i = 0; i < 30; i++) {
		  if (isTheNextBulletAvailable(i) == true) {
			  // Set the bullet to the position of the sprite - some reason I have to add to x value to get it to line up - TODO
			  playerShootingSprite[i].setPosition((playerSprite.getPosition().x) + 18.0f, (playerSprite.getPosition().y) - 20.0f);
			  bulletavailable[i] = false;
			  userBullets--;
		}
	  }
  }

  if (fire) {
	  // Set the shooting sprite to move up the screen
	  playerShootingSprite[0].move(upMovement*100.0f*dt);
  }

  // Move the enemy sprite down the screen
  enemySprite.move(downMovement*25.0f*dt);

  // Move the powerup chest down the screen
  powerupChestSprite.move(downMovement*50.0f*dt);
 
  // Code for collision between bullet and enemy sprite
  if (playerShootingSprite[0].getPosition().x >= enemySprite.getPosition().x && playerShootingSprite[0].getPosition().x <= (enemySprite.getPosition().x) + 41 &&
	  playerShootingSprite[0].getPosition().y >= enemySprite.getPosition().y && playerShootingSprite[0].getPosition().y <= (enemySprite.getPosition().y) + 41) {
	  std::cout << "collision. DESTROYED";
	  userScore++;
  }

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

  // Code collision between enemy ship and player ship
  if (playerSprite.getPosition().x >= enemySprite.getPosition().x && playerSprite.getPosition().x <= (enemySprite.getPosition().x) + 41 &&
	  playerSprite.getPosition().y >= enemySprite.getPosition().y && playerSprite.getPosition().y <= (enemySprite.getPosition().y) + 41) {
	  std::cout << "collision. BOAT HIT";
	  userHealth -= 10;
	  enemyShipHide = true;
  }

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
	if (fire) {
		for (int i = 0; i < 30; i++) {
			window.draw(playerShootingSprite[i]);
		}
	}
	if (!powerupObtained) {
		window.draw(powerupChestSprite);
	}
	if (!enemyShipHide) {
		window.draw(enemySprite);
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
			enemySprite.setTexture(enemySpriteTexture);
			for (int i = 0; i < 30; i++) {
				playerShootingSprite[i].setTexture(playerShootingTexture);
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