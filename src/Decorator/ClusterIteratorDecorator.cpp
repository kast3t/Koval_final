#include "ClusterIteratorDecorator.h"

void ClusterIteratorDecorator::first() {
	if (it->getCurrent().getClusterType() != targetClusterType) {
		next();
	}
}

void ClusterIteratorDecorator::next() {
	do {
		it->next();
	} while (!it->isDone() && it->getCurrent().getClusterType() != targetClusterType);
}
