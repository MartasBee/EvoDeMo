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

#include "RulesTable.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *gen         pointer to genome from genetic algorithm
 */

CRulesTable::CRulesTable(CGenome *gen)
{
  genome = gen;

  pConfigCore = NULL;
}

//==============================================================
//==============================================================
/**
 *  sets given genome for ca computations
 *
 *  @param *gen         pointer to genome from genetic algorithm
 */

void CRulesTable::SetGenome(CGenome *gen)
{
  genome = gen;
}

//==============================================================
/**
 *  returns pointer to actually used genome
 */

CGenome* CRulesTable::GetGenome()
{
  return genome;
}

//==============================================================
/**
 *  return gene from genome at given index
 *
 *  @param index        index to genome
 */

BYTE CRulesTable::at(int index)
{
  if(genome != NULL)
    return genome->GetGene(index);
  else
  {
    {
      std::string msgErr  = "Class:    CRulesTable\n";
      msgErr += "Function: at()\n";
      msgErr += "Genome pointer is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }

    return CELL_STATE_EMPTY;
  }
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CRulesTable::SetConfigCore(CConfigCore *pCC)
{
  pConfigCore = pCC;
}

//==============================================================

