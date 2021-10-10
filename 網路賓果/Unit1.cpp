//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <time.h>

#include "Unit1.h"
#include "Unit2.h"

#define CLIENT_MAX 5 //maximum of client
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TButton *btn[5][5];
int rnd[5][5],tmp[5][5],rd[5][5]; //亂數 //點擊對象
String ss[5][5];
AnsiString str,stt;
int HL = 0, VL = 0, SL = 0, BSL = 0, eva = 0, val=1, tim = 0, ckc = 1;

String strHost;
bool blnServer;
String newClient="";
String ClientHostName="";
String ServerName="";
bool fgConnectState;
TStringList *sList = new TStringList();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//開始
void TForm1::start()
{
	Button2->Enabled=true;
	Label1->Caption = "0";
    ckc = 0;
    ss[1][1]="";
	int a[25];
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btn[i][j]!=NULL)
			{
				//ShowMessage("error");
				return;
			}
			a[(i*5)+j]=(rand()%(25-1+1))+1;

			for(int t=0;t<((i*5)+j);t++)
			{
				while(a[(i*5)+j]==a[t])
				{
					a[(i*5)+j]=(rand()%(25-1+1))+1;
					t=0;
				}
			}
			btn[i][j]=new TButton(this);
			btn[i][j]->Top=50+(i*60);
			btn[i][j]->Left=20+(j*70);
			btn[i][j]->Caption=a[(i*5)+j];
			btn[i][j]->Tag=a[(i*5)+j];
			btn[i][j]->OnClick=clk;
			btn[i][j]->Height=50;
			btn[i][j]->Width=50;
			btn[i][j]->Parent=this;
		}
	}
}
//---------------------------------------------------------------------------
//結束
void TForm1::over()
{
	HL = 0, VL = 0, SL = 0, BSL = 0, eva = 0, val = 1, tim = 0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(btn[i][j]==NULL)
			{
				//ShowMessage("error");
				return;
			}
			delete btn[i][j];
			btn[i][j]=NULL;
		}
	}
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
//點擊判斷
void __fastcall TForm1::clk(TObject *Sender)
{
	TButton *btn1;
	btn1=(TButton *)Sender;
	if(val==0 && ckc==0)
	{
        Timer3->Enabled = false;
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				if(btn1->Caption == ss[i][j])
				{
					Form2->btnn[i][j]->Caption = ss[i][j];
                }
			}
		}
		btn1->Enabled=false;
		btn1->Caption="O";
		lineH();lineV();
		SL1();SL2();
		Label1->Caption =IntToStr(eva);
		Label4->Caption="換對方點擊";

		String msg;
		PACKET pkg;
		String strPkg;
		String srtClient;
		eva = (HL+VL+SL+BSL)/5;
		pkg.ID="PON";

		if(blnServer)
		  pkg.Host=IdIPWatch1->LocalIP();
		else
		  pkg.Host=ClientHostName;

		pkg.separation="@";
		pkg.MainFunc=2; //傳送資料
		pkg.SubFunc=eva;
		pkg.MsgLength=IntToStr(btn1->Tag).Length();
		pkg.Msg=IntToStr(btn1->Tag);
		pkg.EndSymbol="#";
		strPkg=AssemblePacket(pkg);
		Memo2->Lines->Add(strPkg);

		if (blnServer)
		  {
			for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
					ServerSocket1->Socket->Connections[i]->SendText(strPkg);
			/*int index;
			for(index=0;index<ServerSocket1->Socket->ActiveConnections;index++)
			{
				srtClient=ServerSocket1->Socket->Connections[index]->RemoteAddress +
					"-"+IntToStr(ServerSocket1->Socket->Connections[index]->SocketHandle);
				if(ComboBox1->Text==srtClient)
				break;
			}  */
			//ServerSocket1->Socket->Connections[index]->SendText(strPkg);
		  }
		else // Client
			ClientSocket1->Socket->SendText(strPkg) ;

        Sleep(100);

		pkg.ID="PON";
		if(blnServer)
			pkg.Host=IdIPWatch1->LocalIP();
		else
			pkg.Host=ClientHostName;

		pkg.separation="@";
		pkg.MainFunc=3; //傳送資料
		pkg.SubFunc=eva;
		pkg.MsgLength = 0;
		pkg.Msg = "";
		pkg.EndSymbol="#";
		strPkg=AssemblePacket(pkg);

		if (blnServer)
		{
			for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
					ServerSocket1->Socket->Connections[i]->SendText(strPkg);
			/*int index;
			for(index=0;index<ServerSocket1->Socket->ActiveConnections;index++)
			{
				srtClient=ServerSocket1->Socket->Connections[index]->RemoteAddress +
					"-"+IntToStr(ServerSocket1->Socket->Connections[index]->SocketHandle);
				if(ComboBox1->Text==srtClient)
				break;
			}  */
			//ServerSocket1->Socket->Connections[index]->SendText(strPkg);
		}
		else // Client
			ClientSocket1->Socket->SendText(strPkg) ;

		val = 1;
		ckc = 1;
		Timer1->Enabled=true;
		Timer2->Enabled=true;
	}
}
//---------------------------------------------------------------------------
//結束

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	over();
}
//---------------------------------------------------------------------------
//關閉程式
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	for(int i=0;i<25;i++)
	{
		if(btn[i/5][i%5]!=NULL)
		{
			delete btn[i/5][i%5];
			btn[i/5][i%5]=NULL;
		}
	}
}
//---------------------------------------------------------------------------
//賓果連線判斷
void TForm1::lineH()
{
	HL = 0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if((btn[i][0]->Caption)+(btn[i][1]->Caption)+(btn[i][2]->Caption)
					  +(btn[i][3]->Caption)+(btn[i][4]->Caption)=="OOOOO")
			{
				HL++;
			}
		}
	}
}

