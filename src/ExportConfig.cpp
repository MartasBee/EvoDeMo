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

#include "ExportConfig.h"

//==============================================================
/**
 *  class constructor
 */

CExportConfig::CExportConfig()
{
  device = NULL;

  iErrFlag = EXPORT_CONFIG_OK;
}

//==============================================================
/**
 *  class deconstructor
 */

CExportConfig::~CExportConfig()
{

}

//==============================================================
//==============================================================
/**
 *  exports actual app config
 *
 *  @param filePathName file's path/name
 *  @param *widIn       pointer to settings widget input
 *  @param *widOut      pointer to settings widget output
 *  @param *widEvo      pointer to settings widget evolution
 *  @param *widExp      pointer to settings widget export
 */

bool CExportConfig::ExportConfig(QString          filePathName,
                                 CWidgetInput     *widIn,
                                 CWidgetOutput    *widOut,
                                 CWidgetEvolution *widEvo,
                                 CWidgetExport    *widExp)
{
  if((widIn == NULL) || (widOut == NULL) || (widEvo == NULL) || (widExp == NULL))
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return false;
  }
  else
    iErrFlag = EXPORT_CONFIG_OK;


  // open file
  QFile file(filePathName);
  if(!file.open(QFile::WriteOnly | QFile::Text))
  {
    {
      std::string msgErr  = "Class:    CExportConfig\n";
      msgErr += "Function: ExportConfig()\n";
      msgErr += "Unable to open export file";

      std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = EXPORT_GA_ERR_UNKNOWN;
    return false;
  }
  else
    SetIODevice(&file);


  // export
  WriteDocStart();
  WriteSettingsInput(widIn);
  WriteSettingsOutput(widOut);
  WriteSettingsEvolution(widEvo);
  WriteSettingsExport(widExp);
  WriteSettingsInputCASpace(widIn);
  WriteDocEnd();


  // close file
  file.close();

  return true;
}

//==============================================================
//==============================================================
/**
 *  sets IO device (opened file descriptor) into xml class
 *
 *  @param *device      opened file descriptor
 */

void CExportConfig::SetIODevice(QIODevice *device)
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

int CExportConfig::GetErrorFlag()
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

void CExportConfig::WriteDocStart()
{
  xml.writeStartDocument();
  xml.writeDTD("<!DOCTYPE evodemo_run_settings_export>");

  xml.writeStartElement("app_run_config");
  xml.writeAttribute("v","0.8.0");
}

//==============================================================
/**
 *  writes doc end (closing elements)
 */

void CExportConfig::WriteDocEnd()
{
  xml.writeEndElement();  // app_version

  xml.writeEndDocument();
}

//==============================================================
/**
 *  writes input settings
 *
 *  @param *widIn       pointer to input settings widget
 */

void CExportConfig::WriteSettingsInput(CWidgetInput *widIn)
{
  if(widIn == NULL)
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }

  xml.writeStartElement("config_ca_input");

  xml.writeEmptyElement("space_size");
  xml.writeAttribute("width",QString("%1").arg(widIn->GetGrid()->GetWidth()));
  xml.writeAttribute("height",QString("%1").arg(widIn->GetGrid()->GetHeight()));

  xml.writeEmptyElement("states");
  xml.writeAttribute("count",QString("%1").arg(widIn->GetGrid()->GetCellConfig()->GetStatesCount()));
  xml.writeAttribute("default_state",QString("%1").arg(int(widIn->GetGrid()->GetCellConfig()->GetDefState())));

  xml.writeEndElement();  // config_ca_input
}

//==============================================================
/**
 *  writes output settings
 *
 *  @param *widOut      pointer to output settings widget
 */

void CExportConfig::WriteSettingsOutput(CWidgetOutput *widOut)
{
  if(widOut == NULL)
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }

  xml.writeStartElement("config_ca_output");

  xml.writeEmptyElement("space_type");
  xml.writeAttribute("type",QString("%1").arg(widOut->GetOutputArrayType()));

  xml.writeEmptyElement("space_size");
  xml.writeAttribute("width",QString("%1").arg(widOut->GetOutputGridSizeX()));
  xml.writeAttribute("height",QString("%1").arg(widOut->GetOutputGridSizeY()));

  xml.writeEmptyElement("mapping_point");
  xml.writeAttribute("x_coord",QString("%1").arg(widOut->GetOutputMapPosX()));
  xml.writeAttribute("y_coord",QString("%1").arg(widOut->GetOutputMapPosY()));

  xml.writeEndElement();  // config_ca_output
}

//==============================================================
/**
 *  writes evolution settings
 *
 *  @param *widEvo      pointer to evolution settings widget
 */

