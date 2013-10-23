#pragma once
#include "RMTexture.h"

class CRMObject
{
public:
	CRMObject(void);
	~CRMObject(void);

private:
	float	m_PositionX;
	float	m_PositionY;

	CRMTexture*	m_Texture;
};

