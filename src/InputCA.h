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

#ifndef INPUTCA_H
#define INPUTCA_H

//==============================================================

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QFile>

#include "ConfigCore.h"

//==============================================================
/**
 *  class will be (maybe) used for export/import init CA space
 *  to xml file
 *
 *  this functionality is actually cover by CWindowMain and png files
 */

class CInputCA
{
public:
  CInputCA();


  // import / export fcs
  bool ImportCA(QString fileName);
  bool ExportCA(QString fileName);


  // setting fcs
  void SetConfigCore(CConfigCore *cCore);


  // errors fc
  int GetErrorFlag();

private:
  QXmlStreamWriter xmlW;  //!< instance of xml writer class
  QXmlStreamReader xmlR;  //!< instance of xml reader class
  QIODevice *device;      //!< io device - opened file descriptor - for xml class

  CConfigCore *config;    //!< pointer to config class

  int iErrFlag;           //!< error flag
};

//==============================================================

#endif // INPUTCA_H

//==============================================================

