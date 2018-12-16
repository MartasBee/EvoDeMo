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

#include "Fitness.h"

//==============================================================
/**
 *  class constructor
 */

CFitness::CFitness()
{
  pConfigCore = NULL;

  iX_1 = -1;
  iY_1 = -1;
  iX_2 = -1;
  iY_2 = -1;

  bNonEmptyCellExists = false;

  iErrFlag = FITNESS_OK;
}

//==============================================================
//==============================================================
/**
 *  calculates fitness of actual step of ca
 *
 *  @param *spaceInit   init ca space - stores original ca config
 *  @param *spaceAct    actual ca space
 */

int CFitness::Fitness(CSpace *spaceInit, CSpace *spaceAct)
{
  if((spaceInit == NULL) || (spaceAct == NULL) || (pConfigCore == NULL))
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: Fitness()\n";
      msgErr += "Pointer to CSpace or CConfigCore is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = FITNESS_ERR_POINTER_NULL;
    return FITNESS_VALUE_INIT;
  }

  iErrFlag = FITNESS_OK;

  // calculate
  return _Fitness_01(spaceInit,spaceAct);
}

//==============================================================
//==============================================================
/**
 *  checks, if there is any live cell in ca space
 *
 *  @param *s           pointer to ca space
 */

bool CFitness::IsLiveOrganismInSpace(CSpace *s)
{
  iErrFlag = FITNESS_OK;

  if(s == NULL)
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: IdentifyCorners()\n";
      msgErr += "Pointer to CSpace is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = FITNESS_ERR_POINTER_NULL;
    return false;
  }

  if(s->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(int j = 0; j < s->GetHeight(); j++)
      for(int i = 0; i < s->GetWidth(); i++)
        if(s->atGrid(i,j) != CELL_STATE_EMPTY)
          return true;
  }
  else if(s->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(int j = 0; j < s->GetHeight(); j++)
      for(int i = 0; i < s->GetWidth(); i++)
        if(s->atTorus(i,j) != CELL_STATE_EMPTY)
          return true;
  }

  return false;
}

//==============================================================
/**
 *  identifies corners of envelope of object in ca space - used for
 *  determinate if any object is in space
 *  object is covered by rectangle:
 *
 *    ---*---
 *    | *** |
 *    |** **|
 *    ** * **
 *    |** **|
 *    | *** |
 *    ---*---
 *
 *  object is created from asterisks, white space are "dead cells",
 *  rectangle is created from lines
 *
 *  @param *s           pointer to ca space
 */

void CFitness::IdentifyCorners(CSpace *s)
{
  if(s == NULL)
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: IdentifyCorners()\n";
      msgErr += "Pointer to CSpace is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = FITNESS_ERR_POINTER_NULL;
    return;
  }

  int iX_1_Tmp = SPACE_SIZE_X_MAX + SPACE_SIZE_X_MAX;
  int iY_1_Tmp = SPACE_SIZE_Y_MAX + SPACE_SIZE_Y_MAX;
  int iX_2_Tmp = -1;
  int iY_2_Tmp = -1;

  bool bCellFound = false;

  int j = 0;
  int i = 0;

  // find upper left corner
  if(s->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(j = 0; j < s->GetHeight(); j++)
      for(i = 0; i < s->GetWidth(); i++)
        if(s->atGrid(i,j) != CELL_STATE_EMPTY)
        {
          if(i > iX_2_Tmp)
            iX_2_Tmp = i;
          if(j > iY_2_Tmp)
            iY_2_Tmp = j;

          bCellFound = true;
        }
  }
  else if(s->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(j = 0; j < s->GetHeight(); j++)
      for(i = 0; i < s->GetWidth(); i++)
        if(s->atTorus(i,j) != CELL_STATE_EMPTY)
        {
          if(i > iX_2_Tmp)
            iX_2_Tmp = i;
          if(j > iY_2_Tmp)
            iY_2_Tmp = j;

          bCellFound = true;
        }
  }

  // is there any live cell ?
  if(bCellFound)
  {
    bNonEmptyCellExists = true;
    iErrFlag = FITNESS_OK;

    iX_2 = iX_2_Tmp;
    iY_2 = iY_2_Tmp;
  }
  else
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: IdentifyCorners()\n";
      msgErr += "No live cell found in CSpace";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = FITNESS_ERR_NO_NON_EMPTY_CELL;
    return;
  }

  // find lower right corner
  if(s->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(j = (s->GetHeight() - 1); j >= 0; j--)
      for(i = (s->GetWidth() - 1); i >= 0; i--)
        if(s->atGrid(i,j) != CELL_STATE_EMPTY)
        {
          if(i < iX_1_Tmp)
            iX_1_Tmp = i;
          if(j < iY_1_Tmp)
            iY_1_Tmp = j;
        }
  }
  else if(s->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(j = (s->GetHeight() - 1); j >= 0; j--)
      for(i = (s->GetWidth() - 1); i >= 0; i--)
        if(s->atTorus(i,j) != CELL_STATE_EMPTY)
        {
          if(i < iX_1_Tmp)
            iX_1_Tmp = i;
          if(j < iY_1_Tmp)
            iY_1_Tmp = j;
        }
  }

  iX_1 = iX_1_Tmp;
  iY_1 = iY_1_Tmp;
}

