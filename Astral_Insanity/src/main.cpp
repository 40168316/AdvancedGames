#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

// Adds sf in front of everything to reference the library
using namespace sf;

Texture playerSpriteTexture, backgroundTexture, enemySpriteTexture, playerShootingTexture;
Sprite playerSprite, backgroundSprite, enemySprite;
Sprite playerShootingSprite;

bool fire = false;

// Load method which loads all the files required
void Load() {
  if (!playerSpriteTexture.loadFromFile("res/img/spaceship1.png")) {
    throw std::invalid_argument("Loading error with sprite!");
  }

  if (!backgroundTexture.loadFromFile("res/img/background.png")) {
	  throw std::invalid_argument("Loading error with background!");
  }

  if (!enemySpriteTexture.loadFromFile("res/img/enemy.png")) {
	  throw std::invalid_argument("Loading error with enemy!");
  }

  if (!playerShootingTexture.loadFromFile("res/img/gunshot.png")) {
	  throw std::invalid_argument("Loading error with gunfire!");
  }

  // Set the start position of the user sprite
  playerSprite.setPosition(130.0f, 300.0f);

  // Set the scale of the background sprite
  backgroundSprite.setScale(0.5f, 0.5f);

  enemySprite.setPosition(120.f, 5.0f);
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
  if (Keyboard::isKeyPressed(Keyboard::Left)) {
    move.x--;
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
    move.x++;
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

  // Set the shooting sprite to move up the screen
  playerShootingSprite.move(upMovement*100.0f*dt);
 
  // Code for collision
  if (playerShootingSprite.getPosition().x >= enemySprite.getPosition().x && playerShootingSprite.getPosition().x <= (enemySprite.getPosition().x) + 50 &
	  playerShootingSprite.getPosition().y >= enemySprite.getPosition().y && playerShootingSprite.getPosition().y <= (enemySprite.getPosition().y) + 50) {
	  std::cout << "collision";
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