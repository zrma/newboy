#include "RMConfig.h"
#include "RMTextureManager.h"
#include "RMMainLoop.h"

CRMTextureManager* CRMTextureManager::m_pInstance = nullptr;

CRMTextureManager::CRMTextureManager(void) :
	m_pWICFactory(nullptr)
{
	CreateFactory();
	m_TextureMap.clear();
}

CRMTextureManager::~CRMTextureManager(void)
{
	SafeRelease(m_pWICFactory);
	
	for(auto iter = m_TextureMap.begin(); iter != m_TextureMap.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	m_TextureMap.clear();
}

CRMTextureManager* CRMTextureManager::GetInstance()
{
	if(m_pInstance)
	{
		return m_pInstance;
	}
	else
	{
		m_pInstance = new CRMTextureManager();
		return m_pInstance;
	}
}

void CRMTextureManager::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

HRESULT CRMTextureManager::CreateFactory()
{
	HRESULT hr = S_OK;

	if(m_pWICFactory == nullptr)
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );
	}

	return hr;
}

HRESULT CRMTextureManager::InitTexture()
{
	HRESULT hr = S_OK;

	CRMTexture* texture;
	
	texture = new CRMTexture();
	texture->Create( L"Image/test1.png" );
	texture->SetPosition(0, 0);
	m_TextureMap[L"Item1"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test2.png" );
	texture->SetPosition(300, 0);
	m_TextureMap[L"Item2"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test3.png" );
	texture->SetPosition(600, 0);
	m_TextureMap[L"Item3"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test4.png" );
	texture->SetPosition(900, 0);
	m_TextureMap[L"Item4"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test5.png" );
	texture->SetPosition(0, 300);
	m_TextureMap[L"Item5"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test6.png" );
	texture->SetPosition(300, 300);
	m_TextureMap[L"Item6"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test7.png" );
	texture->SetPosition(600, 300);
	m_TextureMap[L"Item7"] = texture;

	texture = new CRMTexture();
	texture->Create( L"Image/test8.png" );
	texture->SetPosition(900, 300);
	m_TextureMap[L"Item8"] = texture;

	return hr;
}
