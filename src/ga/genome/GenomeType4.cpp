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

#include "GenomeType4.h"

//==============================================================
/**
 *  class constructor
 */

CGenomeType4::CGenomeType4()
{
}

//==============================================================
/**
 *  class constructor
 *
 *  @param &rSide       reference to class on right side of "="
 */

CGenomeType4::CGenomeType4(const CGenomeType4 &rSide)
{
  genome.reset();
  genome |= rSide.genome;
}

//==============================================================
//==============================================================
/**
 *  sets gene at given index of genome
 *
 *  @param index        index to genome
 *  @param gene         value of gene
 */

void CGenomeType4::SetGene(int index, BYTE gene)
{
  if((index >= 0) && (index < GENOME_SIZE_TYPE_4_9N))
  {
    index *= 2;

    if(index < GENOME_SIZE_BITS_TYPE_4_9N)
    {
      if(gene == CELL_STATE_EMPTY)
      {
        genome[index]     = 0;
        genome[index + 1] = 0;
      }
      else if(gene == CELL_STATE_LIVE_1)
      {
        genome[index]     = 1;
        genome[index + 1] = 0;
      }
      else if(gene == CELL_STATE_LIVE_2)
      {
        genome[index]     = 0;
        genome[index + 1] = 1;
      }
      else if(gene == CELL_STATE_LIVE_3)
      {
        genome[index]     = 1;
        genome[index + 1] = 1;
      }
      else
      {
        genome[index]     = 0;
        genome[index + 1] = 0;
      }
    }
  }
}

//==============================================================
/**
 *  return value of gene from given index
 *
 *  @param index        index to genome
 */

BYTE CGenomeType4::GetGene(int index)
{
  BYTE tmp = 0;

  if((index >= 0) && (index < GENOME_SIZE_TYPE_4_9N))
  {
    index *= 2;

    if(index < GENOME_SIZE_BITS_TYPE_4_9N)
    {
      tmp = BYTE(genome[index + 1] * 2) + BYTE(genome[index]);

      if(tmp < CELL_STATE_EMPTY)
        tmp = CELL_STATE_EMPTY;
      else if(tmp > CELL_STATE_LIVE_3)
        tmp = CELL_STATE_LIVE_3;
    }
    else
      tmp = CELL_STATE_EMPTY;
  }

  return tmp;
}

//==============================================================

