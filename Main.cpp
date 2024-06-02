//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Для каждого узла необходимо выделять столько памяти
	ClustersVST->NodeDataSize = sizeof(NodeStruct);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
	ClustersFoundLabel->Caption = 0;
	ClustersVST->Clear();

	threadClusterIteratorDecorator = new TClusterIteratorDecorator(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	threadClusterIteratorDecorator->Terminate();
	delete threadClusterIteratorDecorator;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClustersVSTGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
    if (!Node) return;

	NodeStruct* nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column) {
		case 0: CellText = nodeData->id; break;
		case 1: CellText = nodeData->clusterNumber; break;
		case 2: CellText = nodeData->clusterType; break;
		case 3: CellText = nodeData->hexData; break;
	}
}
//---------------------------------------------------------------------------

