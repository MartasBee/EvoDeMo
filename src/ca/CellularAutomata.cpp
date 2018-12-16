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

#include "CellularAutomata.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *configCore  pointer to config class
 */

CCellularAutomata::CCellularAutomata(CConfigCore *configCore)
{
  iErrFlag  = CA_OK;

  bInitDone = false;

  iStepsDone = 0;

  spaceInit = NULL;
  spaceAct  = NULL;
  spaceTmp  = NULL;
  spaceTmpX = NULL;

  pConfigCore = configCore;

  if(pConfigCore == NULL)
  {
    iErrFlag = CA_ERR_UNKNOWN;
    return;
  }

  // setting up transition function class
  tfunction.SetConfigCore(pConfigCore);
  tfunction.SetRulesTable(&rules);
}

//==============================================================
/**
 *  class destructor
 */

CCellularAutomata::~CCellularAutomata()
{
  DeleteSpace();
  DeleteSpaceInit();
}

//==============================================================
//==============================================================
/**
 *  makes one step of ca computation
 */

void CCellularAutomata::Step()
{
  // check if spaces are NULL
  if((spaceAct == NULL) || (spaceTmp == NULL))
    return;


  // calculate next space
  tfunction.NextSpace(spaceAct,spaceTmp);

  // switch pointers to tmp and actual space classes
  spaceTmpX = spaceAct;
  spaceAct  = spaceTmp;
  spaceTmp  = spaceTmpX;
  spaceTmpX = NULL;


  // inc number of steps done
  iStepsDone += 1;
}

//==============================================================
/**
 *  makes one step with special function GoL(), which does not
 *    using transition function class
 */

void CCellularAutomata::StepGoL()
{
  GoL();

  iStepsDone += 1;
}

//==============================================================
//==============================================================
/**
 *  inits memory needed for computation
 */

