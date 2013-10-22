#pragma once
#include "RMTexture.h"
#include <map>

class CRMTextureManager
{
private:
	CRMTextureManager(void);
	~CRMTextureManager(void);
	// �̱����̹Ƿ� �����ڸ� private�� ���Ƶ�

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
	// ���� �߰��ؾ� �� �͵�
	// ���̾� ���� �߰��ϰ�, �ؽ��� ���ҽ����� ���Ϳ� �߰�

public:
	inline IWICImagingFactory*		GetImageFactory() const { return m_pWICFactory; }
};

