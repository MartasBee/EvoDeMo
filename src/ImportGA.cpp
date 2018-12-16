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

#include "ImportGA.h"

//==============================================================
/**
 *  class constructor
 */

CImportGA::CImportGA()
{
  device   = NULL;
  config   = NULL;
  iErrFlag = IMPORT_GA_OK;
}

//==============================================================
//==============================================================
/**
 *  function for imprting genome from xml file created by CExportGA class
 *
 *  @param fileName     path/name of file
 *  @param *gen         pointer to genome class (must exists !!) into which data will be write
 */

void CImportGA::ImportChromosome(QString fileName, CGenome *gen)
{
  if((config == NULL) || (gen == NULL))
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ImportChromosome()\n";
      msgErr += "Pointer to CConfigCore or CGenome is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_NULL_POINTER;
    return;
  }

  iErrFlag = IMPORT_GA_OK;

  // open file
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly | QFile::Text))
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ImportChromosome()\n";
      msgErr += "Unable to open file";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_UNKNOWN;
    return;
  }
  else
    // set device for xml classes
    SetIODevice(&file);

  // import chromosome
  if(ReadDocStart())
    ReadGenome(gen);

  xml.clear();
  file.close();
}

//==============================================================
//==============================================================
/**
 *  sets config class
 *
 *  @param *cCore       pointer to config class
 */

void CImportGA::SetConfigCore(CConfigCore *cCore)
{
  config = cCore;
}

//==============================================================
/**
 *  sets IO devide (opened file) in xml class
 *
 *  @param *device      pointer to opened file descriptor
 */

void CImportGA::SetIODevice(QIODevice *device)
{
  this->device = device;

  xml.setDevice(this->device);
}

//==============================================================
/**
 *  returns error flag
 */

int CImportGA::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  read document header for determining if file is compatibile
 *  and if genome is compatibile with user  settings
 */

bool CImportGA::ReadDocStart()
{
  // read 1st element of xml
  if(xml.readNextStartElement())
  {
    if((xml.name() == "ga_genomes") &&
       (xml.attributes().value("type") == QString("%1").arg(config->GetGenomeType())))
    {
      iErrFlag = IMPORT_GA_OK;
      return true;
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportGA\n";
        msgErr += "Function: ReadDocStart()\n";
        msgErr += "Incompatibile CGenome in file";

        if((config != NULL) && (config->GetExportLogCore() != NULL))
          config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_GA_ERR_UNCOMPATIBILE_GENOME;
      return false;
    }
  }
  // empty file
  else
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ReadDocStart()\n";
      msgErr += "File is empty";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_EMPTY_FILE;
    return false;
  }
}

//==============================================================
/**
 *  this function reads genome data from xml
 *
 *  @param *gen         pointer to genome class in which data will be stored
 */

void CImportGA::ReadGenome(CGenome *gen)
{
  int     atrTmp1 = 0;
  int     atrTmp2 = 0;
  int     atrTmp3 = 0;
  double  atrTmp4 = 0.0;
  bool    convOk  = false;
  QString genText = "";

  if(gen == NULL)
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ReadGenome()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_NULL_POINTER;
    return;
  }


  // read 1st element
  if(xml.readNextStartElement())
  {
    if(xml.name() == "chromosome")
    {
      atrTmp1 = xml.attributes().value("generation").toString().toInt(&convOk,10);
      atrTmp2 = xml.attributes().value("id").toString().toInt(&convOk,10);
      atrTmp3 = xml.attributes().value("ancestors").toString().toInt(&convOk,10);

      gen->SetThisGenomeId(atrTmp1,atrTmp2);
      gen->SetAncestorsCount(atrTmp3);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportGA\n";
        msgErr += "Function: ReadGenome()\n";
        msgErr += "Error while parsing xml - unknown tag -> ";
        msgErr += xml.name().toString().toStdString();

        if((config != NULL) && (config->GetExportLogCore() != NULL))
          config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_GA_ERR_XML_PARSE;
      return;
    }
  }
  else
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ReadGenome()\n";
      msgErr += "Error while parsing xml - 'chromosome' tag not found";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_XML_PARSE;
    return;
  }


  // read another elemnts
  for(int i = 0; i < 5; i++)
  {
    if(xml.readNextStartElement())
    {
      if(xml.name() == "chromosome_init")
      {
        atrTmp1 = xml.attributes().value("generation").toString().toInt(&convOk,10);
        atrTmp2 = xml.attributes().value("id").toString().toInt(&convOk,10);

        gen->SetThisInitGenomeId(atrTmp1,atrTmp2);
      }
      else if(xml.name() == "chromosome_parent")
      {
        atrTmp1 = xml.attributes().value("generation").toString().toInt(&convOk,10);
        atrTmp2 = xml.attributes().value("id").toString().toInt(&convOk,10);

        gen->SetParentGenomeId(atrTmp1,atrTmp2);
      }
      else if(xml.name() == "fitness_max")
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);
        atrTmp2 = xml.attributes().value("ca_step").toString().toInt(&convOk,10);
        atrTmp3 = xml.attributes().value("diff_min").toString().toInt(&convOk,10);
        atrTmp4 = xml.attributes().value("norm").toString().toDouble(&convOk);

        gen->SetFitness(atrTmp1,atrTmp3,atrTmp2);
        gen->SetFitnessNorm(atrTmp4);
      }
      else if(xml.name() == "mutated_genes")
      {
        atrTmp1 = xml.attributes().value("total").toString().toInt(&convOk,10);
        atrTmp2 = xml.attributes().value("total_all_ancestors").toString().toInt(&convOk,10);

        gen->SetMutatedGenesTotal(atrTmp1,atrTmp2);
      }
      // read data - genes of genome
      else if(xml.name() == "data")
      {
         genText = xml.readElementText();
         WriteGenesIntoGenome(&genText,gen);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportGA\n";
          msgErr += "Function: ReadGenome()\n";
          msgErr += "Error while parsing xml - unknown tag -> ";
          msgErr += xml.name().toString().toStdString();

          if((config != NULL) && (config->GetExportLogCore() != NULL))
            config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_GA_ERR_XML_PARSE;
        return;
      }
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportGA\n";
        msgErr += "Function: ReadGenome()\n";
        msgErr += "Error while parsing xml - next tag not found";

        if((config != NULL) && (config->GetExportLogCore() != NULL))
          config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_GA_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
  }

  // read last elements

  // </data> end element
  xml.readNext();
  // </chromosome> end element part 1 - characters token
  xml.readNext();
  // </chromosome> end element part 2 - end element token
  xml.readNext();
  // </ga_genomes> end element
  xml.readNext();

  if(xml.tokenType() != QXmlStreamReader::EndDocument)
  {
    // error - end document token expected
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: ReadGenome()\n";
      msgErr += "Error while parsing xml - EoF after </chromosome> tag not found";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_NOT_LAST_GENOM;
    // iErrFlag = IMPORT_GA_OK;
  }
  else
    iErrFlag = IMPORT_GA_OK;
}

