// sfmlPongGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
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

	// score
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Yellow);
	score.setPosition(370, 10);
	score.setString("0 : 0");

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
	sf::SoundBuffer goalP1;
	sf::SoundBuffer goalP2;


	sf::Sound hit;
	sf::Sound pad1goal;
	sf::Sound pad2goal;

	sf::Music music;


	hit.setBuffer(buff_hit);
	pad1goal.setBuffer(goalP1);
	pad2goal.setBuffer(goalP2);


	if (goalP1.loadFromFile("Data/goal1.wav") == false) {
		return -1;
	}

	if (goalP2.loadFromFile("Data/goal2.wav") == false) {
		return -1;
	}

	if (buff_hit.loadFromFile("Data/hit.wav") == false) {
		return -1;
	}

	if (music.openFromFile("Data/beat.ogg") == false) {
		return -1;
	}


	music.play();
	music.setLoop(true);

	//States
	bool up = false;
	bool down = false;

	//Variables
	int yVelocityPad1 = 0;
	int xVelocityBall = -4;
	int yVelocityBall = -4;
	int yVelocityPad2 = 0;
	int pad1Score = 0;
	int pad2Score = 0;


	//Shapes

	//background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);

	//pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(20, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&tex_pad);

	//pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(20, 100));
	pad2.setPosition(700, 200);
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

		//LOGIC
		//pad1
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

		//pad2- AI
		if (ball.getPosition().y < pad2.getPosition().y) {
			yVelocityPad2 = -3;
		}

		if (ball.getPosition().y > pad2.getPosition().y) {
			yVelocityPad2 = 3;
		}

		pad2.move(0, yVelocityPad2);

		//ball
		ball.move(xVelocityBall, yVelocityBall);

		//out of bounds

		if (ball.getPosition().y < 0) {
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().y > 570) {
			yVelocityBall = -yVelocityBall;
		}

		//score out of bounds
		if (ball.getPosition().x < -50) {
			pad2Score++;
			pad2goal.play();
			ball.setPosition(300, 200);
		}

		if (ball.getPosition().x > 800) {
			pad1Score++;
			pad1goal.play();
			ball.setPosition(300, 200);
		}

		//collision with pad1
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true) {
			xVelocityBall = -xVelocityBall;
			hit.play();
		}
		//collision with pad2
		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true) {
			xVelocityBall = -xVelocityBall;
			hit.play();
		}
		//rendering
		window.clear();

		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);
		//Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);


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
