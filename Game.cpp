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
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::Black);
	this->pointText.setPosition(sf::Vector2f(675.f, 15.f));
		
    this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(sf::Vector2f((this->window->getSize().x / 2.f)- this->gameOverText.getGlobalBounds().width/2.f,
		(this->window->getSize().y / 2.f) - this->gameOverText.getGlobalBounds().height / 2.f));

	//Init player GUI

	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Green);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::Red);
	
}

void Game::initBackground()
{
	if (!this->BackgroundTexture.loadFromFile("Textures/street.png")) {
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND"<<std::endl;
	}
	this->Background.setTexture(this->BackgroundTexture);
	this->Background.scale(2.4f,2.5f);


}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initMusic()
{
	if (!this->music.openFromFile("Sounds/La_Fiesta_De_Los_Panes.mp3")) {
		std::cout<<"ERROR :: MUSIC :: COULD NOT LOAD MUSIC"<<std::endl;
	}
	music.setVolume(10.f);
	music.play();
}

void Game::initBase()
{
	sf::Vector2f center(this->window->getSize().x / 2.f - 30.f, this->window->getSize().y / 2.f - 30.f);

	this->base = new Base(center);
}

void Game::initPlayer()
{
	this->spawnTimer = this->spawnTimerMax;
	this->spawnTimerMax = 20.f;
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
	this->initMusic();
	this->initSystems();
	this->initBase();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->base;

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
		this->updatePollEvents();

		if (this->player->getHp() > 0 && this->base->getHp() > 0) {
			this->update();

			this->render();
		}
		else {
			this->music.stop();
		}
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
            this->window->close();
		}
	}
}

void Game::updateInput()
{
	//Move player

	this->player->animationState = PLAYER_ANIMATION_STATES::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))//LEFT 
	{
		this->player->move(-1.f, 0.f);
		this->player->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))//RIGHT 
	{
		this->player->move(1.f, 0.f);
		this->player->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))//UP 
	{
		this->player->move(0.f, -1.f);
		this->player->animationState = PLAYER_ANIMATION_STATES::MOVING_UP;


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))//DOWN 
	{
		this->player->move(0.f, 1.f);
		this->player->animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;


	}


	//Detect key pressed for shooting && shooting at mouse position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->player->canAttack()) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2f playerPosition = this->player->getPos();
    sf::Vector2f direction = sf::Vector2f(mousePosition.x, mousePosition.y) - playerPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0 && this->player->getAmmo() > 0) {
            direction /= length;

            this->bullets.push_back(new Bullet(this->textures["BULLET"],
                this->player->getPos().x + this->player->getBounds().width / 2.f,
                this->player->getPos().y,
                direction.x, direction.y, 10.f));
            this->player->loseammo(1);
            }
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss <<"Ammo: " << this->player->getAmmo();


	this->pointText.setString(ss.str());

	
	//update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));

}

void Game::updateWorld()
{

}


void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Top world collision
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left,0.f);
	}
	//Right world collision
	if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Bottom world collision
	if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left ,this->window->getSize().y - this->player->getBounds().height);
	}
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

			//Balas sao deletadas? OK
			//std::cout << this->bullets.size() << "\n";
		}
		
		counter++;
	}
}

void Game::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer > this->spawnTimerMax) {
		
		float x, y;

    // Escolha um lado aleatório: 0 = cima, 1 = baixo, 2 = esquerda, 3 = direita
    	int side = rand() % 4;

    	switch (side) {
        	case 0: // Cima
            	x = static_cast<float>(rand() % this->window->getSize().x);
           		y = -100.f;
            	break;
        	case 1: // Baixo
            	x = static_cast<float>(rand() % this->window->getSize().x);
            	y = static_cast<float>(this->window->getSize().y) + 100.f;
            	break;
        	case 2: // Esquerda
            	x = -100.f;
            	y = static_cast<float>(rand() % this->window->getSize().y);
            	break;
        	case 3: // Direita
            	x = static_cast<float>(this->window->getSize().x) + 100.f;
            	y = static_cast<float>(rand() % this->window->getSize().y);
            	break;
   			}

    	this->enemies.push_back(new Enemy(x, y));
			
		this->spawnTimer = 0.f;
	}

	// calcula o centro da tela
    sf::Vector2f center(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);

	// // // // //
	/*for (auto* enemy : this->enemies) {
		enemy->update();
	}*/

	for (int i = 0;i < enemies.size();i++) {
		bool enemy_removed = false;

		this->enemies[i]->update(center);
		
		for (size_t k = 0;k < this->bullets.size() && !enemy_removed;k++) {
			//Check if enemy hit by bullet
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->bullets.erase(this->bullets.begin() + k);

				//Adding points based on the enemy value
				this->points += this->enemies[i]->getPoints();

                //chance de criar munição
                if((rand() % 100) <= 24){
                    this->Ammos.push_back(new Ammo(this->enemies[i]->getPosition()));

                }

				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}

		if (!enemy_removed) {
			
			//Enemy-player collision
			if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
				this->player->loseHp(this->enemies.at(i)->getDamage());
                if((rand() % 100) <= 24){
                    this->Ammos.push_back(new Ammo(this->enemies[i]->getPosition()));

                }
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
        //colisão inimigos com a base
        if(!enemy_removed){
            if (this->enemies[i]->getBounds().intersects(this->base->getBounds())) {
            this->base->loseHp(this->enemies[i]->getDamage());
            this->enemies.erase(this->enemies.begin() + i);  
            enemy_removed = true;
          }
        }
	
	}
}

void Game::updateAmmoCollection(){
	for(int i = 0; i < Ammos.size(); i++){
		if(this->Ammos[i]->getBounds().intersects(this->player->getBounds())) {
			this->player->gainAmmo(5);
			this->Ammos.erase(this->Ammos.begin() + i);
		}
	}
}


void Game::update()
{

	this->updateInput();

	this->player->update();

	this->updateCollision();
	
	this->updateBullets();

	this->updateEnemiesAndCombat();

	this->updateGUI();

	this->updateWorld();

	this->updateAmmoCollection();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
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

	this->base->render(this->window);

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}
    for (auto* ammo : this->Ammos) {
		ammo->render(this->window);
	}

	this->renderGUI();
	
	//Game over screen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}

    if(this->base->getHp() <= 0) {
        this->window->draw(this->gameOverText);
    }

	//Display stuff
	this->window->display();
}