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

#ifndef GENOMETYPE2_H
#define GENOMETYPE2_H

//==============================================================

#include <bitset>
#include <cstring>

#include "../../Defines.h"

//==============================================================
/**
 *  this class contains genome for 9-neighborhood 2 states ca
 *  genome is linear array of BYTES, every element of array
 *  represents one gene
 *  index to genome is calculated from neighbor cells, see
 *  class CTFunction, function CalculateIndexTorus in
 *  ../../ca/TFunction.cpp file, line 280
 *  when index to genome is calculated, gene from this index is returned
 *  to CA - this gene represents new value of cell in next step of ca computation
 *  so this genome is built from values CELL_EMPTY and CELL_LIVE_1,
 *  which are only allowed values of ca space
 */

class CGenomeType2
{
public:
  CGenomeType2();
  CGenomeType2(const CGenomeType2& rSide);

  void SetGene(int index, BYTE gene);
  BYTE GetGene(int index);

  BYTE *GetGenome();

private:
  //std::bitset<GENOME_SIZE_BITS_TYPE_2> genome;
  BYTE genome[GENOME_SIZE_TYPE_2_9N];   //!< linear chromosome
};

//==============================================================

#endif // GENOMETYPE2_H

//==============================================================

