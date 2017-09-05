#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

// Adds sf in front of everything to reference the library
using namespace sf;

Texture playerSpriteTexture, backgroundTexture, enemySpriteTexture, playerShootingTexture, powerupChestTexture;
Sprite playerSprite, backgroundSprite, enemySprite;
Sprite playerShootingSprite, powerupChestSprite;
Font font;
Text scoreText, healthText;

bool fire = false;
bool leftNotAllowed = false;
bool rightNotAllowed = false;
bool powerupHide = false;
int userScore = 0;
int userHealth = 10;

// Method which displays various user values on the interface
void setupGameTexts() {
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
}

// Load method which loads all the files required
void Load() {
  if (!playerSpriteTexture.loadFromFile("res/img/spaceship1.png")) {
    throw std::invalid_argument("Loading error with sprite!");
  }

  if (!backgroundTexture.loadFromFile("res/img/background1.png")) {
	  throw std::invalid_argument("Loading error with background!");
  }

  if (!enemySpriteTexture.loadFromFile("res/img/enemy.png")) {
	  throw std::invalid_argument("Loading error with enemy!");
  }

  if (!playerShootingTexture.loadFromFile("res/img/gunshot.png")) {
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

  // Set the scale of the background sprite
  //backgroundSprite.setScale(0.5f, 0.5f);

  enemySprite.setPosition(120.f, 5.0f);
  powerupChestSprite.setPosition(160.0f, 5.0f);

  setupGameTexts();
}

// Update method which stores a clock and handles the movement of the default user sprite - called while window is open
void Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  Vector2f move;
  Vector2f downMovement;
  Vector2f upMovement;

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
	  // Set the bullet to the position of the sprite - some reason I have to add to x value to get it to line up - TODO
	  playerShootingSprite.setPosition((playerSprite.getPosition().x)+59.0f, playerSprite.getPosition().y);
  }

  // Move the enemy sprite down the screen
  enemySprite.move(downMovement*100.0f*dt);

  // Move the powerup chest down the screen
  powerupChestSprite.move(downMovement*150.0f*dt);

  // Set the shooting sprite to move up the screen
  playerShootingSprite.move(upMovement*100.0f*dt);
 
  // Code for collision between bullet and enemy sprite
  if (playerShootingSprite.getPosition().x >= enemySprite.getPosition().x && playerShootingSprite.getPosition().x <= (enemySprite.getPosition().x) + 50 &&
	  playerShootingSprite.getPosition().y >= enemySprite.getPosition().y && playerShootingSprite.getPosition().y <= (enemySprite.getPosition().y) + 50) {
	  std::cout << "collision. DESTROYED";
	  userScore++;
  }

  // Code for collision between bullet and enemy sprite
  if (playerShootingSprite.getPosition().x >= powerupChestSprite.getPosition().x && playerShootingSprite.getPosition().x <= (powerupChestSprite.getPosition().x) + 50 &&
	  playerShootingSprite.getPosition().y >= powerupChestSprite.getPosition().y && playerShootingSprite.getPosition().y <= (powerupChestSprite.getPosition().y) + 50) {
	  std::cout << "collision. OBTAINED";
	  powerupChestSprite.setPosition(0.0f, 0.0f);
	  powerupHide = true;
	  userHealth+=5;
  }

  // Update various labels
  scoreText.setString("SCORE: " + std::to_string(userScore));
  healthText.setString("HEALTH: " + std::to_string(userHealth));

  // If statement limiting the player to go to far left
  if (playerSprite.getPosition().x < 4.0f) {
	  std::cout << "To far left";
	  leftNotAllowed = true;
  }
  else {
	  leftNotAllowed = false;
  }

  // If statement limiting the player from going to far right
  if (playerSprite.getPosition().x > 270.0f) {
	  std::cout << "To far right";
	  rightNotAllowed = true;
  }
  else {
	  rightNotAllowed = false;
  }
}

// Render method which draws everything required
void Render(RenderWindow &window) { 
	window.draw(backgroundSprite);
	window.draw(playerSprite);
	window.draw(enemySprite);
	if (fire) {
		window.draw(playerShootingSprite);
	}
	if (!powerupHide) {
		window.draw(powerupChestSprite);
	}
	window.draw(scoreText);
	window.draw(healthText);
}

// Main method which runs everything
int main() {
	// Set the window and its size
  RenderWindow window(VideoMode(400, 400), "Pirates of the Firth of Forth!");

  // Call the load method
  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

  backgroundSprite.setTexture(backgroundTexture);

  // Add texture and scale the sprite
  playerSprite.setTexture(playerSpriteTexture);
  playerSprite.setScale(Vector2f(2.f, 2.f));

  enemySprite.setTexture(enemySpriteTexture);
  
  playerShootingSprite.setTexture(playerShootingTexture);

  powerupChestSprite.setTexture(powerupChestTexture);
  
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    window.clear();
    Update();
    Render(window);
    window.display();
  }

  return 0;
}