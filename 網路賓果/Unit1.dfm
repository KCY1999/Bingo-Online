object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 493
  ClientWidth = 673
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 302
    Top = 24
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label2: TLabel
    Left = 256
    Top = 24
    Width = 40
    Height = 13
    Caption = #36899#32218#25976':'
  end
  object Label3: TLabel
    Left = 48
    Top = 24
    Width = 40
    Height = 13
    Caption = #40670#25802#26041':'
  end
  object Label4: TLabel
    Left = 104
    Top = 24
    Width = 20
    Height = 13
    Caption = '-----'
  end
  object Button2: TButton
    Left = 549
    Top = 32
    Width = 75
    Height = 25
    Caption = #32080#26463
    TabOrder = 0
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 416
    Top = 63
    Width = 208
    Height = 177
    ScrollBars = ssVertical
    TabOrder = 1
    OnChange = Memo1Change
  end
  object Memo2: TMemo
    Left = 416
    Top = 273
    Width = 208
    Height = 177
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object ComboBox1: TComboBox
    Left = 416
    Top = 246
    Width = 145
    Height = 21
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 474
    Width = 673
    Height = 19
    DoubleBuffered = False
    Panels = <
      item
        Width = 50
      end
      item
        Width = 50
      end>
    ParentDoubleBuffered = False
    SimplePanel = True
  end
  object Button1: TButton
    Left = 416
    Top = 32
    Width = 75
    Height = 25
    Caption = #37325#26032#38283#22987
    TabOrder = 5
    OnClick = Button1Click
  end
  object IdIPWatch1: TIdIPWatch
    Active = False
    HistoryFilename = 'iphist.dat'
    Left = 104
    Top = 352
  end
  object ServerSocket1: TServerSocket
    Active = False
    Port = 1024
    ServerType = stNonBlocking
    OnAccept = ServerSocket1Accept
    OnClientConnect = ServerSocket1ClientConnect
    OnClientDisconnect = ServerSocket1ClientDisconnect
    OnClientRead = ServerSocket1ClientRead
    OnClientError = ServerSocket1ClientError
    Left = 96
    Top = 416
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 1024
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnError = ClientSocket1Error
    Left = 160
    Top = 416
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50000
    OnTimer = Timer1Timer
    Left = 168
    Top = 352
  end
  object MainMenu1: TMainMenu
    Left = 248
    Top = 352
    object File1: TMenuItem
      Caption = 'File'
      object Listen1: TMenuItem
        Caption = 'Listen'
        OnClick = Listen1Click
      end
      object Connect1: TMenuItem
        Caption = 'Connect'
        OnClick = Connect1Click
      end
      object Disconnect1: TMenuItem
        Caption = 'Disconnect'
        OnClick = Disconnect1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Clear1: TMenuItem
      Caption = 'Clear'
      object Recieve1: TMenuItem
        Caption = 'Receive Log'
        OnClick = Recieve1Click
      end
      object SendLog1: TMenuItem
        Caption = 'Send Log'
        OnClick = SendLog1Click
      end
    end
    object Debug1: TMenuItem
      Caption = 'Debug'
      object DebugWindow1: TMenuItem
        Caption = 'Debug Window'
        OnClick = DebugWindow1Click
      end
    end
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 15000
    OnTimer = Timer2Timer
    Left = 248
    Top = 416
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 50000
    OnTimer = Timer3Timer
    Left = 320
    Top = 384
  end
end
