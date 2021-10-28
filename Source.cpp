#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
#include <time.h>

using namespace sf;
int score = 0;
int mm = -1;


struct candy
{
	int x, y, col, row, kind, match, alpha;
	candy(){ match = 0; alpha = 255; }
} Grid[10][10];

void Match_Find(){
	for (int i = 1; i <= 9; i++){
		for (int j = 1; j <= 9; j++)
		{
			if (Grid[i][j].kind == Grid[i + 1][j].kind)
			if (Grid[i][j].kind == Grid[i - 1][j].kind)
			for (int n = -1; n <= 1; n++) Grid[i + n][j].match++;

			if (Grid[i][j].kind == Grid[i][j + 1].kind)
			if (Grid[i][j].kind == Grid[i][j - 1].kind)
			for (int n = -1; n <= 1; n++) Grid[i][j + n].match++;
		}
	}
}

	void swap(candy c1, candy c2)
	{
		std::swap(c1.col, c2.col);
		std::swap(c1.row, c2.row);

		Grid[c1.row][c1.col] = c1;
		Grid[c2.row][c2.col] = c2;
	}

	void get_score(){
		
		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			score += Grid[i][j].match;
	}

	void sweety(){
		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
		{
			Grid[i][j].kind = rand() % 6;
			Grid[i][j].col = j;
			Grid[i][j].row = i;
			Grid[i][j].x = j * 54;
			Grid[i][j].y = i * 54;
		}

	}


	void playy(){

		

		RenderWindow game(VideoMode(1067, 600), "Match-3 Game!", Style::Resize | Style::Close);
		game.setFramerateLimit(60);
       //music		
		SoundBuffer candy_cane;
		candy_cane.loadFromFile("images/sia.wav");
		Sound sound;
		sound.setBuffer(candy_cane);
		sound.play();
		sound.setLoop(true);
		
		Texture B, C, P;
		B.loadFromFile("images/Level1.png");
		C.loadFromFile("images/sweet.png");

		Sprite Level1(B), sweet(C);
		sweet.setScale(0.8, 0.8);

		sweety();
		int x0, y0, x, y; int click = 0; Vector2i pos;
		bool isSwap = false, isMoving = false;

		while (game.isOpen())
		{
			//cand_cane();
			Event e;
			while (game.pollEvent(e))
			{
				if (e.type == Event::Closed)
					game.close();
				if (e.type == Event::KeyReleased){
					if (e.key.code == Keyboard::Escape){
						game.close();
					}
				}
				if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					if (!isSwap && !isMoving) click++;
					pos = Mouse::getPosition(game) - Vector2i (35, 65);
				}
			}

			// mouse click
			if (click == 1)
			{
				x0 = pos.x / 54 + 1;
				y0 = pos.y / 54 + 1;
			}
			if (click == 2)
			{
				x = pos.x / 54 + 1;
				y = pos.y / 54 + 1;
				if (abs(x - x0) + abs(y - y0) == 1)
				{
					swap(Grid[y0][x0], Grid[y][x]); isSwap = 1; click = 0;
				}
				else click = 1;
			}

			Match_Find();
			//moving animation

			//postion++

			//isMoving = false;
			//if move true
			
			// Deleting amimation
			get_score();
			// Second swap if no match
			//fun problem

			if (isSwap && !isMoving)
			{
				if (!score) swap(Grid[y0][x0], Grid[y][x]); isSwap = 0;
			}

			//update grid
			game.draw(Level1);
			for (int i = 1; i <= 9; i++){
				for (int j = 1; j <= 9; j++){

					sweet.setTextureRect(IntRect(Grid[i][j].kind * 94, 200, 94, 94));
					sweet.setColor(Color(255, 255, 255, 255));
					sweet.setPosition(Grid[i][j].x, Grid[i][j].y);
					sweet.move(35-54, 65-54);

					game.draw(sweet);


				}

			}
			
			game.display();
		}

		
		
	}
	
	void Intial(){
		int page_num = -1;
		srand(time(0));
		//0101635666
		RenderWindow game(VideoMode(1067, 600), "Match-3 Game!", Style::Resize | Style::Close);
		game.setFramerateLimit(60);


		menu menu(1067, 600);


		Texture  P;

		P.loadFromFile("images/play.png");
		Sprite play(P);

		while (game.isOpen())
		{
			Event e;
			while (game.pollEvent(e))
			{
				if (e.type == Event::Closed){
					game.close();
				}
				if (e.type == Event::KeyReleased){
					if (e.key.code == Keyboard::Up){
						menu.move_up();
						break;
					}
					if (e.key.code == Keyboard::Down){
						menu.move_down();
						break;
					}
					if (e.key.code == Keyboard::Return){

						if (menu.mainmenupressed() == 0){
							game.close();
							page_num = 0;
						}
						if (menu.mainmenupressed() == 1){
							game.close();
							page_num = 1;

						}
						if (menu.mainmenupressed() == 2){
							game.close();
							page_num = 2;

						}
					}
					
				}

				game.draw(play);
				menu.draw(game);
				game.display();


			}
			if (page_num == 0)
			{
				
			   playy();
			  

			}
			if (page_num == 1)
			{
				game.close();
				break;

			}
			if (page_num == 2)
			{
				break;

			}
			


			
		}
		
	}
	
	int main()
	{








			Intial();
		

		return 0;
	}