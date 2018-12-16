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

#include "InputCA.h"

//==============================================================
/**
 *  class constructor
 */

CInputCA::CInputCA()
{
  device   = NULL;
  config   = NULL;
  iErrFlag = 0;
}

//==============================================================
//==============================================================
/**
 *  import init CA space config from xml - NOT IMPLEMENTED
 *
 *  @param fileName     path/name of file
 */

bool CInputCA::ImportCA(QString fileName)
{
  if(fileName.isEmpty())
    return false;
  else
    return true;
}

//==============================================================
/**
 *  export init CA space config to xml - NOT IMPLEMENTED
 *
 *  @param fileName     path/name of file
 */

bool CInputCA::ExportCA(QString fileName)
{
  if(fileName.isEmpty())
    return false;
  else
    return true;
}

//==============================================================
//==============================================================
/**
 *  sets config class
 *
 *  @param *cCore       pointer to config class
 */

void CInputCA::SetConfigCore(CConfigCore *cCore)
{
  config = cCore;
}

//==============================================================
/**
 *  returns error flag
 */

int CInputCA::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================

