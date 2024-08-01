#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Atirador bigodudo",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Bullet.png");


}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/Honk_Regular.ttf")) {
		std::cout << "ERROR GAME FAILED TO LOAD FONT";
	}
	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
}

void Game::initBackground()
{
	if (!this->BackgroundTexture.loadFromFile("Textures/street.png")) {
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND"<<std::endl;
	}
	this->Background.setTexture(this->BackgroundTexture);


}

void Game::initPlayer()
{
	this->spawnTimer = this->spawnTimerMax;
	this-> spawnTimerMax = 20.f;
	this->player = new Player();

}

void Game::initEnemies()
{

}

//Con/Des
Game::Game()
{

	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initBackground();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}
	//Delete Bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	//Delete Enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}

//Functions

void Game::run()
{
	while (window->isOpen()) 
	{

	this->update();

	this->render();

	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.Event::type && e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->player->move(-1.f, 0.f);
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->player->move(1.f, 0.f);

	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->player->move(0.f, -1.f);

	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->player->move(0.f, 1.f);

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2f playerPosition = this->player->getPos();
    sf::Vector2f direction = sf::Vector2f(mousePosition.x, mousePosition.y) - playerPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;

        this->bullets.push_back(new Bullet(this->textures["BULLET"],
            this->player->getPos().x + this->player->getBounds().width / 2.f,
            this->player->getPos().y,
            direction.x, direction.y, 10.f));
    	}
	}
}

void Game::updateGUI()
{
}


void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin()+ counter);
			--counter;

			//Balas s�o deletadas? OK
			//std::cout << this->bullets.size() << "\n";
		}
		counter++;
	}
}

void Game::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer > this->spawnTimerMax) {

		this->enemies.push_back(new Enemy(rand()%this->window->getSize().x -20.f, -100.f));
		this->spawnTimer = 0.f;
	}
	// // // // //
	for (auto* enemy : this->enemies) {
		enemy->update();
	}

	for (int i = 0;i < enemies.size();i++) {
		bool enemy_removed = false;
		enemies[i]->update();


		//Remove enemy at the bottom of the screen
		for (size_t k = 0;k < this->bullets.size() && !enemy_removed;k++) {

			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
		//Remove enemy at the bottom of the screen
		if (!enemy_removed) {
			if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
				//std::cout << this->enemies.size() << "\n";
			}
		}
	
	}
}

void Game::update()
{
	this->updatePollEvents();

	this->updateInput();

	this->player->update();
	
	this->updateBullets();

	this->updateEnemiesAndCombat();

	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::renderBackground()
{
	this->window->draw(this->Background);
}


void Game::render()
{
	//Clear
	this->window->clear();

	//Draw background
	this->renderBackground();

	//Draw stuff

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();
	
	//Display stuff
	this->window->display();
}