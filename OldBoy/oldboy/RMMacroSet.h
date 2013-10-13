#pragma once

template <class Interface>
inline void SafeDelete(Interface **ppInterfaceToDelete)
{
	if (*ppInterfaceToDelete != nullptr)
	{
		delete (*ppInterfaceToDelete);
		(*ppInterfaceToDelete) = nullptr;
	}
}

template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = nullptr;
	}
}

template <class Interface>
inline void SafeArrayDelete(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		delete[] (*ppInterfaceToRelease);
		(*ppInterfaceToRelease) = nullptr;
	}
}