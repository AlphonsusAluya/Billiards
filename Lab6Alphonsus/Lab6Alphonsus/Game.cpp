// Alphonsus Aluya
// C00237736
// estimated time: 8 hours
// actual time ??
// issues: none
// Bugs: none

#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "time.h"
#include <stdlib.h>
#include "MyVector3.h"



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setUpBackgroud();
}


Game::~Game()
{
}




void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::friction()
{
	ballVelocity = ballVelocity * 0.996; // slows the ball down

	if (ballVelocity.length() < 0.6) // if the length gets to small it make sure the if statment will be executed and the ball stops
	{
		ballVelocity = { 0.0f, 0.0f, 0.0f }; // makes it stop
	}
}
void Game::border()
{
	if (ballPosition.x >= 750 || ballPosition.x <= 15) // the sides of the table(the cushion)
	{
		ballVelocity.reverseX(); // it gets reversed
	}

	if (ballPosition.y <= 10 || ballPosition.y >= 550) // the top and bottom cushions
	{
		ballVelocity.reverseY(); // the y values gets reversed
	}
}
void Game::ballMovement()
{
	ballPosition = ballPosition + ballVelocity; // makes sure the ball moves
}
void Game::setUpBackgroud()
{
	table.setPosition(10, 10); // position of the table
	table.setSize(sf::Vector2f{ 780.0f,580.0f }); // the size of the table
	table.setFillColor(sf::Color::Red); // colour of the table is red

	cushion.setPosition(0, 0); // position of the cushions
	cushion.setFillColor(sf::Color(117, 41, 31)); // the colour of the cushions is grey
	cushion.setSize(sf::Vector2f{ 800.0f, 600.0f }); // the size of the cushions

	cueBall.setPosition(ballPosition); // the position of the ball
	cueBall.setRadius(20); // the size of the ball
	cueBall.setFillColor(sf::Color::White); // the colour of the ball is white

	
}
void Game::setUpAim() // setting up the aiming
{
	mouseVertex.position = static_cast<sf::Vector2f>(mousePosition); // sets the starting position of the vertext as the mouse
	ballVertex.position = static_cast<sf::Vector2f>(ballPosition); // sets the starting position of the vertex as the ball
	aimingLine.clear(); // clears the line
	aimingLine.append(mouseVertex);
	aimingLine.append(ballVertex);

}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed && m_ballStop)
		{
			m_aim = true; // begins aiming
			mousePosition = MyVector3{ static_cast<double>(event.mouseButton.x), static_cast<double>(event.mouseButton.y), 0.0 };
		}
		if (event.type == sf::Event::MouseMoved && m_aim)
		{
			mousePosition = MyVector3{ static_cast<double>(event.mouseMove.x), static_cast<double>(event.mouseMove.y), 0.0 };
		}
		if (m_aim && event.type == sf::Event::MouseButtonReleased)
		{
			m_aim = false;
			ballVelocity = ballPosition - mousePosition; // gets the distance
			ballVelocity = ballVelocity * POWER; // adds power to the balll on release
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	ballMovement(); // makes sure the ball moves and is animated
	friction(); // makes sure the ball slows down due to friction
	border(); // makes sure the cushion does its job
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	cueBall.setPosition(ballPosition);

	m_window.clear(sf::Color::Black);
	m_window.draw(cushion); // draws the cushion
	m_window.draw(table);// draws the table
	m_window.draw(aimingLine); // draws the line
	m_window.draw(cueBall); // draws the cue ball
	m_window.display();
	
}

