#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
	void MoveForward(float units);
	void Strafe(float units);
	void MoveUp(float units);

	void Yaw(float radians);
	void Pitch(float radians);
	void Roll(float radians);
	void Update();

	void SetPosition(XMVECTOR* pPosition);
	void SetLookAt(XMVECTOR* pLookAt);
	void SetFOV(float fov) { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
	void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
	void SetNearPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
	void SetFarPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetInvertY(bool invert) { m_invertY = invert; }
	void SetMaxPitch(float maxPitch) { m_maxPitch = maxPitch; }

	XMMATRIX* GetViewMatrix() { return &m_view; }
	XMMATRIX* GetProjectionMatrix() { return &m_projection; }
	XMVECTOR* GetPosition() { return &m_position; }
	XMVECTOR* GetLookAt() { return &m_lookAt; }
	float GetFOV() { return m_fov; }
	float GetAspectRatio() { return m_aspect; }
	float GetNearPlane() { return m_nearPlane; }
	float GetFarPlane() { return m_farPlane; }
	float GetMaxVelocity() { return m_maxVelocity; }
	bool  GetInvertY() { return m_invertY; }
	float GetPitch() { return m_pitch; }
	float GetYaw() { return m_yaw; }
	float GetMaxPitch() { return m_maxPitch; }

	float GetVectorLength(XMVECTOR &vec);

private:

	XMMATRIX m_view;
	XMMATRIX m_projection;
	XMVECTOR m_right, m_up, m_look;
	XMVECTOR m_position, m_lookAt, m_velocity;
	float m_yaw, m_pitch, m_maxPitch, m_maxVelocity, m_fov;
	float m_aspect, m_nearPlane, m_farPlane;
	bool m_invertY;
	bool m_enableYMovement;
};

#endif