void CExportConfig::WriteSettingsEvolution(CWidgetEvolution *widEvo)
{
  if(widEvo == NULL)
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }

  xml.writeStartElement("config_evolution");

  xml.writeStartElement("import");

  xml.writeEmptyElement("check_run_sim");
  xml.writeAttribute("checked",QString("%1").arg(int(widEvo->IsImportGenomeEnabledSimulation())));

  xml.writeEmptyElement("check_reevolve");
  xml.writeAttribute("checked",QString("%1").arg(int(widEvo->IsImportGenomeEnabledReevolve())));

  xml.writeEmptyElement("import_file");
  xml.writeAttribute("file",widEvo->GetImportGenomeFile());

  xml.writeEndElement();  // import

  xml.writeStartElement("ga_operations");

  xml.writeEmptyElement("crossover");
  xml.writeAttribute("probability",QString("%1").arg(widEvo->GetCrossoverProbability()));
  xml.writeAttribute("count",QString("%1").arg(widEvo->GetCrossoverCount()));

  xml.writeEmptyElement("mutation");
  xml.writeAttribute("probability",QString("%1").arg(widEvo->GetMutationProbability()));
  xml.writeAttribute("count",QString("%1").arg(widEvo->GetMutationCount()));

  xml.writeEndElement();  // ga_operations

  xml.writeStartElement("evolution");

  xml.writeEmptyElement("evo_runs");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetRepetitionsCount()));

  xml.writeEmptyElement("generations");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetGenerationsCount()));

  xml.writeEmptyElement("population_size");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetPopulationSize()));

  xml.writeEmptyElement("chromosome");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetGenomeType()));

  xml.writeEndElement();  // evolution

  xml.writeStartElement("movement");

  xml.writeEmptyElement("direction");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetMoveDirection()));

  xml.writeEmptyElement("ca_steps");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetStepsCount()));

  xml.writeEmptyElement("distance");
  xml.writeAttribute("value",QString("%1").arg(widEvo->GetMoveDistance()));

  xml.writeEndElement();  // movement

  xml.writeEndElement();  // config_evolution
}

//==============================================================
/**
 *  writes export settings
 *
 *  @param *widExp      pointer to export settings widget
 */

void CExportConfig::WriteSettingsExport(CWidgetExport *widExp)
{
  if(widExp == NULL)
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }

  xml.writeStartElement("config_export");

  xml.writeStartElement("file_export");

  xml.writeEmptyElement("export_path");
  xml.writeAttribute("path",widExp->GetFileExportPath());

  xml.writeEmptyElement("ca_export");
  xml.writeAttribute("mode",QString("%1").arg(widExp->GetFileExportModeCA()));

  xml.writeEmptyElement("ga_export");
  xml.writeAttribute("mode",QString("%1").arg(widExp->GetFileExportModeGA()));

  xml.writeEndElement();  // file_export

  xml.writeStartElement("gddm");

  xml.writeEmptyElement("animation_timeout");
  xml.writeAttribute("miliseconds",QString("%1").arg(widExp->GetGuiDataDisplayModeTimeout()));

  xml.writeEmptyElement("display_mode");
  xml.writeAttribute("mode",QString("%1").arg(widExp->GetGuiDataDisplayModeCA()));

  xml.writeEndElement();  // gddm

  xml.writeEndElement();  // config_export
}

//==============================================================
/**
 *  writes input ca space settings
 */

void CExportConfig::WriteSettingsInputCASpace(CWidgetInput *widIn)
{
  if(widIn == NULL)
  {
    iErrFlag = EXPORT_CONFIG_ERR_NULL_POINTER;
    return;
  }

  QString tmp = "";

  xml.writeStartElement("input_ca_space");

  xml.writeStartElement("data");

  tmp = "\n";

  for(int j = 0; j < widIn->GetGrid()->GetHeight(); j++)
  {
    for(int i = 0; i < widIn->GetGrid()->GetWidth(); i++)
    {
      if(widIn->GetGrid()->GetCell(i,j)->GetState() == 0)
        tmp += "0";
      else if(widIn->GetGrid()->GetCell(i,j)->GetState() == 1)
        tmp += "1";
      else if(widIn->GetGrid()->GetCell(i,j)->GetState() == 2)
        tmp += "2";
      else if(widIn->GetGrid()->GetCell(i,j)->GetState() == 3)
        tmp += "3";
      else
        tmp += "0";
    }

    tmp += "\n";

    xml.writeCharacters(tmp);

    tmp = "";
  }

  xml.writeEndElement();  // data

  xml.writeEndElement();  // input_ca_space
}

//==============================================================

