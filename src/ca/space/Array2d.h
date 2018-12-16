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

#ifndef ARRAY2D_H
#define ARRAY2D_H

//==============================================================

#include "../../ConfigCore.h"
#include "../../Defines.h"

//==============================================================
/**
 *  2d array struct
 */

struct stArray
{
  unsigned int sizeX;   //!< array width
  unsigned int sizeY;   //!< array height

  BYTE **grid;          //!< pointer to 2d array
};

//==============================================================
/**
 *  contains 2d array, which is used as cellular space for CA
 */

class CArray2d
{
public:
  CArray2d(int  sizeX    = SPACE_SIZE_X_DEFAULT,
           int  sizeY    = SPACE_SIZE_Y_DEFAULT,
           BYTE stateDef = CELL_STATE_EMPTY,
           CConfigCore *pCC = NULL);
  ~CArray2d();

  BYTE      operator()(int posX, int posY) const;
  BYTE&     operator()(int posX, int posY);
  CArray2d& operator=(const CArray2d &rSide);

  int GetWidth();
  int GetHeight();

  int GetWidth() const;
  int GetHeight() const;

  void ClearArray();
  void ClearArray(BYTE newDefState);

  int GetErrorFlag();

private:
  int iSizeX;                     //!< array width
  int iSizeY;                     //!< array height

  BYTE byDefCellState;            //!< cell's default state
  BYTE byErrCellState;            //!< error state

  struct stArray *array;          //!< pointer to dyn.allocated 2d array

  CConfigCore *pConfigCoreArray;  //!< pointer to config class

  int iErrFlag;                   //!< error flag

  int AllocMemory();
  int DeleteMemory();

  int InitArray(int sizeX, int sizeY);
};

//==============================================================

#endif // ARRAY2D_H

//==============================================================

