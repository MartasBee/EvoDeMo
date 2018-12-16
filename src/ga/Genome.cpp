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

#include "Genome.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param typeG               genome type
 *  @param initGenerationId    id of generation, in which this genome was created
 *  @param initGenomeId        id of genome
 *  @param *pCC                pointer to config class
 */

CGenome::CGenome(int typeG, int initGenerationId, int initGenomeId, CConfigCore *pCC)
{
  iErrFlag = GENOME_OK;

  pConfigCore = pCC;


  iAncestorsCount       = 0;

  iThisGenerationId     = initGenerationId; // unknown generation
  iThisGenomeId         = initGenomeId;     // unknown id of this genome

  iThisInitGenerationId = initGenerationId; // id of generation in which this genome was created
  iThisInitGenomeId     = initGenomeId;     // id of this genome in creation time

  iParentGenerationId   = -1; // unknown parent generation
  iParentGenomeId       = -1; // unknown parent id


  iFitness              = FITNESS_VALUE_INIT;
  iDifferention         = 999999;
  dFitnessNormalized    = FITNESS_VALUE_INIT;

  iFitMaxStepCA         = 0;
  iFitnessMax           = iFitness;
  iDifferentionMin      = iDifferention;
  dFitnessMaxNormalized = dFitnessNormalized;


  iGenesMutated             = 0;
  iGenesMutatedTotal        = 0;
  iGenesMutatedAllAncestors = 0;


  if((typeG == GENOME_TYPE_2_9N) ||
     (typeG == GENOME_TYPE_3_9N) ||
     (typeG == GENOME_TYPE_4_9N) ||
     (typeG == GENOME_TYPE_2_5N) ||
     (typeG == GENOME_TYPE_3_5N) ||
     (typeG == GENOME_TYPE_4_5N))// ||
     //(typeG == GENOME_TYPE_2_INS) ||
     //(typeG == GENOME_TYPE_3_INS) ||
     //(typeG == GENOME_TYPE_4_INS))
    iGenomeType = typeG;
  // unknown genome type
  else
  {
    {
      std::string msgErr  = "Class:    CGenome\n";
      msgErr += "Function: CGenome()\n";
      msgErr += "Unknown CGenome type given, Default will be used";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iGenomeType = GENOME_TYPE_2_9N;
  }

  // create genome 9-neighborhood 2 state
  if(iGenomeType == GENOME_TYPE_2_9N)
  {
    genomeT2 = new CGenomeType2();
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 9-neighborhood 3 state
  else if(iGenomeType == GENOME_TYPE_3_9N)
  {
    genomeT2 = NULL;
    genomeT3 = new CGenomeType3();
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 9-neighborhood 4 state
  else if(iGenomeType == GENOME_TYPE_4_9N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = new CGenomeType4();

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 2 state
  else if(iGenomeType == GENOME_TYPE_2_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = new CGenomeType2_Nbh5();
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 3 state
  else if(iGenomeType == GENOME_TYPE_3_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = new CGenomeType3_Nbh5();
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 4 state
  else if(iGenomeType == GENOME_TYPE_4_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = new CGenomeType4_Nbh5();

    genomeT2_Ins = NULL;
  }
  // create genome instruction 2 state
  else if(iGenomeType == GENOME_TYPE_2_INS)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = new CGenomeType2_Ins();
  }
  // unknown genome
  else
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }

  // check if memory allocation is OK
  if((genomeT2 == NULL) && (genomeT3 == NULL) && (genomeT4 == NULL) &&
     (genomeT2_N5 == NULL) && (genomeT3_N5 == NULL) && (genomeT4_N5 == NULL))
  {
    {
      std::string msgErr  = "Class:    CGenome\n";
      msgErr += "Function: CGenome()\n";
      msgErr += "Memory allocation for genome failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GENOME_ERR_TX_NULL;
  }
  else
    iErrFlag = GENOME_OK;
}

//==============================================================
/**
 *  class constructor
 *
 *  @param &rSide       reference to genome class at right side of "="
 *  @param mode         class copy mode - DEEP or NEXT-GEN
 *  @param *pCC         pointer to config class
 */

CGenome::CGenome(const CGenome &rSide, int mode, CConfigCore *pCC)
{
  iErrFlag = GENOME_OK;

  pConfigCore = pCC;


  // next-gen mode - this genome will be evolved (e.g. mutated in act generation of ga)
  if(mode == GENOME_CONSTRUCT_COPY_MODE_NEXT_GEN)
  {
    iAncestorsCount       = rSide.iAncestorsCount + 1;

    iThisGenerationId     = -1; // unknown generation
    iThisGenomeId         = -1; // unknown id of this genome

    iThisInitGenerationId = -1; // id of generation in which this genome was created
    iThisInitGenomeId     = -1; // id of this genome in creation time

    iParentGenerationId   = rSide.iThisGenerationId;
    iParentGenomeId       = rSide.iThisGenomeId;


    iFitness              = 0;
    iDifferention         = 999999;
    dFitnessNormalized    = 0;

    iFitMaxStepCA         = 0;
    iFitnessMax           = 0;
    iDifferentionMin      = iDifferention;
    dFitnessMaxNormalized = 0;


    iGenesMutated             = 0;
    iGenesMutatedTotal        = 0;
    iGenesMutatedAllAncestors = rSide.iGenesMutatedAllAncestors + rSide.iGenesMutatedTotal;
  }
  // deep-copy mode - this genome won't be changed in act generation of ga
  else
  {
    iAncestorsCount       = rSide.iAncestorsCount;

    iThisGenerationId     = rSide.iThisGenerationId;
    iThisGenomeId         = rSide.iThisGenomeId;

    iThisInitGenerationId = rSide.iThisInitGenerationId;
    iThisInitGenomeId     = rSide.iThisInitGenomeId;

    iParentGenerationId   = rSide.iParentGenerationId;
    iParentGenomeId       = rSide.iParentGenomeId;


    iFitness              = rSide.iFitness;
    iDifferention         = rSide.iDifferention;
    dFitnessNormalized    = rSide.dFitnessNormalized;

    iFitMaxStepCA         = rSide.iFitMaxStepCA;
    iFitnessMax           = rSide.iFitnessMax;
    iDifferentionMin      = rSide.iDifferentionMin;
    dFitnessMaxNormalized = rSide.dFitnessMaxNormalized;


    iGenesMutated             = rSide.iGenesMutated;
    iGenesMutatedTotal        = rSide.iGenesMutatedTotal;
    iGenesMutatedAllAncestors = rSide.iGenesMutatedAllAncestors + rSide.iGenesMutatedTotal;
  }


  iGenomeType = rSide.iGenomeType;


  // create genome 9-neighborhood 2 state
  if(iGenomeType == GENOME_TYPE_2_9N)
  {
    genomeT2 = new CGenomeType2(*(rSide.genomeT2));
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 9-neighborhood 3 state
  else if(iGenomeType == GENOME_TYPE_3_9N)
  {
    genomeT2 = NULL;
    genomeT3 = new CGenomeType3(*(rSide.genomeT3));
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 9-neighborhood 4 state
  else if(iGenomeType == GENOME_TYPE_4_9N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = new CGenomeType4(*(rSide.genomeT4));

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 2 state
  else if(iGenomeType == GENOME_TYPE_2_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = new CGenomeType2_Nbh5(*(rSide.genomeT2_N5));
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 3 state
  else if(iGenomeType == GENOME_TYPE_3_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = new CGenomeType3_Nbh5(*(rSide.genomeT3_N5));
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }
  // create genome 5-neighborhood 4 state
  else if(iGenomeType == GENOME_TYPE_4_5N)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = new CGenomeType4_Nbh5(*(rSide.genomeT4_N5));

    genomeT2_Ins = NULL;
  }
  // create genome instruction 2 state
  else if(iGenomeType == GENOME_TYPE_2_INS)
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = new CGenomeType2_Ins(*(rSide.genomeT2_Ins));
  }
  // unknown genome
  else
  {
    genomeT2 = NULL;
    genomeT3 = NULL;
    genomeT4 = NULL;

    genomeT2_N5 = NULL;
    genomeT3_N5 = NULL;
    genomeT4_N5 = NULL;

    genomeT2_Ins = NULL;
  }

  // check if memory allocation is OK
  if((genomeT2 == NULL) && (genomeT3 == NULL) && (genomeT4 == NULL) &&
     (genomeT2_N5 == NULL) && (genomeT3_N5 == NULL) && (genomeT4_N5 == NULL))
  {
    {
      std::string msgErr  = "Class:    CGenome\n";
      msgErr += "Function: CGenome()\n";
      msgErr += "Memory allocation for genome failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GENOME_ERR_TX_NULL;
  }
  else
    iErrFlag = GENOME_OK;
}

//==============================================================
/**
 *  class destructor
 */

CGenome::~CGenome()
{
  if(genomeT2 != NULL)
    delete genomeT2;
  if(genomeT3 != NULL)
    delete genomeT3;
  if(genomeT4 != NULL)
    delete genomeT4;
  if(genomeT2_N5 != NULL)
    delete genomeT2_N5;
  if(genomeT3_N5 != NULL)
    delete genomeT3_N5;
  if(genomeT4_N5 != NULL)
    delete genomeT4_N5;
  if(genomeT2_Ins != NULL)
    delete genomeT2_Ins;
}

//==============================================================
//==============================================================
/**
 *  sets gene of genome to given value
 *
 *  @param index        index of gene in genome
 *  @param gene         value of gene
 */

void CGenome::SetGene(int index, BYTE gene)
{
  if(iGenomeType == GENOME_TYPE_2_9N)
  {
    if(genomeT2 != NULL)
      genomeT2->SetGene(index, gene);
  }
  else if(iGenomeType == GENOME_TYPE_3_9N)
  {
    if(genomeT3 != NULL)
      genomeT3->SetGene(index, gene);
  }
  else if(iGenomeType == GENOME_TYPE_4_9N)
  {
    if(genomeT4 != NULL)
      genomeT4->SetGene(index, gene);
  }
  else if(iGenomeType == GENOME_TYPE_2_5N)
  {
    if(genomeT2_N5 != NULL)
      genomeT2_N5->SetGene(index, gene);
  }
  else if(iGenomeType == GENOME_TYPE_3_5N)
  {
    if(genomeT3_N5 != NULL)
      genomeT3_N5->SetGene(index, gene);
  }
  else if(iGenomeType == GENOME_TYPE_4_5N)
  {
    if(genomeT4_N5 != NULL)
      genomeT4_N5->SetGene(index, gene);
  }
  else
  {
    {
      std::string msgErr  = "Class:    CGenome\n";
      msgErr += "Function: SetGene()\n";
      msgErr += "Unknown CGenome type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GENOME_ERR_UNKNOWN;
    return;
  }

  iErrFlag = GENOME_OK;
  return;
}

//==============================================================
/**
 *  return value of gene at given index, if index is out of range
 *  default value will be returned
 *
 *  @param index        index of gene
 */

BYTE CGenome::GetGene(int index)
{
  iErrFlag = GENOME_OK;

  if(iGenomeType == GENOME_TYPE_2_9N)
  {
    if(genomeT2 != NULL)
      return genomeT2->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else if(iGenomeType == GENOME_TYPE_3_9N)
  {
    if(genomeT3 != NULL)
      return genomeT3->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else if(iGenomeType == GENOME_TYPE_4_9N)
  {
    if(genomeT4 != NULL)
      return genomeT4->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else if(iGenomeType == GENOME_TYPE_2_5N)
  {
    if(genomeT2_N5 != NULL)
      return genomeT2_N5->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else if(iGenomeType == GENOME_TYPE_3_5N)
  {
    if(genomeT3_N5 != NULL)
      return genomeT3_N5->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else if(iGenomeType == GENOME_TYPE_4_5N)
  {
    if(genomeT4_N5 != NULL)
      return genomeT4_N5->GetGene(index);
    else
      return CELL_STATE_EMPTY;
  }
  else
  {
    {
      std::string msgErr  = "Class:    CGenome\n";
      msgErr += "Function: GetGene()\n";
      msgErr += "Unknown CGenome type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GENOME_ERR_UNKNOWN;
    return CELL_STATE_EMPTY;
  }
}

//==============================================================
//==============================================================
/**
 *  returns whole instruction genome
 */

CGenomeType2_Ins* CGenome::GetInstructionGenome()
{
  return genomeT2_Ins;
}

//==============================================================
//==============================================================
/**
 *  sets fitness of this genome
 *
 *  @param f            fitness
 *  @param caStep       step of ca, in which this fitness was reached
 */

void CGenome::SetFitness(int f, int d, int caStep)
{
  iFitness      = f;
  iDifferention = d;

  if(iFitness > iFitnessMax)
  {
    iFitnessMax       = iFitness;
    iDifferentionMin  = iDifferention;
    iFitMaxStepCA     = caStep;
  }
}

//==============================================================
/**
 *  sets fitness
 *
 *  @param f            fitness
 */

void CGenome::SetFitness(int f)
{
  iFitness = f;

  if(iFitness > iFitnessMax)
  {
    iFitnessMax = iFitness;
  }
}

//==============================================================
/**
 *  return fitness of actual step of ca
 */

int CGenome::GetFitness()
{
  return iFitness;
}

//==============================================================
/**
 *  return maximum fitness, which was reached during all steps of ca
 */

int CGenome::GetFitnessMax()
{
  return iFitnessMax;
}

//==============================================================
/**
 *  returns minimum differention, which was reached during all steps of ca
 */

int CGenome::GetDifferentionMin()
{
  return iDifferentionMin;
}

//==============================================================
/**
 *  return step of ca, in which max fitness was reached
 */

int CGenome::GetFitnessMaxStepCA()
{
  return iFitMaxStepCA;
}

//==============================================================
/**
 *  sets normalized fitness
 *
 *  @param fn           normalized fitness
 */

void CGenome::SetFitnessNorm(double fn)
{
  dFitnessNormalized = fn;

  if(dFitnessNormalized > dFitnessMaxNormalized)
    dFitnessMaxNormalized = dFitnessNormalized;
}

//==============================================================
/**
 *  returns formalized fitness
 */

double CGenome::GetFitnessNorm()
{
  return dFitnessNormalized;
}

//==============================================================
/**
 *  returns maximum mormalized fitness which was reached during all steps of ca
 */

double CGenome::GetFitnessMaxNorm()
{
  return dFitnessMaxNormalized;
}

//==============================================================
//==============================================================
/**
 *  return type of genome
 */

int CGenome::GetGenomeType()
{
  return iGenomeType;
}

//==============================================================
/**
 *  sets count of ancestor genomes
 *
 *  @param anc          ancestors count
 */

void CGenome::SetAncestorsCount(int anc)
{
  iAncestorsCount = anc;
}

//==============================================================
/**
 *  return count of ancestor genomes
 */

int CGenome::GetAncestorsCount()
{
  return iAncestorsCount;
}

//==============================================================
/**
 *  sets count of mutated genes in actual generation of ga
 *
 *  @param mgc          mutated genes count
 */

void CGenome::SetMutatedGenes(int mgc)
{
  iGenesMutated = mgc;
  iGenesMutatedTotal += mgc;
}

//==============================================================
/**
 *  return count of mutated genes from actual generation of ga
 */

int CGenome::GetMutatedGenes()
{
  return iGenesMutated;
}

//==============================================================
/**
 *  sets total count of mutated genes - this genome + ancestors
 *
 *  @param thisG        mutated genes of this genome
 *  @param ancestorsG   mutated genes of all ancestors
 */

void CGenome::SetMutatedGenesTotal(int thisG, int ancestorG)
{
  iGenesMutatedTotal = thisG;
  iGenesMutatedAllAncestors = ancestorG;
}

//==============================================================
/**
 *  returns total mutated genes of this genome
 */

int CGenome::GetMutatedGenesTotal()
{
  return iGenesMutatedTotal;
}

//==============================================================
/**
 *  return total mutated genes of all ancestor genomes
 */

int CGenome::GetMutatedGenesAllAncestors()
{
  return iGenesMutatedAllAncestors;
}

//==============================================================
//==============================================================
/**
 *  sets this genome actual id and actual generation id - generation in
 *  which this genome was created
 *
 *  @param generationId   id of ACTUAL generation
 *  @param genomeId       id of genome in ACTUAL generation
 */

void CGenome::SetThisGenomeId(int generationId, int genomeId)
{
  iThisGenerationId = generationId;
  iThisGenomeId     = genomeId;
}

//==============================================================
/**
 *  return this genome actual generation id
 */

int CGenome::GetThisGenerationId()
{
  return iThisGenerationId;
}

//==============================================================
/**
 *  returns this genome id in actual generation
 */

int CGenome::GetThisGenomeId()
{
  return iThisGenomeId;
}

//==============================================================
/**
 *  sets this genome init id and init generation id - generation in
 *  which this genome was created
 *
 *  @param generationInitId   id of INIT generation
 *  @param genomeInitId       id of genome in INIT generation
 */

void CGenome::SetThisInitGenomeId(int generationInitId, int genomeInitId)
{
  iThisInitGenerationId = generationInitId;
  iThisInitGenomeId     = genomeInitId;
}

//==============================================================
/**
 *  return this genome init generation id
 */

int CGenome::GetThisInitGenerationId()
{
  return iThisInitGenerationId;
}

//==============================================================
/**
 *  returns this genome id in init generation
 */

int CGenome::GetThisInitGenomeId()
{
  return iThisInitGenomeId;
}

//==============================================================
/**
 *  sets parent genome id and generation id - generation in which parent
 *  of this genome was created
 *
 *  @param generationId   id of PARENT generation
 *  @param genomeId       id of genome in PARENT generation
 */

void CGenome::SetParentGenomeId(int generationId, int genomeId)
{
  iParentGenerationId = generationId;
  iParentGenomeId     = genomeId;
}

//==============================================================
/**
 *  returns parent genome generation id
 */

int CGenome::GetParentGenerationId()
{
  return iParentGenerationId;
}

//==============================================================
/**
 *  returns parent id
 */

int CGenome::GetParentGenomeId()
{
  return iParentGenomeId;
}

//==============================================================
//==============================================================
/**
 *  return error flag
 */

int CGenome::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================

