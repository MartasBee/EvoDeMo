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

#include "GenomeType2_Ins.h"

//==============================================================
/**
 *  class constructor
 */

CGenomeType2_Ins::CGenomeType2_Ins()
{
  errGene.instruction = GENOME_INS__TYPE_NOP;
  errGene.preCon      = 0;
  errGene.preConLogic = 0;
  errGene.postCon     = 0;

  for(int i = 0; i < GENOME_INS__COUNT; i++)
  {
    genome[i].instruction = GENOME_INS__TYPE_NOP;
  }
}

//==============================================================
/**
 *  class constructor
 *
 *  @param &rSide       reference to class on right side of "="
 */

CGenomeType2_Ins::CGenomeType2_Ins(const CGenomeType2_Ins &rSide)
{
  for(int i = 0; i < GENOME_INS__COUNT; i++)
  {
    genome[i].instruction = rSide.genome[i].instruction;
    genome[i].preCon      = rSide.genome[i].preCon;
    genome[i].preConLogic = rSide.genome[i].preConLogic;
    genome[i].postCon     = rSide.genome[i].postCon;
  }
}

//==============================================================
//==============================================================
/**
 *  returns gene from given position of genome
 *
 *  @param index        index to gene from genome
 */

struct stGeneInstruction* CGenomeType2_Ins::GetGene(int index)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
    return &(genome[index]);
  else
    return &errGene;
}

//==============================================================
//==============================================================
/**
 *  sets instruction type of gene at given index of genome
 *
 *  @param index        index to gene from genome
 *  @param instruction  intruction type
 */

void CGenomeType2_Ins::SetInstruction(int index, BYTE instruction)
{
  if((instruction != GENOME_INS__TYPE_NOP) ||
     (instruction != GENOME_INS__TYPE_IF))
    return;

  if((index >= 0) && (index < GENOME_INS__COUNT))
    genome[index].instruction = instruction;
  else
    errGene.instruction = instruction;
}

//==============================================================
/**
 *  returns instruction type of gene at given index of genome
 *
 *  @param index        index to gene from genome
 */

BYTE CGenomeType2_Ins::GetInstruction(int index)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
    return genome[index].instruction;
  else
    return errGene.instruction;
}

//==============================================================
//==============================================================
/**
 *  sets precondition type of gene at given index of genome
 *
 *  @param index        index to gene from genome
 *  @param preCon       precondition
 */

void CGenomeType2_Ins::SetPreCondition(int index, BYTE preCon)
{
  if((preCon < 0) || (preCon > 255))
    return;

  if((index >= 0) && (index < GENOME_INS__COUNT))
    genome[index].preCon = preCon;
  else
    errGene.preCon = preCon;
}

//==============================================================
/**
 *  returns instruction type of gene at given index of genome
 *
 *  @param index        index to gene from genome
 */

BYTE CGenomeType2_Ins::GetPreCondition(int index)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
    return genome[index].preCon;
  else
    return errGene.preCon;
}

//==============================================================
/**
 *  sets one bit of precondition of gene at given index
 *
 *  @param index        index to gene from genome
 *  @param bitIndex     index of bit of precondition
 *  @param preCon       value of bit
 */

void CGenomeType2_Ins::SetPreConditionBit(int index, int bitIndex, bool preCon)
{
  if((bitIndex >= 0) && (bitIndex < 8))
  {
    if((index >= 0) && (index < GENOME_INS__COUNT))
      SetBitValue(&(genome[index].preCon),bitIndex,preCon);
    else
      SetBitValue(&(errGene.preCon),bitIndex,preCon);
  }
}

//==============================================================
/**
 *  returns one bit of precondition of gene at given index
 *
 *  @param index        index to gene from genome
 *  @param bitIndex     index of bit of precondition
 */

bool CGenomeType2_Ins::GetPreConditionBit(int index, int bitIndex)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
  {
    if((bitIndex >= 0) && (bitIndex < 8))
    {
      if(GetBitValue(genome[index].preCon, bitIndex) == 1)
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
  {
    if((bitIndex >= 0) && (bitIndex < 8))
    {
      if(GetBitValue(errGene.preCon, bitIndex) == 1)
        return true;
      else
        return false;
    }
    else
      return false;
  }
}

//==============================================================
//==============================================================
/**
 *  sets precondition logic - and OR or between bits of precondition
 *
 *  @param index        index to gene from genome
 *  @param preConLog    precondition logic
 */

void CGenomeType2_Ins::SetPreConditionLogic(int index, BYTE preConLog)
{
  if((preConLog < 0) || (preConLog > 255))
    return;

  if((index >= 0) && (index < GENOME_INS__COUNT))
    genome[index].preConLogic = preConLog;
  else
    errGene.preConLogic = preConLog;
}

//==============================================================
/**
 *  returns precondition logic - and OR or between bits of precondition
 *
 *  @param index        index to gene from genome
 */

BYTE CGenomeType2_Ins::GetPreConditionLogic(int index)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
    return genome[index].preConLogic;
  else
    return errGene.preConLogic;
}

