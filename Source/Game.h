#pragma once
class Game
{
public:
	Game();
	~Game();

	static Game* GetInstance() { return instance; }

	void PlayerDeath();
	void Lose();

	void AddScore(int s);


	int GetScore() { return score; }
	int GetLives() { return lives; }
	int GetHealth() { return playerHealth; }
	void SetScore(int s) { score = s; }
	void SetLives(int l) { lives = l; }

private:
	static Game* instance;

	int score;
	int lives;
	int playerHealth;

	int lifeIncrement = 10000; // Constant to determine how many points are required to get another life.
	int level; // Should be used to make the game more difficult.
};

