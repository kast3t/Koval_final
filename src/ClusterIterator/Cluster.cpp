#include "Cluster.h"

Cluster::Cluster() {
	number = 0;
	fs = NULL;
    clusterType = ClusterEnum::None;
}
Cluster::Cluster(unsigned int clusterNumber, BaseFileSystem *fsPtr) {
	number = clusterNumber;
	fs = fsPtr;
    clusterType = ClusterEnum::None;
}
Cluster::~Cluster() {
	if (data != NULL) {
		delete[] data;
		data = NULL;
	}
	if (hexData != NULL) {
		delete[] hexData;
		hexData = NULL;
	}
}
unsigned int Cluster::getNumber() {
	return number;
}
void Cluster::readCluster() {
	data = new BYTE[fs->getClusterSize()];
	fs->readClusterNumber(number, data);
}
BYTE* Cluster::getData() {
	return data;
}
char* Cluster::getHexData() {
	std::ostringstream ss;  // ostringstream - удобный интерфейс потоков ввода-вывода, поддерживает многие типы данных
	ss << std::hex << std::uppercase;  // hex переводит все числа в 16 СС
	for (unsigned int i = 0; i < fs->getClusterSize(); i++) {
		ss << std::setw(2) << std::setfill('0') << (0xff & (int)data[i]);
	}
	hexData = new char[fs->getClusterSize() * 2 + 1];
	hexData[fs->getClusterSize() * 2] = (char)"\0";
	// Копирование памяти, ostringstream -> string -> const char*
	memcpy(hexData, ss.str().c_str(), fs->getClusterSize() * 2 + 1);
	return hexData;
}
ClusterEnum Cluster::getClusterType() {
	// Сигнатуры файлов
	BYTE PNG[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	BYTE EXE[2] = { 0x4D, 0x5A };
	BYTE PDF[5] = { 0x25, 0x50, 0x44, 0x46, 0x2D };

	if (data == NULL) {
		throw "Ошибка определения типа кластера: данные кластера не были прочитаны методом readCluster";
	}
	if (memcmp(data, PNG, 8) == 0) {
		clusterType = ClusterEnum::PNG;
	}
	else if (memcmp(data, EXE, 2) == 0) {
		clusterType = ClusterEnum::EXE;
	}
	else if (memcmp(data, PDF, 5) == 0) {
		clusterType = ClusterEnum::PDF;
	}
	else {
		clusterType = ClusterEnum::Unknown;
    }
	return clusterType;
}
char* Cluster::getClusterTypeChar() {
	if (clusterType == ClusterEnum::None) {
		getClusterType();
	}

	switch (clusterType) {
		case ClusterEnum::PNG: return "PNG";
		case ClusterEnum::EXE: return "EXE";
		case ClusterEnum::PDF: return "PDF";
		default: return "Unknown";
	}
}