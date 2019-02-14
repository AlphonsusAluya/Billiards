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
	loadMessages();
	setUpBackgroud();
}


Game::~Game()
{
}

int radius = 20;


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
void Game::friction(MyVector3 &t_ballVelocity)
{
	t_ballVelocity = t_ballVelocity * 0.996; // slows the balls down
	


}
void Game::allBallStopped()
{
	if (ballVelocity.length() < 0.6 && redBallVelocity.length() < 0.6 && yellowBallVelocity.length() < 0.6 && !m_ballStop) // if the length gets to small it make sure the if statment will be executed and the ball stops
	{
		ballVelocity = { 0.0f, 0.0f, 0.0f }; // makes it stop
		redBallVelocity = { 0.0f, 0.0f, 0.0f }; // makes it stop
		yellowBallVelocity = { 0.0f, 0.0f, 0.0f }; // makes it stop
		cannon();
		scoring();
		displayMessages();
		pottedBalls();
		m_ballStop = true;
		if (m_score == false)
		{
			m_yellowSpawn = false;
			m_whiteSpawn = false;
			m_turns = !m_turns;
		}
		boolReset();
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="t_positionA"></param>
/// <param name="t_velocityA"></param>
/// <param name="t_positionB"></param>
/// <param name="t_velocityB"></param>
void Game::collisions(MyVector3 t_positionA, MyVector3 &t_velocityA, MyVector3 t_positionB, MyVector3 &t_velocityB)
{
	MyVector3 space = t_positionA - t_positionB;

	MyVector3 boom = t_velocityA;
	t_velocityA = boom.rejection(space) + t_velocityB.projection(space);
	t_velocityB = t_velocityB.rejection(space) + boom.projection(space);
	//t_velocityA.reverseX();

}
void Game::collisionDetection()
{
	MyVector3 yellowSpace = yellowBallPosition - ballPosition;
	MyVector3 space = ballPosition - redBallPosition;
	MyVector3 redSpace = redBallPosition - yellowBallPosition;

	if (yellowSpace.length() <= radius * 2)
	{
		collisions(ballPosition, ballVelocity, yellowBallPosition, yellowBallVelocity);
		if (m_turns == true)
		{
			m_yellowHitsWhite = true;
		}
		else
		{
			m_whiteHitsYellow = true;
		}
	}

	if (space.length() <= radius * 2)
	{
		collisions(ballPosition, ballVelocity, redBallPosition, redBallVelocity);
		m_whiteHitsRed = true;
	}

	if (redSpace.length() <= radius * 2)
	{

		collisions(yellowBallPosition, yellowBallVelocity, redBallPosition, redBallVelocity);
		m_yellowHitsRed = true;
	}
	for (int i = 0; i < 6; i++)
	{
		MyVector3 whiteSpacePocket = ballPosition - pocketPostion[i];
		MyVector3 redSpacePocket = redBallPosition - pocketPostion[i];
		MyVector3 yellowSpacePocket = yellowBallPosition - pocketPostion[i];

		if (whiteSpacePocket.length() <= radius * 2)
		{
			ballVelocity = { 0.0f, 0.0f, 0.0f };
			ballPosition = { 1000, 1000, 0 };
			m_whitePocketed = true;
		}

		if (redSpacePocket.length() <= radius * 2)
		{
			redBallVelocity = { 0.0f, 0.0f, 0.0f };
			redBallPosition = { 1000, 1000, 0 };
			m_redPocketed = true;
		}

		if (yellowSpacePocket.length() <= radius * 2)
		{
			yellowBallVelocity = { 0.0f, 0.0f, 0.0f };
			yellowBallPosition = { 1000, 1000, 0 };
			m_yellowPocketed = true;
		}
	}
}
void Game::scoring()
{
	if (m_whitePocketed == true)
	{
		if (m_yellowSpawn == false && m_turns == true)
		{
			theScoreForYellow = theScoreForYellow + 2;
			m_whitePotByYellow = true;
			m_yellowSpawn = true;
			m_score = true;
		}
		if (m_turns == false)
		{
			if (m_whiteHitsYellow)
			{
				m_score = true;
				theScoreForWhite = theScoreForWhite + 2;
				InOff = 2;
				m_inOffWhite = true;
			}
			if (!m_whiteHitsYellow && m_whiteHitsRed)
			{
				m_score = true;
				theScoreForWhite = theScoreForWhite + 3;
				InOff = 3;
				m_inOffWhite = true;
			}
			if (!m_whiteHitsRed && !m_whiteHitsYellow)
			{
				m_foulPotting = true;
			}
		}

	}
	if (m_redPocketed == true)
	{
		if (m_turns == false)
		{
			m_redPotByWhite = true;
			m_score = true;
			theScoreForWhite = theScoreForWhite + 3;
		}
		else
		{
			m_redPotByYellow = true;
			m_score = true;
			theScoreForYellow = theScoreForYellow + 3;
		}
	}
	if (m_yellowPocketed == true)
	{
		if (m_whiteSpawn == false && m_turns == false)
		{
			m_whiteSpawn = true;
			m_score = true;
			m_yellowPotByWhite = true;
			theScoreForWhite = theScoreForWhite + 2;
		}
		if (m_turns == true)
		{
			if (m_yellowHitsWhite)
			{
				m_score = true;
				theScoreForYellow = theScoreForYellow + 2;
				InOff = 2;
				m_inOffYellow = true;
			}
			if (!m_whiteHitsYellow && m_whiteHitsRed)
			{
				m_score = true;
				theScoreForYellow = theScoreForYellow + 3;
				InOff = 3;
				m_inOffYellow = true;
			}
			if (!m_whiteHitsRed && !m_whiteHitsYellow)
			{
				m_foulPotting = true;
			}
		}
	}
}
void Game::cannon()
{
	if (m_turns == true)
	{
		if (m_cannon == true)
		{
			m_cannon = true;
			m_score = true;
			theScoreForYellow = theScoreForYellow + 2;
		}
	}
	else if (m_turns == false)
	{
		if (m_cannon == true)
		{
			m_score = true;
			m_cannon = true;
			theScoreForWhite = theScoreForWhite + 2;
		}
	}
}
void Game::cannonDetection()
{
	if (m_turns == false)
	{
		if (m_whiteHitsYellow && m_whiteHitsRed)
		{
			m_cannon = true;
			m_score = true;
			theScoreForWhite = theScoreForWhite + 2;
		}
	}

	if (m_turns == true)
	{
		if (m_yellowHitsWhite && m_yellowHitsRed)
		{
			m_cannon = true;
			m_score = true;
			theScoreForYellow = theScoreForYellow + 2;
		}
	}
	if (m_cannon == true)
	{
		
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

	if (redBallPosition.x >= 750 || redBallPosition.x <= 15) // the sides of the table(the cushion)
	{
		redBallVelocity.reverseX(); // it gets reversed
	}

	if (redBallPosition.y <= 10 || redBallPosition.y >= 550) // the top and bottom cushions
	{
		redBallVelocity.reverseY(); // the y values gets reversed
	}

	if (yellowBallPosition.x >= 750 || yellowBallPosition.x <= 15) // the sides of the table(the cushion)
	{
		yellowBallVelocity.reverseX(); // it gets reversed
	}

	if (yellowBallPosition.y <= 10 || yellowBallPosition.y >= 550) // the top and bottom cushions
	{
		yellowBallVelocity.reverseY(); // the y values gets reversed
	}
}
void Game::fouls()
{
	if (m_turns == true)
	{
		if (!m_yellowHitsRed && !m_yellowHitsWhite)
		{
			m_nothingHit = true;
		}
		if (m_nothingHit || m_foulPotting)
		{
			theScoreForWhite = theScoreForWhite + 2;
		}
	}
	if (m_turns == false)
	{
		if (!m_whiteHitsRed && !m_whiteHitsYellow)
		{
			m_nothingHit = true;
		}
		if (m_nothingHit || m_foulPotting)
		{
			theScoreForYellow = theScoreForYellow + 2;
		}
	}
}
void Game::pottedBalls()
{
	if (m_whitePocketed == true)
	{
		if (m_turns == false)
		{
			ballPosition = newBallPosition;
			m_whitePocketed == false;
		}

		if (m_turns == true)
		{
			if(m_score == false)
			{
				ballPosition = newBallPosition;
				m_whitePocketed == false;
			}
		}
	}
	if (m_yellowPocketed == true)
	{
		if (m_turns == false)
		{
			if (m_score == false)
			{
				yellowBallPosition = newYellowBallPosition;
				m_yellowPocketed = false;
			}
		}
		if (m_turns == true)
		{
			yellowBallPosition = newYellowBallPosition;
			m_yellowPocketed = false;
		}
	}
	if (m_redPocketed == true)
	{
		redBallPosition = newRedBallPosition;
		m_redPocketed = false;
	}
}
void Game::ballMovement(MyVector3 &t_ballPosition, MyVector3 &t_ballVelocity)
{
	t_ballPosition = t_ballPosition + t_ballVelocity;
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

	ballVertex = sf::Vertex(ballPosition, sf::Color::Green);
	yellowBallVertex = sf::Vertex(yellowBallPosition, sf::Color::Green);
	mouseVertex = sf::Vertex(mousePosition, sf::Color::Green);



}
void Game::passBall(sf::Color t_colour, MyVector3 t_ballPosition)
{
	cueBall.setPosition(t_ballPosition.x - radius, t_ballPosition.y - radius);
	cueBall.setFillColor(t_colour);
	m_window.draw(cueBall);
}


void Game::setUpAim() // setting up the aiming
{
	mouseVertex.position = static_cast<sf::Vector2f>(mousePosition); // sets the starting position of the vertext as the mouse
	if(m_turns == false)
	{
		ballVertex = static_cast<sf::Vector2f>(ballPosition);
	}
	if (m_turns == false)
	{
		ballVertex.position = static_cast<sf::Vector2f>(ballPosition); // sets the starting position of the vertex as the ball
		aimingLine.clear();
		aimingLine.append(mouseVertex);
		aimingLine.append(ballVertex);
	}
	if (m_turns == true)
	{
		yellowBallVertex = static_cast<sf::Vector2f>(yellowBallPosition);
	}
	if (m_turns == true)
	{
		
		aimingLine.clear();
		aimingLine.append(mouseVertex);
		aimingLine.append(yellowBallVertex);
	}
	

}
void Game::displayMessages()
{
	display = "White has " + std::to_string(theScoreForWhite) + " points " "\n" + "Yellow has " + std::to_string(theScoreForYellow) + " points" + "\n";
	if (m_turns == false)
	{
		std::cout << "Whites turn " << "\n";
		if (m_whiteHitsRed)
		{
			std::cout << "White hit red " << "\n";
		}
		if (m_whiteHitsYellow)
		{
			std::cout << "White hit yellow " << "\n";
		}
		if (m_nothingHit || m_foulPotting)
		{
			std::cout << " foul pot two points for yellow " << "\n";
		}
		if (m_cannon)
		{
			std::cout << " white Cannon " << "\n";
		}
	}
	if (m_turns == true)
	{
		std::cout << "Whites turn " << "\n";
		if (m_yellowHitsRed)
		{
			std::cout << "Yellow hit red " << "\n";
		}
		if (m_yellowHitsWhite)
		{
			std::cout << "Yellow hit white " << "\n";
		}
		if (m_nothingHit || m_foulPotting)
		{
			std::cout << " foul pot two points for white " << "\n";
		}
		if (m_cannon)
		{
			std::cout << " Yellow Cannon " << "\n";
		}
	}

	if (m_redPotByWhite)
	{
		std::cout << "White pots red " << "2 points " << "\n";
	}
	if (m_redPotByYellow)
	{
		std::cout << "Yellow pots red " << "2 points " << "\n";
	}
	if (m_whitePotByYellow)
	{
		std::cout << "Yellow pots White " << "2 points " << "\n";
	}
	if (m_yellowPotByWhite)
	{
		std::cout << "White pots yellow  " << "2 points " << "\n";
	}
	if (m_inOffYellow == true)
	{
		std::cout << "Yellow in-Off gets " << InOff << "\n";
	}
	if (m_inOffWhite == true)
	{
		std::cout << "White in-Off gets " << InOff << "\n";
	}

	std::cout << "White currently has " << theScoreForWhite << "points" << "\n";
	std::cout << "Yellow currently has " << theScoreForYellow << "points" << "\n";
}
void Game::loadMessages()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error ";
	}

	messages.setFont(font);
	messages.setCharacterSize(20);
	messages.setFillColor(sf::Color::White);
	messages.setPosition(30, 40);
}
void Game::boolReset()
{
	bool m_whiteHitsRed = false;
	bool m_yellowHitsRed = false;
	bool m_whiteHitsYellow = false;
	bool m_yellowHitsWhite = false;
	bool m_cannon = false;
	bool m_foulPotting = false;
	bool m_nothingHit = false;
	bool m_redPotByWhite = false;
	bool m_redPotByYellow = false;
	bool m_whitePotByYellow = false;
	bool m_yellowPotByWhite = false;
	bool m_inOffWhite = false;
	bool m_inOffYellow = false;
	bool m_score;
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
		if (m_ballStop && m_turns == false)
		{
			if (sf::Event::Closed == event.type) // window message
			{
				m_window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && m_ballStop == true)
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
				m_ballStop = false;
				m_aimDone = true;
			}
		}
		if (m_ballStop && m_turns == true)
		{
			if (sf::Event::Closed == event.type) // window message
			{
				m_window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && m_ballStop == true)
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
				yellowBallVelocity = yellowBallPosition - mousePosition; // gets the distance
				yellowBallVelocity = yellowBallVelocity * POWER; // adds power to the balll on release
				m_ballStop = false;
				m_aimDone = true;
			}
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

	// makes sure the ball moves and is animated
	friction(ballVelocity); // makes sure the ball slows down due to friction
	friction(redBallVelocity); // makes sure the red ball slows down due to friction
	friction(yellowBallVelocity); // makes sure the yellow ball slows down due to friction
	border(); // makes sure the cushion does its job
	cannonDetection();
	allBallStopped();
	setUpAim();
	


	collisionDetection();
	if (m_aimDone == true)
	{
		ballMovement(redBallPosition, redBallVelocity);
		ballMovement(ballPosition, ballVelocity);
		ballMovement(yellowBallPosition, yellowBallVelocity);

	}


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

	aimingLine.clear(); // clears the line
	m_window.clear(sf::Color::Black);
	m_window.draw(cushion); // draws the cushion
	m_window.draw(table);// draws the table

	passBall(sf::Color::Yellow, yellowBallPosition);
	passBall(sf::Color::Color(155, 9, 31), redBallPosition);
	passBall(sf::Color::White, ballPosition);

	passBall(sf::Color::Black, pocketPositionOne);
	passBall(sf::Color::Black, pocketPositionTwo);
	passBall(sf::Color::Black, pocketPositionThree);
	passBall(sf::Color::Black, pocketPositionFour);
	passBall(sf::Color::Black, pocketPositionFive);
	passBall(sf::Color::Black, pocketPositionSix);

	if (m_aim == true)
	{
		m_window.draw(aimingLine); // draws the line
	}

	if (m_ballStop)
	{
		m_window.draw(messages);
	}

	messages.setString(display);
	m_window.display();

}
