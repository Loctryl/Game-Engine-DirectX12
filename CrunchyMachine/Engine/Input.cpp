#include "Input.h"

Input* Input::mInstance = nullptr;

Input::Input()
{
	//Set every input key to state KeyNone
	mInputState.reserve(mInputArray.size());
	for (size_t i = 0; i < mInputArray.size(); i++)
	{
		mInputState.push_back(KeyState::KEYNONE);
	}
}

Input* Input::GetInstance()
{
	if (mInstance != nullptr) return mInstance;
	mInstance = new Input();
	return mInstance;
}


XMFLOAT2 Input::GetMousePosition(HWND windowHwnd)
{
	//Get cursor position & adapt it to application window
	GetCursorPos(&mPoint);
	ScreenToClient(windowHwnd, &mPoint);
	XMFLOAT2 tempFloat = XMFLOAT2(mPoint.x, mPoint.y);
	return tempFloat;
}

std::vector<Input::KeyState> Input::GetInputStates()
{
	return mInputState;
}

void Input::UpdateArray()
{
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
			{
				mInputState[i] = KeyState::KEYDOWN;
			}
			else
			{
				mInputState[i] = KeyState::KEYHOLD;
			}
		}
		else
		{
			if (mInputState[i] == KeyState::KEYDOWN || mInputState[i] == KeyState::KEYHOLD)
			{
				mInputState[i] = KeyState::KEYUP;
			}
			else
			{
				mInputState[i] = KeyState::KEYNONE;
			}
		}
	}
}