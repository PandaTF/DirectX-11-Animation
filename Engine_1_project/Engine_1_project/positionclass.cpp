////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"

#define ROTATE_VELOCITY_ADD 4.0f;
#define ROTATE_VELOCITY_SUB 0.4f
#define ROTATE_VELOCITY_MAX 60.0f

#define TRANSFORM_VELOCITY_ADD 0.1f
#define TRANSFORM_VELOCITY_MAX 5.0f
#define TRANSFORM_VELOCITY_SUB 0.02f

PositionClass::PositionClass()
{
	m_frameTime = 0.0f;

	m_forwardSpeed = 0.0f;
	m_backSpeed = 0.0f;
	m_upSpeed = 0.0f;
	m_downSpeed = 0.0f;
	m_leftSpeed = 0.0f;
	m_rightSpeed = 0.0f;

	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;
}

PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * ROTATE_VELOCITY_ADD;

		if (m_leftTurnSpeed > (m_frameTime * ROTATE_VELOCITY_MAX))
		{
			m_leftTurnSpeed = m_frameTime * ROTATE_VELOCITY_MAX;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * ROTATE_VELOCITY_SUB;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * ROTATE_VELOCITY_ADD;

		if (m_rightTurnSpeed > (m_frameTime * ROTATE_VELOCITY_MAX))
		{
			m_rightTurnSpeed = m_frameTime * ROTATE_VELOCITY_MAX;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * ROTATE_VELOCITY_SUB;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoForward(bool keydown)
{
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_forwardSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_forwardSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoBack(bool keydown)
{
	if (keydown)
	{
		m_backSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_backSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_backSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_backSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_backSpeed < 0.0f)
		{
			m_backSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoLeft(bool keydown)
{
	if (keydown)
	{
		m_leftSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_leftSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_leftSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_leftSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_leftSpeed < 0.0f)
		{
			m_leftSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoRight(bool keydown)
{
	if (keydown)
	{
		m_rightSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_rightSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_rightSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_rightSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_rightSpeed < 0.0f)
		{
			m_rightSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoUp(bool keydown)
{
	if (keydown)
	{
		m_upSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_upSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_upSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_upSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_upSpeed < 0.0f)
		{
			m_upSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::GoDown(bool keydown)
{
	if (keydown)
	{
		m_downSpeed += m_frameTime * TRANSFORM_VELOCITY_ADD;

		if (m_downSpeed > (m_frameTime * TRANSFORM_VELOCITY_MAX))
		{
			m_downSpeed = m_frameTime * TRANSFORM_VELOCITY_MAX;
		}
	}
	else
	{
		m_downSpeed -= m_frameTime * TRANSFORM_VELOCITY_SUB;

		if (m_downSpeed < 0.0f)
		{
			m_downSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookUpSpeed += m_frameTime * ROTATE_VELOCITY_ADD;

		if (m_lookUpSpeed > (m_frameTime * ROTATE_VELOCITY_MAX))
		{
			m_lookUpSpeed = m_frameTime * ROTATE_VELOCITY_MAX;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime * ROTATE_VELOCITY_SUB;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	return;
}


void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * ROTATE_VELOCITY_ADD;

		if (m_lookDownSpeed > (m_frameTime * ROTATE_VELOCITY_MAX))
		{
			m_lookDownSpeed = m_frameTime * ROTATE_VELOCITY_MAX;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime * ROTATE_VELOCITY_SUB;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	return;
}