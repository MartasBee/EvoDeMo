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

#include "GenomeType2.h"

//==============================================================
/**
 *  class constructor
 */

CGenomeType2::CGenomeType2()
{
  memset(genome,CELL_STATE_EMPTY,GENOME_SIZE_TYPE_2_9N);
}

//==============================================================
/**
 *  class constructor
 *
 *  @param &rSide       reference to class on right side of "="
 */

CGenomeType2::CGenomeType2(const CGenomeType2 &rSide)
{
  memcpy(genome,rSide.genome,GENOME_SIZE_TYPE_2_9N);
}

//==============================================================
//==============================================================
/**
 *  sets gene at given index of genome
 *
 *  @param index        index to genome
 *  @param gene         value of gene
 */

void CGenomeType2::SetGene(int index, BYTE gene)
{
  if((index >= 0) && (index < GENOME_SIZE_TYPE_2_9N))
  {
    if(gene == CELL_STATE_EMPTY)
    {
      genome[index] = 0;
    }
    else if(gene == CELL_STATE_LIVE_1)
    {
      genome[index] = 1;
    }
    else
    {
      genome[index] = 0;
    }
  }
}

//==============================================================
/**
 *  return value of gene from given index
 *
 *  @param index        index to genome
 */

BYTE CGenomeType2::GetGene(int index)
{
  BYTE tmp = CELL_STATE_EMPTY;

  if((index >= 0) && (index < GENOME_SIZE_TYPE_2_9N))
  {
    if(genome[index] == 0)
      tmp = CELL_STATE_EMPTY;
    else if(genome[index] == 1)
      tmp = CELL_STATE_LIVE_1;
    else
      tmp = genome[index];
  }

  return tmp;
}

//==============================================================
/**
 *  return pointer to whole genome
 */

BYTE* CGenomeType2::GetGenome()
{
  return genome;
}

//==============================================================

