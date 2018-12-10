#pragma once
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class DXINPUT
{
public:
	DXINPUT();
	~DXINPUT();

	bool InitDirectInput(HWND hwnd, HINSTANCE hInstance, int width, int height);
	void DetectInput();
	void Release();

	bool IsKey_Esc_Pressed();
	bool IsKey_W_Pressed();
	bool IsKey_S_Pressed();
	bool IsKey_A_Pressed();
	bool IsKey_D_Pressed();
	bool IsKey_Q_Pressed();
	bool IsKey_E_Pressed();
	bool IsKey_R_Pressed();
	bool IsKey_F_Pressed();
	bool IsKey_C_Pressed();

	bool IsKey_LCTR_Pressed();
	bool IsKey_SPACE_Pressed();
	bool IsKey_LSHIFT_Pressed();
	bool IsKey_LALT_Pressed();

	bool IsKey_1_Pressed();
	bool IsKey_2_Pressed();
	bool IsKey_3_Pressed();
	bool IsKey_4_Pressed();
	bool IsKey_5_Pressed();
	bool IsKey_6_Pressed();
	bool IsKey_7_Pressed();
	bool IsKey_8_Pressed();
	bool IsKey_9_Pressed();
	bool IsKey_0_Pressed();

	bool IsKey_UP_Pressed();
	bool IsKey_DOWN_Pressed();
	bool IsKey_LEFT_Pressed();
	bool IsKey_RIGHT_Pressed();

	bool IsKey_NUMPAD_1_Pressed();
	bool IsKey_NUMPAD_2_Pressed();
	bool IsKey_NUMPAD_3_Pressed();
	bool IsKey_NUMPAD_4_Pressed();
	bool IsKey_NUMPAD_5_Pressed();
	bool IsKey_NUMPAD_6_Pressed();
	bool IsKey_NUMPAD_7_Pressed();
	bool IsKey_NUMPAD_8_Pressed();
	bool IsKey_NUMPAD_9_Pressed();
	bool IsKey_NUMPAD_0_Pressed();

	LONG GetMouseX();
	LONG GetMouseY();
	float GetMouseDeltaX();
	float GetMouseDeltaY();

private:
	IDirectInputDevice8 * DIKeyboard;
	IDirectInputDevice8 * DIMouse;
	DIMOUSESTATE mouseState;
	LPDIRECTINPUT8 DirectInput;
	BYTE keyboardState[256];

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};