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

#include "Mutation.h"

//==============================================================
/**
 * class constructor
 */

CMutation::CMutation()
{
  pConfigCore = NULL;

  iErrFlag = MUTATION_OK;
}

//==============================================================
//==============================================================
/**
 *  performs mutation of given genome
 *
 *  @param *g           pointer to genome which should be mutated
 */

void CMutation::Mutation(CGenome *g)
{
  if((pConfigCore == NULL) || (g == NULL))
  {
    {
      std::string msgErr  = "Class:    CMutation\n";
      msgErr += "Function: Mutation()\n";
      msgErr += "Pointer to CConfigCore or CGenome is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = MUTATION_ERR_POINTER_NULL;
    return;
  }


  /*
  if(config->GetGenomeType() == GENOME_TYPE_2_INS)
    _Mutation_Ins_01(g);
  else
    */
  _Mutation_01(g);
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CMutation::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
/**
 *  return error flag
 */

int CMutation::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  performs mutation of given genome
 *
 *  @param *g           pointer to genome which should be mutated
 */

void CMutation::_Mutation_01(CGenome *g)
{
  // if(g == NULL) is tested in fc Mutation(), which calls this one

  if(pConfigCore->GetMutationCount() <= 0)
    return;

  int randL  = 0; // mutation low value
  int randHP = 0; // mutation high Position - max index of genome
  int randHV = 0; // mutation hight Value - highest possible vlue of gene
  int iRandP = 0; // Position of gene for mutation
  int iRandV = 0; // new Value of gene
  int iRandE = 0; // mutation Execution probability

  int iMutGenesCount = 0;

  // setting up variables needed for mutation
  // 9-neighborhood 2 state genome
  if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_9N)
  {
    randHV = 199;
    randHP = GENOME_SIZE_TYPE_2_9N;
  }
  // 9-neighborhood 3 state genome
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_9N)
  {
    randHV = 299;
    randHP = GENOME_SIZE_TYPE_3_9N;
  }
  // 9-neighborhood 4 state genome
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_9N)
  {
    randHV = 399;
    randHP = GENOME_SIZE_TYPE_4_9N;
  }
  // 5-neighborhood 2 state genome
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_5N)
  {
    randHV = 199;
    randHP = GENOME_SIZE_TYPE_2_5N;
  }
  // 5-neighborhood 3 state genome
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_5N)
  {
    randHV = 299;
    randHP = GENOME_SIZE_TYPE_3_5N;
  }
  // 5-neighborhood 4 state genome
  else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_5N)
  {
    randHV = 399;
    randHP = GENOME_SIZE_TYPE_4_5N;
  }
  // unknown genome
  else
  {
    {
      std::string msgErr  = "Class:    CMutation\n";
      msgErr += "Function: _Mutation_01()\n";
      msgErr += "Unknown CGenome type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = MUTATION_ERR_UNKNOWN;
    return;
  }

  iErrFlag = MUTATION_OK;

  // loop for count of mutation genes
  for(int i = 0; i < pConfigCore->GetMutationCount(); i++)
  {
    // position of gene, which should be mutated
    iRandP = static_cast<int>(random.Uniform((unsigned long)randL,(unsigned long)randHP));

    // mutation probability
    iRandE = static_cast<int>(random.Uniform((unsigned long)0,(unsigned long)100));
    if(iRandE > pConfigCore->GetMutationProbability())
      continue;
    else
      iMutGenesCount += 1;

    // select new value of gene
    do
    {
      iRandV = static_cast<int>(random.Uniform((unsigned long)randL,(unsigned long)randHV) / 100);
    } while(iRandV == g->GetGene(iRandP));

    g->SetGene(iRandP,iRandV);
  }

  // mutate
  g->SetMutatedGenes(iMutGenesCount);
}

//==============================================================
/**
 *  new mutation function - NOT IMPLEMENTED
 *
 *  @param *g           pointer to genome which should be mutated
 */

void CMutation::_Mutation_02(CGenome *g)
{
  if(g == NULL)
    return;
}

//==============================================================
/**
 *  performs mutation of instruction genome - NOT IMPLEMENTED
 *
 *  @param *g           pointer to genome which should be mutated
 */

void CMutation::_Mutation_Ins_01(CGenome *g)
{
  if(g == NULL)
    return;
}

//==============================================================

