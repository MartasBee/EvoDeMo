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

#include "ImportConfig.h"

//==============================================================
/**
 *  class constructor
 */

CImportConfig::CImportConfig()
{
  device   = NULL;
  iErrFlag = IMPORT_CONFIG_OK;
}

//==============================================================
//==============================================================
/**
 *  function for imprting genome from xml file created by CExportGA class
 *
 *  @param fileName     path/name of file
 *  @param *gen         pointer to genome class (must exists !!) into which data will be write
 */

void CImportConfig::ImportConfig(QString fileName,
                                 CWidgetInput *widIn,
                                 CWidgetOutput *widOut,
                                 CWidgetEvolution *widEvo,
                                 CWidgetExport *widExp)
{
  if((widIn == NULL) || (widOut == NULL) || (widEvo == NULL) || (widExp == NULL))
  {
    iErrFlag = IMPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }
  else
    iErrFlag = IMPORT_CONFIG_OK;


  // open file
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly | QFile::Text))
  {
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ImportConfig()\n";
      msgErr += "Unable to open import file";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_UNKNOWN;
    return;
  }
  else
    // set device for xml classes
    SetIODevice(&file);

  // import chromosome
  if(ReadDocStart())
  {
    ReadSettingsInput(widIn);
    ReadSettingsOutput(widOut);
    ReadSettingsEvolution(widEvo);
    ReadSettingsExport(widExp);
    ReadSettingsInputCASpace(widIn);

    ReadDocEnd();
  }

  xml.clear();
  file.close();
}

//==============================================================
//==============================================================
/**
 *  sets IO devide (opened file) in xml class
 *
 *  @param *device      pointer to opened file descriptor
 */

void CImportConfig::SetIODevice(QIODevice *device)
{
  this->device = device;

  xml.setDevice(this->device);
}

//==============================================================
/**
 *  returns error flag
 */

int CImportConfig::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  read document header for determining if file is compatibile
 *  and if genome is compatibile with user  settings
 */

bool CImportConfig::ReadDocStart()
{
  // read 1st element of xml
  if(xml.readNextStartElement())
  {
    if((xml.name() == "app_run_config") &&
       (xml.attributes().value("v") == "0.8.0"))
    {
      iErrFlag = IMPORT_CONFIG_OK;
      return true;
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadDocStart()\n";
        msgErr += "Incompatibile config in file";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_UNCOMPATIBILE_CONFIG;
      return false;
    }
  }
  // empty file
  else
  {
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadDocStart()\n";
      msgErr += "File is empty";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_EMPTY_FILE;
    return false;
  }
}

//==============================================================
/**
 *  read document's last (closing) tags
 */

void CImportConfig::ReadDocEnd()
{
  // </data> end element
  xml.readNext();
  // </input_ca_space> end element part 1 - characters token
  xml.readNext();
  // </input_ca_space> end element part 2 - end element token
  xml.readNext();
  // </app_run_config> end element part 1
  xml.readNext();
  // </app_run_config> end element part 2
  xml.readNext();

  if(xml.tokenType() != QXmlStreamReader::EndDocument)
  {
    // error - end document token expected
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadDocEnd()\n";
      msgErr += "Error while parsing xml - EoF after </chromosome> tag not found";

      std::cerr << "ERROR: " << msgErr;
    }

    iErrFlag = IMPORT_CONFIG_ERR_EOF_NOT_FOUND;
    // iErrFlag = IMPORT_CONFIG_OK;
  }
  else
    iErrFlag = IMPORT_CONFIG_OK;
}

//==============================================================
/**
 *  reads input settings
 *
 *  @param *widIn       pointer to widget with input settings
 */

void CImportConfig::ReadSettingsInput(CWidgetInput *widIn)
{
  int atrTmp1 = 0;
  int atrTmp2 = 0;
  bool convOk = false;

  // read 1st element
  if((xml.readNextStartElement()) && (xml.name() == "config_ca_input"))
  {
    if((xml.readNextStartElement()) && (xml.name() == "space_size"))
    {
      atrTmp1 = xml.attributes().value("width").toString().toInt(&convOk,10);
      atrTmp2 = xml.attributes().value("height").toString().toInt(&convOk,10);

      widIn->SetInputGridSize(atrTmp1,atrTmp2);
    }
    else
    {      
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'space_size' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "states"))
    {
      atrTmp1 = xml.attributes().value("count").toString().toInt(&convOk,10);
      atrTmp2 = xml.attributes().value("default_state").toString().toInt(&convOk,10);

      widIn->SetStatesCount(atrTmp1);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'states' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
  }
  else
  {    
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadSettingsInput()\n";
      msgErr += "Error while parsing xml - 'config_ca_input' tag not found";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
    return;
  }
  xml.readNext();
  xml.readNext();
}

