; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DMJournal.h"
LastPage=0

ClassCount=25
Class1=CDMJournalApp
Class2=CDMJournalDoc
Class3=CDMJournalView
Class4=CMainFrame

ResourceCount=38
Resource1=IDD_TESTDLG
Resource2=IDD_PLACEEDIT (Russian)
Resource3=IDR_DREAMBAR
Resource4=IDD_LAYERBAR (Russian)
Class5=CAboutDlg
Class6=CDMJournalListView
Class7=CDMDreamEdit
Resource5=IDD_ABOUTBOX (Russian)
Resource6=IDD_DREAMEDIT2 (Russian)
Resource7=IDR_MAPTOOLBAR_SM
Resource8=IDR_DREAMBAR_SM
Class8=CDMDreamEdit3
Resource9=IDD_DREAMBAR (Russian)
Resource10=IDD_PLACEEDIT
Resource11=IDR_DMLIST (Russian)
Resource12=IDR_DREAMTOOLBAR (Russian)
Class9=CDMDreamEdit866
Class10=CDMDescriptionPage
Class11=CDMDreamEdit2
Resource13=IDR_MAPTOOLBAR_SM (Russian)
Class12=CDMDreamPage
Resource14=IDR_DREAM (Russian)
Class13=CDMDreamBar
Resource15=IDD_DREAM (Russian)
Resource16=IDR_DMLIST
Resource17=IDD_DREAMEDIT (Russian)
Resource18=IDR_MAP
Resource19=IDR_MAINFRAME (Russian)
Class14=CDMPlaceListCtrl
Class15=CDMPlaceListBox
Class16=COwnerDrawListBox
Class17=CDMPlaceListPage
Resource20=IDR_DREAMBAR (Russian)
Class18=CDMPlacePage
Class19=CPlaceEdit
Class20=CDMPlaceEdit
Resource21=IDR_MAPTOOLBAR (Russian)
Resource22=IDR_MAINFRAME_SM
Class21=CDMMapView
Resource23=IDD_PLACELIST2 (Russian)
Resource24=IDD_DREAM
Resource25=IDD_LAYERBAR
Resource26=IDD_PLACELIST
Resource27=IDD_DESCRIPTION
Resource28=IDR_MAP (Russian)
Resource29=IDR_DREAMBAR_SM (Russian)
Resource30=IDD_PLACELIST (Russian)
Class22=CLayerBar
Resource31=IDD_PLACELIST2
Resource32=IDD_ABOUTBOX
Resource33=IDR_MAPTOOLBAR
Resource34=IDR_DREAMTOOLBAR
Class23=CZoneEdit
Resource35=IDR_MAINFRAME (English (U.S.))
Class24=CDMPlaceListSm
Resource36=IDD_DESCRIPTION (Russian)
Resource37=IDR_MAINFRAME_SM (Russian)
Class25=CSplashWnd
Resource38=IDR_MAINFRAME

[CLS:CDMJournalApp]
Type=0
HeaderFile=DMJournal.h
ImplementationFile=DMJournal.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDMJournalDoc]
Type=0
HeaderFile=DMJournalDoc.h
ImplementationFile=DMJournalDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDMJournalView]
Type=0
HeaderFile=DMJournalView.h
ImplementationFile=DMJournalView.cpp
Filter=W
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=DMJournal.cpp
ImplementationFile=DMJournal.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUILD_NUM

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=2
Control1=IDC_SPLASH,static,1342177294
Control2=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=IDM_SAVEXML
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=IDM_NEW
Command9=IDM_DVIEW
Command10=IDM_DELETE
Command11=IDM_ZOOMIN
Command12=IDM_ZOOMOUT
Command13=IDM_NEWZONE
Command14=IDM_ZONEEDITR
Command15=IDM_NEWPLACE
Command16=ID_VIEW_TOOLBAR
Command17=IDW_DREAMBAR
Command18=IDW_MAPBAR
Command19=IDW_LAYERBAR
Command20=IDW_DIALOGBAR
Command21=ID_VIEW_STATUS_BAR
Command22=IDM_BIGICONS
Command23=IDM_GRIDONOFF
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_ZOOMIN
Command4=IDM_NEWPLACE
Command5=IDM_GRIDONOFF
Command6=ID_FILE_NEW
Command7=ID_FILE_OPEN
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=IDM_ZOOMIN
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=IDM_NEW
Command18=IDM_ZOOMOUT
Command19=IDM_TAB
Command20=ID_EDIT_CUT
Command21=IDM_NEWZONE
Command22=ID_EDIT_UNDO
CommandCount=22

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_ZOOMIN
Command4=IDM_NEWPLACE
Command5=IDM_GRIDONOFF
Command6=ID_FILE_NEW
Command7=ID_FILE_OPEN
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=IDM_ZOOMIN
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=IDM_NEW
Command18=IDM_ZOOMOUT
Command19=IDM_TAB
Command20=ID_EDIT_CUT
Command21=IDM_NEWZONE
Command22=ID_EDIT_UNDO
CommandCount=22

