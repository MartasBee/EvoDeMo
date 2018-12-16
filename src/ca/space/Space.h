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

#ifndef SPACE_H
#define SPACE_H

//==============================================================

#include "Array2d.h"
#include "../../ConfigCore.h"
#include "../../Defines.h"

//==============================================================
/**
 *  inherits CArray2d, which is carring 2d array,
 *  this class implements behaviour of ca space - grid or torus
 */

class CSpace : private CArray2d
{
public:
  CSpace(int type      = SPACE_TYPE_GRID,
         int sizeX     = SPACE_SIZE_X_DEFAULT,
         int sizeY     = SPACE_SIZE_Y_DEFAULT,
         BYTE defState = CELL_STATE_EMPTY,
         CConfigCore *pCC = NULL);
  ~CSpace();

  BYTE  at(int posX, int posY) const;
  BYTE& at(int posX, int posY);

  BYTE  atGrid(int posX, int posY) const;
  BYTE& atGrid(int posX, int posY);

  BYTE  atTorus(int posX, int posY) const;
  BYTE& atTorus(int posX, int posY);

  int GetWidth();
  int GetHeight();

  int GetSpaceType();

  int GetErrorFlag();

private:
  int iSpaceType;   //!< space type

  BYTE errCell;     //!< error cell
  BYTE byDefCell;   //!< default value cell
};

//==============================================================

#endif // SPACE_H

//==============================================================

