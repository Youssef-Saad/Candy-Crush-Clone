#pragma once
#define max_main_menu 3
#include <SFML/Graphics.hpp>
using namespace sf;
class menu
{
public:
	menu(float width , float hight);

	void draw(sf::RenderWindow &game);
	void move_up();
	void move_down();
	int mainmenupressed(){
		return mainmenuselected;
	}
	~menu();
	private:
		int mainmenuselected;
		Font font;
		Text mainmenu[max_main_menu];
};

