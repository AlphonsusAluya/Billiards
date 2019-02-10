// author alphonsus
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "MyVector3.h"

class Game
{
public:
	Game();
	~Game();


	void run();

private:
	MyVector3 ballPosition = { 200.0f, 300.0f, 0.0f };
	MyVector3 ballVelocity = { 0.0f, 0.0f, 0.0f };
	MyVector3 mousePosition = { 0.0f, 0.0f, 0.0f };

	MyVector3 redBallPosition = { 50.0f, 100.0f, 0.0f };
	MyVector3 redBallVelocity = { 0.0f, 0.0f, 0.0f };

	MyVector3 yellowBallPosition = { 300.0f, 200.0f, 0.0f };
	MyVector3 yellowBallVelocity = { 0.0f, 0.0f, 0.0f };

	MyVector3 pocketPositionOne = { 0,0,0 };
	MyVector3 pocketPositionTwo = { 400,0,0 };
	MyVector3 pocketPositionThree = { 800,0,0 };
	MyVector3 pocketPositionFour = { 0,600,0 };
	MyVector3 pocketPositionFive = { 400,600,0 };
	MyVector3 pocketPositionSix = { 800,600,0 };

	sf::RectangleShape table;
	sf::RectangleShape cushion;
	sf::CircleShape cueBall;
	sf::Vertex mouseVertex;
	sf::Vertex ballVertex;
	sf::VertexArray aimingLine;

	MyVector3 Radius{ 20, 20, 0 };

	const double POWER = 0.06;



	void friction();
	void collisions(MyVector3 t_positionA, MyVector3 &t_velocityA, MyVector3 t_positionB, MyVector3 &t_velocityB);
	void collisionDetection();
	void border();
	void ballMovement(MyVector3 &t_ballPosition, MyVector3 &t_ballVelocity);
	void setUpBackgroud();
	void passBall(sf::Color, MyVector3);
	void setUpAim();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();



	sf::RenderWindow m_window; // main SFML window

	bool m_exitGame; // control exiting game
	bool m_ballStop = false;
	bool m_aim;
	bool collision = false;
	bool m_aimDone = false;

};

#endif // !GAME

