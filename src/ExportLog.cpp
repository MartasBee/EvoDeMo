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

#include "ExportLog.h"

//==============================================================
/**
 *  class constructor
 */

CExportLog::CExportLog()
{
  filePath = QDir::currentPath();
  fileName = "log.txt";
}

//==============================================================
/**
 *  class destructor
 */

CExportLog::~CExportLog()
{
  CloseLogFile();
}

//==============================================================
//==============================================================
/**
 *  sets path of log file
 *
 *  @param path         relative or absolute path
 */

void CExportLog::SetFilePath(QString path)
{
  filePath = path;
}

//==============================================================
/**
 *  sets log file name
 *
 *  @param name         log file name
 */

void CExportLog::SetFileName(QString name)
{
  fileName = name;
}

//==============================================================
//==============================================================
/**
 *  opens log file
 */

bool CExportLog::OpenLogFile()
{
  filePathName  = filePath;
  filePathName += "/";
  filePathName += fileName;

  // set name to file device and open file
  fileDevice.setFileName(filePathName);
  if(!fileDevice.open(QFile::WriteOnly | QFile::Text))
  {
    QMessageBox::critical(NULL,
                          "Log File Error",
                          "Unable to open log file",
                          QMessageBox::Ok);

    bFileOpened = false;
  }
  // file opening failed
  else
  {
    bFileOpened = true;
    fileStream.setDevice(&fileDevice);

    WriteInfoLog("Log opened");
  }

  return bFileOpened;
}

//==============================================================
/**
 *  closes file
 */

void CExportLog::CloseLogFile()
{
  if(bFileOpened)
  {
    WriteInfoLog("Log closed");
    fileStream.flush();

    fileDevice.close();
    fileStream.setDevice(NULL);
    bFileOpened = false;
  }
}

//==============================================================
//==============================================================
/**
 *  writes INFORMATION into log file
 *
 *  @param info         string to be write
 */

void CExportLog::WriteInfoLog(QString info)
{
  if(!bFileOpened)
    return;

  QString dt = QDateTime::currentDateTime().toString("MMM dd yyyy, hh:mm:ss ap");

  fileStream << "==== ==== ==== ====\n";
  fileStream << "INFO: " << dt << "\n";
  fileStream << info << "\n";
  fileStream.flush();
}

//==============================================================
/**
 *  writes ERROR into log file
 *
 *  @param errId        error id (described in Defines.h)
 */

void CExportLog::WriteErrorLog(int errId)
{
  if(!bFileOpened)
    return;

  QString dt = QDateTime::currentDateTime().toString("MMM dd yyyy, hh:mm:ss ap");

  fileStream << "==== ==== ==== ====\n";
  fileStream << "ERROR: " << dt << "\n";
  fileStream << errId << "\n";
  fileStream.flush();
}

//==============================================================
/**
 *  writes ERROR into log file
 *
 *  @param error        string to be write
 */

void CExportLog::WriteErrorLog(QString error)
{
  if(!bFileOpened)
    return;

  QString dt = QDateTime::currentDateTime().toString("MMM dd yyyy, hh:mm:ss ap");

  fileStream << "==== ==== ==== ====\n";
  fileStream << "ERROR: " << dt << "\n";
  fileStream << error << "\n";
  fileStream.flush();
}

//==============================================================
//==============================================================
/**
 *  shows message box with error
 *
 *  @param errId        error id (described in Defines.h)
 */

