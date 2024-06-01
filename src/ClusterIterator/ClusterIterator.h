#pragma once
#include "Cluster.h"

template<class Type> class Iterator
{
protected:
	Iterator() {};
public:
	virtual ~Iterator() {};
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() const = 0;
	virtual Type getCurrent() = 0;
};

class ClusterIterator : public Iterator<Cluster>
{
private:
	BaseFileSystem* fs;
	Cluster currentCluster;
	unsigned int count;
	unsigned int position;
public:
	ClusterIterator(BaseFileSystem* fsArg);
	void first();
	void next();
	bool isDone() const;
	Cluster getCurrent();
};
