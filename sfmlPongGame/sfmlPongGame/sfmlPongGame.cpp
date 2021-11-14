// sfmlPongGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works");

	window.setFramerateLimit(60);

	window.setKeyRepeatEnabled(false);

	bool play = true;

	sf::Event event;

	//font

	sf::Font font;

	if (font.loadFromFile("Data/arial.ttf") == 0) {
		return 1;
	}

	//images
	sf::Texture tex_pad;
	sf::Texture tex_ball;
	sf::Texture tex_background;

	if (tex_pad.loadFromFile("Data/pad.png") == false) {
		return -1;
	}

	if (tex_ball.loadFromFile("Data/ball.png") == false) {
		return -1;
	}

	if (tex_background.loadFromFile("Data/background.png") == false) {
		return -1;
	}

	//sounds

	sf::SoundBuffer buff_hit;

	if (buff_hit.loadFromFile("Data/hit.wav") == false) {
		return -1;
	}

	//States
	bool up = false;
	bool down = false;

	//Variables
	int yVelocityPad1 = 0;


	//Shapes

	//background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);

	//pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(30, 150));
	pad1.setPosition(50, 200);
	pad1.setTexture(&tex_pad);

	//pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(30, 150));
	pad2.setPosition(720, 200);
	pad2.setTexture(&tex_pad);

	//ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(30, 30));
	ball.setPosition(400, 270);
	ball.setTexture(&tex_ball);

	//game loop
	while (play == true) {

		//Events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				play = false;
			}
			//key pressed
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				up = true;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				down = true;
			}
			//key released
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
				up = false;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
				down = false;
			}
		}

		//logic
		if (up == true) {
			yVelocityPad1 = -5;
		}

		if (down == true) {
			yVelocityPad1 = 5;
		}

		if (up == true && down == true) {
			yVelocityPad1 = 0;
		}

		if (up == false && down == false) {
			yVelocityPad1 = 0;
		}


		pad1.move(0, yVelocityPad1);

		//out of bounds

		if (pad1.getPosition().y < 0) {
			pad1.setPosition(50, 0);
		}

		if (pad1.getPosition().y > 450) {
			pad1.setPosition(50, 450);
		}
		//rendering
		window.clear();

		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);


		window.display();
	}

	window.close();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