void CExportLog::ShowMessageBox(int errId)
{
  QString err_msg = "";

  switch(errId)
  {
  case 0:
    err_msg = ERROR_STRING__OK;
    break;

  case -1:
    err_msg = ERROR_STRING__ERR_UNKNOWN;
    break;

  case ARRAY_ERR_MEM_FAIL:
    err_msg = ERROR_STRING__ARRAY_ERR_MEM_FAIL;
    break;

    case SPACE_ERR_ACCESS_FAIL:
    err_msg = ERROR_STRING__SPACE_ERR_ACCESS_FAIL;
    break;

  case SPACE_ERR_OUT_OF_RANGE:
    err_msg = ERROR_STRING__SPACE_ERR_OUT_OF_RANGE;
    break;

  case SPACE_ERR_MEM_ALLOC:
    err_msg = ERROR_STRING__SPACE_ERR_MEM_ALLOC;
    break;

  case CA_ERR_TORUS_NULL:
    err_msg = ERROR_STRING__CA_ERR_TORUS_NULL;
    break;

  case CA_ERR_GRID_NULL:
    err_msg = ERROR_STRING__CA_ERR_GRID_NULL;
    break;

  case TFUNCTION_ERR_GRID_NULL:
    err_msg = ERROR_STRING__TFUNCTION_ERR_GRID_NULL;
    break;

  case TFUNCTION_ERR_TORUS_NULL:
    err_msg = ERROR_STRING__TFUNCTION_ERR_TORUS_NULL;
    break;

  case TFUNCTION_ERR_RULES_NULL:
    err_msg = ERROR_STRING__TFUNCTION_ERR_RULES_NULL;
    break;

  case TFUNCTION_ERR_SUB_A_NULL:
    err_msg = ERROR_STRING__TFUNCTION_ERR_SUB_A_NULL;
    break;

  case TFUNCTION_ERR_GRIDS_SIZE:
    err_msg = ERROR_STRING__TFUNCTION_ERR_GRIDS_SIZE;
    break;

  case TFUNCTION_ERR_GRIDS_SAME:
    err_msg = ERROR_STRING__TFUNCTION_ERR_GRIDS_SAME;
    break;

  case TFUNCTION_ERR_TORUSES_SIZE:
    err_msg = ERROR_STRING__TFUNCTION_ERR_TORUSES_SIZE;
    break;

  case TFUNCTION_ERR_TORUSES_SAME:
    err_msg = ERROR_STRING__TFUNCTION_ERR_TORUSES_SAME;
    break;

  case CROSSOVER_ERR_POINTER_NULL:
    err_msg = ERROR_STRING__CROSSOVER_ERR_POINTER_NULL;
    break;

  case FITNESS_ERR_POINTER_NULL:
    err_msg = ERROR_STRING__FITNESS_ERR_POINTER_NULL;
    break;

  case FITNESS_ERR_NO_NON_EMPTY_CELL:
    err_msg = ERROR_STRING__FITNESS_ERR_NO_NON_EMPTY_CELL;
    break;

  case GA_ERR_MEMORY_FAIL:
    err_msg = ERROR_STRING__GA_ERR_MEMORY_FAIL;
    break;

  case GA_ERR_NULL_POINTER:
    err_msg = ERROR_STRING__GA_ERR_NULL_POINTER;
    break;

  case GA_ERR_OUT_OF_RANGE:
    err_msg = ERROR_STRING__GA_ERR_OUT_OF_RANGE;
    break;

  case GA_ERR_NO_INPUT:
    err_msg = ERROR_STRING__GA_ERR_NO_INPUT;
    break;

  case GENOME_ERR_TX_NULL:
    err_msg = ERROR_STRING__GENOME_ERR_TX_NULL;
    break;

  case MUTATION_ERR_POINTER_NULL:
    err_msg = ERROR_STRING__MUTATION_ERR_POINTER_NULL;
    break;

  case RANDOM_ERR_POINTER_NULL:
    err_msg = ERROR_STRING__RANDOM_ERR_POINTER_NULL;
    break;

  case CORE_ERR_MEM_FAIL:
    err_msg = ERROR_STRING__CORE_ERR_MEM_FAIL;
    break;

  case EXPORT_GA_ERR_POINTER_NULL:
    err_msg = ERROR_STRING__EXPORT_GA_ERR_POINTER_NULL;
    break;

  case THREAD_CORE_ERR_POINTERS:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_POINTERS;
    break;

  case THREAD_CORE_ERR_MEM_FAIL:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_MEM_FAIL;
    break;

  case THREAD_CORE_ERR_INIT_GA:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_INIT_GA;
    break;

  case THREAD_CORE_ERR_INIT_CA:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_INIT_CA;
    break;

  case THREAD_CORE_ERR_INIT_CA_M:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_INIT_CA_M;
    break;

  case THREAD_CORE_ERR_CORE_GA:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_CORE_GA;
    break;

  case THREAD_CORE_ERR_CORE_CA:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_CORE_CA;
    break;

  case THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL:
    err_msg = ERROR_STRING__THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL;
    break;

  default:
    err_msg = ERROR_STRING__ERR_UNKNOWN;
  }

  QMessageBox::critical(NULL,
                        "EvoDeMo Error",
                        err_msg,
                        QMessageBox::Ok);
}

//==============================================================
/**
 *  shows message box with error
 *
 *  @param error        string to be showed
 */

void CExportLog::ShowMessageBox(QString error)
{
  QMessageBox::critical(NULL,
                        "EvoDeMo Error",
                        error,
                        QMessageBox::Ok);
}

//==============================================================

