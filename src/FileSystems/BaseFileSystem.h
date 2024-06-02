#pragma once
#include <windows.h>

class BaseFileSystem
{
private:
    unsigned int clusterSize;
    unsigned int totalClusters;
	HANDLE fileHandle;

	volatile bool* pTerminated;

protected:
	void readBytesFromOffset(LARGE_INTEGER startOffset, BYTE* pResultBuffer, DWORD bytesToRead);
    void setClusterSize(unsigned int clSize);
    void setTotalClusters(unsigned int totalCl);

public:
    virtual unsigned int getClusterSize() const;
    virtual unsigned int getTotalClusters() const;
	virtual void readClusterNumber(unsigned int clusterNumber, BYTE* pResultBuffer) = 0;

	void setPointerTerminated(volatile bool* pTerminatedArg);
	volatile bool getPointerTerminated();

    BaseFileSystem(const WCHAR* pFileName);
    ~BaseFileSystem();
};
