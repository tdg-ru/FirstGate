# Microsoft Developer Studio Project File - Name="DMJournal" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DMJournal - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DMJournal.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DMJournal.mak" CFG="DMJournal - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DMJournal - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DMJournal - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DMJournal - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "DMJournal - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DMJournal - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BIN\Release"
# PROP Intermediate_Dir "BIN\Release\Journal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"BIN\Release\FirstGate.exe" /libpath:"Release"
# SUBTRACT LINK32 /nodefaultlib
# Begin Custom Build
ProjDir=.
InputPath=.\BIN\Release\FirstGate.exe
SOURCE="$(InputPath)"

"nul" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\buildnum.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "DMJournal - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BIN\Debug"
# PROP Intermediate_Dir "BIN\Debug\Journal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /profile /debug /machine:I386 /out:"BIN\Debug\FirstGate.exe" /libpath:"Debug"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "DMJournal - Win32 Debug Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DMJournal___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "DMJournal___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BIN\DebugU\"
# PROP Intermediate_Dir "BIN\DebugU\Journal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /pdb:none /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /pdb:none /debug /machine:I386 /out:"BIN\DebugU\FirstGate.exe" /libpath:"DMJournal___Win32_Debug_Unicode"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "DMJournal - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DMJournal___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "DMJournal___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BIN\ReleaseU\"
# PROP Intermediate_Dir "BIN\ReleaseU\Journal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/FirstGate.exe" /libpath:"Release"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"BIN\ReleaseU\FirstGate.exe" /libpath:"Release"
# SUBTRACT LINK32 /nodefaultlib
# Begin Custom Build
ProjDir=.
InputPath=.\BIN\ReleaseU\FirstGate.exe
SOURCE="$(InputPath)"

"nul" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\buildnum.bat

# End Custom Build

!ENDIF 

# Begin Target

# Name "DMJournal - Win32 Release"
# Name "DMJournal - Win32 Debug"
# Name "DMJournal - Win32 Debug Unicode"
# Name "DMJournal - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\DMDescriptionPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\DMDreamBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DMDreamEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DMDreamEdit2.cpp
# End Source File
# Begin Source File

SOURCE=.\DMDreamPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DMJournal.cpp
# End Source File
# Begin Source File

SOURCE=.\DMJournal.rc
# End Source File
# Begin Source File

SOURCE=.\DMJournalDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DMJournalListView.cpp
# End Source File
# Begin Source File

SOURCE=.\DMJournalView.cpp
# End Source File
# Begin Source File

SOURCE=.\DMMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListSm.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlacePage.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ZoneEdit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# Begin Source File

SOURCE=.\DMDescriptionPage1.h
# End Source File
# Begin Source File

SOURCE=.\DMDreamBar.h
# End Source File
# Begin Source File

SOURCE=.\DMDreamEdit.h
# End Source File
# Begin Source File

SOURCE=.\DMDreamEdit2.h
# End Source File
# Begin Source File

SOURCE=.\DMDreamPage.h
# End Source File
# Begin Source File

SOURCE=.\DMJournal.h
# End Source File
# Begin Source File

SOURCE=.\DMJournalDoc.h
# End Source File
# Begin Source File

SOURCE=.\DMJournalListView.h
# End Source File
# Begin Source File

SOURCE=.\DMJournalView.h
# End Source File
# Begin Source File

SOURCE=.\DMMapView.h
# End Source File
# Begin Source File

SOURCE=.\DMMessages.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListBox.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListPage.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListSm.h
# End Source File
# Begin Source File

SOURCE=.\DMPlacePage.h
# End Source File
# Begin Source File

SOURCE=.\LayerBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapLayer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Sphere.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ZoneEdit.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\action.ico
# End Source File
# Begin Source File

SOURCE=.\res\add.ico
# End Source File
# Begin Source File

SOURCE=.\res\Max\addball.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Max\br.ico
# End Source File
# Begin Source File

SOURCE=.\res\Max2\bred_dream_f.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Max\chat.ico
# End Source File
# Begin Source File

SOURCE=.\res\Max2\chat_dream_f.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Cmdbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Max2\con_dream_f.BMP
# End Source File
# Begin Source File

SOURCE=.\res\conscious.ico
# End Source File
# Begin Source File

SOURCE=.\res\del.ico
# End Source File
# Begin Source File

SOURCE=.\res\delplace.ico
# End Source File
# Begin Source File

SOURCE=.\res\DMJournal.ico
# End Source File
# Begin Source File

SOURCE=.\res\DMJournal.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DMJournalDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\dream.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Max\dream.ico
# End Source File
# Begin Source File

SOURCE=.\res\dreambar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dreambarsm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dreamtb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dreamtb256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dreamtb256a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dreamtb256d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_acti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\loop.ico
# End Source File
# Begin Source File

SOURCE=.\res\lucid.ico
# End Source File
# Begin Source File

SOURCE=.\res\Max2\lucid_dream_f.BMP
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mapbarsm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mapbarsm256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\maptoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\maptoolb256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\maptoolb256m.bmp
# End Source File
# Begin Source File

SOURCE=.\res\new.ico
# End Source File
# Begin Source File

SOURCE=.\res\newplace.ico
# End Source File
# Begin Source File

SOURCE=.\res\other.ico
# End Source File
# Begin Source File

SOURCE=.\res\small.ico
# End Source File
# Begin Source File

SOURCE=.\res\small256.ico
# End Source File
# Begin Source File

SOURCE=.\res\speack.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256M.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Max2\usual_dream2_f copy.BMP"
# End Source File
# Begin Source File

SOURCE=.\res\Max2\usual_dream_f.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\default.dm
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section DMJournal : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:103
# 	2:21:SplashScreenInsertKey:4.0
# End Section
