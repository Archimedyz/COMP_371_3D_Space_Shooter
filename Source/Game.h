//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------



#pragma once

#include <glm/glm.hpp>

class Game
{
public:
	Game();
	~Game();

	static Game* GetInstance() { return instance; }


	// TALK SHIT
	void GetHit();



	void PlayerDeath();
	void Lose();

	void AddScore(int s);

	int GetScore() { return score; }
	int GetLives() { return lives; }
	int GetHealth() { return playerHealth; }
	void SetScore(int s) { score = s; }
	void SetLives(int l) { lives = l; }
	bool GameOver() { return lost; }

private:
	static Game* instance;

	bool lost;

	int score;
	int lives;
	int playerHealth;

	int lifeIncrement = 200; // Constant to determine how many points are required to get another life.
	int level; // Should be used to make the game more difficult.
};

