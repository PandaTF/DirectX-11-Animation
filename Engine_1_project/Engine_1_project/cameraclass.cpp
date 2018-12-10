#include "cameraclass.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CameraClass::CameraClass()
{
	m_maxPitch = (float)XMConvertToRadians(89.0f);
	m_maxVelocity = 1.0f;
	m_invertY = false;
	m_enableYMovement = true;
	m_position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_velocity = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_look = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	CreateProjectionMatrix((float)(XM_PI / 4.0f), 1280.0f/720.0f, 1.0f, 1000.0f);
	Update();
}

CameraClass::CameraClass(const CameraClass &)
{
}

CameraClass::~CameraClass()
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Creates the projection matrix.
Parameters:
[in] fov - Field of view
[in] aspect - Aspect ratio
[in] near - Near plane
[in] far - Far plane
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane)
{
	m_fov = fov;
	m_aspect = aspect;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	m_projection = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearPlane, m_farPlane);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Moves the camera forward and backward
Parameters:
[in] units - Amount to move
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::MoveForward(float units)
{
	if (m_enableYMovement)
	{
		m_velocity += m_look * units;
	}
	else
	{
		XMVECTOR moveVector = XMVectorSet(XMVectorGetX(m_look), 0.0f, XMVectorGetZ(m_look), 0.0f);
		moveVector = XMVector3Normalize(moveVector);
		moveVector *= units;
		m_velocity += moveVector;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Moves the camera left and right
Parameters:
[in] units - Amount to move
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::Strafe(float units)
{
	m_velocity += m_right * units;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Moves the camera up and down
Parameters:
[in] units - Amount to move
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::MoveUp(float units)
{
	if (m_enableYMovement)
	{
		m_velocity = XMVectorSet(XMVectorGetX(m_velocity), XMVectorGetY(m_velocity) + units, XMVectorGetZ(m_velocity), 0.0f);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Yaw the camera around its Y-axis.
Parameters:
[in] radians - Radians to yaw.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::Yaw(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	XMMATRIX rotation;
	rotation = XMMatrixRotationAxis(m_up, radians);
	m_right = XMVector3TransformNormal(m_right, rotation);
	m_look = XMVector3TransformNormal(m_look, rotation);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Pitch the camera around its X-axis.
Parameters:
[in] radians - Radians to pitch.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::Pitch(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	radians = (m_invertY) ? -radians : radians;
	m_pitch -= radians;
	if (m_pitch > m_maxPitch)
	{
		radians += m_pitch - m_maxPitch;
	}
	else if (m_pitch < -m_maxPitch)
	{
		radians += m_pitch + m_maxPitch;
	}

	XMMATRIX rotation;
	rotation = XMMatrixRotationAxis(m_right, radians);
	m_up = XMVector3TransformNormal(m_up, rotation);
	m_look = XMVector3TransformNormal(m_look, rotation);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Roll the camera around its Z-axis.
Parameters:
[in] radians - Radians to roll.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::Roll(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	XMMATRIX rotation;
	rotation = XMMatrixRotationAxis(m_look, radians);
	m_right = XMVector3TransformNormal(m_right, rotation);
	m_up = XMVector3TransformNormal(m_up, rotation);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Updates the camera and creates a new view matrix.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::Update()
{
	// Cap velocity to max velocity
	if (GetVectorLength(m_velocity) > m_maxVelocity)
	{
		m_velocity = XMVector3Normalize(m_velocity) * m_maxVelocity;
	}

	// Move the camera
	m_position += m_velocity;
	// Could decelerate here. I'll just stop completely.
	m_velocity = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_lookAt = m_position + m_look;

	// Calculate the new view matrix
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_view = XMMatrixLookAtLH(m_position, m_lookAt, up);

	// Set the camera axes from the view matrix
	XMFLOAT4X4 tempView;
	XMStoreFloat4x4(&tempView, m_view);
	m_right = XMVectorSet(tempView._11, tempView._21, tempView._31, 0.0f);
	m_up = XMVectorSet(tempView._12, tempView._22, tempView._32, 0.0f);
	m_look = XMVectorSet(tempView._13, tempView._23, tempView._33, 0.0f);

	// Calculate yaw and pitch
	float x, y, z;
	x = XMVectorGetX(m_look);
	y = XMVectorGetY(m_look);
	z = XMVectorGetZ(m_look);

	float lookLengthOnXZ = sqrtf(z * z + x * x);
	m_pitch = atan2f(y, lookLengthOnXZ);
	m_yaw = atan2f(x, z);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Updates the camera and creates a new view matrix.
Parameters:
[in] pPosition - New position
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::SetPosition(XMVECTOR* pPosition)
{
	m_position = XMVectorSet(XMVectorGetX(*pPosition), XMVectorGetY(*pPosition), XMVectorGetZ(*pPosition), 0.0f);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Updates the camera and creates a new view matrix.
Parameters:
[in] pPosition - New target
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CameraClass::SetLookAt(XMVECTOR* pLookAt)
{
	m_lookAt = XMVectorSet(XMVectorGetX(*pLookAt), XMVectorGetY(*pLookAt), XMVectorGetZ(*pLookAt), 0.0f);
	m_look = XMVector3Normalize(m_lookAt - m_position);
}

float CameraClass::GetVectorLength(XMVECTOR &vec)
{
	float x, y, z;
	x = XMVectorGetX(vec);
	y = XMVectorGetY(vec);
	z = XMVectorGetZ(vec);

	return (float)sqrt(x * x + y * y + z * z);
}