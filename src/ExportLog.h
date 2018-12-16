/*
 *  Project:      EvoDeMo - Bachelor Thesis
 *  Date:         May 10, 2010 (estimated)
 **
 *  Author:       Martin Balaz
 *  Contact:      balaz.marti@gmail.com
 *                xbalaz00@stud.fit.vutbr.cz
 **
 *  Institution:  Brno University of Technology
 *                Faculty of Information Technology
 *                www.fit.vutbr.cz
 **
 *  Copyright (c) 2010 by Martin Balaz
 */

//==============================================================

#ifndef EXPORTLOG_H
#define EXPORTLOG_H

//==============================================================

#include <string>
#include <iostream>

#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

#include "Defines.h"

//==============================================================
/**
 *  this class exports logs from CORE part of application into txt file
 *  it is used just as ONE instance, created in CThreadCore (i hope there)
 *  and pointer to this instance is send to all core classes
 *
 *  is used for exporting error and warning strings into file or messagebox
 */

class CExportLog
{
public:
  CExportLog();
  ~CExportLog();


  // setting functions
  void SetFilePath(QString path);
  void SetFileName(QString name);


  // file open/close fc
  bool OpenLogFile();
  void CloseLogFile();


  // write INFO into file
  void WriteInfoLog(QString info);


  // write ERROR into file
  void WriteErrorLog(int errId);
  void WriteErrorLog(QString error);


  // show message box
  void ShowMessageBox(int errId);
  void ShowMessageBox(QString error);

private:
  QString     filePath;       //!< export path
  QString     fileName;       //!< export file name
  QString     filePathName;   //!< combination of previous two

  QFile       fileDevice;     //!< file descriptor
  QTextStream fileStream;     //!< file writer

  bool bFileOpened;           //!< is file opened?
};

//==============================================================

#endif // EXPORTLOG_H

//==============================================================

