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

#include "TFunction.h"

//==============================================================
/**
 *  class constructor
 */

CTFunction::CTFunction()
{
  rules       = NULL;
  pConfigCore = NULL;

  iErrFlag = TFUNCTION_OK;
}

//==============================================================
//==============================================================
/**
 *  sets actual rules table, which mapping genome from ga
 *
 *  @param *rt          pointer to rules table class
 */

void CTFunction::SetRulesTable(CRulesTable *rt)
{
  rules = rt;
}

//==============================================================
/**
 *  sets config class
 */

void CTFunction::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
//==============================================================
/**
 *  computes new ca array from old one with rules table given
 *
 *  @param *sa          ca space actual
 *  @param *sn          ca space next
 */

void CTFunction::NextSpace(CSpace *sa, CSpace *sn)
{
  /*
  if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_INS)
    NextSpaceGenomeInstruction(sa,sn);
  else
    */
  NextSpaceGenomeStandard(sa,sn);
}

//==============================================================
//==============================================================
/**
 *  computes new ca space with standard, non-instruction genome
 *
 *  @param *sa          ca space actual
 *  @param *sn          ca space next
 */

void CTFunction::NextSpaceGenomeStandard(CSpace *sa, CSpace *sn)
{
  iErrFlag = TFUNCTION_OK;

  if(rules == NULL)
  {
    {
      std::string msgErr  = "Class:    CTFunction\n";
      msgErr += "Function: NextSpaceGenomeStandard()\n";
      msgErr += "Pointer to class CRulesTable is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = TFUNCTION_ERR_RULES_NULL;
    return;
  }
  if((sa == NULL) || (sn == NULL))
  {
    {
      std::string msgErr  = "Class:    CTFunction\n";
      msgErr += "Function: NextSpaceGenomeStandard()\n";
      msgErr += "Space pointer is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = TFUNCTION_ERR_TORUS_NULL;
    return;
  }
  if((sa->GetWidth() != sn->GetWidth()) ||
     (sa->GetHeight() != sn->GetHeight()))
  {
    {
      std::string msgErr  = "Class:    CTFunction\n";
      msgErr += "Function: NextSpaceGenomeStandard()\n";
      msgErr += "Actual & Next Spaces do not have same size";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = TFUNCTION_ERR_TORUSES_SIZE;
    return;
  }
  if(sa == sn)
  {
    {
      std::string msgErr  = "Class:    CTFunction\n";
      msgErr += "Function: NextSpaceGenomeStandard()\n";
      msgErr += "Actual & Next Space pointers are same";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = TFUNCTION_ERR_TORUSES_SAME;
    return;
  }

  if(sa->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(int j = 0; j < sa->GetHeight(); j++)
      for(int i = 0; i < sa->GetWidth(); i++)
        sn->atGrid(i,j) = rules->at(CalculateIndexGrid(sa, i, j));
  }
  else if(sa->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(int j = 0; j < sa->GetHeight(); j++)
      for(int i = 0; i < sa->GetWidth(); i++)
        sn->atTorus(i,j) = rules->at(CalculateIndexTorus(sa, i, j));
  }
  else
  {
    {
      std::string msgErr  = "Class:    CTFunction\n";
      msgErr += "Function: NextSpaceGenomeStandard()\n";
      msgErr += "Unknown space type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = TFUNCTION_ERR_UNKNOWN;
  }
}

//==============================================================
/**
 *  computes new ca space with instruction genome, NOT IMPLEMENTED
 *
 *  @param *sa          ca space actual
 *  @param *sn          ca space next
 */

void CTFunction::NextSpaceGenomeInstruction(CSpace *sa, CSpace *sn)
{
  if((sa == NULL) || (sn == NULL))
  {
    if(sa == NULL)
      sa = sn;
    else
      sn = sa;
  }
}

//==============================================================
//==============================================================
/**
 *  calculates index into genome using "grid" rules
 *
 *  @param *s           pointer to actual ca space
 *  @param x            x coordinate of actual cell
 *  @param y            y coordinate of actual cell
 */

int CTFunction::CalculateIndexGrid(CSpace *s, int x, int y)
{
  unsigned int index = 0;

  // 9-neighborhood, 4 states
  if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_9N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T4_4_8;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T4_4_7;
    index += s->atGrid(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T4_4_6;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T4_4_5;
    index += s->atGrid(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T4_4_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T4_4_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T4_4_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T4_4_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T4_4_0;
  }
  // 9-neighborhood, 3 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_9N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T3_3_8;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T3_3_7;
    index += s->atGrid(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T3_3_6;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T3_3_5;
    index += s->atGrid(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T3_3_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T3_3_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T3_3_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T3_3_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T3_3_0;
  }
  // 9-neighborhood, 2 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_9N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T2_2_8;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T2_2_7;
    index += s->atGrid(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T2_2_6;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T2_2_5;
    index += s->atGrid(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T2_2_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T2_2_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T2_2_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T2_2_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T2_2_0;
  }
  // 5-neighborhood, 2 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_5N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T2_2_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T2_2_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T2_2_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T2_2_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T2_2_0;
  }
  // 5-neighborhood, 3 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_5N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T3_3_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T3_3_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T3_3_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T3_3_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T3_3_0;
  }
  // 5-neighborhood, 4 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_5N)
  {
    index += s->atGrid(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T4_4_4;
    index += s->atGrid(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T4_4_3;
    index += s->atGrid(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T4_4_2;
    index += s->atGrid(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T4_4_1;
    index += s->atGrid(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T4_4_0;
  }

  return (signed)index;
}

//==============================================================
/**
 *  calculates index into genome using "torus" rules
 *
 *  @param *s           pointer to actual ca space
 *  @param x            x coordinate of actual cell
 *  @param y            y coordinate of actual cell
 */

int CTFunction::CalculateIndexTorus(CSpace *s, int x, int y)
{
  unsigned int index = 0;

  // 9-neighborhood, 4 states
  if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_9N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T4_4_8;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T4_4_7;
    index += s->atTorus(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T4_4_6;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T4_4_5;
    index += s->atTorus(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T4_4_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T4_4_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T4_4_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T4_4_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T4_4_0;
  }
  // 9-neighborhood, 3 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_9N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T3_3_8;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T3_3_7;
    index += s->atTorus(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T3_3_6;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T3_3_5;
    index += s->atTorus(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T3_3_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T3_3_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T3_3_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T3_3_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T3_3_0;
  }
  // 9-neighborhood, 2 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_9N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T2_2_8;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T2_2_7;
    index += s->atTorus(GRID_NEIGHBOR_POS_NW) * GENOME_INDEX_T2_2_6;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T2_2_5;
    index += s->atTorus(GRID_NEIGHBOR_POS_SW) * GENOME_INDEX_T2_2_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T2_2_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_SE) * GENOME_INDEX_T2_2_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T2_2_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_NE) * GENOME_INDEX_T2_2_0;
  }
  // 5-neighborhood, 2 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_5N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T2_2_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T2_2_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T2_2_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T2_2_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T2_2_0;
  }
  // 5-neighborhood, 3 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_5N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T3_3_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T3_3_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T3_3_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T3_3_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T3_3_0;
  }
  // 5-neighborhood, 4 states
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_5N)
  {
    index += s->atTorus(GRID_NEIGHBOR_POS_C)  * GENOME_INDEX_T4_4_4;
    index += s->atTorus(GRID_NEIGHBOR_POS_N)  * GENOME_INDEX_T4_4_3;
    index += s->atTorus(GRID_NEIGHBOR_POS_W)  * GENOME_INDEX_T4_4_2;
    index += s->atTorus(GRID_NEIGHBOR_POS_S)  * GENOME_INDEX_T4_4_1;
    index += s->atTorus(GRID_NEIGHBOR_POS_E)  * GENOME_INDEX_T4_4_0;
  }

  return (signed)index;
}

//==============================================================

