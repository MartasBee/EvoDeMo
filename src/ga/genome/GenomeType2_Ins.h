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

#ifndef GENOMETYPE2_INS_H
#define GENOMETYPE2_INS_H

//==============================================================

#define GENOME_INS__COUNT           16

#define GENOME_INS__TYPE_NOP        0
#define GENOME_INS__TYPE_IF         1

#define GENOME_INS__PRECON_0        0

#define GENOME_INS__BIT_INDEX_2_0   1
#define GENOME_INS__BIT_INDEX_2_1   2
#define GENOME_INS__BIT_INDEX_2_2   4
#define GENOME_INS__BIT_INDEX_2_3   8
#define GENOME_INS__BIT_INDEX_2_4   16
#define GENOME_INS__BIT_INDEX_2_5   32
#define GENOME_INS__BIT_INDEX_2_6   64
#define GENOME_INS__BIT_INDEX_2_7   128

//==============================================================

#include "../../Defines.h"

//==============================================================
/**
 *  this struct containt instruction based gene
 */

struct stGeneInstruction
{
  BYTE instruction;   //!< instruction type
  BYTE preCon;        //!< precondition
  BYTE preConLogic;   //!< precondition logic
  BYTE postCon;       //!< postcondition
};

//==============================================================
/**
 *  this class carry instruction-based genome for 2-state ca
 *  chromosome (genome) is created from 4-BYTE (char) structs
 *  struct contains instruction type (NOP or IF), precondition -
 *  precondition defines combination of cells in neighborhood,
 *  which shoul be active, one precon bit can define more cells
 *  preConLogic defines clutchs (???) AND or OR between preCon bits
 *  postcon defines value of cell, if instruction (gene) can be implemented
 *  on this cell
 */

class CGenomeType2_Ins
{
public:
  CGenomeType2_Ins();
  CGenomeType2_Ins(const CGenomeType2_Ins& rSide);

  struct stGeneInstruction *GetGene(int index);

  void SetInstruction(int index, BYTE instruction);
  BYTE GetInstruction(int index);

  void SetPreCondition(int index, BYTE preCon);
  BYTE GetPreCondition(int index);
  void SetPreConditionBit(int index, int bitIndex, bool preCon);
  bool GetPreConditionBit(int index, int bitIndex);

  void SetPreConditionLogic(int index, BYTE preConLog);
  BYTE GetPreConditionLogic(int index);
  void SetPreConditionLogicBit(int index, int bitIndex, bool preConLog);
  bool GetPreConditionLogicBit(int index, int bitIndex);

  void SetPostCondition(int index, BYTE postCon);
  BYTE GetPostCondition(int index);

private:
  struct stGeneInstruction genome[GENOME_INS__COUNT];   //!< chromosome

  struct stGeneInstruction errGene;                     //!< error gene

  void SetBitValue(BYTE *field, int index, bool value);
  BYTE GetBitValue(BYTE field, int index);
};

//==============================================================

#endif // GENOMETYPE2_INS_H

//==============================================================