//==============================================================
/**
 *  sets one bit of precondition logic of gene at given index
 *
 *  @param index        index to gene from genome
 *  @param bitIndex     index of bit of precondition logic
 *  @param preConLog    value of bit
 */

void CGenomeType2_Ins::SetPreConditionLogicBit(int index, int bitIndex, bool preConLog)
{
  if((bitIndex >= 0) && (bitIndex < 8))
  {
    if((index >= 0) && (index < GENOME_INS__COUNT))
      SetBitValue(&(genome[index].preConLogic),bitIndex,preConLog);
    else
      SetBitValue(&(errGene.preConLogic),bitIndex,preConLog);
  }
}

//==============================================================
/**
 *  returns one bit of precondition logic of gene at given index
 *
 *  @param index        index to gene from genome
 *  @param bitIndex     index of bit of precondition logic
 */

bool CGenomeType2_Ins::GetPreConditionLogicBit(int index, int bitIndex)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
  {
    if((bitIndex >= 0) && (bitIndex < 8))
    {
      if(GetBitValue(genome[index].preConLogic, bitIndex) == 1)
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
  {
    if((bitIndex >= 0) && (bitIndex < 8))
    {
      if(GetBitValue(errGene.preConLogic, bitIndex) == 1)
        return true;
      else
        return false;
    }
    else
      return false;
  }
}

//==============================================================
//==============================================================
/**
 *  sets postcondition of gene at given index
 *
 *  @param index        index to gene from genome
 *  @param postCon      postcondition
 */

void CGenomeType2_Ins::SetPostCondition(int index, BYTE postCon)
{
  if((postCon != CELL_STATE_EMPTY) ||
     (postCon != CELL_STATE_LIVE_1))// ||
     //(postCon != CELL_STATE_LIVE_2) ||
     //(postCon != CELL_STATE_LIVE_3))
    return;

  if((index >= 0) && (index < GENOME_INS__COUNT))
    genome[index].postCon = postCon;
  else
    errGene.postCon = postCon;
}

//==============================================================
/**
 *  returns postcondition of gene at given index
 *
 *  @param index        index to gene from genome
 */

BYTE CGenomeType2_Ins::GetPostCondition(int index)
{
  if((index >= 0) && (index < GENOME_INS__COUNT))
    return genome[index].postCon;
  else
    return errGene.postCon;
}

//==============================================================
//==============================================================
/**
 *  sets bit of given BYTE field at given bitIndex to given value
 *
 *  @param *field       pointer to BYTE field of some gene from genome
 *  @param index        index to bit of field
 *  @param value        value of bit
 */

void CGenomeType2_Ins::SetBitValue(BYTE *field, int index, bool value)
{
  BYTE tmp = 1;

  switch(index)
  {
  case 0:
    tmp = GENOME_INDEX_T2_2_0;
    break;

  case 1:
    tmp = GENOME_INDEX_T2_2_1;
    break;

  case 2:
    tmp = GENOME_INDEX_T2_2_2;
    break;

  case 3:
    tmp = GENOME_INDEX_T2_2_3;
    break;

  case 4:
    tmp = GENOME_INDEX_T2_2_4;
    break;

  case 5:
    tmp = GENOME_INDEX_T2_2_5;
    break;

  case 6:
    tmp = GENOME_INDEX_T2_2_6;
    break;

  case 7:
    tmp = GENOME_INDEX_T2_2_7;
    break;
  }

  if(!value)
  {
    tmp = ~tmp;
    *field &= tmp;
  }
  else
    *field |= tmp;
}

//==============================================================
/**
 *  return bit of given BYTE field at given bitIndex
 *
 *  @param field        BYTE field of some gene from genome
 *  @param index        index to bit of field
 */

BYTE CGenomeType2_Ins::GetBitValue(BYTE field, int index)
{
  BYTE tmp = 1;

  switch(index)
  {
  case 0:
    tmp = GENOME_INDEX_T2_2_0;
    break;

  case 1:
    tmp = GENOME_INDEX_T2_2_1;
    break;

  case 2:
    tmp = GENOME_INDEX_T2_2_2;
    break;

  case 3:
    tmp = GENOME_INDEX_T2_2_3;
    break;

  case 4:
    tmp = GENOME_INDEX_T2_2_4;
    break;

  case 5:
    tmp = GENOME_INDEX_T2_2_5;
    break;

  case 6:
    tmp = GENOME_INDEX_T2_2_6;
    break;

  case 7:
    tmp = GENOME_INDEX_T2_2_7;
    break;
  }

  field &= tmp;

  return field >> index;
}

//==============================================================

