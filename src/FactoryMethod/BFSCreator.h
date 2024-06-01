#pragma once
#include "BaseFileSystem.h"
#include "FAT32.h"
#include "NTFS.h"

enum class FSType { FAT32, NTFS, None }; // К сожалению, коллеги не доделали FAT16, exFAT, Ext4, HFS

class BFSCreator
{
public:
	virtual FSType detectFileSystem(const WCHAR* pFileName) = 0;
	virtual const char* getFSTypeChar(FSType fsType) = 0;
	virtual BaseFileSystem* createFileSystem(FSType fsType, const WCHAR* pFileName) = 0;
};

class ConcreteBFSCreator : public BFSCreator
{
public:
	virtual FSType detectFileSystem(const WCHAR* pFileName);
    virtual const char* getFSTypeChar(FSType fsType);
	virtual BaseFileSystem* createFileSystem(FSType fsType, const WCHAR* pFileName);
};