//==============================================================
//==============================================================
/**
 *  returns coordinate of object corner on x-axes
 *
 *  @param corn         specifies which corner should be returned
 */

int CFitness::GetCornerPosX(int corn)
{
  if(corn == FITNESS_CORNER_LU)
    return iX_1;
  else if(corn == FITNESS_CORNER_RD)
    return iX_2;
  else
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: GetCornerPosX()\n";
      msgErr += "Unknown corner required";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return -1;
  }
}

//==============================================================
/**
 *  returns coordinate of object corner on y-axes
 *
 *  @param corn         specifies which corner should be returned
 */

int CFitness::GetCornerPosY(int corn)
{
  if(corn == FITNESS_CORNER_LU)
    return iY_1;
  else if(corn == FITNESS_CORNER_RD)
    return iY_2;
  else
  {
    {
      std::string msgErr  = "Class:    CFitness\n";
      msgErr += "Function: GetCornerPosY()\n";
      msgErr += "Unknown corner required";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return -1;
  }
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CFitness::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
/**
 *  return error flag
 */

int CFitness::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  this function calculates relative position of cell, on which
 *  is cell expected to be, result is written into "pointer params"
 *  result is added to each cell position from INIT space, and then is
 *  checked, if cell in ACTUAL space aton newly computed position have expected value
 *  so, it calculates position in ACT relative to INIT
 *
 *  @param dir          direction of movement
 *  @param distance     distance in "cell units" which object should go through
 *  @param *iMoveDir_X  pointer to var which determines x coordinate,
 *                      on which should cell be in actual step - result of this fc
 *  @param *iMoveDir_Y  pointer to var which determines y coordinate,
 *                      on which should cell be in actual step - result of this fc
 */

void CFitness::_MoveA(int dir, int distance, int *iMoveDir_X, int *iMoveDir_Y)
{
  // calculates position of cell in ACT space relative to this cell in INIT space
  switch(dir)
  {
  case MOVE_DIR_N:
    *iMoveDir_X =  0;
    *iMoveDir_Y =  distance;
    break;

  case MOVE_DIR_NW:
    *iMoveDir_X =  distance;
    *iMoveDir_Y =  distance;
    break;

  case MOVE_DIR_W:
    *iMoveDir_X =  distance;
    *iMoveDir_Y =  0;
    break;

  case MOVE_DIR_SW:
    *iMoveDir_X =  distance;
    *iMoveDir_Y = -distance;
    break;

  case MOVE_DIR_S:
    *iMoveDir_X =  0;
    *iMoveDir_Y = -distance;
    break;

  case MOVE_DIR_SE:
    *iMoveDir_X = -distance;
    *iMoveDir_Y = -distance;
    break;

  case MOVE_DIR_E:
    *iMoveDir_X = -distance;
    *iMoveDir_Y =  0;
    break;

  case MOVE_DIR_NE:
    *iMoveDir_X = -distance;
    *iMoveDir_Y =  distance;
    break;

  default:
    *iMoveDir_X =  0;
    *iMoveDir_Y =  0;
    break;
  }
}

//==============================================================
/**
 *  this function calculates fitness - compares every cell in INIT space with ACT space
 *  of course, is expected that object from INIT is shifted in ACT in given direction
 *  to given distance (direction and distance given from GUI)
 *  function uses _MoveA to determine position of object in ACT relative to INIT
 *  maximum fitness is returned, when all cells in ACT have expected values - so,
 *  more cells have expected values, higher the fitness will be
 *
 *  @param *spaceInit   pointer to init spce of ca
 *  @param *spaceAct    pointer to actual space of ca
 */

int CFitness::_Fitness_01(CSpace *spaceInit, CSpace *spaceAct)
{
  int iFitness   = 0;

  int iMoveDir_X = 0;
  int iMoveDir_Y = 0;

  // calculate relative position of each cell
  _MoveA(pConfigCore->GetMoveDirection(),pConfigCore->GetMoveDistance(),&iMoveDir_X,&iMoveDir_Y);

  int i = 0;
  int j = 0;

  // space type "GRID"
  if(spaceAct->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(j = 0; j < spaceAct->GetHeight(); j++)
      for(i = 0; i < spaceAct->GetWidth(); i++)
        // check, if cell from act space have expected position
        if(spaceAct->atGrid(i,j) == spaceInit->atGrid(i + iMoveDir_X,j + iMoveDir_Y))
          iFitness += 1;
        else
          iFitness += 0;
  }
  // space type "TORUS"
  else if(spaceAct->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(j = 0; j < spaceAct->GetHeight(); j++)
      for(i = 0; i < spaceAct->GetWidth(); i++)
        // check, if cell from act space have expected position
        if(spaceAct->atTorus(i,j) == spaceInit->atTorus(i + iMoveDir_X,j + iMoveDir_Y))
          iFitness += 1;
        else
          iFitness += 0;
  }

  return iFitness;
}

//==============================================================
/**
 *  provides same functionality as _Fitness_01, but is able to cumpute
 *  with direction "ANY" and calculates with variable distances (from 1 to
 *  distance given as param in GUI)
 *
 *  @param *spaceInit   pointer to init spce of ca
 *  @param *spaceAct    pointer to actual space of ca
 */

int CFitness::_Fitness_02(CSpace *spaceInit, CSpace *spaceAct)
{
  int iFitness    = 0;
  int iFitnessMax = 0;
  int iFitMaxDis  = 1;

  int iMoveDir    = pConfigCore->GetMoveDirection();
  int iMoveDir_X  = 0;
  int iMoveDir_Y  = 0;

  // direction is not "ANY" - calculating with only one direction
  if(iMoveDir != MOVE_DIR_ANY)
  {
    // loop for variable distances of movement
    for(int d = 1; d <= pConfigCore->GetMoveDistance(); d++)
    {
      // calculate relative position of each cell
      _MoveA(iMoveDir,d,&iMoveDir_X,&iMoveDir_Y);

      int i = 0;
      int j = 0;

      // compute through whole ca space
      for(j = 0; j < spaceAct->GetHeight(); j++)
      {
        for(i = 0; i < spaceAct->GetWidth(); i++)
        {
          // check, if cell from act space have expected position
          if(spaceAct->at(i,j) == spaceInit->at(i + iMoveDir_X,j + iMoveDir_Y))
            iFitness += 1;
          else
            iFitness += 0;
        }
      }

      // fitness of this distance "d" is higher as fitness from previous distances,
      //  use this distance as best
      if(iFitness > iFitnessMax)
      {
        iFitnessMax = iFitness;
        iFitMaxDis  = d;
      }
    }
  }
  else
  {
    // loop for all possible directions
    for(int m = MOVE_DIR_N; m <= MOVE_DIR_NE; m++)
    {
      // loop for variable distances of movement
      for(int d = 1; d <= pConfigCore->GetMoveDistance(); d++)
      {
        // calculate relative position of each cell
        _MoveA(m,d,&iMoveDir_X,&iMoveDir_Y);

        int i = 0;
        int j = 0;

        // compute through whole ca space
        for(j = 0; j < spaceAct->GetHeight(); j++)
        {
          for(i = 0; i < spaceAct->GetWidth(); i++)
          {
            // check, if cell from act space have expected position
            if(spaceAct->at(i,j) == spaceInit->at(i + iMoveDir_X,j + iMoveDir_Y))
              iFitness += 1;
            else
              iFitness += 0;
          }
        }

        // fitness of this distance "d" is higher as fitness from previous distances,
        //  use this distance as best
        if(iFitness > iFitnessMax)
        {
          iFitnessMax = iFitness;
          iFitMaxDis  = d;
        }
      }
    }
  }

  return iFitnessMax;
}

//==============================================================

