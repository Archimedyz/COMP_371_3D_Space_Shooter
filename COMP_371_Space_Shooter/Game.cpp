#include "Game.h"


Game* Game::instance;

Game::Game()
{
	instance = this;
	Score = 0;
	Lives = 3;
}

Game::~Game()
{
}

void Game::PlayerDeath()
{
	if (Lives <= 0)
		Lose();
	else
	{
		// Create new ship
	}
}

void Game::Lose()
{
	// Display text like "YOU LOSE!"
	// Show final score
	// Create explosion(?)
	// Stop update loop for asteroids and things (?)
}

void Game::AddScore(int s)
{
	if ((Score + s) % LifeIncrement > Score % LifeIncrement)
		Lives++;
	Score += s;
}