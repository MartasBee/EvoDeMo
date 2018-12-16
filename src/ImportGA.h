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

#ifndef IMPORTGA_H
#define IMPORTGA_H

//==============================================================

#include <QXmlStreamReader>
#include <QString>
#include <QFile>

#include "ConfigCore.h"
#include "ga/Genome.h"

//==============================================================
/**
 *  imports genome from xml file (created by CExportGA class) into
 *  genome (CGenome class)
 */

class CImportGA
{
public:
  CImportGA();


  // import chromosome
  void ImportChromosome(QString fileName, CGenome *gen);


  // settigs
  void SetConfigCore(CConfigCore *cCore);


  // get errors
  int GetErrorFlag();

private:
  QXmlStreamReader xml;   //!< xml reader
  QIODevice *device;      //!< io device - opened file descriptor - for xml class

  CConfigCore *config;    //!< pointer to config class

  int iErrFlag;           //!< error flag


  // doc reading fcs
  bool ReadDocStart();
  void ReadGenome(CGenome *gen);
  void WriteGenesIntoGenome(QString *genes, CGenome *gen);


  // file descriptor setting-er
  void SetIODevice(QIODevice *device);
};

//==============================================================

#endif // IMPORTGA_H

//==============================================================

