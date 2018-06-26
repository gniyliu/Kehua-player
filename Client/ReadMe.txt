========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : MyTest
========================================================================


AppWizard has created this MyTest application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your MyTest application.

MyTest.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

MyTest.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMyTestApp application class.

MyTest.cpp
    This is the main application source file that contains the application
    class CMyTestApp.

MyTest.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

MyTest.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\MyTest.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file MyTest.rc.

res\MyTest.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.

MyTest.reg
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
    file to go along with your application.

MyTest.odl
    This file contains the Object Description Language source code for the
    type library of your application.



/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog class and automation proxy class:

MyTestDlg.h, MyTestDlg.cpp - the dialog
    These files contain your CMyTestDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in MyTest.rc, which can be edited in Microsoft
	Visual C++.

DlgProxy.h, DlgProxy.cpp - the automation object
    These files contain your CMyTestDlgAutoProxy class.  This class
    is called the "automation proxy" class for your dialog, because it
    takes care of exposing the automation methods and properties that
    automation controllers can use to access your dialog.  These methods
    and properties are not exposed from the dialog class directly, because
    in the case of a modal dialog-based MFC application it is cleaner and
    easier to keep the automation object separate from the user interface.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named MyTest.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////


数据发送格式
16个字节位一个包，顺序为从0->F
____0____*	器件名  
____1____*	操作参数1
____2____*	操作参数2
____3____*	操作参数3
____4____*	器件参数1[如地址]
____5____*	器件参数2[如地址]
____6____*	器件参数3[如地址]
____7____*	数据[0]
____8____*	数据[1]
____9____*	数据[2]
____A____*	数据[3]
____B____*	数据[4]
____C____*	数据[5]
____D____*	数据[6]
____E____*	数据[7]
____F____*	校验字节
   

数据返回格式
根据读/写分为两种数据返回格式
[写]
1个字节		
0x55	收到正确数据
0xAA	收到错误数据
[读]
16个字节位一个包，顺序为从0->F
____0____*	0x55	收到正确数据	0xAA	收到错误数据
____1____*	操作参数1
____2____*	操作参数2
____3____*	操作参数3
____4____*	器件参数1[如地址]
____5____*	器件参数2[如地址]
____6____*	器件参数3[如地址]
____7____*	数据[0]
____8____*	数据[1]
____9____*	数据[2]
____A____*	数据[3]
____B____*	数据[4]
____C____*	数据[5]
____D____*	数据[6]
____E____*	数据[7]
____F____*	校验字节

10:21 2006-1-11
发送部分未完成