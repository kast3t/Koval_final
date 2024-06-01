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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
	ClustersFoundLabel->Caption = 0;

	threadClusterIteratorDecorator = new TClusterIteratorDecorator(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	threadClusterIteratorDecorator->Terminate();
	delete threadClusterIteratorDecorator;
}
//---------------------------------------------------------------------------

