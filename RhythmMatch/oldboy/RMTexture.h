#pragma once
#include "RMConfig.h"

class CRMTexture
{
public:
	CRMTexture(void);
	~CRMTexture(void);

public:
	HRESULT Create( std::wstring path );

	void	SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; }
	void	GetPosition(float *x, float *y) { *x = m_PositionX; *y = m_PositionY; }

private:
	ID2D1Bitmap*		m_D2D1Bitmap;

public:
	float				m_Width;
	float				m_Height;
	float				m_PositionX;
	float				m_PositionY;

public:
	inline ID2D1Bitmap* GetD2D1Bitmap() const { return m_D2D1Bitmap; }
};