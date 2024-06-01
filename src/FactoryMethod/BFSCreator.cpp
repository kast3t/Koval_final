#include "BFSCreator.h"

FSType ConcreteBFSCreator::detectFileSystem(const WCHAR* pFileName) {
	// Сигнатуры файловых систем
	BYTE NTFS[4] = { 0x4E, 0x54, 0x46, 0x53 };
	BYTE FAT32[5] = { 0x46, 0x41, 0x54, 0x33, 0x32 };
	
	// Создать здесь экземпляр класса BaseFileSystem нельзя, т.к. в нём есть абстрактный метод readClusterNumber
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
	
	LARGE_INTEGER startOffset;
	startOffset.QuadPart = 0;

	int bytesToRead = 512;
	BYTE* pBootRecordBuffer = new BYTE[bytesToRead];

	fileHandle = CreateFileW(pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		throw "Ошибка инициализации fileHandle";
	}

	unsigned long filePointer = SetFilePointer(fileHandle, startOffset.LowPart, &startOffset.HighPart, FILE_BEGIN);
	if (filePointer == INVALID_SET_FILE_POINTER) {
		throw "Ошибка установки filePointer";
	}

	DWORD bytesRead;
	bool readResult = ReadFile(fileHandle, pBootRecordBuffer, bytesToRead, &bytesRead, NULL);
	if (!readResult || bytesRead != bytesToRead) {
		throw "Ошибка чтения readResult";
	}

	CloseHandle(fileHandle);

	FSType result;
	if (memcmp(pBootRecordBuffer + 3, NTFS, 4) == 0) {
		result = FSType::NTFS;
	}
	else if (memcmp(pBootRecordBuffer + 82, FAT32, 5) == 0) {
		result = FSType::FAT32;
	}
	else {
		result = FSType::None;
	}

	delete[] pBootRecordBuffer;
	return result;
}

const char* ConcreteBFSCreator::getFSTypeChar(FSType fsType) {
	switch (fsType) {
		case FSType::FAT32: return "FAT32";
		case FSType::NTFS: return "NTFS";
		default: return NULL;
	}
}

BaseFileSystem* ConcreteBFSCreator::createFileSystem(FSType fsType, const WCHAR* pFileName) {
	switch (fsType) {
		case FSType::FAT32: return new FAT32(pFileName);
		case FSType::NTFS: return new NTFS(pFileName);
		default: return NULL;
	}
}