[DLG:IDR_MAINFRAME]
Type=1
Class=CMainFrame
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342178052

[CLS:CDMJournalListView]
Type=0
HeaderFile=DMJournalListView.h
ImplementationFile=DMJournalListView.cpp
BaseClass=CListView
Filter=C
VirtualFilter=VWC

[CLS:CDMDreamEdit]
Type=0
HeaderFile=DMDreamEdit.h
ImplementationFile=DMDreamEdit.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CDMDreamEdit

[DLG:IDD_DREAMEDIT (Russian)]
Type=1
Class=CDMDreamEdit
ControlCount=13
Control1=IDC_TYPE,combobox,1344339970
Control2=IDC_DATE,SysDateTimePick32,1342242848
Control3=IDC_TITLE,edit,1350631552
Control4=IDC_DESCRIPTION,edit,1352732740
Control5=IDC_COMMENT,edit,1352732740
Control6=IDC_APPLY,button,1342242817
Control7=IDC_CANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_NEW,button,1342242816

[MNU:IDR_DMLIST (Russian)]
Type=1
Class=?
Command1=IDM_DVIEW
Command2=IDM_NEW
Command3=IDM_DELETE
CommandCount=3

[MNU:IDR_DMLIST]
Type=1
Class=?
Command1=IDM_DVIEW
Command2=IDM_NEW
Command3=IDM_DELETE
CommandCount=3

[DLG:IDD_TESTDLG]
Type=1
Class=CDMDreamEdit3
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342177280

[DLG:IDD_DESCRIPTION]
Type=1
Class=CDMDescriptionPage
ControlCount=1
Control1=IDC_DESCRIPTION,edit,1352732676

[CLS:CDMDreamEdit3]
Type=0
HeaderFile=DMDreamEdit2.h
ImplementationFile=DMDreamEdit2.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC

[DLG:IDD_ABOUTBOX (Russian)]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177294
Control2=IDOK,button,1342373889
Control3=IDC_BUILD_NUM,edit,1350633605

[DLG:IDR_MAINFRAME (Russian)]
Type=1
Class=CMainFrame
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342178052

[DLG:IDD_DESCRIPTION (Russian)]
Type=1
Class=CDMDescriptionPage
ControlCount=1
Control1=IDC_DESCRIPTION,edit,1352732676

[DLG:IDD_DREAMEDIT2 (Russian)]
Type=1
Class=CDMPlaceListSm
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342177280

[CLS:CDMDreamEdit866]
Type=0
HeaderFile=DMDreamEdit2.h
ImplementationFile=DMDreamEdit2.cpp
BaseClass=CPropertySheet
Filter=W

[CLS:CDMDescriptionPage]
Type=0
HeaderFile=DMDescriptionPage1.h
ImplementationFile=DMDescriptionPage1.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDMDescriptionPage
VirtualFilter=idWC

[CLS:CDMDreamEdit2]
Type=0
HeaderFile=DMDreamEdit2.h
ImplementationFile=DMDreamEdit2.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC

[DLG:IDD_DREAM (Russian)]
Type=1
Class=CDMDreamPage
ControlCount=6
Control1=IDC_TYPE,combobox,1344339970
Control2=IDC_DATE,SysDateTimePick32,1342242816
Control3=IDC_TITLE,edit,1350631552
Control4=IDC_CAPT,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDMDreamPage]
Type=0
HeaderFile=DMDreamPage.h
ImplementationFile=DMDreamPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_DATE

[CLS:CDMDreamBar]
Type=0
HeaderFile=DMDreamBar.h
ImplementationFile=DMDreamBar.cpp
BaseClass=CDialog
Filter=D
LastObject=CDMDreamBar
VirtualFilter=dWC

