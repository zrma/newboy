#pragma once
#include "RMTexture.h"
#include <map>

class CRMTextureManager
{
private:
	CRMTextureManager(void);
	~CRMTextureManager(void);
	// 싱글톤이므로 생성자를 private로 막아둠

public:
	static CRMTextureManager*	GetInstance();
	static void					ReleaseInstance();

public:
	HRESULT						CreateFactory();

private:
	static CRMTextureManager*	m_pInstance;

private:
	IWICImagingFactory*			m_pWICFactory;

private:
	std::map<std::wstring, CRMTexture*>
								m_TextureMap;

public:
	HRESULT						InitTexture();
	std::map<std::wstring, CRMTexture*>	
								GetTextureMap() { return m_TextureMap; }
	CRMTexture*					GetTexture( std::wstring key ) { return m_TextureMap[key]; }

private:
	// 여기 추가해야 할 것들
	// 레이어 벡터 추가하고, 텍스쳐 리소스들을 벡터에 추가

public:
	inline IWICImagingFactory*		GetImageFactory() const { return m_pWICFactory; }
};

