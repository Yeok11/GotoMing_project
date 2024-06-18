#pragma once

class GM
{
private:
	GM() {};
	static GM* instance;

	void Update();
	void Render(Board& _gameBoard);
	

public:
	Board battleBoard = Board(5);
	bool Init();
	void Run();
	
public:
	static GM* GetInstance()
	{
		if (instance == nullptr)
			instance = new GM;

		return instance;
	}

	static void DestroyInst()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	
};

