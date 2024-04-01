unit main_form;

{$mode objfpc}{$H+}

interface

uses
  Classes,
  SysUtils,
  Forms,
  Controls,
  Graphics,
  Dialogs,
  ExtCtrls,
  StdCtrls,
  Process,
  StrUtils,
  FGL,
  LCLTranslator,
  LazHelpHTML,
  UTF8Process,
  ini_handler;

type

  AppLangDict = specialize TFPGMap<string, string>;
  AppManualDict = specialize TFPGMap<string, string>;

  { TMainForm }

  TMainForm = class(TForm)
    OpenUsrManual: TButton;
    ResetBtn: TButton;
    ResolutionCombo: TComboBox;
    Label1: TLabel;
    SaveBtn: TButton;
    LaunchBtn: TButton;
    MaximizeCheck: TCheckBox;
    GroupBox2: TGroupBox;
    LangCombo: TComboBox;
    GroupBox1: TGroupBox;
    function CheckManualExists(LangCode: String): Boolean;
    function GetPathToManualFile(LangCode: String): String;
    procedure OpenUsrManualClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure LangComboSelect(Sender: TObject);
    procedure LaunchBtnClick(Sender: TObject);
    procedure ResetBtnClick(Sender: TObject);
    procedure SaveBtnClick(Sender: TObject);
    procedure UpdateWidgetsFromIni(ini: IniHandler);
    procedure UpdateWidgets(ini: IniHandler);
    procedure OpenManualInBrowser(Path: String);
    procedure ShowMsgIniNotFound;
    procedure ShowMsgExeNotFound;
    public
      destructor Destroy; override;
  end;

const
  ExecutablePath = 'bin/StraightSpiralArmsDetector.exe';
  IniPath = 'bin/settings.ini';

var
  MainForm: TMainForm;
  ProcessCls: TProcess;
  IniFileHandler: IniHandler;
  AvailableLangs: AppLangDict;
  ManualFilePaths: AppManualDict;

resourcestring
  MsgIniNotFoundText = 'Settings file not found.'#10'Default settings set.';
  MsgExeNotFoundText = 'Executable file not found.';
  MsgManualFileNotFound = 'Manual file could not be found.';

implementation

{$R *.lfm}

{ TMainForm }

destructor TMainForm.Destroy;
begin
  FreeAndNil(IniFileHandler);
  FreeAndNil(AvailableLangs);
  FreeAndNil(ManualFilePaths);
  inherited;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  AvailableLangs := AppLangDict.Create;
  AvailableLangs.Add('en_GB', 'English');
  AvailableLangs.Add('ru_RU', 'Russian');

  ManualFilePaths := AppManualDict.Create;
  ManualFilePaths.Add('en_GB', 'manual\UserManualEN.pdf');
  ManualFilePaths.Add('ru_RU', 'manual\UserManualRU.pdf');

  IniFileHandler := IniHandler.Create();

  if IniFileHandler.IsIniExists() then
    begin
      IniFileHandler.ReadIniFile();
      SetDefaultLang(IniFileHandler.WinLanguage);
      UpdateWidgetsFromIni(IniFileHandler);
    end
  else
    begin
      ShowMsgIniNotFound();
      IniFileHandler.CreateDefaultIni();
    end;
end;

procedure TMainForm.OpenUsrManualClick(Sender: TObject);
var
  LangCode: String;
begin
  LangCode := AvailableLangs.GetKey(LangCombo.ItemIndex);

  if not CheckManualExists(LangCode) then
    begin
      ShowMessage(MsgManualFileNotFound);
      Exit;
    end;

  OpenManualInBrowser(GetPathToManualFile(LangCode));
end;

function TMainForm.CheckManualExists(LangCode: String): Boolean;
begin
  if FileExists(GetPathToManualFile(LangCode)) then
    Result := true
  else
    Result := false;
end;

function TMainForm.GetPathToManualFile(LangCode: String): String;
var
  Idx: Integer;
