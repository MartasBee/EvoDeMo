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

#ifndef EXPORTCONFIG_H
#define EXPORTCONFIG_H

//==============================================================

#include <QXmlStreamWriter>
#include <QString>
#include <QFile>

#include <iostream>

#include "gui/WidgetInput.h"
#include "gui/WidgetOutput.h"
#include "gui/WidgetEvolution.h"
#include "gui/WidgetExport.h"

//==============================================================

#define EXPORT_CONFIG_OK                   0
#define EXPORT_CONFIG_ERR_UNKNOWN         -1
#define EXPORT_CONFIG_ERR_NULL_POINTER    -2

//==============================================================
/**
 *  exports run config
 */

class CExportConfig
{
public:
  CExportConfig();
  ~CExportConfig();


  // export fc
  bool ExportConfig(QString          filePathName,
                    CWidgetInput     *widIn,
                    CWidgetOutput    *widOut,
                    CWidgetEvolution *widEvo,
                    CWidgetExport    *widExp);


  // get errors
  int GetErrorFlag();

private:
  QXmlStreamWriter xml;   //!< xml writer
  QIODevice *device;      //!< io device - opened file descriptor - for xml class


  int iErrFlag;           //!< error flag


  // doc writing fcs
  void WriteDocStart();
  void WriteDocEnd();

  void WriteSettingsInput(CWidgetInput *widIn);
  void WriteSettingsOutput(CWidgetOutput *widOut);
  void WriteSettingsEvolution(CWidgetEvolution *widEvo);
  void WriteSettingsExport(CWidgetExport *widExp);
  void WriteSettingsInputCASpace(CWidgetInput *widIn);


  // file descriptor setting-er
  void SetIODevice(QIODevice *device);
};

//==============================================================

#endif // EXPORTCONFIG_H

//==============================================================

