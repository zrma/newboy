#pragma once
#include "RMConfig.h"

class CRMTexture
{
public:
	CRMTexture(void);
	~CRMTexture(void);

public:
	HRESULT Create( std::wstring path );

private:
	ID2D1Bitmap*		m_D2D1Bitmap;

public:
	inline ID2D1Bitmap* GetD2D1Bitmap() const { return m_D2D1Bitmap; }
};