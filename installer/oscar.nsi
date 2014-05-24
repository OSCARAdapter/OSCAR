;OSCAR NSIS Installer using MUI
!include "MUI2.nsh"

;General information
Name "OSCAR Screen Adapter"
OutFile "oscar-installer.exe"
InstallDir "$LOCALAPPDATA\OSCAR"
InstallDirRegKey HKCU "Software\OSCAR" ""
RequestExecutionLevel user

;UI settings
!define MUI_ABORTWARNING

;Pages
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;Languages
!insertmacro MUI_LANGUAGE "English"

;Sections
Section "OSCAR" SecOSCAR
  SetOutPath "$INSTDIR"

  ;TODO: Add files here

  ;QT Library
  File /r "qtlib\*.*"
  SetOutPath "$INSTDIR\platforms"
  File /r "qtlib\platforms\*.*"


  WriteRegStr HKCU "Software\OSCAR" "" $INSTDIR
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;Descriptions
LangString DESC_SecOSCAR ${LANG_ENGLISH} "OSCAR control program + drivers"
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecOSCAR} ${DESC_SecOSCAR}
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstaller
Section "Uninstall"
  Delete "$INSTDIR\platforms\*"
  RMDir "$INSTDIR\platforms"
  Delete "$INSTDIR\*"

  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
  DeleteRegKey /ifempty HKCU "Software\OSCAR"
SectionEnd
