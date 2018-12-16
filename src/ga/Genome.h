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

#ifndef GENOME_H
#define GENOME_H

//==============================================================

#include <iostream>

#include "genome/GenomeType2.h"
#include "genome/GenomeType3.h"
#include "genome/GenomeType4.h"
#include "genome/GenomeType2_Nbh5.h"
#include "genome/GenomeType3_Nbh5.h"
#include "genome/GenomeType4_Nbh5.h"
#include "genome/GenomeType2_Ins.h"
#include "../ConfigCore.h"
#include "../Defines.h"

//==============================================================

#define GENOME_CONSTRUCT_COPY_MODE_DEEP       0
#define GENOME_CONSTRUCT_COPY_MODE_NEXT_GEN   1

//==============================================================
/**
 *  this class contains genome of GA
 *  using classes from ./genome/ folder - this classes contain
 *  genome itself, this class just make up-level iterface for them
 */

class CGenome
{
public:
  CGenome(int typeG            = GENOME_TYPE_2_9N,
          int initGenerationId = -1,
          int initGenomeId     = -1,
          CConfigCore *pCC     = NULL);
  CGenome(const CGenome& rSide,
          int mode             = GENOME_CONSTRUCT_COPY_MODE_NEXT_GEN,
          CConfigCore *pCC     = NULL);
  ~CGenome();


  // functions for work with genes
  void SetGene(int index, BYTE gene);
  BYTE GetGene(int index);


  // get instruction genome
  CGenomeType2_Ins *GetInstructionGenome();


  // functions for work with fitness value of genome
  void   SetFitness(int f, int d, int caStep);
  void   SetFitness(int f);
  int    GetFitness();

  int    GetFitnessMax();
  int    GetDifferentionMin();
  int    GetFitnessMaxStepCA();

  void   SetFitnessNorm(double fn);
  double GetFitnessNorm();
  double GetFitnessMaxNorm();


  // determine type of chromosome
  int  GetGenomeType();


  // count of ancestors
  void SetAncestorsCount(int anc);
  int  GetAncestorsCount();


  // count of mutated genes
  void SetMutatedGenes(int mgc);
  int  GetMutatedGenes();

  void SetMutatedGenesTotal(int thisG, int ancestorG);
  int  GetMutatedGenesTotal();
  int  GetMutatedGenesAllAncestors();


  // this chromosome settings
  void SetThisGenomeId(int generationId, int genomeId);
  int  GetThisGenerationId();
  int  GetThisGenomeId();

  void SetThisInitGenomeId(int generationInitId, int genomeInitId);
  int  GetThisInitGenerationId();
  int  GetThisInitGenomeId();


  // parent chromosome settings
  void SetParentGenomeId(int generationId, int genomeId);
  int  GetParentGenerationId();
  int  GetParentGenomeId();


  // check if any error happened
  int GetErrorFlag();

private:
  CGenomeType2 *genomeT2;           //!< pointer to instance of 9-neighborhood 2 state genome class
  CGenomeType3 *genomeT3;           //!< pointer to instance of 9-neighborhood 3 state genome class
  CGenomeType4 *genomeT4;           //!< pointer to instance of 9-neighborhood 4 state genome class

  CGenomeType2_Nbh5 *genomeT2_N5;   //!< pointer to instance of 5-neighborhood 2 state genome class
  CGenomeType3_Nbh5 *genomeT3_N5;   //!< pointer to instance of 5-neighborhood 3 state genome class
  CGenomeType4_Nbh5 *genomeT4_N5;   //!< pointer to instance of 5-neighborhood 4 state genome class

  CGenomeType2_Ins  *genomeT2_Ins;  //!< pointer to instance of instruction 2 state genome class

  CConfigCore *pConfigCore;         //!< pointer to config class

  int iGenomeType;                  //!< type of genome

  int    iFitness;                  //!< fitness in actual step of ca
  int    iDifferention;             //!< difference between perfect solution and actual solution

  int    iFitnessMax;               //!< maximum fitness which this genome was able to obtain in act ga generation
  int    iDifferentionMin;          //!< maximum fitness = minimum differention
  int    iFitMaxStepCA;             //!< step of ca in which max fitness was obtained

  double dFitnessNormalized;        //!< normalized fitness
  double dFitnessMaxNormalized;     //!< normalized max fitness

  int iGenesMutated;                //!< mutated genes of this genome in act generation
  int iGenesMutatedTotal;           //!< mutated genes of this genome during it's life time
  int iGenesMutatedAllAncestors;    //!< mutated genes of all ancestors of this genome

  int iAncestorsCount;              //!< ancestor count

  int iThisGenerationId;            //!< id of actual generation
  int iThisGenomeId;                //!< id of this genome in actual generation

  int iThisInitGenerationId;        //!< id of generation in which this genome was created
  int iThisInitGenomeId;            //!< id of this genome in it's init generation

  int iParentGenerationId;          //!< id of parent genome generation
  int iParentGenomeId;              //!< id of parent genome in it's generation

  int iErrFlag;
};

//==============================================================

#endif // GENOME_H

//==============================================================