//==============================================================
/**
 *  reads output settings
 *
 *  @param *widIn       pointer to widget with  settings
 */

void CImportConfig::ReadSettingsOutput(CWidgetOutput *widOut)
{
  int atrTmp1 = 0;
  int atrTmp2 = 0;
  bool convOk = false;

  // read 1st element
  if((xml.readNextStartElement()) && (xml.name() == "config_ca_output"))
  {
    if((xml.readNextStartElement()) && (xml.name() == "space_type"))
    {
      atrTmp1 = xml.attributes().value("type").toString().toInt(&convOk,10);

      widOut->SetOutputArrayType(atrTmp1);
    }
    else
    {      
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'space_type' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "space_size"))
    {
      atrTmp1 = xml.attributes().value("width").toString().toInt(&convOk,10);
      atrTmp2 = xml.attributes().value("height").toString().toInt(&convOk,10);

      widOut->SetOutputGridSizeX(atrTmp1);
      widOut->SetOutputGridSizeY(atrTmp2);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'states' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "mapping_point"))
    {
      atrTmp1 = xml.attributes().value("x_coord").toString().toInt(&convOk,10);
      atrTmp2 = xml.attributes().value("y_coord").toString().toInt(&convOk,10);

      widOut->SetOutputMapPosX(atrTmp1);
      widOut->SetOutputMapPosY(atrTmp2);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'mapping_point' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
  }
  else
  {
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadSettingsOutput()\n";
      msgErr += "Error while parsing xml - 'config_ca_output' tag not found";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
    return;
  }
  xml.readNext();
  xml.readNext();
}

//==============================================================
/**
 *  reads evolution settings
 *
 *  @param *widEvo      pointer to widget with evolution settings
 */

