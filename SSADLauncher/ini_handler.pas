unit ini_handler;

{$mode objfpc}{$H+}

interface

uses IniFiles,
     SysUtils;

type

 { IniHandler }

  IniHandler = class
    private
      FLanguage: String;
      FWinWidth: Integer;
      FWinHeight: Integer;
      FIsMaximize: Boolean;
      procedure SetHeight(AValue: Integer);
      procedure SetLanguage(AValue: String);
      procedure SetMaximize(AValue: Boolean);
      procedure SetWidth(AValue: Integer);
    public
      property IsMaximize: Boolean read FIsMaximize write SetMaximize;
      property WinWidth: Integer read FWinWidth write SetWidth;
      property WinHeight: Integer read FWinHeight write SetHeight;
      property WinLanguage: String read FLanguage write SetLanguage;
      function IsIniExists: Boolean;
      function GetResolution: String;
      procedure SetDefaultSettings;
      procedure CreateDefaultIni;
      procedure ReadIniFile;
      procedure WriteIniFile;
      procedure SetIniFileOptions(VAR ini: TIniFile);
  end;

const
  IniFilePath = 'bin/settings.ini';

implementation

{ IniHandler }

procedure IniHandler.SetHeight(AValue: Integer);
begin
  if FWinHeight = AValue then Exit;
  FWinHeight := AValue;
end;

procedure IniHandler.SetLanguage(AValue: String);
begin
  if FLanguage = AValue then Exit;
  FLanguage := AValue;
end;

procedure IniHandler.SetMaximize(AValue: Boolean);
begin
  if FIsMaximize = AValue then Exit;
  FIsMaximize := AValue;
end;

procedure IniHandler.SetWidth(AValue: Integer);
begin
  if FWinWidth = AValue then Exit;
  FWinWidth := AValue;
end;

function IniHandler.IsIniExists: Boolean;
begin
  if FileExists(IniFilePath) then
    IsIniExists := True
  else
    IsIniExists := False;
end;

function IniHandler.GetResolution: String;
begin
  GetResolution := IntToStr(FWinWidth) + 'x' + IntToStr(FWinHeight);
end;

procedure IniHandler.SetDefaultSettings;
begin
  FLanguage := 'en_GB';
  FWinWidth := 800;
  FWinHeight := 600;
  FIsMaximize := false;
end;

procedure IniHandler.CreateDefaultIni;
begin
  SetDefaultSettings();
  WriteIniFile();
end;

procedure IniHandler.ReadIniFile;
var
  IR: TIniFile;
begin
  IR := TIniFile.Create(IniFilePath);
  SetIniFileOptions(IR);

  FLanguage := IR.ReadString('locale', 'language', '');
  FWinWidth := IR.ReadInteger('window', 'width', 800);
  FWinHeight := IR.ReadInteger('window', 'height', 600);
  FIsMaximize := IR.ReadBool('window', 'maximize', false);

  IR.Free();
end;

procedure IniHandler.WriteIniFile;
var
  IR: TIniFile;
begin
  IR := TIniFile.Create(IniFilePath);
  SetIniFileOptions(IR);

  IR.WriteString('locale', 'language', FLanguage);
  IR.WriteInteger('window', 'width', FWinWidth);
  IR.WriteInteger('window', 'height', FWinHeight);
  IR.WriteBool('window', 'maximize', FIsMaximize);

  IR.Free();
end;

procedure IniHandler.SetIniFileOptions(var ini: TIniFile);
begin
  ini.Options := ini.Options + [ifoWriteStringBoolean];
  ini.BoolTrueStrings := ['true'];
  ini.BoolFalseStrings := ['false'];
end;

end.
