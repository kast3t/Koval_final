//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "TClusterIteratorDecorator.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *EditDiskLetter;
	TPanel *Panel1;
	TRadioButton *PNGButton;
	TRadioButton *EXEButton;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *FSTypeLabel;
	TButton *StartButton;
	TButton *StopButton;
	TVirtualStringTree *ClustersVST;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *ClustersFoundLabel;
	TLabel *ClusterSizeLabel;
	TRadioButton *PDFButton;
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall ClustersVSTGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);


private:	// User declarations
	TClusterIteratorDecorator* threadClusterIteratorDecorator;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct {
	ULONG id;
	ULONG clusterNumber;
	UnicodeString clusterType;
	UnicodeString hexData;
} NodeStruct;
#endif