void TForm1::lineV()
{
	VL = 0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if((btn[0][j]->Caption)+(btn[1][j]->Caption)+(btn[2][j]->Caption)
			   +(btn[3][j]->Caption)+(btn[4][j]->Caption)=="OOOOO")
			{
				VL++;
			}
		}
	}
}

void TForm1::SL1()
{
	SL = 0;
	if((btn[0][4]->Caption)+(btn[1][3]->Caption)+(btn[2][2]->Caption)
			   +(btn[3][1]->Caption)+(btn[4][0]->Caption)=="OOOOO")
	{
	   SL+=5;
	}
}

void TForm1::SL2()
{
	BSL = 0;
	if((btn[0][0]->Caption)+(btn[1][1]->Caption)+(btn[2][2]->Caption)
			   +(btn[3][3]->Caption)+(btn[4][4]->Caption)=="OOOOO")
	{
	   BSL+=5;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	time_t t;
	srand((unsigned)time(&t));

	Button1->Enabled = false;
    Button2->Enabled = false;

	fgConnectState=false;
	Disconnect1->Enabled=false;
	Form1->Caption="Local host: "+IdIPWatch1->LocalIP();
	for(int i=0;i<25;i++)
	{
		btn[i/5][i%5]=NULL;
	}
}
//---------------------------------------------------------------------------
//Server連接
void __fastcall TForm1::Listen1Click(TObject *Sender)
{
	PACKET pkg;
	String strPkg;

	Form1->Caption="I am a server"+IdIPWatch1->LocalIP();

	Listen1->Checked =! Listen1->Checked;

	ComboBox1->Clear();

	if(Listen1->Checked)
	{
		ClientSocket1->Active =false;
		try{
			ServerSocket1->Active = true;
		}
		catch(...)
		{
			Listen1->Checked=false;
			ShowMessage("Be a server failure.");
			return;
		}

		ServerName="Server-"+IdIPWatch1->LocalIP();
		StatusBar1->SimpleText="Status: Chat Server Listening...";
		Connect1->Enabled=false;
		Form2->Memo1->Lines->Add("Server: "+ServerName+", socket:"+
								 IntToStr(ServerSocket1->Socket->SocketHandle));
		ComboBox1->Enabled=true;
	}
	else
	{
		if(ServerSocket1->Active)
		{
			pkg.ID="PON";
			pkg.MainFunc=1;
			pkg.SubFunc=2;
			pkg.MsgLength=0;
			pkg.Msg="";
			pkg.separation="@";
			pkg.EndSymbol="#";
			pkg.Host=ServerName;

			strPkg=AssemblePacket(pkg);
			for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
			{
				ServerSocket1->Socket->Connections[i]->SendText(strPkg);
			}
			ServerSocket1->Active=false;
		}
		Connect1->Enabled=true;
		StatusBar1->SimpleText="Status: Chat Server Close";
	}
	blnServer = true;
	Form1->Tag=0;
}
//---------------------------------------------------------------------------

String TForm1::AssemblePacket(PACKET pkg)
{
	String str="",tmp;
	//-----檔頭-----
	if(pkg.ID.Length()!=3)
	{
		ShowMessage("檔頭錯誤");
		return NULL;
	}
	else
	{
		str+=pkg.ID;
	}
	//-----Host-----
	if(pkg.Host.Length()==0)
	{
		ShowMessage("Host錯誤");
		return NULL;
	}
	else
	{
		str+=pkg.Host;
		str+=pkg.separation;
	}
	//-----Main Function-----
	str+=pkg.MainFunc;
	//-----Sub Function-----
	str+=pkg.SubFunc;
	//-----Msg Length-----
	tmp=IntToStr(pkg.MsgLength);
	if(tmp.Length()>3)
	{
		ShowMessage("msg長度紀錄錯誤");
			return NULL;
    }
	else
	{
		for(int i=0;i<3-tmp.Length();i++)
			str+="0";

		str+=tmp;
	}
	//-----Message-----

	if(pkg.MsgLength!=pkg.Msg.Length())
	{
		ShowMessage("msg長度錯誤");
			return NULL;
	}
	else
	{
		str+=pkg.Msg;
		str+=pkg.EndSymbol;
	}
	//str="CHAT127.0.0.1-123#110@";
	return str;
}
//--------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1Accept(TObject *Sender, TCustomWinSocket *Socket)

{
   fgConnectState=true;
   Memo2->Visible=true;
   ReflashClientList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Recieve1Click(TObject *Sender)
{
	Memo1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SendLog1Click(TObject *Sender)
{
	Memo2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Connect1Click(TObject *Sender)
{
	Form1->Caption="I am a client";
	if(ClientSocket1->Active)
		ClientSocket1->Active=false;

	strHost="127.0.0.1";
	if(InputQuery("Chat Conncetion", "Chat Server IP", strHost))
	{
		if(strHost.Length() > 0)
		{
			ClientSocket1->Host=strHost;
			ClientSocket1->Active=true;

			Listen1->Checked=false;
			//Disconnect1->Enabled=false;
			blnServer=false;
			ComboBox1->Enabled=false;
		 }
   	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	tim = 1;
	Timer1->Enabled=false;
	ShowMessage("Time Out");
	dis();
	over();

	ClientSocket1->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)

{
	val = 1;
    ckc = 0;
	PACKET pkg;
	String strPkg;
	start();
	Button1->Enabled=false;
	StatusBar1->SimpleText="Status: Connect to" + Socket->RemoteHost;
	fgConnectState=true;
	Memo2->Clear();
	Memo2->Visible=true;
	Memo2->Lines->Add("Server先手");

	Listen1->Enabled=false;
	Connect1->Enabled=false;
	Disconnect1->Enabled=true;

	ClientSocket1->ClientType=ctNonBlocking;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket)

{
	StatusBar1->SimpleText="server disconnect";

	fgConnectState=false;
	Memo2->Visible=false;

	Listen1->Enabled=true;
	Disconnect1->Enabled=false;
	Connect1->Enabled=true;
	ShowMessage("你已斷線");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)

{
	pPACKET pPkg;
	String strPacket;

	if(!fgConnectState)
	{
		return;
    }

	strPacket=Socket->ReceiveText();
	Form2->Memo1->Lines->Add("["+Time()+"]"+strPacket);

	pPkg=DisassemblePacket(strPacket);
	if(pPkg==NULL)
	{
		Memo1->Lines->Add("Packet error");
		return;
	}
	ParsePacket(pPkg);
	Memo1->Lines->Add(strPacket);
	if(val==0)
	{
		Memo2->Lines->Add("換Client點擊");
		Label4->Caption = "換你點擊";
		Timer1->Enabled = true;
    }
}
//---------------------------------------------------------------------------

pPACKET TForm1::DisassemblePacket(String strPkg)
{
   PACKET tmpPkg;
   pPACKET pPkg;
   int separator;
   String strTmp;

   Form2->Memo1->Lines->Add("===== Diassemble packet ====");

   if(strPkg[strPkg.Length()]!='#')
   {
	  Form2->Memo1->Lines->Add("Packet error 1");
	  return NULL;
   }

   if(strPkg.Pos("@")<=0)
   {
	  Form2->Memo1->Lines->Add("Packet error 2");
	  return NULL;
   }

   if(strPkg.SubString(1,3)!="PON")
   {
	  Form2->Memo1->Lines->Add("Packet error 3");
	  return NULL;
   }

   //---------------------------------------
   tmpPkg.ID=strPkg.SubString(1,3);

   separator= strPkg.Pos("@");
   tmpPkg.Host=strPkg.SubString(4,separator-4);
   tmpPkg.separation=strPkg.SubString(separator,1);

   tmpPkg.MainFunc=strPkg.SubString(separator+1,1);
   tmpPkg.SubFunc=strPkg.SubString(separator+2,1);

   //-----------------------------------------
   strTmp=strPkg.SubString(separator+3,3);
   try{
	   tmpPkg.MsgLength=StrToInt(strTmp);
   }
   catch(...)
   {
	  Form2->Memo1->Lines->Add("Packet error 4");
	  return NULL;
   }

   if(tmpPkg.MsgLength<0)
   {
	  Form2->Memo1->Lines->Add("Packet error 5");
	  return NULL;
   }

   strTmp=strPkg.SubString(separator+6,strPkg.Length()-separator-6);
   if(strTmp.Length()!=tmpPkg.MsgLength)
   {
	  Form2->Memo1->Lines->Add("Packet error 6");
	  return NULL;
   }
   else
   {
		tmpPkg.Msg=strTmp;
   }

   pPkg=new PACKET;
   pPkg->ID=tmpPkg.ID;
   pPkg->Host=tmpPkg.Host;
   pPkg->separation=tmpPkg.separation;
   pPkg->MainFunc=tmpPkg.MainFunc;
   pPkg->SubFunc=tmpPkg.SubFunc;
   pPkg->MsgLength=tmpPkg.MsgLength;
   pPkg->Msg=tmpPkg.Msg;
   pPkg->EndSymbol=tmpPkg.EndSymbol;

   return pPkg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
	ServerSocket1->Close();
	ClientSocket1->Close();

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
	Memo2->Lines->Add("Error:"+strHost);
	ErrorCode = 0;
}
//---------------------------------------------------------------------------

void TForm1::ParsePacket(pPACKET pPkg)
{
	int mFunc,sFunc;

	mFunc=StrToInt(pPkg->MainFunc);
	sFunc=StrToInt(pPkg->SubFunc);
	sList->Delimiter = ','; // 設定要分割的字元
	sList->DelimitedText = pPkg->Msg;

	switch(mFunc)
	{
		case 1:
			switch(sFunc)
			{
				case 1: //new connection
						ClientHostName=pPkg->Msg;
						Form2->Memo1->Lines->Add("New name:"+ClientHostName);
						Form1->Caption=ClientHostName;
						break;
				case 2: //Disconnect
						if(blnServer)
							Form2->Memo1->Lines->Add("["+Time()+"] Client'"+pPkg->Host+"'requests to disconnect.");
						else
							Form2->Memo1->Lines->Add("["+Time()+"] Server'"+pPkg->Host+"'disconnected.");
						break;
				case 3:
						if(!blnServer)
						{
							check();
						}
						for(int i=0;i<25;i++)
						{
							ss[i/5][i%5] = sList ->Strings[i];
						}
			}
			break;

		case 2:
				for(int i=0;i<5;i++)
				{
					for(int j=0;j<5;j++)
					{
					   if(pPkg->Msg == ss[i][j])
					   {
							Form2->btnn[i][j]->Caption=ss[i][j];
					   }
					   if(btn[i][j]->Tag==StrToInt(pPkg->Msg))
					   {
							String msg;
							PACKET pkg;
							String strPkg;
							String srtClient;
							pkg.ID="PON";
							if(blnServer)
								pkg.Host=IdIPWatch1->LocalIP();
							else
								pkg.Host=ClientHostName;

								pkg.separation="@";
							pkg.MainFunc=3; //傳送資料
							pkg.SubFunc=eva;
							pkg.MsgLength = 0;
							pkg.Msg = "";
							pkg.EndSymbol="#";
							strPkg=AssemblePacket(pkg);

							if(blnServer)
							{
								for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
									ServerSocket1->Socket->Connections[i]->SendText(strPkg);
							}
							else
							{
								ClientSocket1->Socket->SendText(strPkg);
							}

							btn[i][j]->Enabled = false;
							btn[i][j]->Caption = "O";
							val = 0;
							ckc = 0;
					   }
					}
				}

                Timer1->Enabled = false;
				lineH();lineV();
				SL1();SL2();
				Memo1->Lines->Add("["+pPkg->Host+"]:"+pPkg->Msg);
				if(sFunc>=3 || eva>=3)
				{
					String msg;
					PACKET pkg;
					String strPkg;
					String srtClient;

					pkg.ID="PON";

					if(blnServer)
					pkg.Host=IdIPWatch1->LocalIP();
					else
					pkg.Host=ClientHostName;

					pkg.separation="@";
					pkg.MainFunc=3; //傳送資料
					pkg.SubFunc=eva;
					pkg.MsgLength = 0;
					pkg.Msg = "";
					pkg.EndSymbol="#";
					strPkg=AssemblePacket(pkg);
					Memo2->Lines->Add(strPkg);

					if (blnServer)
					{
						ServerSocket1->Socket->Connections[0]->SendText(strPkg);
					}
					else // Client
						ClientSocket1->Socket->SendText(strPkg);
					if(sFunc>=3 && eva>=3)
					{
						ShowMessage("平手");
						over();
						//start();
					}
					else if(sFunc>=3 && eva<3)
					{
						ShowMessage("輸了");
						over();
						Button1->Enabled=true;
						//start();
					}
					else if(sFunc<3 && eva>=3)
					{
						ShowMessage("勝利");
						over();
						//start();
					}
				}
				break;

		case 3:
				Timer2->Enabled = false;
				//Timer3->Enabled = true;
				if(sFunc>=3 && eva >=3)
				{
					ShowMessage("平手");
					over();
					start();

				}
				else if(sFunc>=3 && eva<3)
				{
					ShowMessage("輸了");
					over();
					start();

				}
				else if(sFunc<3 && eva>=3)
				{
					ShowMessage("勝利");
					over();
					start();
				}
				break;
		default:
				break;
    }
}
//---------------------------------------------------------------------------

void TForm1::ReflashClientList()
{
	ComboBox1->Clear();

	if(ServerSocket1->Socket->ActiveConnections>1)
	{
		ComboBox1->Items->Add("All");
	}

	for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
	{
		ComboBox1->Items->Add(ServerSocket1->Socket->Connections[i]->RemoteAddress+"-"+
							  IntToStr(ServerSocket1->Socket->Connections[i]->SocketHandle));
	}

	ComboBox1->ItemIndex=0;
	ComboBox1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)

{
	Form2->Memo1->Lines->Add("'"+Socket->RemoteAddress+"-"+IntToStr(Socket->SocketHandle)+"'disconnect");
	StatusBar1->SimpleText="Status:Listening...";

	if(ServerSocket1->Socket->ActiveConnections==1)
	{
		fgConnectState=false;
		Memo2->Visible=false;
	}
	ComboBox1->Enabled=false;
	ckc = 1;
    over();
	ShowMessage("對方已斷線");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo1Change(TObject *Sender)
{
	ReflashClientList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
	StatusBar1->SimpleText="Error from Client scoket.";
	ReflashClientList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket)

{
	pPACKET pPkg;
	String strPacket;

	strPacket=Socket->ReceiveText();
	Form2->Memo1->Lines->Add("["+Time()+"]"+strPacket);
	pPkg=DisassemblePacket(strPacket);

	if(pPkg==NULL)
	{
		Memo1->Lines->Add("Packet error");
		return;
	}
	ParsePacket(pPkg);
	Memo1->Lines->Add(strPacket);
	if(val==0)
	{
		Memo2->Lines->Add("換Server點擊");
		Label4->Caption = "換你點擊";
        Timer1->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	val = 0;
	PACKET pkg;
	String strPkg;
	int clientNum;
	start();
	Button1->Enabled = false;
	Memo2->Lines->Add("你先手");
	clientNum= ServerSocket1->Socket->ActiveConnections;

	if(clientNum>5)
	{
		Form2->Memo1->Lines->Add("已達連線最大數量");
		Socket->Close();
		return;
	}
	StatusBar1->SimpleText="Status:Connect from"+Socket->RemoteHost+"socket ID:"+IntToStr(Socket->SocketHandle);
	Sleep(1000);
	if(!CheckClients(Socket))
	{
	 pkg.ID="PON";
	 pkg.Host=ServerName;
	 pkg.separation="@";
	 pkg.MainFunc=1;
	 pkg.SubFunc=1;
	 pkg.MsgLength=newClient.Length();
	 pkg.Msg=newClient;
	 pkg.EndSymbol="#";
	 strPkg=AssemblePacket(pkg);
     Sleep(1000);
	 ServerSocket1->Socket->Connections[clientNum-1]->SendText(strPkg);
	}
	 check();
}
//---------------------------------------------------------------------------

bool TForm1::CheckClients(TCustomWinSocket *Socket)
{
	bool fg;
	int sHnd;
	String hostIP;

	hostIP=Socket->RemoteAddress;
	sHnd=Socket->SocketHandle;

	newClient=hostIP+"-"+IntToStr(sHnd);
	Form2->Memo1->Lines->Add("New connection"+newClient);
	Form2->Memo1->Lines->Add("Connection number:"+
							 IntToStr(ServerSocket1->Socket->ActiveConnections));

	fg=false;
	return fg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DebugWindow1Click(TObject *Sender)
{
	Form2->Top=Form1->Top;
	Form2->Left=Left+Form1->Width+10;
    Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	start();
	val = 0;
    Label4->Caption = "換你點擊";
}
//---------------------------------------------------------------------------
void TForm1::check()  //傳牌面
{
	String msg;
	String srtClient;
	PACKET pkg;                 //存字串ss[][]
	String strPkg;             //Form2->btnn
	pkg.ID="PON";

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			msg += btn[i][j]->Caption + ",";
		}
	}
	msg = msg.SubString(0,msg.Length()-1);

	if(blnServer)
	  pkg.Host=IdIPWatch1->LocalIP();
	else
	  pkg.Host=ClientHostName;

	pkg.separation="@";
	pkg.MainFunc=1; //傳送資料
	pkg.SubFunc=3;
	pkg.MsgLength=msg.Length();
	pkg.Msg=msg;
	pkg.EndSymbol="#";
	strPkg=AssemblePacket(pkg);
	Memo2->Lines->Add(strPkg);
	if(blnServer)
	{
		for(int i=0;i<ServerSocket1->Socket->ActiveConnections;i++)
				ServerSocket1->Socket->Connections[i]->SendText(strPkg);
	}
	else
	{
		ClientSocket1->Socket->SendText(strPkg);
	}
}

//---------------------------------------------------------------------------
void TForm1::dis()
{
	PACKET pkg;
	String strPkg;

	if(blnServer)
	{
		return;
	}

	pkg.ID="PON";
	pkg.MainFunc=1;
	pkg.SubFunc=2;
	pkg.MsgLength=0;
	pkg.Msg="";
	pkg.separation="@";
	pkg.EndSymbol="#";
	pkg.Host=ClientHostName;

	strPkg=AssemblePacket(pkg);

	//ClientSocket1->Socket->SendText(strPkg);
	ClientSocket1->Active=false;

	Memo2->Lines->Add("["+Time()+"] Disconnect.");
	Listen1->Checked=false;
	Connect1->Checked=false;
	Disconnect1->Checked=false;

	fgConnectState=false;
	Memo2->Visible=false;

	StatusBar1->SimpleText="Status: Disconnect";
	Form1->Caption="";
}

void __fastcall TForm1::Disconnect1Click(TObject *Sender)
{
	dis();
    over();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	ckc = 1;
	dis();
	over();
	start();
	ShowMessage("對方逾時");
	Timer2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
   	dis();
	over();
	Timer3->Enabled = false;
	ShowMessage("太久沒回應");
}
//---------------------------------------------------------------------------

