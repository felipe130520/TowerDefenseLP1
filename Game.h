#pragma once
#include<map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	
	//GUI
	sf::Font font;
	sf::Text pointText;

	//Background
	sf::Texture BackgroundTexture;
	sf::Sprite Background;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initBackground();

	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();


	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateEnemiesAndCombat();
	
	void update();

	void renderGUI();
	void renderBackground();
	void render();

};

