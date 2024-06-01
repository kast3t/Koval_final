object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1055#1086#1080#1089#1082' '#1082#1083#1072#1089#1090#1077#1088#1086#1074
  ClientHeight = 526
  ClientWidth = 1262
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 24
    Width = 135
    Height = 31
    Caption = #1055#1091#1090#1100' '#1082' '#1076#1080#1089#1082#1091':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 91
    Width = 127
    Height = 31
    Caption = #1058#1080#1087' '#1092#1072#1081#1083#1086#1074':'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 275
    Width = 198
    Height = 31
    Caption = #1060#1072#1081#1083#1086#1074#1072#1103' '#1089#1080#1089#1090#1077#1084#1072':'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object FSTypeLabel: TLabel
    Left = 256
    Top = 275
    Width = 55
    Height = 31
    Caption = 'None'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 24
    Top = 331
    Width = 181
    Height = 31
    Caption = #1056#1072#1079#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072':'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 24
    Top = 379
    Width = 209
    Height = 31
    Caption = #1053#1072#1081#1076#1077#1085#1086' '#1082#1083#1072#1089#1090#1077#1088#1086#1074':'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object ClustersFoundLabel: TLabel
    Left = 256
    Top = 379
    Width = 12
    Height = 31
    Caption = '0'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object ClusterSizeLabel: TLabel
    Left = 256
    Top = 331
    Width = 12
    Height = 31
    Caption = '0'
    DragCursor = crAppStart
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object EditDiskLetter: TEdit
    Left = 176
    Top = 23
    Width = 169
    Height = 36
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = '\\?\F:'
  end
  object Panel1: TPanel
    Left = 24
    Top = 136
    Width = 321
    Height = 133
    TabOrder = 1
    object PNGButton: TRadioButton
      Left = 16
      Top = 8
      Width = 73
      Height = 33
      Caption = 'PNG'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
    end
    object EXEButton: TRadioButton
      Left = 16
      Top = 47
      Width = 73
      Height = 33
      Caption = 'EXE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object PDFButton: TRadioButton
      Left = 16
      Top = 86
      Width = 73
      Height = 33
      Caption = 'PDF'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
  end
  object StartButton: TButton
    Left = 24
    Top = 440
    Width = 145
    Height = 49
    Caption = #1057#1090#1072#1088#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = StartButtonClick
  end
  object StopButton: TButton
    Left = 200
    Top = 440
    Width = 145
    Height = 49
    Caption = #1057#1090#1086#1087
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = StopButtonClick
  end
  object ClustersVST: TVirtualStringTree
    Left = 384
    Top = 24
    Width = 833
    Height = 466
    DefaultNodeHeight = 35
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    Header.AutoSizeIndex = -1
    Header.Height = 35
    Header.MainColumn = -1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    ParentFont = False
    TabOrder = 4
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <>
  end
end
