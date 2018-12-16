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

#include "Crossover.h"

//==============================================================
/**
 *  class constructor
 */

CCrossover::CCrossover()
{
  pConfigCore = NULL;

  iErrFlag = CROSSOVER_OK;
}

//==============================================================
//==============================================================
/**
 *  performs crossover of given genomes - NOT IMPLEMENTED
 *
 *  @param *g1          pointer to 1st genome
 *  @param *g2          pointer to 2nd genome
 */

void CCrossover::Crossover(CGenome *g1, CGenome *g2)
{
  if((g1 == NULL) || (g2 == NULL))
  {
    iErrFlag = CROSSOVER_ERR_POINTER_NULL;
    return;
  }
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CCrossover::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
/**
 *  returns error flag
 */

int CCrossover::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================

