// author Peter Lowe
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
	MyVector3 ballPosition = { 100.0f, 100.0f, 0.0f };
	MyVector3 ballVelocity = { 0.0f, 0.0f, 0.0f };
	MyVector3 mousePosition = { 0.0f, 0.0f, 0.0f };

	sf::RectangleShape table;
	sf::RectangleShape cushion;
	sf::CircleShape cueBall;
	sf::Vertex mouseVertex;
	sf::Vertex ballVertex;
	sf::VertexArray aimingLine;


	const double POWER = 0.06;

	void friction();
	void border();
	void ballMovement();
	void setUpBackgroud();
	void setUpAim();
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	

	sf::RenderWindow m_window; // main SFML window
	
	bool m_exitGame; // control exiting game
	bool m_ballStop;
	bool m_aim;

};

#endif // !GAME