void CImportConfig::ReadSettingsEvolution(CWidgetEvolution *widEvo)
{
  int atrTmp1 = 0;
  int atrTmp2 = 0;
  bool convOk = false;

  // read 1st element
  if((xml.readNextStartElement()) && (xml.name() == "config_evolution"))
  {
    if((xml.readNextStartElement()) && (xml.name() == "import"))
    {
      if((!xml.readNextStartElement()) || !(xml.name() == "check_run_sim"))
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'check_run_sim' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((!xml.readNextStartElement()) || !(xml.name() == "check_reevolve"))
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'check_reevolve' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((!xml.readNextStartElement()) || !(xml.name() == "import_file"))
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'import_file' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsEvolution()\n";
        msgErr += "Error while parsing xml - 'import' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "ga_operations"))
    {
      if((!xml.readNextStartElement()) && !(xml.name() == "crossover"))
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'crossover' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "mutation"))
      {
        atrTmp1 = xml.attributes().value("probability").toString().toInt(&convOk,10);
        atrTmp2 = xml.attributes().value("count").toString().toInt(&convOk,10);

        widEvo->SetMutationProbability(atrTmp1);
        widEvo->SetMutationCount(atrTmp2);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'mutation' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsEvolution()\n";
        msgErr += "Error while parsing xml - 'ga_operations' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "evolution"))
    {
      if((xml.readNextStartElement()) && (xml.name() == "evo_runs"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetRepetitionsCount(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'evo_runs' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "generations"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetGenerationsCount(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'generations' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "population_size"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetPopulationSize(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'population_size' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "chromosome"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetGenomeType(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'chromosome' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'evolution' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "movement"))
    {
      if((xml.readNextStartElement()) && (xml.name() == "direction"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetMoveDirection(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'direction' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "ca_steps"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetStepsCount(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'ca_steps' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "distance"))
      {
        atrTmp1 = xml.attributes().value("value").toString().toInt(&convOk,10);

        widEvo->SetMoveDistance(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsEvolution()\n";
          msgErr += "Error while parsing xml - 'distance' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'movement' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();
  }
  else
  {    
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadSettingsEvolution()\n";
      msgErr += "Error while parsing xml - 'config_evolution' tag not found";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
    return;
  }
  xml.readNext();
  xml.readNext();
}

//==============================================================
/**
 *  reads export settings
 *
 *  @param *widExp      pointer to widget with export settings
 */

void CImportConfig::ReadSettingsExport(CWidgetExport *widExp)
{
  int atrTmp1 = 0;
  bool convOk = false;

  // read 1st element
  if((xml.readNextStartElement()) && (xml.name() == "config_export"))
  {
    if((xml.readNextStartElement()) && (xml.name() == "file_export"))
    {
      if((!xml.readNextStartElement()) && !(xml.name() == "export_path"))
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsInput()\n";
          msgErr += "Error while parsing xml - 'export_path' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "ca_export"))
      {
        atrTmp1 = xml.attributes().value("mode").toString().toInt(&convOk,10);

        widExp->SetFileExportModeCA(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsInput()\n";
          msgErr += "Error while parsing xml - 'ca_export' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "ga_export"))
      {
        atrTmp1 = xml.attributes().value("mode").toString().toInt(&convOk,10);

        widExp->SetFileExportModeGA(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsInput()\n";
          msgErr += "Error while parsing xml - 'ga_export' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'file_export' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();

    if((xml.readNextStartElement()) && (xml.name() == "gddm"))
    {
      if((xml.readNextStartElement()) && (xml.name() == "animation_timeout"))
      {
        atrTmp1 = xml.attributes().value("miliseconds").toString().toInt(&convOk,10);

        widExp->SetGuiDataDisplayModeTimeout(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsInput()\n";
          msgErr += "Error while parsing xml - 'animation_timeout' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();

      if((xml.readNextStartElement()) && (xml.name() == "display_mode"))
      {
        atrTmp1 = xml.attributes().value("mode").toString().toInt(&convOk,10);

        widExp->SetGuiDataDisplayModeCA(atrTmp1);
      }
      else
      {
        {
          std::string msgErr  = "Class:    CImportConfig\n";
          msgErr += "Function: ReadSettingsInput()\n";
          msgErr += "Error while parsing xml - 'display_mode' tag not found";

          std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
        return;
      }
      xml.readNext();
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'gddm' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
    xml.readNext();
  }
  else
  {    
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadSettingsExport()\n";
      msgErr += "Error while parsing xml - 'config_export' tag not found";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
    return;
  }
  xml.readNext();
  xml.readNext();
}

//==============================================================
/**
 *  reads input ca space
 *
 *  @param *widIn       pointer to widget with input settings
 */

void CImportConfig::ReadSettingsInputCASpace(CWidgetInput *widIn)
{
  QString data = "";
  int indexS   = 0;
  int value    = 0;
  char num ;

  // read 1st element
  if((xml.readNextStartElement()) && (xml.name() == "input_ca_space"))
  {    
    if((xml.readNextStartElement()) && (xml.name() == "data"))
    {
      data = xml.readElementText();

      while(indexS < data.size())
      {
        for(int j = 0; j < widIn->GetGrid()->GetHeight(); j++)
          for(int i = 0; i < widIn->GetGrid()->GetWidth(); i++)
          {
            if(indexS >= data.size())
              return;
            if(data.at(indexS).isNumber())
            {
              num = data.at(indexS).toAscii();
              value = atoi(&num);
              if((value == CELL_STATE_EMPTY) ||
                 (value == CELL_STATE_LIVE_1) ||
                 (value == CELL_STATE_LIVE_2) ||
                 (value == CELL_STATE_LIVE_3))
                widIn->GetGrid()->GetCell(i,j)->SetState((BYTE)value);
            }
            else
              i -= 1;

            indexS += 1;
          }
      }
    }
    else
    {
      {
        std::string msgErr  = "Class:    CImportConfig\n";
        msgErr += "Function: ReadSettingsInput()\n";
        msgErr += "Error while parsing xml - 'data' tag not found";

        std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
      return;
    }
    xml.readNext();
  }
  else
  {
    {
      std::string msgErr  = "Class:    CImportConfig\n";
      msgErr += "Function: ReadSettingsInput()\n";
      msgErr += "Error while parsing xml - 'input_ca_space' tag not found";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = IMPORT_CONFIG_ERR_XML_PARSE;
    return;
  }
}

//==============================================================

