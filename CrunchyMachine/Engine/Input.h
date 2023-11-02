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

	static Input* GetInstance();

	XMFLOAT2 GetMousePosition(HWND windowHwnd);
	std::vector<KeyState> GetInputStates(); /*Example: static_cast<int>(vector[x]), vector being Input object name& x being array index*/
	void UpdateArray(); /*Update method for InputState array*/

private:
	POINT mPoint;

	//Make an array to register key list & another one to register corresponding key states at the start of new frame (mInputState)
	std::vector<char> mInputArray = { 'Z','Q','S','D','R',VK_LBUTTON,VK_RBUTTON};
	std::vector<KeyState> mInputState;

	static Input* mInstance;
};

