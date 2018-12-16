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

#ifndef EXPORTCA_H
#define EXPORTCA_H

//==============================================================

#include <QImage>
#include <QString>

#include "ca/space/Space.h"
#include "ConfigCore.h"
#include "Defines.h"

//==============================================================
/**
 *  this class exports ca space
 *  it has two modes - standard, which makes 10x zoom on exported images
 *  and input, which is used for exporting input ca space from gui settings tab,
 *  this mode does not used zoom, because input png should be imported into app later
 */

class CExportCA
{
public:
  CExportCA();


  // export fcs
  void ExportCellularAutomaton(QString fileName, CSpace *space);
  void ExportCellularAutomatonInput(QString fileName, CSpace *space);


  // settings fc
  void SetConfigCore(CConfigCore *cCore);


  // get errors
  int GetErrorFlag();

private:
  CConfigCore *config;  //!< pointer to config class

  int iErrFlag;         //!< error flag
};

//==============================================================

#endif // EXPORTCA_H

//==============================================================

