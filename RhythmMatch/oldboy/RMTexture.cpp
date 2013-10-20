#include "RMConfig.h"
#include "RMTexture.h"
#include "RMTextureManager.h"
#include "RMRender.h"


CRMTexture::CRMTexture(void) :
	m_D2D1Bitmap(nullptr)
{

}

CRMTexture::~CRMTexture(void)
{
	SafeRelease(m_D2D1Bitmap);
}

HRESULT CRMTexture::Create( std::wstring path )
{
	IWICImagingFactory*	imageFactory = CRMTextureManager::GetInstance()->GetImageFactory();
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	HRESULT hr = S_OK;

	// ���ڴ� ����
	hr = imageFactory->CreateDecoderFromFilename( path.c_str(), nullptr, GENERIC_READ, 
		WICDecodeMetadataCacheOnDemand, &bitmapDecoder );

	if(FAILED(hr))
		return hr;

	// ���ڴ����� ������ ����
	IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
	hr = bitmapDecoder->GetFrame( 0, &bitmapFrameDecode );
	
	if(FAILED(hr))
	{
		SafeRelease(bitmapDecoder);
		return hr;
	}

	IWICFormatConverter*	formatConverter = nullptr;

	// �������� ������� ������ ����
	hr = imageFactory->CreateFormatConverter( &formatConverter );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
		return hr;
	}

	hr = formatConverter->Initialize( bitmapFrameDecode, 
									GUID_WICPixelFormat32bppPBGRA,
									WICBitmapDitherTypeNone, nullptr, 0.0f,
									WICBitmapPaletteTypeCustom );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	hr = CRMRender::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(formatConverter, nullptr, &m_D2D1Bitmap);
	
	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	SafeRelease( bitmapFrameDecode );
	SafeRelease( bitmapDecoder );

	return hr;
}
