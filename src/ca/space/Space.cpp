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

#include "Space.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param type         torus or lattice
 *  @param sizeX        array width
 *  @param sizeY        array height
 *  @param defState     default state
 *  @param *pConfigCore pointer to config class
 *
 *  @param CArray2d     CSpace inherits this class
 */

CSpace::CSpace(int type, int sizeX, int sizeY, BYTE defState, CConfigCore *pConfigCore) : CArray2d(sizeX, sizeY, defState, pConfigCore)
{
  if(type == SPACE_TYPE_GRID)
    iSpaceType = type;
  else if(type == SPACE_TYPE_TORUS)
    iSpaceType = type;
  else
    iSpaceType = SPACE_TYPE_GRID;

  errCell   = CELL_STATE_ERR;
  byDefCell = defState;
}

//==============================================================
/**
 *  class destructor
 */

CSpace::~CSpace()
{

}

//==============================================================
//==============================================================
/**
 *  returns element at given coorditates
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE CSpace::at(int posX, int posY) const
{
  if(iSpaceType == SPACE_TYPE_GRID)
    return atGrid(posX,posY);
  else if(iSpaceType == SPACE_TYPE_TORUS)
    return atTorus(posX,posY);
  else
    return errCell;
}

//==============================================================
/**
 *  returns reference to element at given coorditates
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE& CSpace::at(int posX, int posY)
{
  if(iSpaceType == SPACE_TYPE_GRID)
    return atGrid(posX,posY);
  else if(iSpaceType == SPACE_TYPE_TORUS)
    return atTorus(posX,posY);
  else
    return errCell;
}

//==============================================================
//==============================================================
/**
 *  returns element at given coorditates with respect to cellular
 *    space type "grid"
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE CSpace::atGrid(int posX, int posY) const
{
  if((posX < 0) || (posX >= CArray2d::GetWidth()))
    return byDefCell;

  if((posY < 0) || (posY >= CArray2d::GetHeight()))
    return byDefCell;

  return CArray2d::operator()(posX, posY);
}

//==============================================================
/**
 *  returns reference to element at given coorditates with
 *    respect to cellular space type "grid"
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE& CSpace::atGrid(int posX, int posY)
{
  if((posX < 0) || (posX >= CArray2d::GetWidth()))
    return byDefCell;

  if((posY < 0) || (posY >= CArray2d::GetHeight()))
    return byDefCell;

  return CArray2d::operator()(posX, posY);
}

//==============================================================
//==============================================================
/**
 *  returns element at given coorditates with respect to cellular
 *    space type "torus" - quasi-infinate space
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE CSpace::atTorus(int posX, int posY) const
{
  if(posX < 0)
    posX = ((posX + CArray2d::GetWidth()) % CArray2d::GetWidth());
  else if(posX >= CArray2d::GetWidth())
    posX = (posX % CArray2d::GetWidth());

  if(posY < 0)
    posY = ((posY + CArray2d::GetHeight()) % CArray2d::GetHeight());
  else if(posY >= CArray2d::GetHeight())
    posY = (posY % CArray2d::GetHeight());

  return CArray2d::operator()(posX, posY);
}

//==============================================================
/**
 *  returns reference to element at given coorditates with respect
 *    to cellular space type "torus" - quasi-infinate space
 *
 *  @param posX         position on x-axes
 *  @param posY         position on y-axes
 */

BYTE& CSpace::atTorus(int posX, int posY)
{
  if(posX < 0)
    posX = ((posX + CArray2d::GetWidth()) % CArray2d::GetWidth());
  else if(posX >= CArray2d::GetWidth())
    posX = (posX % CArray2d::GetWidth());

  if(posY < 0)
    posY = ((posY + CArray2d::GetHeight()) % CArray2d::GetHeight());
  else if(posY >= CArray2d::GetHeight())
    posY = (posY % CArray2d::GetHeight());

  return CArray2d::operator()(posX, posY);
}

//==============================================================
//==============================================================
/**
 *  returns space type
 */

int CSpace::GetSpaceType()
{
  return iSpaceType;
}

//==============================================================
/**
 *  returns  array width
 */

int CSpace::GetWidth()
{
  return CArray2d::GetWidth();
}

//==============================================================
/**
 *  returns array height
 */

int CSpace::GetHeight()
{
  return CArray2d::GetHeight();
}

//==============================================================
/**
 *  return error flag
 */

int CSpace::GetErrorFlag()
{
  if(CArray2d::GetErrorFlag() == ARRAY_OK)
    return SPACE_OK;
  else
    return CArray2d::GetErrorFlag();
}

//==============================================================

