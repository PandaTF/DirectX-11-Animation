#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_

//////////////
// INCLUDES //
//////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);

	void GoForward(bool);
	void GoBack(bool);
	void GoLeft(bool);
	void GoRight(bool);
	void GoUp(bool);
	void GoDown(bool);

	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);

	float GetForwardSpeed() { return m_forwardSpeed; }
	float GetBackwardSpeed() { return m_backSpeed; }
	float GetLeftSpeed() { return m_leftSpeed; }
	float GetRightSpeed() { return m_rightSpeed; }
	float GetUpSpeed() { return m_upSpeed; }
	float GetDownSpeed() { return m_downSpeed; }

	float GetLeftTurnSpeed() { return m_leftTurnSpeed; }
	float GetRightTurnSpeed() { return m_rightTurnSpeed; }
	float GetLookupSpeed() { return m_lookUpSpeed; }
	float GetLookdownSpeed() { return m_lookDownSpeed; }

private:
	float m_frameTime;

	float m_forwardSpeed, m_backSpeed, m_upSpeed, m_downSpeed, m_leftSpeed, m_rightSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed, m_lookUpSpeed, m_lookDownSpeed;
};

#endif

