;OSCAR NSIS Installer using MUI
!include "MUI2.nsh"

;General information
Name "OSCAR Screen Adapter"
OutFile "oscar-installer.exe"
InstallDir "$LOCALAPPDATA\OSCAR"
InstallDirRegKey HKCU "Software\OSCAR" ""

RequestExecutionLevel admin

!define APPNAME "OSCAR Screen Adapter"
!define COMPANYNAME "Team OSCAR"
!define VERSIONMAJOR 0
!define VERSIONMINOR 1
!define VERSIONBUILD 1
!define INSTALLSIZE  30000

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

  ;Actual OSCAR executable
  File "oscar.exe"
  File "oscar.ico"

  ;Libraries
  File /r "qtlib\*.*"
  SetOutPath "$INSTDIR\platforms"
  File /r "qtlib\platforms\*.*"

  ;TODO: Install drivers

  ;Add to start menu
  createDirectory "$SMPROGRAMS\OSCAR"
  createShortCut  "$SMPROGRAMS\OSCAR\OSCAR.lnk" "$INSTDIR\oscar.exe" "" "$INSTDIR/oscar.ico"

  ;Create unistaller
  WriteRegStr HKCU "Software\OSCAR" "" $INSTDIR
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ;Registry stuff for Add/remove programs
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayName" "${COMPANYNAME} - ${APPNAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\Uninstall.exe$\" /S"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "Publisher" "${COMPANYNAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayVersion" "$\"${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}$\""
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMajor" ${VERSIONMAJOR}
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMinor" ${VERSIONMINOR}
  ;There is no option for modifying or repairing the install
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoRepair" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "EstimatedSize" ${INSTALLSIZE}
SectionEnd

;Descriptions
LangString DESC_SecOSCAR ${LANG_ENGLISH} "OSCAR control program + drivers"
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecOSCAR} ${DESC_SecOSCAR}
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstaller
Section "Uninstall"
  ;Delete from Program Files
  Delete "$INSTDIR\platforms\*"
  RMDir "$INSTDIR\platforms"
  Delete "$INSTDIR\*"

  ;Delete from Start Menu
  Delete "$SMPROGRAMS\OSCAR\OSCAR.link"
  RMDir "$SMPROGRAMS\OSCAR"

  ;Delete add/remove programs reg keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}"

  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
  DeleteRegKey /ifempty HKCU "Software\OSCAR"
SectionEnd
