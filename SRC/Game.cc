#include "Game.hh"

Game::Game():
menu_game("Images/menu.png"),
window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Le monde d'apres ...")
{
	this->map = menu;
}

Game::~Game()
{
}

bool Game::get_map() const
{
	return this->map;
}

void Game::set_map(Map map)
{
	this->map = map;
}

void Game::run()
{
	while (this->window.isOpen())
    {
        // ==ON S'OCCUPE DE SAVOIR SI ON DOIT FERMER LA window==
        while (this->window.pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed)
            {
                this->window.close();
            }
        }
        this->window.clear();
        this->draw();
        this->window.display();
    }
}

void Game::draw()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && map==menu)
		this->map = personnage;
	if(this->map == menu)
		this->menu_game.draw(this->window);
}