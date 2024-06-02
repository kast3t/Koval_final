//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TDB_VST.h"
#include "Main.h"
#pragma package(smart_init)

__fastcall TDB_VST::TDB_VST(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	dataSentEvent = new TEvent(NULL, true, false, "", false);
	dataWrittenEvent = new TEvent(NULL, true, false, "", false);

	currentId = 0;
}
//---------------------------------------------------------------------------
void __fastcall TDB_VST::Execute()
{
	while(!Terminated) {
		// Ждём до тех пор, пока событие dataSentEvent не будет проставлено
		if(dataSentEvent->WaitFor(1000) == wrSignaled) {
			/* Т.к. проставлено событие dataSentEvent, значит поток TClItDec
			   записал кластер в свойство cluster */
			dataSentEvent->ResetEvent();
			currentId++;

			Synchronize(UpdateVST);
			db.insertData(currentClusterNumber,
						  currentСlusterTypeChar,
						  currentСlusterHexData);

			dataWrittenEvent->SetEvent();
		}
    }
	delete dataSentEvent;
	delete dataWrittenEvent;
}

void __fastcall TDB_VST::UpdateVST()
{
	Form1->ClustersVST->BeginUpdate();

	// Добавим дочерний узел-запись
	PVirtualNode pEntryNode = Form1->ClustersVST->AddChild(Form1->ClustersVST->RootNode);

	// Накладываем NodeStruct на выделенную для узла память
	NodeStruct* nodeData = (NodeStruct*)Form1->ClustersVST->GetNodeData(pEntryNode);
	nodeData->id = currentId;
	nodeData->clusterNumber = currentClusterNumber;
	nodeData->clusterType = currentСlusterTypeChar;
	nodeData->hexData = currentСlusterHexData;

    Form1->ClustersVST->EndUpdate();
}

void __fastcall TDB_VST::sendClusterToTDB(unsigned int currentClusterNumberArg,
										  char* currentСlusterTypeCharArg,
										  char* currentСlusterHexDataArg) {
	currentClusterNumber = currentClusterNumberArg;
	currentСlusterTypeChar = currentСlusterTypeCharArg;
	currentСlusterHexData = currentСlusterHexDataArg;
}
