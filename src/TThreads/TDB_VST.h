//---------------------------------------------------------------------------

#ifndef TDB_VSTH
#define TDB_VSTH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>  // Для TEvent
#include "DB.h"
#include "Cluster.h"
//---------------------------------------------------------------------------
class TDB_VST : public TThread
{
private:
    unsigned int currentId;
	unsigned int currentClusterNumber;
	char* currentСlusterTypeChar;
	char* currentСlusterHexData;
    DB db;
protected:
	void __fastcall Execute();

    void __fastcall UpdateVST();
public:
	__fastcall TDB_VST(bool CreateSuspended);

	void __fastcall sendClusterToTDB(unsigned int currentClusterNumberArg,
									 char* currentСlusterTypeCharArg,
									 char* currentСlusterHexDataArg);

	TEvent* dataSentEvent;  // Когда кластер из TClItDec отправлен в TDB_VST
	TEvent* dataWrittenEvent;  // Когда кластер записан в БД и VST
};
//---------------------------------------------------------------------------
#endif
