#include "DXInput.h"

DXINPUT::DXINPUT()
{
}

DXINPUT::~DXINPUT()
{
}

bool DXINPUT::InitDirectInput(HWND hwnd, HINSTANCE hInstance, int width, int height)
{
	HRESULT hr;
	hr = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);

	hr = DirectInput->CreateDevice(GUID_SysKeyboard,
		&DIKeyboard,
		NULL);

	hr = DirectInput->CreateDevice(GUID_SysMouse,
		&DIMouse,
		NULL);

	hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	m_screenWidth = width;
	m_screenHeight = height;
	m_mouseX = 0;
	m_mouseY = 0;

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	return true;
}

void DXINPUT::DetectInput()
{
	HRESULT result;

	result = DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			DIMouse->Acquire();
		}
	}

	result = DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			DIKeyboard->Acquire();
		}
	}

	m_mouseX += mouseState.lX;
	m_mouseY += mouseState.lY;

	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	//ShowCursor(true);
}

void DXINPUT::Release()
{
	if (DIKeyboard)
	{
		DIKeyboard->Unacquire();
		DIKeyboard->Release();
		DIKeyboard = 0;
	}
	if (DIMouse)
	{
		DIMouse->Unacquire();
		DIMouse->Release();
		DIMouse = 0;
	}
	if (DirectInput)
	{
		DirectInput->Release();
		DirectInput = 0;
	}
}

bool DXINPUT::IsKey_Esc_Pressed()
{
	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_W_Pressed()
{
	if (keyboardState[DIK_W] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_S_Pressed()
{
	if (keyboardState[DIK_S] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_A_Pressed()
{
	if (keyboardState[DIK_A] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_D_Pressed()
{
	if (keyboardState[DIK_D] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_Q_Pressed()
{
	if (keyboardState[DIK_Q] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_E_Pressed()
{
	if (keyboardState[DIK_E] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_R_Pressed()
{
	if (keyboardState[DIK_R] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_F_Pressed()
{
	if (keyboardState[DIK_F] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_C_Pressed()
{
	if (keyboardState[DIK_C] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_LCTR_Pressed()
{
	if (keyboardState[DIK_LCONTROL] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_SPACE_Pressed()
{
	if (keyboardState[DIK_SPACE] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_LSHIFT_Pressed()
{
	if (keyboardState[DIK_LSHIFT] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_LALT_Pressed()
{
	if (keyboardState[DIK_LALT] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_1_Pressed()
{
	if (keyboardState[DIK_1] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_2_Pressed()
{
	if (keyboardState[DIK_2] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_3_Pressed()
{
	if (keyboardState[DIK_3] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_4_Pressed()
{
	if (keyboardState[DIK_4] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_5_Pressed()
{
	if (keyboardState[DIK_5] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_6_Pressed()
{
	if (keyboardState[DIK_6] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_7_Pressed()
{
	if (keyboardState[DIK_7] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_8_Pressed()
{
	if (keyboardState[DIK_8] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_9_Pressed()
{
	if (keyboardState[DIK_9] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_0_Pressed()
{
	if (keyboardState[DIK_0] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_UP_Pressed()
{
	if (keyboardState[DIK_UP] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_DOWN_Pressed()
{
	if (keyboardState[DIK_DOWN] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_LEFT_Pressed()
{
	if (keyboardState[DIK_LEFT] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_RIGHT_Pressed()
{
	if (keyboardState[DIK_RIGHT] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_1_Pressed()
{
	if (keyboardState[DIK_NUMPAD1] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_2_Pressed()
{
	if (keyboardState[DIK_NUMPAD2] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_3_Pressed()
{
	if (keyboardState[DIK_NUMPAD3] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_4_Pressed()
{
	if (keyboardState[DIK_NUMPAD4] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_5_Pressed()
{
	if (keyboardState[DIK_NUMPAD5] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_6_Pressed()
{
	if (keyboardState[DIK_NUMPAD6] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_7_Pressed()
{
	if (keyboardState[DIK_NUMPAD7] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_8_Pressed()
{
	if (keyboardState[DIK_NUMPAD8] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_9_Pressed()
{
	if (keyboardState[DIK_NUMPAD9] & 0x80)
	{
		return true;
	}
	else
		return false;
}

bool DXINPUT::IsKey_NUMPAD_0_Pressed()
{
	if (keyboardState[DIK_NUMPAD0] & 0x80)
	{
		return true;
	}
	else
		return false;
}

LONG DXINPUT::GetMouseX()
{
	return m_mouseX;
}

LONG DXINPUT::GetMouseY()
{
	return m_mouseY;
}

float DXINPUT::GetMouseDeltaX()
{
	return (float)mouseState.lX;
}

float DXINPUT::GetMouseDeltaY()
{
	return (float)mouseState.lY;
}
