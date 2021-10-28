#include "menu.h"


menu::menu(float width, float hight)
{
	if (!font.loadFromFile("images/yoyo.ttf")){}
	//play
	mainmenu[0].setFont(font );
	mainmenu[0].setColor(sf::Color::Blue);
	mainmenu[0].setString("play");
	mainmenu[0].setCharacterSize(65);
	mainmenu[0].setPosition(sf::Vector2f(width / 2-20,hight-350));
	//list
	mainmenu[1].setFont(font);
	mainmenu[1].setColor(sf::Color::White);
	mainmenu[1].setString("score");
	mainmenu[1].setCharacterSize(65);
	mainmenu[1].setPosition(sf::Vector2f(width / 2-20, hight-250));

	//exit
	mainmenu[2].setFont(font);
	mainmenu[2].setColor(sf::Color::White);
	mainmenu[2].setString("exit");
	mainmenu[2].setCharacterSize(65);
	mainmenu[2].setPosition(sf::Vector2f(width /2 -20, hight-150));

	mainmenuselected = 0;
}


menu::~menu()
{
}

//fun draw mmainmenu
void menu::draw(sf::RenderWindow &game){
	for (int i = 0; i <= 2; i++){
		game.draw(mainmenu[i]);
	}
}

//move down
void menu::move_down(){
	if (mainmenuselected + 1 <= max_main_menu){
		mainmenu[mainmenuselected].setColor(sf::Color::White);

		mainmenuselected++;
		if (mainmenuselected == 3){
			mainmenuselected = 0;
		}
		mainmenu[mainmenuselected].setColor(sf::Color::Blue);
	}

}


//move up
void menu::move_up(){
	if (mainmenuselected - 1 >= -1){
		mainmenu[mainmenuselected].setColor(sf::Color::White);

		mainmenuselected++;
		if (mainmenuselected == -1){
			mainmenuselected = 2;
		}
		mainmenu[mainmenuselected].setColor(sf::Color::Blue);
	}

}