[DLG:IDD_DREAMBAR (Russian)]
Type=1
Class=CDMDreamBar
ControlCount=7
Control1=IDC_SAVE,button,1342242817
Control2=IDC_CANCEL,button,1342242816
Control3=IDC_NEW,button,1342242816
Control4=IDC_FIRST,button,1342242816
Control5=IDC_PREV,button,1342242816
Control6=IDC_NEXT,button,1342242816
Control7=IDC_LAST,button,1342242816

[TB:IDR_DREAMTOOLBAR (Russian)]
Type=1
Class=?
Command1=ID_BUTTONSAVE
Command2=ID_BUTTONCANCEL
Command3=ID_BUTTONNEW
Command4=ID_BUTTONDELETE
Command5=ID_BUTTONFIRST
Command6=ID_BUTTONPREV
Command7=ID_BUTTONNEXT
Command8=ID_BUTTONLAST
CommandCount=8

[DLG:IDD_DREAM]
Type=1
Class=CDMDreamPage
ControlCount=6
Control1=IDC_TYPE,combobox,1344339970
Control2=IDC_DATE,SysDateTimePick32,1342242816
Control3=IDC_TITLE,edit,1350631552
Control4=IDC_CAPT,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDMPlaceListCtrl]
Type=0
HeaderFile=DMPlaceListCtrl.h
ImplementationFile=DMPlaceListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC

[CLS:CDMPlaceListBox]
Type=0
HeaderFile=DMPlaceListBox.h
ImplementationFile=DMPlaceListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC

[CLS:COwnerDrawListBox]
Type=0
HeaderFile=OwnList.h
ImplementationFile=OwnList.cpp
BaseClass=CListBox

[DLG:IDD_PLACELIST (Russian)]
Type=1
Class=CDMPlaceListPage
ControlCount=5
Control1=IDC_LIST,SysListView32,1350638593
Control2=IDC_ADD,button,1342242880
Control3=IDC_DELETE,button,1342242880
Control4=IDC_GLOBALLIST,combobox,1344341315
Control5=IDC_NEW,button,1342242880

[CLS:CDMPlaceListPage]
Type=0
HeaderFile=DMPlaceListPage.h
ImplementationFile=DMPlaceListPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_ADD
VirtualFilter=idWC

[DLG:IDD_PLACEEDIT (Russian)]
Type=1
Class=CDMPlacePage
ControlCount=4
Control1=IDC_TITLETEXT,static,1342308352
Control2=IDC_TITLE,edit,1350631552
Control3=IDC_COLOR,button,1342275595
Control4=IDC_STATIC,static,1342308352

[CLS:CDMPlacePage]
Type=0
HeaderFile=DMPlacePage.h
ImplementationFile=DMPlacePage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_COLOR

[CLS:CPlaceEdit]
Type=0
HeaderFile=PlaceEdit.h
ImplementationFile=PlaceEdit.cpp
BaseClass=CPropertySheet
Filter=W

[CLS:CDMPlaceEdit]
Type=0
HeaderFile=DMPlaceEdit.h
ImplementationFile=DMPlaceEdit.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC

[DLG:IDD_PLACELIST]
Type=1
Class=CDMPlaceListPage
ControlCount=5
Control1=IDC_LIST,SysListView32,1350638593
Control2=IDC_ADD,button,1342242880
Control3=IDC_DELETE,button,1342242880
Control4=IDC_GLOBALLIST,combobox,1344341315
Control5=IDC_NEW,button,1342242880

[DLG:IDD_PLACEEDIT]
Type=1
Class=CDMPlacePage
ControlCount=4
Control1=IDC_TITLETEXT,static,1342308352
Control2=IDC_TITLE,edit,1350631552
Control3=IDC_COLOR,button,1342275595
Control4=IDC_STATIC,static,1342308352

[CLS:CDMMapView]
Type=0
HeaderFile=DMMapView.h
ImplementationFile=DMMapView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CDMMapView

[MNU:IDR_MAINFRAME (Russian)]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=IDM_SAVEXML
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=IDM_NEW
Command9=IDM_DVIEW
Command10=IDM_DELETE
Command11=IDM_ZOOMIN
Command12=IDM_ZOOMOUT
Command13=IDM_NEWZONE
Command14=IDM_ZONEEDITR
Command15=IDM_NEWPLACE
Command16=ID_VIEW_TOOLBAR
Command17=IDW_DREAMBAR
Command18=IDW_MAPBAR
Command19=IDW_LAYERBAR
Command20=IDW_DIALOGBAR
Command21=ID_VIEW_STATUS_BAR
Command22=IDM_BIGICONS
Command23=IDM_GRIDONOFF
Command24=ID_APP_ABOUT
CommandCount=24

