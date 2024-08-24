#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Atirador bigodudo",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}


void Game::initGUI()
{
    // Load font
    if (!this->font.loadFromFile("Fonts/Honk_Regular.ttf")) {
        std::cout << "ERROR GAME FAILED TO LOAD FONT";
    }

    // Init point text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(24);
    this->pointText.setFillColor(sf::Color::Black);
    this->pointText.setPosition(sf::Vector2f(675.f, 15.f));

	//init ammo text
	this->ammoText.setFont(this->font);
	this->ammoText.setCharacterSize(24);
	this->ammoText.setFillColor(sf::Color::Black);
	this->ammoText.setPosition(sf::Vector2(675.f, 40.f));

	//init playerHp text
	this->playerHpText.setFont(this->font);
	this->playerHpText.setCharacterSize(24);
	this->playerHpText.setFillColor(sf::Color::Black);
	this->playerHpText.setPosition(this->playerHpBar.getPosition().x + 230.f, this->playerHpBar.getPosition().y + 25.f);

	this->baseHpText.setFont(this->font);
	this->baseHpText.setCharacterSize(24);
	this->baseHpText.setFillColor(sf::Color::Black);
	this->baseHpText.setPosition(this->baseHpBar.getPosition().x + 230.f, this->baseHpBar.getPosition().y + 60.f);

    // Init Game Over text
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(80);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(sf::Vector2f((this->window->getSize().x / 2.f) - this->gameOverText.getGlobalBounds().width / 2.f,
                                                (this->window->getSize().y / 2.f) - this->gameOverText.getGlobalBounds().height / 2.f - 150.f));

	//init You Win text
	this->YouWinText.setFont(this->font);
    this->YouWinText.setCharacterSize(80);
    this->YouWinText.setFillColor(sf::Color::Green);
    this->YouWinText.setString("You Win!");
    this->YouWinText.setPosition(sf::Vector2f((this->window->getSize().x / 2.f) - this->YouWinText.getGlobalBounds().width / 2.f,
                                                (this->window->getSize().y / 2.f) - this->YouWinText.getGlobalBounds().height / 2.f - 150.f));


    // Init player GUI
    this->playerHpBar.setSize(sf::Vector2f(200.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(25.f, 25.f);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::Red);


    // Init base GUI
    this->baseHpBar.setSize(sf::Vector2f(200.f, 25.f));
    this->baseHpBar.setFillColor(sf::Color::Blue); 
    this->baseHpBar.setPosition(sf::Vector2f(25.f, 65.f)); 

 
    this->baseHpBarBack = this->baseHpBar;
    this->baseHpBarBack.setFillColor(sf::Color::Red);

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
	this->spawnTimerMax = 100.f;
	this->firstDifIncrease = false;
	this->secondDifIncrease = false;
	this->thirdDifIncrease = false;

	sf::Vector2f center(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);

	this->player = new Player(center);

}


void Game::initEnemies()
{

}

//Con/Des
Game::Game()
{

	this->initWindow();

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

void Game::run(){
	this->pausado = false;

    while (window->isOpen())
    {
        this->updatePollEvents();

        if (this->player->getHp() > 0 && this->base->getHp() > 0 && this->points < 200)
        {
            if (!this->pausado)
            {
                this->update();
            }

            this->render();
        }
        else
        {
            this->music.stop();
        }
    }
}

void Game::togglePausado(){
	this->pausado = !this->pausado;
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
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P) {
            this->togglePausado();
        }
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) {
			this->restartGame();
		}
	}
}

void Game::updateInput()
{
	//Move player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))//LEFT 
	{
		this->player->move(-1.f, 0.f);
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))//RIGHT 
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))//UP 
	{
		this->player->move(0.f, -1.f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))//DOWN 
	{
		this->player->move(0.f, 1.f);
	}


	//Detect key pressed for shooting && shooting at mouse position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->player->canAttack()) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2f playerPosition = this->player->getPos();
    sf::Vector2f direction = sf::Vector2f(mousePosition.x, mousePosition.y) - playerPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0 && this->player->getAmmo() > 0) {
            direction /= length;

            this->bullets.push_back(new Bullet(
                this->player->getPos().x + this->player->getBounds().width / 2.f,
                this->player->getPos().y,
                direction.x, direction.y, 7.f));
            this->player->loseammo(1);
            }
	}
}

void Game::updateGUI()
{
	std::stringstream GUIpoints;
	std::stringstream GUIammo;
	std::stringstream GUIplayerHpText;
	std::stringstream GUIbaseHpText;

	GUIpoints <<"Points: " << this->points;
	GUIammo << "Ammo: " << this->player->getAmmo();
	GUIplayerHpText << "Player Hp";
	GUIbaseHpText << "Base Hp";

	this->pointText.setString(GUIpoints.str());
	this->ammoText.setString(GUIammo.str());
	this->playerHpText.setString(GUIplayerHpText.str());
	this->baseHpText.setString(GUIbaseHpText.str());

	
	//update player GUI
	float playerHpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(200.f * playerHpPercent,this->playerHpBar.getSize().y));

	//update base GUI
	float baseHpPercent = static_cast<float>(this->base->getHp()) / this->base->getHpMax();
	this->baseHpBar.setSize(sf::Vector2f(200.f * baseHpPercent, this->baseHpBar.getSize().y));
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

