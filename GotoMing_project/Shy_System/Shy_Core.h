#pragma once

class GM
{
private:
	GM();
	static GM* instance;

public:
	void Run();
	void Update();
	void Render();

	static GM* GetInstance()
	{
		if (instance == nullptr)
			instance = new GM;

		return instance;
	}
};

