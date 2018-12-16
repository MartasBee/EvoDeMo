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

#include "GenomeType4_Nbh5.h"

//==============================================================
/**
 *  class constructor
 */

CGenomeType4_Nbh5::CGenomeType4_Nbh5()
{
  memset(genome,CELL_STATE_EMPTY,GENOME_SIZE_TYPE_4_5N);
}

//==============================================================
/**
 *  class constructor
 *
 *  @param &rSide       reference to class on right side of "="
 */

CGenomeType4_Nbh5::CGenomeType4_Nbh5(const CGenomeType4_Nbh5 &rSide)
{
  memcpy(genome,rSide.genome,GENOME_SIZE_TYPE_4_5N);
}

//==============================================================
//==============================================================
/**
 *  sets gene at given index of genome
 *
 *  @param index        index to genome
 *  @param gene         value of gene
 */

void CGenomeType4_Nbh5::SetGene(int index, BYTE gene)
{
  if((index >= 0) && (index < GENOME_SIZE_TYPE_4_5N))
  {
    if((gene == CELL_STATE_EMPTY) ||
       (gene == CELL_STATE_LIVE_1) ||
       (gene == CELL_STATE_LIVE_2) ||
       (gene == CELL_STATE_LIVE_3))
      genome[index] = gene;
    else
      genome[index] = CELL_STATE_EMPTY;
  }
}

//==============================================================
/**
 *  return value of gene from given index
 *
 *  @param index        index to genome
 */

BYTE CGenomeType4_Nbh5::GetGene(int index)
{
  BYTE tmp = CELL_STATE_EMPTY;

  if((index >= 0) && (index < GENOME_SIZE_TYPE_4_5N))
  {
    tmp = genome[index];
  }

  return tmp;
}

//==============================================================
/**
 *  return pointer to whole genome
 */

BYTE* CGenomeType4_Nbh5::GetGenome()
{
  return genome;
}

//==============================================================
