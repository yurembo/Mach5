/******************************************************************************/
/*!
\file   PlayerInputComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Player input for AstroShot
*/
/******************************************************************************/
#include "PlayerInputComponent.h"
#include "Core\M5IniFile.h"
#include "Core\M5Input.h"
#include "Core\M5Vec2.h"
#include "Core\M5ObjecT.h"
#include "Core\M5Math.h"
#include "Core\M5Gfx.h"
#include <cmath>

namespace
{
const float DAMP_EFFECT = 0.99f;
}

/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
PlayerInputComponent::PlayerInputComponent(void) :
	M5Component(CT_PlayerInputComponent),
	m_forwardSpeed(0),
	m_rotationSpeed(0)
{
}
/******************************************************************************/
/*!
PlayerInputDestructor, does nothing
*/
/******************************************************************************/
PlayerInputComponent::~PlayerInputComponent(void)
{
}
/******************************************************************************/
/*!
Updates the player based on input
*/
/******************************************************************************/
void PlayerInputComponent::Update(float dt)
{
	//Do forward motion
	if (M5Input::IsPressed(M5_W) || M5Input::GetLeftTrigger() > 0)
	{
		M5Vec2 dir(std::cos(m_pObj->rotation), std::sin(m_pObj->rotation));
		M5Vec2::Scale(dir, dir, m_forwardSpeed * dt);
		m_pObj->vel += dir;
		M5Vec2::Scale(m_pObj->vel, m_pObj->vel, DAMP_EFFECT);

	}

	//If gamepad is working just face the direction of left thumbstick
	if (M5Input::GamePadIsConnected())
	{
		M5Vec2 leftThumb;
		M5Input::GetLeftThumb(leftThumb);
		m_pObj->rotation = std::atan2(leftThumb.y, leftThumb.x);
	}
	
	//Back up controls to rotate if there is no game pad.
	if (M5Input::IsPressed(M5_A))
	{
		m_pObj->rotationVel += m_rotationSpeed * dt;
	}
	else if (M5Input::IsPressed(M5_D))
	{
		m_pObj->rotationVel -= m_rotationSpeed * dt;
	}
	else
	{
		m_pObj->rotationVel = 0;
	}

	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);

	m_pObj->pos.x += m_pObj->vel.x * dt;
	m_pObj->pos.x = M5Math::Wrap(m_pObj->pos.x, botLeft.x, topRight.x);

	m_pObj->pos.y += m_pObj->vel.y * dt;
	m_pObj->pos.y = M5Math::Wrap(m_pObj->pos.y, botLeft.y, topRight.y);

	m_pObj->rotation += m_pObj->rotationVel * dt;

}
/******************************************************************************/
/*!
Virtual constructor for PlayerInputComponent
*/
/******************************************************************************/
M5Component* PlayerInputComponent::Clone(void)
{
	PlayerInputComponent* pNew = new PlayerInputComponent;
	pNew->m_forwardSpeed  = m_forwardSpeed;
	pNew->m_rotationSpeed = m_rotationSpeed;
	return pNew;
}
/******************************************************************************/
/*!
Loads PlayerInput data from an iniFile

\param
The preloaded iniFile to read.
*/
/******************************************************************************/
void PlayerInputComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("PlayerInputComponent");
	iniFile.GetValue("forwardSpeed", m_forwardSpeed);
	iniFile.GetValue("rotationSpeed", m_rotationSpeed);
}