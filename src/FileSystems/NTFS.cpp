#include "NTFS.h"

NTFS::NTFS(const WCHAR* pFileName) : BaseFileSystem(pFileName) {
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

	// Читаем 1-й сектор
	BYTE* pBootRecordBuffer = new BYTE[512];
	readBytesFromOffset(startOffset, pBootRecordBuffer, 512);

	// Записываем его в подготовленную структуру BootRecord
    // reinterpret_cast преобразует указатель в указатель типа BootRecord
	BootRecord* pBootRecord = reinterpret_cast<BootRecord*>(pBootRecordBuffer);

	// Вытаскиваем нужные значения, считаем и записываем размер кластера
    // static_cast преобразует выражение в тип unsigned int
	unsigned int bytesPerSector = static_cast<unsigned int>(pBootRecord->bytesPerSector);
	unsigned int sectorsPerCluster = static_cast<unsigned int>(pBootRecord->sectorsPerCluster);
	unsigned int clusterSize = bytesPerSector * sectorsPerCluster;
	setClusterSize(clusterSize);

	// Вытаскиваем нужные значения, считаем общее количество кластеров
	unsigned int totalSectors = static_cast<unsigned int>(pBootRecord->totalSectors);
	unsigned int totalClusters = totalSectors / sectorsPerCluster;
	setTotalClusters(totalClusters);

	delete[] pBootRecordBuffer;
}

NTFS::~NTFS() {}

void NTFS::readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) {
	DWORD clusterSize = getClusterSize();
	if (clusterSize == 0) {
		throw "Ошибка чтения кластера: размер кластера не определён";
	}

	if (clusterNumber < 0) {
		throw "Ошибка: номер кластера должен быть не менее 0";
	}

	LARGE_INTEGER startOffset;
	startOffset.QuadPart = clusterNumber * clusterSize;

	readBytesFromOffset(startOffset, pResultBuffer, clusterSize);
}
