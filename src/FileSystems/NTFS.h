#pragma once
#include <iostream>
#include "BaseFileSystem.h"

class NTFS : public BaseFileSystem
{
private:
	#pragma pack(push, 1)
	typedef struct {
		BYTE skip1[11];
		uint16_t bytesPerSector;
		uint8_t sectorsPerCluster;
		BYTE skip2[26];
		uint64_t totalSectors;
	} BootRecord;
	#pragma pack(pop)
public:
	virtual void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer);

	NTFS(const WCHAR* pFileName);
	~NTFS();
};
