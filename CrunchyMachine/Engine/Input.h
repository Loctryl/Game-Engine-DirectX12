#pragma once
#include "EngineResources/framework.h"
#include <vector>

#define MOUSE_REFRESH_TIMING 0.07f
#define MAX_SENSIBILITY 150.0f

enum KeyState
{
	KEYNONE,
	KEYUP, 
	KEYDOWN, 
	KEYHOLD 
};

// Manages the inputs and get the mouse position on the window.
class Input
{
private:
	static Input* mInstance;
	HWND mWindow;
	
	POINT mPoint;

	//Make an array to register key list & another one to register corresponding key states at the start of new frame (mInputState)
	vector<char> mInputArray = { 'Z','Q','S','D','R',VK_LBUTTON,VK_RBUTTON, VK_ESCAPE, 'A', 'E', VK_SHIFT, VK_SPACE};
	vector<KeyState> mInputState;

	float mMouseTimer;
	
public:
	Input();
	~Input() = default;

	vector<KeyState> GetInputStates(); /*Example: static_cast<int>(vector[x]), vector being Input object name& x being array index*/
	
	static Input* GetInstance();

	XMFLOAT2 GetMouseDelta();
	
	void CenterCursor() const;
	
	void UpdateArray(float deltaTime); /*Update method for InputState array*/
};