void Game::updateEnemieBullets(){

	for(size_t i = 0; i < this->enemyBullets.size(); i++){


		this->enemyBullets[i]->update();
		bool erased=false;
		
		if(this->enemyBullets[i]->getBounds().intersects(this->player->getBounds())){
			this->player->loseHp(5);
			this->enemyBullets.erase(this->enemyBullets.begin() + i);
			erased = true;
		}

		if(erased == false && this->enemyBullets[i]->getBounds().intersects(this->base->getBounds())){
			this->base->loseHp(5);
			this->enemyBullets.erase(this->enemyBullets.begin() + i);
		}
	}

	//Faz o inimigo atirar
	for(int i = 0; i < this->enemies.size(); i++){

		if(this->enemies[i]->canAttack()){

			this->enemyBullets.push_back(new EnemyBullet(this->enemies[i]->getPosition(), this->player->getPos()));
		}
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

                //chance de criar munição e health
				int randomNum = rand() % 100;
                if(randomNum <= 19){
                    this->Ammos.push_back(new Ammo(this->enemies[i]->getPosition()));

                }
				if(randomNum <= 39 && randomNum >= 20) {
					this->healths.push_back(new Health(this->enemies[i]->getPosition()));
				}

				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}

		if (!enemy_removed) {
			
			//Enemy-player collision
			if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
				this->player->loseHp(this->enemies.at(i)->getDamage());
                if((rand() % 100) <= 19){
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
	for(int i = 0; i < this->Ammos.size(); i++){
		if(this->Ammos[i]->getBounds().intersects(this->player->getBounds())) {
			this->player->gainAmmo(5);
			this->Ammos.erase(this->Ammos.begin() + i);
		}
	}
}

void Game::updateHealthCollection() {
	for(int i = 0; i < this->healths.size(); i++) {
		if(this->healths[i]->getBounds().intersects(this->player->getBounds())) {
			this->base->gainHp(10);
			this->healths.erase(this->healths.begin() + i);
		}
	}
}


void Game::update()
{

	this->updateInput();

	this->player->update();

	this->updateCollision();
	
	this->updateBullets();

	this->updateEnemieBullets();

	this->updateEnemiesAndCombat();

	this->updateGUI();

	this->updateWorld();

	this->updateAmmoCollection();

	this->updateHealthCollection();

	this->updateGameDificulty();
}

void Game::renderGUI()
{
	//text
	this->window->draw(this->pointText);
	this->window->draw(this->ammoText);
	this->window->draw(this->playerHpText);
	this->window->draw(this->baseHpText);
	
	//hp bar
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->baseHpBarBack);
	this->window->draw(this->baseHpBar);

	
	
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

	for(auto* health : this->healths) {
		health->render(this->window);
	}
	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	this->player->render(*this->window);


	for(auto* enemyBullet : this->enemyBullets) {
		enemyBullet->render(this->window);
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
	
	if(this->points >= 200) {
		this->window->draw(this->YouWinText);
	}
	//Display stuff
	this->window->display();
}

void Game::restartGame() {

	// resetar tudo
	
	sf::Vector2f center(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);

	this->player->setPosition(center);

	this->points = 0;

	this->base->setHp(this->base->getHpMax());

	this->player->setHp(this->player->getHpMax());

	this->player->setAmmo(10);

	//deletar objetos (menos player)
	for(int i = this->enemies.size() - 1; i >= 0; i--) {
		this->enemies.erase(this->enemies.begin() + i);
	}

	for(int i = this->enemyBullets.size() - 1; i >= 0; i--) {
		this->enemyBullets.erase(this->enemyBullets.begin() + i);
	}

	for(int i = this->Ammos.size() - 1; i >= 0; i--) {
		this->Ammos.erase(this->Ammos.begin() + i);
	}

	for(int i = this->healths.size() - 1; i>= 0; i--) {
		this->healths.erase(this->healths.begin() + i);
	}

	this->firstDifIncrease = false;
	this->secondDifIncrease = false;
	this->thirdDifIncrease = false;

	this->spawnTimerMax = 100.f;
}

void Game::updateGameDificulty() {

	if(this->points > 50 && !this->firstDifIncrease) {
		this->spawnTimerMax -= 20.f;
		this->firstDifIncrease = true;
	}

	if(this->points > 100 && !this->secondDifIncrease) {
		this->spawnTimerMax -= 20.f;
		this->secondDifIncrease = true;
	}

	if(this->points > 150 && !this->thirdDifIncrease) {
		this->spawnTimerMax -= 20.f;
		this->thirdDifIncrease = true;
	}

}