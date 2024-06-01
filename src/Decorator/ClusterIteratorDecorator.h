#pragma once
#include "ClusterIterator.h"

template<class Type> class IteratorDecorator : public Iterator<Type>
{
protected:
	Iterator<Type>* it;
public:
	IteratorDecorator(Iterator<Type>* iterator) { it = iterator; };
	virtual ~IteratorDecorator() { delete it; };
	virtual void first() { it->first(); };
	virtual void next() { it->next(); };
	virtual bool isDone() const { return it->isDone(); };
	virtual Type getCurrent() { return it->getCurrent(); };
};

class ClusterIteratorDecorator : public IteratorDecorator<Cluster>
{
private:
	ClusterEnum targetClusterType;
public:
	ClusterIteratorDecorator(Iterator<Cluster>* it, ClusterEnum clusterType) : IteratorDecorator(it) { targetClusterType = clusterType; }
	void first();
	void next();
};
