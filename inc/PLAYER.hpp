#pragma once
#include <SFML/Graphics.hpp>
#include <MAP.hpp>

float offsetX = 0, offsetY = 0;

namespace my {
	class PLAYER {

	public:

		float dx, dy;
		sf::FloatRect rect;
		bool onGround;
		sf::Sprite sprite;
		float currentFrame;
		bool f, direction;

		PLAYER(sf::Texture& image)
		{
			sprite.setTexture(image);
			rect = sf::FloatRect(7 * 32, 9 * 32, 40, 50);
			dx = dy = 0.1;
			currentFrame = 0;
		}


		void update(float time)
		{
			rect.left += dx * time;
			Collision(0);
			if (!onGround) 
			{
				dy = dy + 0.0005 * time;
			}
			rect.top += dy * time;
			onGround = false;
			Collision(1);

			if (f)
			{
				currentFrame += 0.005 * time;
				
				if (currentFrame > 6) {
					currentFrame -= 6;
				}
				if (dx > 0) {
					sprite.setTextureRect(sf::IntRect(40 * int(currentFrame), 244, 40, 50));
				}

				if (dx < 0) {
					sprite.setTextureRect(sf::IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
				}
				f = false;
			}
			else
			{
				currentFrame += 0.0025 * time;
				if (currentFrame > 3) {
					currentFrame -= 3;
				}
				if (direction) {
					sprite.setTextureRect(sf::IntRect(44 * int(currentFrame), 190, 40, 50));
				}
				if (!direction) {
					sprite.setTextureRect(sf::IntRect(44 * int(currentFrame) + 44, 190, -40, 50));
				}
			}

			sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

			dx = 0;
		}



		void Collision(int dir)
		{
			for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
				for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
				{
					if ((TileMap[i][j] == 'B') || (TileMap[i][j] == 'Z'))
					{
						if ((dx > 0) && (dir == 0)) {
							rect.left = j * 32 - rect.width;
						}
						if ((dx < 0) && (dir == 0)) {
							rect.left = j * 32 + 32;
						}
						if ((dy > 0) && (dir == 1)) { 
							rect.top = i * 32 - rect.height;  
							dy = 0; 
							onGround = true;
						}
						if ((dy < 0) && (dir == 1)) { 
							rect.top = i * 32 + 32;   
							dy = 0; 
						}
					}

					if (TileMap[i][j] == '0')
					{
						TileMap[i][j] = ' ';
					}

				}
		}
		~PLAYER();
	};
	
}