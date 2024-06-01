#include "FAT32.h"

FAT32::FAT32(const WCHAR *pFileName) : BaseFileSystem(pFileName) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

	// Читаем 1-й сектор
	BYTE *pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);
	
	// Записываем его в подготовленную структуру BootRecord
	BootRecord *pBootRecord = reinterpret_cast<BootRecord*>(pBootRecordBuffer);
    
	// Вытаскиваем нужные значения, считаем и записываем размер кластера
	unsigned int bytesPerSector = static_cast<unsigned int>(pBootRecord->bytesPerSector);
	unsigned int sectorsPerCluster = static_cast<unsigned int>(pBootRecord->sectorsPerCluster);
    unsigned int clusterSize = bytesPerSector * sectorsPerCluster;
	setClusterSize(clusterSize);
	
	// Вытаскиваем нужные значения, считаем и записываем смещение 2-го кластера
	unsigned int initialSector = static_cast<unsigned int>(pBootRecord->initialSector);
	unsigned int countOfFAT = static_cast<unsigned int>(pBootRecord->countOfFAT);
	unsigned int sizeOfFAT = static_cast<unsigned int>(pBootRecord->sizeOfFAT);
	secondClusterOffset = (initialSector + countOfFAT * sizeOfFAT) * 512;

	// Вытаскиваем нужные значения, считаем общее количество кластеров
	unsigned int totalSectors = static_cast<unsigned int>(pBootRecord->totalSectors);
	unsigned int totalClusters = totalSectors / sectorsPerCluster;
	setTotalClusters(totalClusters);

	delete[] pBootRecordBuffer;
}

FAT32::~FAT32() {}

void FAT32::readClusterNumber(unsigned int clusterNumber, BYTE *pResultBuffer) {
	unsigned int clusterSize = getClusterSize();
	if (clusterSize == 0) {
		throw "Ошибка чтения кластера: размер кластера не определён";
	}

	// Считаем, как будто бы кластер начинается с нуля, хотя по факту с 2
	if (clusterNumber < 0) {
		throw "Ошибка: номер кластера должен быть не менее 0";
	}

	LARGE_INTEGER startOffset;
	startOffset.QuadPart = secondClusterOffset + clusterNumber * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