begin
  Idx := ManualFilePaths.IndexOf(LangCode);
  Result := ManualFilePaths.GetData(Idx);
end;

procedure TMainForm.OpenManualInBrowser(Path: String);
var
  HTMLHelp: THTMLBrowserHelpViewer;
  BrowserPath, BrowserParams: String;
  ParamPos: LongInt;
  BrowserProcess: TProcessUTF8;
  AbsoluteFilePath: String;
begin
  HTMLHelp := THTMLBrowserHelpViewer.Create(nil);

  try
    HTMLHelp.FindDefaultBrowser(BrowserPath, BrowserParams);
    ParamPos := System.Pos('%s', BrowserParams);
    System.Delete(BrowserParams, ParamPos, 2);
    AbsoluteFilePath := GetCurrentDir() + '\' + Path;
    System.Insert(AbsoluteFilePath, BrowserParams, ParamPos);

    BrowserProcess := TProcessUTF8.Create(nil);
    try
      BrowserProcess.CommandLine := BrowserPath + ' ' + BrowserParams;
      BrowserProcess.Execute;
    finally
      BrowserProcess.Free;
    end;
  finally
    HTMLHelp.Free;
  end;
end;

procedure TMainForm.LangComboSelect(Sender: TObject);
var
  LangIdx: Integer;
begin
  LangIdx := LangCombo.ItemIndex;
  SetDefaultLang(AvailableLangs.GetKey(LangIdx));
  LangCombo.ItemIndex := LangIdx;
  UpdateWidgets(IniFileHandler);
end;

procedure TMainForm.LaunchBtnClick(Sender: TObject);
begin
  if FileExists(ExecutablePath) then
    begin
      ProcessCls := TProcess.Create(nil);
      try
        ProcessCls.Executable := ExecutablePath;
        ProcessCls.Execute;
      finally
        ProcessCls.Free;
        Close;
      end;
    end
  else
    ShowMsgExeNotFound();
end;

procedure TMainForm.SaveBtnClick(Sender: TObject);
var
  LangIdx: Integer;
begin
  IniFileHandler.WinWidth := StrToInt(SplitString(ResolutionCombo.Text, 'x')[0]);
  IniFileHandler.WinHeight := StrToInt(SplitString(ResolutionCombo.Text, 'x')[1]);
  IniFileHandler.IsMaximize := MaximizeCheck.Checked;
  LangIdx := LangCombo.ItemIndex;
  IniFileHandler.WinLanguage := AvailableLangs.GetKey(LangIdx);
  IniFileHandler.WriteIniFile();
end;

procedure TMainForm.UpdateWidgetsFromIni(ini: IniHandler);
var
  LangIdx: Integer;
begin
  LangIdx := AvailableLangs.IndexOf(ini.WinLanguage);
  if (LangIdx <> -1) then
    LangCombo.ItemIndex := LangIdx
  else
    LangCombo.ItemIndex := 0;

  UpdateWidgets(ini);
end;

procedure TMainForm.UpdateWidgets(ini: IniHandler);
var
  ResIdx: Integer;
begin
  MaximizeCheck.Checked := ini.IsMaximize;

  ResIdx := ResolutionCombo.Items.IndexOf(ini.GetResolution);
  if (ResIdx <> -1) then
    ResolutionCombo.ItemIndex := ResIdx
  else
    ResolutionCombo.ItemIndex := 0;
end;

procedure TMainForm.ShowMsgIniNotFound;
begin
  ShowMessage(MsgIniNotFoundText + #10#10 + IniPath);
end;

procedure TMainForm.ShowMsgExeNotFound;
begin
  ShowMessage(MsgExeNotFoundText + #10#10 + ExecutablePath);
end;

procedure TMainForm.ResetBtnClick(Sender: TObject);
begin
  IniFileHandler.SetDefaultSettings();
  UpdateWidgetsFromIni(IniFileHandler);
end;

end.

