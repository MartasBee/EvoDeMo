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

#include "Array2d.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param sizeX        x-dimension of array
 *  @param sizeY        y-dimension of array
 *  @param stateDef     default state of cell
 *  @param *pCC         pointer to config class
 */

CArray2d::CArray2d(int sizeX, int sizeY, BYTE stateDef, CConfigCore *pCC)
{
  byDefCellState = stateDef;
  byErrCellState = CELL_STATE_ERR;

  array = NULL;

  iErrFlag = InitArray(sizeX, sizeY);

  pConfigCoreArray = pCC;
}

//==============================================================
/**
 *  class destructor
 */

CArray2d::~CArray2d()
{
  DeleteMemory();
}

//==============================================================
//==============================================================
/**
 *  returns element from given coordinates
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE CArray2d::operator()(int posX, int posY) const
{
  if((iErrFlag == ARRAY_OK) && (array != NULL) && (array->grid != NULL))
  {
    if((posX >= 0) && (posX < (signed)array->sizeX) &&
          (posY >= 0) && (posY < (signed)array->sizeY))
    {
      return array->grid[(unsigned)posY][(unsigned)posX];
    }
    else
      // out of range
      return byDefCellState;
  }
  else
  {
    {
      std::string msgErr  = "Class:    CArray2d\n";
      msgErr += "Function: operator() const\n";
      msgErr += "Unable to access array";

      if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
        pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return byDefCellState;
  }
}

//==============================================================
/**
 *  returns reference to element at given coordinates
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE& CArray2d::operator()(int posX, int posY)
{
  if((iErrFlag == ARRAY_OK) && (array != NULL) && (array->grid != NULL))
  {
    if((posX >= 0) && (posX < (signed)array->sizeX) &&
          (posY >= 0) && (posY < (signed)array->sizeY))
    {
      return array->grid[(unsigned)posY][(unsigned)posX];
    }
    else
      // out of range
      return byErrCellState;
  }
  else
  {
    {
      std::string msgErr  = "Class:    CArray2d\n";
      msgErr += "Function: operator()\n";
      msgErr += "Unable to access array";

      if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
        pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return byErrCellState;
  }
}

//==============================================================
/**
 *  copies one array into another
 *
 *  @param &rSide       reference to class on right side of '='
 */

