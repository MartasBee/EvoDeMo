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

#ifndef GENOMETYPE3_H
#define GENOMETYPE3_H

//==============================================================

#include <bitset>

#include "../../Defines.h"

//==============================================================
/**
 *  this class contains genome for 5-neighborhood 3 states ca
 *  genome is created from bitset template class, every 2 elements
 *  of bitset represents one gene (2 bits are needed for int value "2")
 *  index to genome is calculated from neighbor cells, see
 *  class CTFunction, function CalculateIndexTorus in
 *  ../../ca/TFunction.cpp file, line 280
 *  when index to genome is calculated, gene from this index is returned
 *  to CA - this gene represents new value of cell in next step of ca computation
 *  so this genome is built from values CELL_EMPTY and CELL_LIVE_1, CELL_LIVE_2
 *  which are only allowed values of ca space
 */

class CGenomeType3
{
public:
  CGenomeType3();
  CGenomeType3(const CGenomeType3& rSide);

  void SetGene(int index, BYTE gene);
  BYTE GetGene(int index);

private:
  std::bitset<GENOME_SIZE_BITS_TYPE_3_9N> genome;   //!< linear chromosome
};

//==============================================================

#endif // GENOMETYPE3_H

//==============================================================

