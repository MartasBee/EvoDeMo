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

#include "ExportGA.h"

//==============================================================
/**
 *  class constructor
 */

CExportGA::CExportGA()
{
  config = NULL;
  device = NULL;

  iErrFlag = EXPORT_GA_OK;
}

//==============================================================
//==============================================================
/**
 *  exports one generation of whole population
 *
 *  @param fileName     file path/name
 *  @param *vecGen      pointer to population of genomes
 */

void CExportGA::ExportGeneration(QString fileName, std::vector<CGenome *> *vecGen)
{
  if((config == NULL) || (vecGen == NULL))
  {
    {
      std::string msgErr  = "Class:    CExportGA\n";
      msgErr += "Function: ExportGeneration()\n";
      msgErr += "Pointer to CConfigCore or std::vector<CGenome*> is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_POINTER_NULL;
    return;
  }

  CGenome *genome = NULL;

  // open file
  QFile file(fileName);
  if(!file.open(QFile::WriteOnly | QFile::Text))
  {
    {
      std::string msgErr  = "Class:    CExportGA\n";
      msgErr += "Function: ExportGeneration()\n";
      msgErr += "Unable to open export file";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_UNKNOWN;
    return;
  }
  else
    SetIODevice(&file);


  // export xml
  WriteDocStart();
  for(unsigned int i = 0; i < vecGen->size(); i++)
  {
    genome = vecGen->at(i);
    WriteGenome(genome);
  }
  WriteDocEnd();


  // close file
  file.close();
}

//==============================================================
/**
 *  exports one genome
 *
 *  @param fileName     file path/name
 *  @param *gen         pointer to genome
 */

void CExportGA::ExportChromosome(QString fileName, CGenome *gen)
{
  if((config == NULL) || (gen == NULL))
  {
    {
      std::string msgErr  = "Class:    CExportGA\n";
      msgErr += "Function: ExportChromosome()\n";
      msgErr += "Pointer to CConfigCore or CGenome is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_POINTER_NULL;
    return;
  }

  // open file
  QFile file(fileName);
  if(!file.open(QFile::WriteOnly | QFile::Text))
  {
    {
      std::string msgErr  = "Class:    CExportGA\n";
      msgErr += "Function: ExportGeneration()\n";
      msgErr += "Unable to open export file";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_UNKNOWN;
    return;
  }
  else
    SetIODevice(&file);


  // export xml
  WriteDocStart();
  WriteGenome(gen);
  WriteDocEnd();


  // close file
  file.close();
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CExportGA::SetConfigCore(CConfigCore *cCore)
{
  config = cCore;
}

//==============================================================
/**
 *  sets IO device (opened file descriptor) into xml class
 *
 *  @param *device      opened file descriptor
 */

void CExportGA::SetIODevice(QIODevice *device)
{
  this->device = device;

  xml.setDevice(this->device);
  xml.setAutoFormatting(true);
  xml.setAutoFormattingIndent(2);
}

//==============================================================
/**
 *  returns error flag
 */

int CExportGA::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  writes doc start
 *  doc type
 *  genome type
 */

void CExportGA::WriteDocStart()
{
  xml.writeStartDocument();
  xml.writeDTD("<!DOCTYPE evodemo_ga_xml_export>");

  xml.writeStartElement("ga_genomes");
  if(config->GetGenomeType() == GENOME_TYPE_2_9N)
    xml.writeAttribute("type","29");
  else if(config->GetGenomeType() == GENOME_TYPE_3_9N)
    xml.writeAttribute("type","39");
  else if(config->GetGenomeType() == GENOME_TYPE_4_9N)
    xml.writeAttribute("type","49");
  else if(config->GetGenomeType() == GENOME_TYPE_2_5N)
    xml.writeAttribute("type","25");
  else if(config->GetGenomeType() == GENOME_TYPE_3_5N)
    xml.writeAttribute("type","35");
  else if(config->GetGenomeType() == GENOME_TYPE_4_5N)
    xml.writeAttribute("type","45");
  /*
  else if(config->GetGenomeType() == GENOME_TYPE_2_INS)
    xml.writeAttribute("type","21");
  else if(config->GetGenomeType() == GENOME_TYPE_3_INS)
    xml.writeAttribute("type","31");
  else if(config->GetGenomeType() == GENOME_TYPE_4_INS)
    xml.writeAttribute("type","41");
  */
  else
    xml.writeAttribute("type","0");
}

//==============================================================
/**
 *  writes doc end (closing elements)
 */

void CExportGA::WriteDocEnd()
{
  xml.writeEndElement();  // ga_genomes

  xml.writeEndDocument();
}

//==============================================================
/**
 *  writes one genome into file
 *
 *  @param *genome      pointer to genome class to be exported
 */

void CExportGA::WriteGenome(CGenome *genome)
{
  if(genome == NULL)
  {
    {
      std::string msgErr  = "Class:    CExportGA\n";
      msgErr += "Function: WriteGenome()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_UNKNOWN;
    return;
  }

  QString tmp = "";
  int i       = 0;
  int iMax    = 0;

  // get and set genome length
  if(config->GetGenomeType() == GENOME_TYPE_2_9N)
    iMax = GENOME_SIZE_TYPE_2_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_3_9N)
    iMax = GENOME_SIZE_TYPE_3_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_4_9N)
    iMax = GENOME_SIZE_TYPE_4_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_2_5N)
    iMax = GENOME_SIZE_TYPE_2_5N;
  else if(config->GetGenomeType() == GENOME_TYPE_3_5N)
    iMax = GENOME_SIZE_TYPE_3_5N;
  else if(config->GetGenomeType() == GENOME_TYPE_4_5N)
    iMax = GENOME_SIZE_TYPE_4_5N;
  /*
  else if(config->GetGenomeType() == GENOME_TYPE_2_INS)
    iMax = GENOME_SIZE_TYPE_2_INS;
  else if(config->GetGenomeType() == GENOME_TYPE_3_INS)
    iMax = GENOME_SIZE_TYPE_3_INS;
  else if(config->GetGenomeType() == GENOME_TYPE_4_INS)
    iMax = GENOME_SIZE_TYPE_4_INS;
  */
  else
    iMax = GENOME_SIZE_TYPE_2_9N;


  // export statistical data:

  xml.writeStartElement("chromosome");
  xml.writeAttribute("generation",QString("%1").arg(genome->GetThisGenerationId()));
  xml.writeAttribute("id",QString("%1").arg(genome->GetThisGenomeId()));
  xml.writeAttribute("ancestors",QString("%1").arg(genome->GetAncestorsCount()));

  xml.writeEmptyElement("chromosome_init");
  xml.writeAttribute("generation",QString("%1").arg(genome->GetThisInitGenerationId()));
  xml.writeAttribute("id",QString("%1").arg(genome->GetThisInitGenomeId()));

  xml.writeEmptyElement("chromosome_parent");
  xml.writeAttribute("generation",QString("%1").arg(genome->GetParentGenerationId()));
  xml.writeAttribute("id",QString("%1").arg(genome->GetParentGenomeId()));

  xml.writeEmptyElement("fitness_max");
  xml.writeAttribute("value",QString("%1").arg(genome->GetFitnessMax()));
  xml.writeAttribute("norm",QString("%1").arg(genome->GetFitnessMaxNorm()));
  xml.writeAttribute("diff_min",QString("%1").arg(genome->GetDifferentionMin()));
  xml.writeAttribute("ca_step",QString("%1").arg(genome->GetFitnessMaxStepCA()));

  xml.writeEmptyElement("mutated_genes");
  xml.writeAttribute("total",QString("%1").arg(genome->GetMutatedGenesTotal()));
  xml.writeAttribute("total_all_ancestors",QString("%1").arg(genome->GetMutatedGenesAllAncestors()));

  xml.writeStartElement("data");

  tmp = "\n";

  // export genes:
  // 0302 1000 0300 1002 0020
  // 1001 1010 0110 0001 1020
  // etc.
  while(i < iMax)
  {
    for(int j = 0; j < 4; j++)
    {
      for(int k = 0; k < 4; k++)
      {
        if(i < iMax)
        {
          if(genome->GetGene(i) == 0)
            tmp += "0";
          else if(genome->GetGene(i) == 1)
            tmp += "1";
          else if(genome->GetGene(i) == 2)
            tmp += "2";
          else if(genome->GetGene(i) == 3)
            tmp += "3";
          else
            tmp += QString("%1").arg((int)genome->GetGene(i));
        }
        i += 1;
      }
      tmp += " ";
    }
    tmp += "\n";

    xml.writeCharacters(tmp);

    tmp = "";
  }

  xml.writeEndElement();  // "data"
  xml.writeEndElement();  // "chromosome"
}

//==============================================================

