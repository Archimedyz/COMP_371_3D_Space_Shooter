#include "Game.h"
#include "World.h"
#include "Model.h"
#include <iostream>

Game* Game::instance;

Game::Game()
{
	instance = this;
	score = 0;
	lives = 1;
	playerHealth = 5;
}

Game::~Game()
{
}

void Game::PlayerDeath()
{
	if (lives <= 0)
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
	std::cout << "You lose!" << std::endl;
	std::cout << "Your score was: " << score << std::endl;
}

void Game::AddScore(int s)
{
	if ((score + s) % lifeIncrement > score % lifeIncrement)
		lives++;
	score += s;
}

void Game::GetHit()
{
	playerHealth -= 1;
	if (playerHealth < 1)
		PlayerDeath();
	World::GetInstance()->GetPlayer()->SetDestroy(true);
}