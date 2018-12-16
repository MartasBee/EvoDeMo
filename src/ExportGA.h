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

#ifndef EXPORTGA_H
#define EXPORTGA_H

//==============================================================

#include <QXmlStreamWriter>
#include <QString>
#include <QFile>

#include "ConfigCore.h"
#include "ga/Genome.h"

//==============================================================
/**
 *  this class exports ga genomes or whole population of genomes
 *  into xml files, which can be imported later into app by CImportGA class
 */

class CExportGA
{
public:
  CExportGA();


  // export fcs
  void ExportGeneration(QString fileName, std::vector<CGenome*> *gen);
  void ExportChromosome(QString fileName, CGenome *gen);


  // settings fc
  void SetConfigCore(CConfigCore *cCore);


  // get errors
  int GetErrorFlag();

private:
  QXmlStreamWriter xml;   //!< xml writer
  QIODevice *device;      //!< io device - opened file descriptor - for xml class

  CConfigCore *config;    //!< pointer to config class

  int iErrFlag;           //!< error flag


  // doc writing fcs
  void WriteDocStart();
  void WriteDocEnd();
  void WriteGenome(CGenome *genome);


  // file descriptor setting-er
  void SetIODevice(QIODevice *device);
};

//==============================================================

#endif // EXPORTGA_H

//==============================================================

