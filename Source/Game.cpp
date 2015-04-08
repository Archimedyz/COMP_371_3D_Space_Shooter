/*
Contributors:

Nicholas Dudek





*/

#include "Game.h"
#include "World.h"
#include "Model.h"
#include <iostream>

Game* Game::instance;

Game::Game()
{
	instance = this;
	score = 0;
	lives = 0;
	playerHealth = 5;
	lost = false;
}

Game::~Game()
{
}

void Game::PlayerDeath()
{
	if (lives <= 0)
		Lose();
}

void Game::Lose()
{
	lost = true;
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
}