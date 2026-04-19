object Form1: TForm1
  Left = 293
  Top = 230
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Plug Tool '#25554#20214#26694#20214#20135#29983#31243#24207' 8.0'
  ClientHeight = 246
  ClientWidth = 496
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 425
    Height = 18
    AutoSize = False
    Caption = #35831#36755#20837#25554#20214#30340#21517#31216#65292#35831#20351#29992#33521#25991#21517#31216#19988#19981#35201#26377#31354#26684#65281'            '
  end
  object Label2: TLabel
    Left = 14
    Top = 42
    Width = 74
    Height = 15
    Caption = #32452#20214#21517#31216#65306'   '
  end
  object Label3: TLabel
    Left = 14
    Top = 92
    Width = 77
    Height = 15
    Caption = #29983#25104#36335#24452#65306'    '
  end
  object Label4: TLabel
    Left = 14
    Top = 66
    Width = 206
    Height = 15
    Caption = #35831#25351#23450#19968#20010#25554#20214#29983#25104#36335#24452':                    '
  end
  object Edit1: TEdit
    Left = 86
    Top = 37
    Width = 390
    Height = 23
    TabOrder = 0
    OnKeyPress = Edit1KeyPress
  end
  object Edit2: TEdit
    Left = 86
    Top = 89
    Width = 293
    Height = 23
    TabOrder = 1
  end
  object Button2: TButton
    Left = 401
    Top = 87
    Width = 75
    Height = 25
    Caption = #37325#26032#36873
    TabOrder = 2
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 11
    Top = 125
    Width = 169
    Height = 74
    Caption = #39033#30446#31867#22411
    TabOrder = 3
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 125
    Width = 157
    Height = 74
    Caption = #27979#35797#31243#24207
    TabOrder = 4
    object CheckBox1: TCheckBox
      Left = 18
      Top = 20
      Width = 97
      Height = 17
      Caption = 'Main '#27979#35797
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 18
      Top = 43
      Width = 95
      Height = 18
      Caption = 'WinMain '#27979#35797
      TabOrder = 1
    end
  end
  object Button1: TButton
    Left = 406
    Top = 211
    Width = 75
    Height = 25
    Caption = #29983#25104
    TabOrder = 5
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 304
    Top = 211
    Width = 75
    Height = 25
    Caption = #29256#26435#25152#26377
    TabOrder = 6
    OnClick = Button3Click
  end
  object Memo1: TMemo
    Left = 355
    Top = 130
    Width = 121
    Height = 69
    Color = clGradientInactiveCaption
    Lines.Strings = (
      #25552#31034#21306'...')
    ReadOnly = True
    TabOrder = 7
  end
  object ComboBox1: TComboBox
    Left = 21
    Top = 162
    Width = 143
    Height = 23
    Style = csDropDownList
    DropDownCount = 15
    TabOrder = 8
    Items.Strings = (
      'VC6'
      'VC7.1'
      'VC8'
      'VC9'
      'VC10'
      'VC11 (vs2012)'
      'VC12 (vs2013)'
      'VS2015'
      'VS2017'
      'VS2019'
      'VS2022'
      'C++ Builder 6'
      'C++ Builder 2006'
      'C++ Builder 2009'
      'C++ Builder 2010'
      'C++ Builder XE2'
      'C++ Builder XE10'
      'C++ Builder 10.1 Berlin'
      'C++ Builder 11'
      'C++ Builder 12'
      'Mac Xcode'
      'Code Blocks'
      'vs2019_linux')
  end
  object Button4: TButton
    Left = 210
    Top = 211
    Width = 75
    Height = 25
    Caption = #37197#32622'VC'#29615#22659
    TabOrder = 9
    OnClick = Button4Click
  end
end
