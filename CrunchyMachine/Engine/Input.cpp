#include "Input.h"
#include "Window/Window.h"
#include <iostream>
#include <algorithm>

Input* Input::mInstance = nullptr;

Input::Input()
{
	//Set every input key to state KeyNone
	mInputState.reserve(mInputArray.size());
	for (size_t i = 0; i < mInputArray.size(); i++)
		mInputState.push_back(KeyState::KEYNONE);

	mPoint = POINT();
	mouseTimer = 0;
	mWindow = &Window::GetHWND();
}

Input* Input::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new Input();
	return mInstance;
}

void Input::CenterCursor()
{
	RECT rect;
	GetClientRect(*mWindow, &rect);

	POINT windowCenter = { rect.right / 2, rect.bottom / 2 };

	ClientToScreen(*mWindow, &windowCenter);
	//SetCursorPos(windowCenter.x, windowCenter.y);
}


XMFLOAT2 Input::GetMouseDelta()
{
	//Get cursor position & adapt it to application window
	RECT rect;
	GetClientRect(*mWindow, &rect);

	POINT windowCenter = { rect.right / 2, rect.bottom / 2 };

	GetCursorPos(&mPoint);
	ScreenToClient(*mWindow, &mPoint);

	XMFLOAT2 tempFloat = XMFLOAT2(
	std::clamp((float)(mPoint.x - windowCenter.x), -MAX_SENSIBILITY, MAX_SENSIBILITY) / MAX_SENSIBILITY,
	std::clamp((float)(mPoint.y - windowCenter.y), -MAX_SENSIBILITY, MAX_SENSIBILITY) / MAX_SENSIBILITY
	);

	return tempFloat;
}

std::vector<Input::KeyState> Input::GetInputStates() { return mInputState; }

void Input::UpdateArray(float deltatime)
{
	ShowCursor(false);

	//Go Through InputArray to get key (char value)
	for (size_t i = 0; i < mInputArray.size(); i++)
	{
		//Retrieve key & use it allow the use of a for loop - * 0x8000 is the unicode verification for pressed key
		char key = mInputArray[i];
		bool keyDown = GetAsyncKeyState(key) * 0x8000;

		//Manage & attribute all states for each input key
		if (keyDown)
		{
			if (mInputState[i] == KeyState::KEYUP || mInputState[i] == KeyState::KEYNONE)
				mInputState[i] = KeyState::KEYDOWN;
			else
				mInputState[i] = KeyState::KEYHOLD;
		}
		else
		{
			if (mInputState[i] == KeyState::KEYDOWN || mInputState[i] == KeyState::KEYHOLD)
				mInputState[i] = KeyState::KEYUP;
			else
				mInputState[i] = KeyState::KEYNONE;
		}
	}

	mouseTimer += deltatime;

	if (mouseTimer >= MOUSE_REFRESH_TIMING) {
		mouseTimer = 0;
		CenterCursor();
	}
}