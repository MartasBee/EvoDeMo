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

#ifndef IMPORTCONFIG_H
#define IMPORTCONFIG_H

//==============================================================

#include <QXmlStreamReader>
#include <QString>
#include <QFile>

#include <iostream>

#include "gui/WidgetInput.h"
#include "gui/WidgetOutput.h"
#include "gui/WidgetEvolution.h"
#include "gui/WidgetExport.h"

//==============================================================

#define IMPORT_CONFIG_OK                         0
#define IMPORT_CONFIG_ERR_UNKNOWN               -1
#define IMPORT_CONFIG_ERR_NULL_POINTER          -2
#define IMPORT_CONFIG_ERR_UNCOMPATIBILE_CONFIG  -3
#define IMPORT_CONFIG_ERR_EMPTY_FILE            -4
#define IMPORT_CONFIG_ERR_XML_PARSE             -5
#define IMPORT_CONFIG_ERR_EOF_NOT_FOUND         -6

//==============================================================
/**
 *  imports app's configuration from extern file
 */

class CImportConfig
{
public:
  CImportConfig();


  // import config
  void ImportConfig(QString          fileName,
                    CWidgetInput     *widIn,
                    CWidgetOutput    *widOut,
                    CWidgetEvolution *widEvo,
                    CWidgetExport    *widExp);


  // get errors
  int GetErrorFlag();

private:
  QXmlStreamReader xml;   //!< xml reader
  QIODevice *device;      //!< io device - opened file descriptor - for xml class


  int iErrFlag;           //!< error flag


  // doc reading fcs
  bool ReadDocStart();
  void ReadDocEnd();

  void ReadSettingsInput(CWidgetInput *widIn);
  void ReadSettingsOutput(CWidgetOutput *widOut);
  void ReadSettingsEvolution(CWidgetEvolution *widEvo);
  void ReadSettingsExport(CWidgetExport *widExp);
  void ReadSettingsInputCASpace(CWidgetInput *widIn);


  // file descriptor setting-er
  void SetIODevice(QIODevice *device);
};

//==============================================================

#endif // IMPORTCONFIG_H

//==============================================================

