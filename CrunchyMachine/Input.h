#include "Resources/framework.h"
#include <vector>

class Input
{

	enum class KeyState
	{
		KEYUP, 
		KEYDOWN, 
		KEYHOLD, 
		KEYNONE
	};

private:
	//Make an array to register key states at the start of new frame (int[])
	std::vector<char> mInputArray = { 'Z','Q','S','D',VK_LBUTTON,VK_RBUTTON };
	std::vector<KeyState> mInputState;

public:
	Input();

	//Update method for array
	void UpdateArray();
};