CArray2d& CArray2d::operator=(const CArray2d &rSide)
{
  // same instances
  if(this == &rSide)
    return *this;

  // alloc new array
  iErrFlag = InitArray(rSide.array->sizeX, rSide.array->sizeY);
  if(iErrFlag != ARRAY_OK)
  {
    {
      std::string msgErr  = "Class:    CArray2d\n";
      msgErr += "Function: operator=\n";
      msgErr += "Grid reinitialization failed";

      if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
        pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return *this;
  }

  // copy
  for(unsigned int j = 0; j < (unsigned)GetHeight(); j++)
    for(unsigned int i = 0; i < (unsigned)GetWidth(); i++)
      array->grid[j][i] = rSide(i, j);

  iErrFlag = ARRAY_OK;
  return *this;
}

//==============================================================
//==============================================================
/**
 *  returns width of array
 */

int CArray2d::GetWidth()
{
  return (signed)array->sizeX;
}

//==============================================================
/**
 *  returns width of array
 */

int CArray2d::GetWidth() const
{
  return (signed)array->sizeX;
}

//==============================================================
/**
 *  returns height of array
 */

int CArray2d::GetHeight()
{
  return (signed)array->sizeY;
}

//==============================================================
/**
 *  returns height of array
 */

int CArray2d::GetHeight() const
{
  return (signed)array->sizeY;
}

//==============================================================
/**
 *  clears array - sets all cell to default value
 */

void CArray2d::ClearArray()
{
  if((array != NULL) && (array->grid != NULL))
    for(unsigned int j = 0; j < array->sizeY; j++)
      for(unsigned int i = 0; i < array->sizeX; i++)
        array->grid[j][i] = byDefCellState;
}

//==============================================================
/**
 *  clears array - sets all cell to given value
 *
 *  @param newDefState  new default state of cells
 */

void CArray2d::ClearArray(BYTE newDefState)
{
  byDefCellState = newDefState;

  if((array != NULL) && (array->grid != NULL))
    for(unsigned int j = 0; j < array->sizeY; j++)
      for(unsigned int i = 0; i < array->sizeX; i++)
        array->grid[j][i] = byDefCellState;
}

//==============================================================
/**
 *  returns error flag
 */

int CArray2d::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  array init - checking sizes of axes
 */

int CArray2d::InitArray(int sizeX, int sizeY)
{
  if(sizeX < SPACE_SIZE_X_MIN)
    iSizeX = (unsigned)SPACE_SIZE_X_MIN;
  else if(sizeX > SPACE_SIZE_X_MAX)
    iSizeX = (unsigned)SPACE_SIZE_X_MAX;
  else
    iSizeX = (unsigned)sizeX;

  if(sizeY < SPACE_SIZE_Y_MIN)
    iSizeY = (unsigned)SPACE_SIZE_Y_MIN;
  else if(sizeY > SPACE_SIZE_Y_MAX)
    iSizeY = (unsigned)SPACE_SIZE_Y_MAX;
  else
    iSizeY = (unsigned)sizeY;

  iErrFlag = AllocMemory();
  if(iErrFlag == ARRAY_OK)
    ClearArray();

  return iErrFlag;
}

//==============================================================
/**
 *  allocates memory for 2d array
 */

int CArray2d::AllocMemory()
{
  if(array != NULL)
    DeleteMemory();

  array = new struct stArray;
  if(array == NULL)
  {
    {
      std::string msgErr  = "Class:    CArray2d\n";
      msgErr += "Function: AllocMemory()\n";
      msgErr += "Memory allocation failed";

      if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
        pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = ARRAY_ERR_MEM_FAIL;
    return ARRAY_ERR_MEM_FAIL;
  }

  array->sizeX = 0;
  array->sizeY = 0;
  array->grid  = NULL;

  array->grid = new BYTE* [iSizeY];
  if(array->grid == NULL)
  {
    {
      std::string msgErr  = "Class:    CArray2d\n";
      msgErr += "Function: AllocMemory()\n";
      msgErr += "Memory allocation failed";

      if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
        pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    DeleteMemory();

    iErrFlag = ARRAY_ERR_MEM_FAIL;
    return ARRAY_ERR_MEM_FAIL;
  }
  else
    array->sizeY = (unsigned)iSizeY;

  for(unsigned int j = 0; j < array->sizeY; j++)
  {
    array->grid[j] = new BYTE [iSizeX];
    if(array->grid[j] == NULL)
    {
      {
        std::string msgErr  = "Class:    CArray2d\n";
        msgErr += "Function: AllocMemory()\n";
        msgErr += "Memory allocation failed";

        if((pConfigCoreArray != NULL) && (pConfigCoreArray->GetExportLogCore() != NULL))
          pConfigCoreArray->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      array->sizeY = j;

      DeleteMemory();

      iErrFlag = ARRAY_ERR_MEM_FAIL;
      return ARRAY_ERR_MEM_FAIL;
    }
  }

  array->sizeX = iSizeX;

  iErrFlag = ARRAY_OK;
  return ARRAY_OK;
}

//==============================================================
/**
 *  deletes memory of 2d array
 */

int CArray2d::DeleteMemory()
{
  if(array != NULL)
  {
    if(array->grid != NULL)
    {
      for(unsigned int j = 0; j < array->sizeY; j++)
        if(array->grid[j] != NULL)
          delete [] array->grid[j];

      delete [] array->grid;
    }

    delete array;

    array = NULL;
  }

  iErrFlag = ARRAY_OK;
  return ARRAY_OK;
}

//==============================================================