[TB:IDR_DREAM (Russian)]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_DELETE
CommandCount=2

[TB:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
CommandCount=3

[TB:IDR_MAPTOOLBAR (Russian)]
Type=1
Class=?
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_GRIDONOFF
Command4=IDM_NEWZONE
Command5=IDM_ZONEEDITR
Command6=IDM_NEWPLACE
CommandCount=6

[TB:IDR_DREAMTOOLBAR]
Type=1
Class=?
Command1=ID_BUTTONSAVE
Command2=ID_BUTTONCANCEL
Command3=ID_BUTTONNEW
Command4=ID_BUTTONDELETE
Command5=ID_BUTTONFIRST
Command6=ID_BUTTONPREV
Command7=ID_BUTTONNEXT
Command8=ID_BUTTONLAST
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
CommandCount=3

[TB:IDR_MAPTOOLBAR]
Type=1
Class=?
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_GRIDONOFF
Command4=IDM_NEWZONE
Command5=IDM_ZONEEDITR
Command6=IDM_NEWPLACE
CommandCount=6

[MNU:IDR_MAP]
Type=1
Class=CDMMapView
Command1=IDM_VIEWPLACE
Command2=IDM_MOVEPLACE
Command3=IDM_DELETEPLACE
Command4=IDM_SETZONE
Command5=IDM_NEWZONE
Command6=IDM_DELZONE
Command7=IDM_ZONEEDITR
CommandCount=7

[TB:IDR_DREAMBAR]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_DELETE
CommandCount=2

[MNU:IDR_MAP (Russian)]
Type=1
Class=CDMMapView
Command1=IDM_VIEWPLACE
Command2=IDM_MOVEPLACE
Command3=IDM_DELETEPLACE
Command4=IDM_SETZONE
Command5=IDM_NEWZONE
Command6=IDM_DELZONE
Command7=IDM_ZONEEDITR
CommandCount=7

[TB:IDR_DREAMBAR (Russian)]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_DELETE
CommandCount=2

[DLG:IDD_LAYERBAR (Russian)]
Type=1
Class=CLayerBar
ControlCount=1
Control1=IDC_LIST,combobox,1344339971

[CLS:CLayerBar]
Type=0
HeaderFile=LayerBar.h
ImplementationFile=LayerBar.cpp
BaseClass=CDialogBar
Filter=D
LastObject=CLayerBar
VirtualFilter=dWC

[DLG:IDD_LAYERBAR]
Type=1
Class=CLayerBar
ControlCount=1
Control1=IDC_LIST,combobox,1344339971

[TB:IDR_DREAMBAR_SM]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_DELETE
CommandCount=2

[TB:IDR_MAINFRAME_SM]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
CommandCount=3

[TB:IDR_MAPTOOLBAR_SM]
Type=1
Class=?
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_GRIDONOFF
Command4=IDM_NEWZONE
Command5=IDM_ZONEEDITR
Command6=IDM_NEWPLACE
CommandCount=6

[CLS:CZoneEdit]
Type=0
HeaderFile=ZoneEdit.h
ImplementationFile=ZoneEdit.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC

[DLG:IDD_PLACELIST2]
Type=1
Class=CDMPlaceListSm
ControlCount=1
Control1=IDC_LIST,SysListView32,1350636545

[CLS:CDMPlaceListSm]
Type=0
HeaderFile=DMPlaceListSm.h
ImplementationFile=DMPlaceListSm.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDM_SETZONE

[DLG:IDD_PLACELIST2 (Russian)]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST,SysListView32,1350636545

[TB:IDR_DREAMBAR_SM (Russian)]
Type=1
Class=?
Command1=IDM_NEW
Command2=IDM_DELETE
CommandCount=2

[TB:IDR_MAINFRAME_SM (Russian)]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
CommandCount=3

[TB:IDR_MAPTOOLBAR_SM (Russian)]
Type=1
Class=?
Command1=IDM_ZOOMIN
Command2=IDM_ZOOMOUT
Command3=IDM_GRIDONOFF
Command4=IDM_NEWZONE
Command5=IDM_ZONEEDITR
Command6=IDM_NEWPLACE
CommandCount=6

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

