#include "Input.h"

Input::Input()
{
	mInputState.reserve(mInputArray.size());
	for (size_t i = 0; i < mInputArray.size(); i++)
	{
		mInputState.push_back(KeyState::KEYNONE);
	}
}

void Input::UpdateArray()
{
	for (size_t i = 0; i < mInputArray.size(); i++)
	{
		char key = mInputArray[i];
		bool keyDown = GetAsyncKeyState(key) * 0x8000;

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