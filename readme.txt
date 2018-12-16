################################################################
#
#  Project:      EvoDeMo - Bachelor Thesis
#  Date:         May 10, 2010 (estimated)
##
#  Author:       Martin Balaz
#  Contact:      balaz.marti@gmail.com
#                xbalaz00@stud.fit.vutbr.cz
##
#  Institution:  Brno University of Technology
#                Faculty of Information Technology
#                www.fit.vutbr.cz
##
#  Copyright (c) 2010 by Martin Balaz
#
################################################################

INFORMATION:


  CVT FIT BUT Brno (Linux system):

    For compiling application EvoDeMo in CVT FIT BUT Brno (http://www.fit.vutbr.cz/CVT/index.php)
    just run script "install-cvt.sh" which sets system enviroment up and starts compilation.
    Binary release of compiled application will be located in /EvoDeMo/bin/ folder.

    Note that given script was created JUST for GNU/Linux enviroment. If you decide to compile
    under Windows systems, please read whole this file. It will give you informations how to
    proceed in this case.

====

  Other enviroments:

    If you decide not to use given script or you are not compiling this application in
    CVT FIT BUT Brno, you will use "Makefile" given in same folder as this readme file.
    In this case you should read informations about prerequisities needed for compilation,
    installing Qt and setting up system enviroment which are provided in next few lines.




================================
================================
PREREQUISITIES:


  Qt Framework 4.6 or higher
  GCC Compiler 4.4 or higher


  Ideal solution is to download and install Qt from this site:
  http://qt.nokia.com/downloads

  You can choose to download:
    "Qt SDK"
    "Qt Framework Only"
  These two packages contains all you will need to compile and run this application.

  Direct links:
    Windows:
      SDK:        http://qt.nokia.com/downloads/sdk-windows-cpp
      Framework:  http://qt.nokia.com/downloads/windows-cpp

    Linux/X11:
      SDK:        http://qt.nokia.com/downloads/sdk-linux-x11-32bit-cpp
                  http://qt.nokia.com/downloads/sdk-linux-x11-64bit-cpp
      Framework:  http://qt.nokia.com/downloads/linux-x11-cpp

      You can also use Linux package manager to download and install Qt SDK/Framework
      (if available on your platform).

    Note, that other platforms was NOT TESTED.




================================
================================
INSTALLING Qt (Windows):


  Both given links contain installers, so just download SDK or Framework
  package and run installer.

  If you have any problems, this links will be helpful for you:

  http://doc.qt.nokia.com/4.6/requirements-win.html
  http://doc.qt.nokia.com/4.6/install-win.html


================================
SETTING UP ENVIROMENT (Windows):


  Qt and GCC/Mingw must be correctly installed and set up.
  It is required to add these strings into Windows system variable PATH
  in EXACTLY this sequence:

    $(QT_INSTALL_FOLDER)mingw\bin
    $(QT_INSTALL_FOLDER)qt\bin
    $(QT_INSTALL_FOLDER)bin

    Example: $(QT_INSTALL_FOLDER) = C:\Qt\2009.05\


  Application requires these dynamic link libraries:

    Folder $(QT_INSTALL_FOLDER)mingw\bin

      libgcc_s_dw2-1.dll
      mingwm10.dll

    Folder $(QT_INSTALL_FOLDER)qt\bin

      QtCore4.dll
      QtGui4.dll

      IMPORTANT:

        These two dlls MUST be from folder "$(QT_INSTALL_FOLDER)qt\bin"
        There are second copies of these Qt dlls in "$(QT_INSTALL_FOLDER)bin",
        but application DOES NOT WORK with dlls FROM THIS LOCATION (!!!)




================================
================================
INSTALLING Qt (Linux):


  Note that if you decide to download Linux Framework package from link
  given above, you will download source codes (Linux only), so you must
  compile them: http://doc.trolltech.com/4.6/install-x11.html

  SDK packages are distributed as binary installers, so just download one
  of them and run installer.

  If you have any problems, this links will be helpful for you:

  http://doc.qt.nokia.com/4.6/requirements-x11.html
  http://doc.trolltech.com/4.6/install-x11.html


================================
SETTING UP ENVIROMENT (Linux):


  Qt and GCC/Mingw must be correctly installed and set up.
  Point 4 of this page will tell you, how to set up enviroment on Linux system:

  http://doc.trolltech.com/4.6/install-x11.html




================================
================================
COMPILINING APPLICATION:


  After you correctly install Qt and MinGW/G++ you can compile source codes
  of EvoDeMo into runable binary.

  First of all you must locate file "Makefile" in /EvoDeMo/ folder (same folder as this readme file).
  Then set up this path in your Terminal (Linux) or Command Line (Windows).
  Typing "make" will start compilation of application EvoDeMo on your system.
  After compiling is done, you can find your binary release of EvoDeMo in
  /EvoDeMo/bin/ folder.




================================
================================
RUNNING APPLICATION:


  Just run binary file EvoDeMo (Linux) respectively EvoDeMo.exe (Windows).


