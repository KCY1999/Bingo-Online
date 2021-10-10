//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIPWatch.hpp>
#include <System.Win.ScktComp.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------

typedef struct _PACKET
{
	String ID;            // 3 bytes
	String Host;          // unfixed length
	String separation;    // 1 byte
	String MainFunc;      // 1 byte
	String SubFunc;       // 1 byte
	int MsgLength;        // 3 bytes (String)
	String Msg;           // unfixed length
	String EndSymbol;     // 1 byte, @
}PACKET, *pPACKET;

typedef struct _CLIENT_SOCKET
{
	bool active;
	TCustomWinSocket * pSocket;
	String ClientID;
}CLIENTSOCKET, *pCLIENTSOCKET;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TIdIPWatch *IdIPWatch1;
	TServerSocket *ServerSocket1;
	TClientSocket *ClientSocket1;
	TButton *Button2;
	TMemo *Memo1;
	TTimer *Timer1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Clear1;
	TMenuItem *Debug1;
	TMenuItem *Listen1;
	TMenuItem *Connect1;
	TMenuItem *Disconnect1;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TMenuItem *Recieve1;
	TMenuItem *SendLog1;
	TMenuItem *DebugWindow1;
	TMemo *Memo2;
	TComboBox *ComboBox1;
	TStatusBar *StatusBar1;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TLabel *Label3;
	TLabel *Label4;
	TTimer *Timer2;
	TTimer *Timer3;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Listen1Click(TObject *Sender);
	void __fastcall ServerSocket1Accept(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Recieve1Click(TObject *Sender);
	void __fastcall SendLog1Click(TObject *Sender);
	void __fastcall Connect1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall ServerSocket1ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Memo1Change(TObject *Sender);
	void __fastcall ServerSocket1ClientError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ServerSocket1ClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall DebugWindow1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Disconnect1Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	void __fastcall clk(TObject *Sender);
	void lineH();
	void lineV();
	void SL1();
	void SL2();

	bool CheckClients(TCustomWinSocket *);
	String AssemblePacket(PACKET pkg);
	pPACKET DisassemblePacket(String);
	void ShowPacket(PACKET);
	void ShowPacket(pPACKET);
	void ParsePacket(pPACKET);
	void ReflashClientList();
	void start();
	void over();
	void check();
    void dis();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