void CCellularAutomata::InitMemory()
{
  DeleteSpace();
  DeleteSpaceInit();

  // array with init configuration
  spaceInit = new CSpace(pConfigCore->GetSpaceType(),
                         pConfigCore->GetSpaceSizeX(),
                         pConfigCore->GetSpaceSizeY(),
                         pConfigCore->GetDefaultState(),
                         pConfigCore);

  // array with actual step
  spaceAct  = new CSpace(pConfigCore->GetSpaceType(),
                         pConfigCore->GetSpaceSizeX(),
                         pConfigCore->GetSpaceSizeY(),
                         pConfigCore->GetDefaultState(),
                         pConfigCore);

  // tmp array
  spaceTmp  = new CSpace(pConfigCore->GetSpaceType(),
                         pConfigCore->GetSpaceSizeX(),
                         pConfigCore->GetSpaceSizeY(),
                         pConfigCore->GetDefaultState(),
                         pConfigCore);

  spaceTmpX = NULL;

  // checking arrays
  if((spaceInit == NULL) || (spaceAct == NULL) || (spaceTmp == NULL))
  {
    {
      std::string msgErr  = "Class:    CCellularAutomata\n";
      msgErr += "Function: InitMemory()\n";
      msgErr += "Unable to alloc memory for CSpace";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = CA_ERR_GRID_NULL;

    DeleteSpace();
    DeleteSpaceInit();
  }
  else if((spaceInit->GetErrorFlag() != SPACE_OK) ||
          (spaceAct->GetErrorFlag()  != SPACE_OK) ||
          (spaceTmp->GetErrorFlag()  != SPACE_OK))
  {
    iErrFlag = CA_ERR_GRID_NULL;

    DeleteSpace();
    DeleteSpaceInit();
  }
  else
    iErrFlag = CA_OK;
}

//==============================================================
/**
 *  init spaces - copies init space into actual space
 */

void CCellularAutomata::InitSpace()
{
  if(pConfigCore->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    if(iErrFlag != CA_OK)
      return;

    for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
      for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
        spaceAct->atTorus(i,j) = spaceInit->atTorus(i,j);
  }
  else if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
  {
    if(iErrFlag != CA_OK)
      return;

    for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
      for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
        spaceAct->atGrid(i,j) = spaceInit->atGrid(i,j);
  }
  else
  {

  }
}

//==============================================================
/**
 *  reinitialization of CA
 */

void CCellularAutomata::ReInit()
{
  InitSpace();

  iStepsDone = 0;
}

//==============================================================
///==============================================================
/**
 *  returns pointer to rules table function
 */

CRulesTable* CCellularAutomata::GetRulesTable()
{
  return &rules;
}

//==============================================================
/**
 *  sets pointer to config class into this class and transition
 *    function class
 *
 *  @param *ccc         pointer to config core class
 */

void CCellularAutomata::SetConfigCore(CConfigCore *ccc)
{
  pConfigCore = ccc;

  tfunction.SetConfigCore(pConfigCore);
}

//==============================================================
//==============================================================
/**
 *  returns pointer to actual CA space
 */

CSpace* CCellularAutomata::GetSpace()
{
  return spaceAct;
}

//==============================================================
/**
 *  returns pointer to init ca space
 */

CSpace* CCellularAutomata::GetInitSpace()
{
  return spaceInit;
}

//==============================================================
//==============================================================
/**
 *  return number of done steps
 */

int CCellularAutomata::GetStepsDone()
{
  return iStepsDone;
}

//==============================================================
/**
 *  return error flag
 */

int CCellularAutomata::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
/**
 *  checking if initialization is done
 */

bool CCellularAutomata::IsInitDone()
{
  return bInitDone;
}

//==============================================================
//==============================================================
/**
 *  deletes actual and tmp ca spaces
 */

void CCellularAutomata::DeleteSpace()
{
  if(spaceAct != NULL)
    delete spaceAct;
  if(spaceTmp != NULL)
    delete spaceTmp;

  spaceAct  = NULL;
  spaceTmp  = NULL;
  spaceTmpX = NULL;
}

//==============================================================
/**
 *  deletes init ca space
 */

void CCellularAutomata::DeleteSpaceInit()
{
  if(spaceInit != NULL)
    delete spaceInit;

  spaceInit = NULL;
}

//==============================================================
//==============================================================
/**
 *  special funtion for "Game of Life" computations
 *    this function does not using chromosomes mapped into
 *    transition function
 */

void CCellularAutomata::GoL()
{
  int iLCC = 0;
  int iCCS = CELL_STATE_EMPTY;

  if((spaceAct == NULL) || (spaceTmp == NULL))
    return;

  for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
  {
    for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
    {

      // NEIGHBORHOOD
      for(int k = -1; k <= 1; k++)
      {
        for(int l = -1; l <= 1; l++)
        {
          if((k == 0) && (l == 0))
          {
            // CENTRAL CELL STATE
            if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
            {
              if((spaceAct->atGrid(i,j) == CELL_STATE_LIVE_1) ||
                  (spaceAct->atGrid(i,j) == CELL_STATE_LIVE_2) ||
                    (spaceAct->atGrid(i,j) == CELL_STATE_LIVE_3))
                iCCS = CELL_STATE_LIVE_1;
              else
                iCCS = CELL_STATE_EMPTY;
            }
            else if(pConfigCore->GetSpaceType() == SPACE_TYPE_TORUS)
            {
              if((spaceAct->atTorus(i,j) == CELL_STATE_LIVE_1) ||
                  (spaceAct->atTorus(i,j) == CELL_STATE_LIVE_2) ||
                    (spaceAct->atTorus(i,j) == CELL_STATE_LIVE_3))
                iCCS = CELL_STATE_LIVE_1;
              else
                iCCS = CELL_STATE_EMPTY;
            }

          }
          else
          {
            // 8-NEIGHBORHOOD CELLS
            if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
            {
              if((spaceAct->atGrid(i + l,j + k) == CELL_STATE_LIVE_1) ||
                  (spaceAct->atGrid(i + l,j + k) == CELL_STATE_LIVE_2) ||
                    (spaceAct->atGrid(i + l,j + k) == CELL_STATE_LIVE_3))
                iLCC += 1;
            }
            else if(pConfigCore->GetSpaceType() == SPACE_TYPE_TORUS)
            {
              if((spaceAct->atTorus(i + l,j + k) == CELL_STATE_LIVE_1) ||
                  (spaceAct->atTorus(i + l,j + k) == CELL_STATE_LIVE_2) ||
                    (spaceAct->atTorus(i + l,j + k) == CELL_STATE_LIVE_3))
                iLCC += 1;
            }
          }
        }
      }

      // grid type of space
      if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
      {
        if(iCCS == CELL_STATE_EMPTY)
        {
          if(iLCC == 3)
            spaceTmp->atGrid(i,j) = CELL_STATE_LIVE_1;
          else
            spaceTmp->atGrid(i,j) = CELL_STATE_EMPTY;
        }
        else
        {
          if((iLCC == 2) || (iLCC == 3))
            spaceTmp->atGrid(i,j) = CELL_STATE_LIVE_1;
          else
            spaceTmp->atGrid(i,j) = CELL_STATE_EMPTY;
        }
      }
      // torus type of space
      else
      {
        if(iCCS == CELL_STATE_EMPTY)
        {
          if(iLCC == 3)
            spaceTmp->atTorus(i,j) = CELL_STATE_LIVE_1;
          else
            spaceTmp->atTorus(i,j) = CELL_STATE_EMPTY;
        }
        else
        {
          if((iLCC == 2) || (iLCC == 3))
            spaceTmp->atTorus(i,j) = CELL_STATE_LIVE_1;
          else
            spaceTmp->atTorus(i,j) = CELL_STATE_EMPTY;
        }
      }

      iLCC = 0;
    }
  }

  // switch pointers
  spaceTmpX = spaceAct;
  spaceAct  = spaceTmp;
  spaceTmp  = spaceTmpX;
  spaceTmpX = NULL;
}

//==============================================================

