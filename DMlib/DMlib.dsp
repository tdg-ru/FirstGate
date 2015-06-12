# Microsoft Developer Studio Project File - Name="DMlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DMlib - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DMlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DMlib.mak" CFG="DMlib - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DMlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DMlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "DMlib - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "DMlib - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DMlib - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BIN\Release"
# PROP Intermediate_Dir "..\BIN\Release\DMlib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DMlib - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\BIN\Debug"
# PROP Intermediate_Dir "..\BIN\Debug\DMlib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DMlib - Win32 Debug Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Unicode"
# PROP BASE Intermediate_Dir "Debug Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\BIN\DebugU\"
# PROP Intermediate_Dir "..\BIN\DebugU\DMlib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "UNICODE" /D "_UNICODE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DMlib - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DMlib___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "DMlib___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BIN\ReleaseU\"
# PROP Intermediate_Dir "..\BIN\ReleaseU\DMlib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "DMlib - Win32 Release"
# Name "DMlib - Win32 Debug"
# Name "DMlib - Win32 Debug Unicode"
# Name "DMlib - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DMDescription.cpp
# End Source File
# Begin Source File

SOURCE=.\DMMapLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlace.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListV.cpp
# End Source File
# Begin Source File

SOURCE=.\DMxml.cpp
# End Source File
# Begin Source File

SOURCE=.\DMZones.cpp
# End Source File
# Begin Source File

SOURCE=.\DreamJournal.cpp
# End Source File
# Begin Source File

SOURCE=.\DreamRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpatXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\ownerinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Unicode.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLWriter.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DMDescription.h
# End Source File
# Begin Source File

SOURCE=.\DMMapLayer.h
# End Source File
# Begin Source File

SOURCE=.\DMPlace.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\DMPlaceListV.h
# End Source File
# Begin Source File

SOURCE=.\DMxml.h
# End Source File
# Begin Source File

SOURCE=.\DMZones.h
# End Source File
# Begin Source File

SOURCE=.\DreamJournal.h
# End Source File
# Begin Source File

SOURCE=.\DreamRecord.h
# End Source File
# Begin Source File

SOURCE=.\ExpatXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\IDreamList.h
# End Source File
# Begin Source File

SOURCE=.\IDreamRecord.h
# End Source File
# Begin Source File

SOURCE=.\IDreams.h
# End Source File
# Begin Source File

SOURCE=.\IMapLayer.h
# End Source File
# Begin Source File

SOURCE=.\IPlace.h
# End Source File
# Begin Source File

SOURCE=.\IPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\IZoneList.h
# End Source File
# Begin Source File

SOURCE=.\ownerinfo.h
# End Source File
# Begin Source File

SOURCE=.\Unicode.h
# End Source File
# Begin Source File

SOURCE=.\XMLWriter.h
# End Source File
# End Group
# End Target
# End Project
