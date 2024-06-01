//---------------------------------------------------------------------------

#ifndef TClusterIteratorDecoratorH
#define TClusterIteratorDecoratorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "BFSCreator.h"
#include "Cluster.h"
#include "ClusterIterator.h"
#include "ClusterIteratorDecorator.h"
#include "TDB_VST.h"
//---------------------------------------------------------------------------
class TClusterIteratorDecorator : public TThread
{
private:
	bool startButtonEnabled;
    bool stopButtonEnabled;
	const char* fsTypeChar;
	unsigned int clusterSize;
    unsigned int clustersFound = 0;

	TDB_VST* threadDB_VST;
protected:
	void __fastcall Execute();

	void __fastcall UpdateStartButtonEnabled();
	void __fastcall UpdateStopButtonEnabled();
	void __fastcall UpdateFSTypeLabel();
	void __fastcall UpdateClusterSizeLabel();
	void __fastcall UpdateClustersFoundLabel();

	ClusterEnum __fastcall getClusterType();
public:
	__fastcall TClusterIteratorDecorator(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
