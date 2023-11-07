#include "EngineResources/framework.h"
#include <vector>

#define MOUSE_REFRESH_TIMING 0.07f

// Manages the inputs and get the mouse position on the window.
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

	void CenterCursor();

	XMFLOAT2 GetMousePosition();
	std::vector<KeyState> GetInputStates(); /*Example: static_cast<int>(vector[x]), vector being Input object name& x being array index*/
	void UpdateArray(float deltatime); /*Update method for InputState array*/

private:
	POINT mPoint;

	//Make an array to register key list & another one to register corresponding key states at the start of new frame (mInputState)
	std::vector<char> mInputArray = { 'Z','Q','S','D','R',VK_LBUTTON,VK_RBUTTON, VK_ESCAPE};
	std::vector<KeyState> mInputState;

	static Input* mInstance;

	HWND* mWindow;

	float mouseTimer;
};

