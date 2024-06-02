#pragma once
#include <iostream>
#include "BaseFileSystem.h"

class FAT32 : public BaseFileSystem
{
private:
    unsigned int secondClusterOffset;

	#pragma pack(push, 1)
	typedef struct {
		BYTE skip1[11];
		uint16_t bytesPerSector;
		uint8_t sectorsPerCluster;
		uint16_t initialSector;
		uint8_t countOfFAT;
		BYTE skip2[15];
		uint32_t totalSectors;
		uint32_t sizeOfFAT;
	} BootRecord;
	#pragma pack(pop)
public:
	virtual void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer);

    FAT32(const WCHAR* pFileName);
    ~FAT32();
};
