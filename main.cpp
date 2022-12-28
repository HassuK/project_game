#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>


int main()
{

	const int W = 40;

	int stayflag = 0;

	sf::RenderWindow window(sf::VideoMode(600, 400), "Test!");

	sf::Texture t;
	t.loadFromFile("../assets/fang.png");
	t.loadFromFile("assets/fang.png");

	sf::Texture tileSet;
	tileSet.loadFromFile("assets/blocks.png");
	tileSet.loadFromFile("../assets/blocks.png");

	float currentFrame = 0;
	
	sf::Sprite tile(tileSet);
	my::PLAYER p(t);

	sf::Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;

		if (time > 20) time = 20;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			p.dx = -0.1;
			stayflag = 1;
			p.f = true;
			p.direction = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p.dx = 0.1;
			stayflag = 1;
			p.f = true;
			p.direction = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (p.onGround) { p.dy = -0.35; p.onGround = false; stayflag = 1; }
		}
		if (stayflag != 1)
		{
			p.f = false;
		}

		p.update(time);

		if (p.rect.left > 300 && p.rect.left < 980)
		{
			offsetX = p.rect.left - 300;
		}
		offsetY = p.rect.top - 200;

		window.clear(sf::Color(200, 140, 255));


		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'Z')
				{
					tile.setTextureRect((sf::IntRect(0, 0, 32, 32)));
				}

				if (TileMap[i][j] == 'B')
				{
					tile.setTextureRect((sf::IntRect(0, 80, 32, 32)));
				}

				if (TileMap[i][j] == '0')
				{
					tile.setTextureRect((sf::IntRect(240, 80, 32, 32)));
				}


				if (TileMap[i][j] == ' ')
				{
					continue;
				}

				tile.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(tile);
			}

		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
