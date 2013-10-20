#pragma once

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
	// ���� �߰��ؾ� �� �͵�
	// ���̾� ���� �߰��ϰ�, �ؽ��� ���ҽ����� ���Ϳ� �߰�

public:
	inline IWICImagingFactory*		GetImageFactory() const { return m_pWICFactory; }
};

