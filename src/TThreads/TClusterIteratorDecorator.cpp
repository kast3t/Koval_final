//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TClusterIteratorDecorator.h"
#include "Main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TClusterIteratorDecorator::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TClusterIteratorDecorator::TClusterIteratorDecorator(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	threadDB_VST = new TDB_VST(false);
}
//---------------------------------------------------------------------------
void __fastcall TClusterIteratorDecorator::Execute()
{
	/* Думаю, что while(!Terminated) здесь излишне, проверка на Terminated
	   происходит в ClusterIterator::next() */
	startButtonEnabled = false;
	stopButtonEnabled = true;
	Synchronize(UpdateStartButtonEnabled);
	Synchronize(UpdateStopButtonEnabled);

	UnicodeString fileNameString = Form1->EditDiskLetter->Text;
	const WCHAR* pFileName = fileNameString.c_str();

	ClusterEnum chosenClusterType = getClusterType();

	BFSCreator* fsCreator = new ConcreteBFSCreator;
	FSType fsType = fsCreator->detectFileSystem(pFileName);
	BaseFileSystem* fs = fsCreator->createFileSystem(fsType, pFileName);
	fs->setPointerTerminated(&Terminated);

	fsTypeChar = fsCreator->getFSTypeChar(fsType);
	Synchronize(UpdateFSTypeLabel);

	clusterSize = fs->getClusterSize();
	Synchronize(UpdateClusterSizeLabel);

	Iterator<Cluster>* iteratorDecorated = new ClusterIteratorDecorator(new ClusterIterator(fs), chosenClusterType);

	for (iteratorDecorated->first(); !iteratorDecorated->isDone(); iteratorDecorated->next()) {
		// В ClusterIterator::getCurrent происходит инициализация текущего кластера, а затем чтение в память
		Cluster currentCluster = iteratorDecorated->getCurrent();
		unsigned int currentClusterNumber = currentCluster.getNumber();
		char* currentСlusterTypeChar = currentCluster.getClusterTypeChar();
		char* currentСlusterHexData = currentCluster.getHexData();

		// Отправляем данные из текущего Cluster в TDB_VST, в сооотв-ие свойства
		threadDB_VST->sendClusterToTDB(currentClusterNumber,
									   currentСlusterTypeChar,
									   currentСlusterHexData);
		threadDB_VST->dataSentEvent->SetEvent();

		while(threadDB_VST->dataWrittenEvent->WaitFor(1000) != wrSignaled) { }
		threadDB_VST->dataWrittenEvent->ResetEvent();

        clustersFound++;
		Synchronize(UpdateClustersFoundLabel);
	}
	delete iteratorDecorated;

	threadDB_VST->Terminate();
	delete threadDB_VST;
	delete fsCreator;

	startButtonEnabled = true;
	stopButtonEnabled = false;
	Synchronize(UpdateStartButtonEnabled);
    Synchronize(UpdateStopButtonEnabled);
}

void __fastcall TClusterIteratorDecorator::UpdateStartButtonEnabled()
{
	Form1->StartButton->Enabled = startButtonEnabled;
}

void __fastcall TClusterIteratorDecorator::UpdateStopButtonEnabled()
{
	Form1->StopButton->Enabled = stopButtonEnabled;
}

void __fastcall TClusterIteratorDecorator::UpdateFSTypeLabel()
{
	Form1->FSTypeLabel->Caption = fsTypeChar;
}

void __fastcall TClusterIteratorDecorator::UpdateClusterSizeLabel()
{
	Form1->ClusterSizeLabel->Caption = clusterSize;
}

void __fastcall TClusterIteratorDecorator::UpdateClustersFoundLabel()
{
	Form1->ClustersFoundLabel->Caption = clustersFound;
}

ClusterEnum __fastcall TClusterIteratorDecorator::getClusterType()
{
	if(Form1->PNGButton->Checked) {
		return  ClusterEnum::PNG;
	}
	else if(Form1->EXEButton->Checked) {
		return  ClusterEnum::EXE;
	}
	else if(Form1->PDFButton->Checked) {
		return  ClusterEnum::PDF;
	}

	return ClusterEnum::None;
}
