#include "ClusterIterator.h"

ClusterIterator::ClusterIterator(BaseFileSystem* fsArg) {
	fs = fsArg;
	count = fs->getTotalClusters();
	position = 0;
}

void ClusterIterator::first() {
	position = 0;
}

void ClusterIterator::next() {
	if (fs->getPointerTerminated()) {
		position = count;
	}
	position++;
}

bool ClusterIterator::isDone() const {
	return position >= count;
}

Cluster ClusterIterator::getCurrent() {
	// Здесь была ошибка: нельзя тут делать new Cluster, т.к. обязательно нужно делать delete. Логичнее статично выделить память под текущий кластер
	currentCluster = Cluster(position, fs);
	currentCluster.readCluster();
	return currentCluster;
}
