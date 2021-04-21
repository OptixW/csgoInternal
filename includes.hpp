#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <string>
#include "CVMTHooking.hpp"
#include "interface.hpp"

#define IsInRange(x, a, b)		(x >= a && x <= b)
#define GetBits(x)				(IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x)				(GetBits(x[0]) << 4 | GetBits(x[1]))

PBYTE PatternScan(const std::string& ImageName, const std::string& Pattern)
{
	if (ImageName.empty() || Pattern.empty())
	{
		return 0;
	}

	HMODULE hModule = GetModuleHandleA(ImageName.c_str());

	if (!hModule)
	{
		return 0;
	}

	MODULEINFO ImageInfo;

	if (!K32GetModuleInformation(GetCurrentProcess(), hModule, &ImageInfo, sizeof(MODULEINFO)))
	{
		return 0;
	}

	const PBYTE pScanStart = (const PBYTE)(hModule);

	const PBYTE pScanEnd = (const PBYTE)(pScanStart + ImageInfo.SizeOfImage);

	PBYTE pFirstMatch = 0;

	PBYTE pByteArray = (PBYTE)(Pattern.c_str());

	for (PBYTE pCurrent = pScanStart; pCurrent < pScanEnd; ++pCurrent)
	{
		if (*(PBYTE)pByteArray == (BYTE)'\?' || *pCurrent == GetByte(pByteArray))
		{
			if (!pFirstMatch)
				pFirstMatch = pCurrent;

			if (!pByteArray[2])
				return pFirstMatch;

			pByteArray += (*(PWORD)pByteArray == (WORD)'\?\?' || *(PBYTE)pByteArray != (BYTE)'\?') ? 3 : 2;

			if (!*pByteArray)
				return pFirstMatch;
		}
		else if (pFirstMatch)
		{
			pCurrent = pFirstMatch;

			pByteArray = (PBYTE)(Pattern.c_str());

			pFirstMatch = 0;
		}
	}

	return 0;
}