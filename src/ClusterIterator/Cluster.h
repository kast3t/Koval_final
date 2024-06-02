#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include "BaseFileSystem.h"

enum class ClusterEnum { None, Unknown, PNG, EXE, PDF };

class Cluster
{
private:
	unsigned int number;
	BaseFileSystem* fs;
	BYTE* data = NULL;
	ClusterEnum clusterType;
	char* hexData = NULL;
public:
	Cluster();
	~Cluster();
	Cluster(unsigned int clusterNumber, BaseFileSystem* fsPtr);
	unsigned int getNumber();
	void readCluster();
	BYTE* getData();
	char* getHexData();
	ClusterEnum getClusterType();
	char* getClusterTypeChar();
};
