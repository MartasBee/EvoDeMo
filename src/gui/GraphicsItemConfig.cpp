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

#include "GraphicsItemConfig.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param statesC      states count
 *  @param defState     cell's default state
 *  @param edit         is cell editable ?
 */

CGraphicsItemConfig::CGraphicsItemConfig(int statesC, BYTE defState, bool edit)
{
  SetStatesCount(statesC);
  SetDefState(defState);
  SetEditable(edit);

  SetCellActState(CELL_STATE_ERR);
}

//==============================================================
//==============================================================
/**
 *  sets cell's states count
 *
 *  @param sc           states count
 */

void CGraphicsItemConfig::SetStatesCount(int sc)
{
  if(sc < STATES_COUNT_MIN)
    sc = STATES_COUNT_MIN;
  if(sc > STATES_COUNT_MAX)
    sc = STATES_COUNT_MAX;

  iCellStatesCount = (unsigned)sc;
}

//==============================================================
/**
 *  returns states count
 */

int CGraphicsItemConfig::GetStatesCount()
{
  return iCellStatesCount;
}

//==============================================================
/**
 *  sets cell's default state
 *
 *  @param ds           default state
 */

void CGraphicsItemConfig::SetDefState(BYTE ds)
{
  if((ds != CELL_STATE_EMPTY) &&
     (ds != CELL_STATE_LIVE_1) &&
     (ds != CELL_STATE_LIVE_2) &&
     (ds != CELL_STATE_LIVE_3))
    ds = CELL_STATE_EMPTY;

  byCellDefState = ds;
}

//==============================================================
/**
 *  returns cell's default state
 */

BYTE CGraphicsItemConfig::GetDefState()
{
  return byCellDefState;
}

//==============================================================
/**
 *  sets if cell is editable
 *
 *  @param e            is editable ?
 */

void CGraphicsItemConfig::SetEditable(bool e)
{
  bCellEditable = e;
}

//==============================================================
/**
 *  returns if cell is editable
 */

bool CGraphicsItemConfig::GetEditable()
{
  return bCellEditable;
}

//==============================================================
/**
 *  sets cell's "actual" state
 *  fc is used to set concrate state to which is cell set after clicking
 *
 *  @param as           actual state to set
 */

void CGraphicsItemConfig::SetCellActState(BYTE as)
{
  if((as != CELL_STATE_EMPTY) ||
     (as != CELL_STATE_LIVE_1) ||
     (as != CELL_STATE_LIVE_2) ||
     (as != CELL_STATE_LIVE_3))
    as = CELL_STATE_ERR;

  byCellActState = as;
}

//==============================================================
/**
 *  returns actual state to set
 */

BYTE CGraphicsItemConfig::GetCellActState()
{
  return byCellActState;
}

//==============================================================

