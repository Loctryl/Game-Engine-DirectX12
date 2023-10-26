#include "Resources/framework.h"
#include <vector>

class Input
{
public:
	enum class KeyState
	{
		KEYNONE,
		KEYUP, 
		KEYDOWN, 
		KEYHOLD 
	};

	Input();

	//Example : static_cast<int>(vector[x]), vector being Input object name & x being array index
	std::vector<KeyState> GetInputStates();
	//Update method for InputState array
	void UpdateArray();

private:
	//Make an array to register key list & another one to register corresponding key states at the start of new frame (mInputState)
	std::vector<char> mInputArray = { 'Z','Q','S','D',VK_LBUTTON,VK_RBUTTON };
	std::vector<KeyState> mInputState;

};

