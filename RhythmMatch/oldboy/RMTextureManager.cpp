#include "RMConfig.h"
#include "RMTextureManager.h"

CRMTextureManager* CRMTextureManager::m_pInstance = nullptr;

CRMTextureManager::CRMTextureManager(void) :
	m_pWICFactory(nullptr)
{
	CreateFactory();
}

CRMTextureManager::~CRMTextureManager(void)
{
	SafeRelease(m_pWICFactory);
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