//==============================================================
/**
 *  this function reads genome data - genes - from file and
 *  stores them into genome class
 *
 *  @param *genes       string with genes read in previous function
 *  @param *genom       pointer to genome class for writing data
 */

void CImportGA::WriteGenesIntoGenome(QString *genes, CGenome *genom)
{
  if((config == NULL) || (genom == NULL) || (genes == NULL))
  {
    {
      std::string msgErr  = "Class:    CImportGA\n";
      msgErr += "Function: WriteGenesIntoGenome()\n";
      msgErr += "Pointer to CConfigCore or CGenome or QString is NULL";

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_GA_ERR_NULL_POINTER;
    return;
  }

  int indexG = 0;                 // actual index in genome class
  int indexS = 0;                 // actual index in string
  int indexGMax = 0;              // max index in genome
  int indexSMax = genes->size();  // max index in string

  // get and set size of genome
  if(config->GetGenomeType() == GENOME_TYPE_2_9N)
    indexGMax = GENOME_SIZE_TYPE_2_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_3_9N)
    indexGMax = GENOME_SIZE_TYPE_3_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_4_9N)
    indexGMax = GENOME_SIZE_TYPE_4_9N;
  else if(config->GetGenomeType() == GENOME_TYPE_2_5N)
    indexGMax = GENOME_SIZE_TYPE_2_5N;
  else if(config->GetGenomeType() == GENOME_TYPE_3_5N)
    indexGMax = GENOME_SIZE_TYPE_3_5N;
  else if(config->GetGenomeType() == GENOME_TYPE_4_5N)
    indexGMax = GENOME_SIZE_TYPE_4_5N;
  /*
  else if(config->GetGenomeType() == GENOME_TYPE_2_INS)
    indexGMax = GENOME_SIZE_TYPE_2_INS;
  else if(config->GetGenomeType() == GENOME_TYPE_3_INS)
    indexGMax = GENOME_SIZE_TYPE_3_INS;
  else if(config->GetGenomeType() == GENOME_TYPE_4_INS)
    indexGMax = GENOME_SIZE_TYPE_4_INS;
  */
  else
    indexGMax = GENOME_SIZE_TYPE_2_9N;


  // read string and store genes into genome
  while((indexS < indexSMax) && (indexG < indexGMax))
  {
    if(genes->at(indexS) == '0')
    {
      genom->SetGene(indexG, CELL_STATE_EMPTY);
      indexG += 1;
      indexS += 1;
    }
    else if(genes->at(indexS) == '1')
    {
      genom->SetGene(indexG, CELL_STATE_LIVE_1);
      indexG += 1;
      indexS += 1;
    }
    else if(genes->at(indexS) == '2')
    {
      genom->SetGene(indexG, CELL_STATE_LIVE_2);
      indexG += 1;
      indexS += 1;
    }
    else if(genes->at(indexS) == '3')
    {
      genom->SetGene(indexG, CELL_STATE_LIVE_3);
      indexG += 1;
      indexS += 1;
    }
    else
    {
      //genom->SetGene(indexG, CELL_STATE_EMPTY);
      //indexG += 1;
      indexS += 1;
    }
  }
}

//==============================================================

