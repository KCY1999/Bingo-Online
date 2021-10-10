//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btnn[i][j]!=NULL)
			{
				ShowMessage("error");
				return;
			}
			btnn[i][j]=new TButton(this);
			btnn[i][j]->Top=50+(i*60);
			btnn[i][j]->Left=20+(j*70);
			btnn[i][j]->Height=50;
			btnn[i][j]->Width=50;
			btnn[i][j]->Parent=this;
			btnn[i][j]->Caption="¡´";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btnn[i][j]==NULL)
			{
				ShowMessage("µL¸ê®Æ");
				return;
			}
			delete btnn[i][j];
			btnn[i][j]=NULL;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btnn[i][j]!=NULL)
			{
				ShowMessage("error");
				return;
			}
			btnn[i][j]=new TButton(this);
			btnn[i][j]->Top=50+(i*60);
			btnn[i][j]->Left=20+(j*70);
			btnn[i][j]->Height=50;
			btnn[i][j]->Width=50;
			btnn[i][j]->Parent=this;
			btnn[i][j]->Caption="¡´";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btnn[i][j]==NULL)
			{
				ShowMessage("error");
				return;
			}
			delete btnn[i][j];
			btnn[i][j]=NULL;
		}
	}
}
//---------------------------------------------------------------------------

