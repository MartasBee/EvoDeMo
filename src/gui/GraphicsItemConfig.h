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

#ifndef GRAPHICSITEMCONFIG_H
#define GRAPHICSITEMCONFIG_H

//==============================================================

#include "../Defines.h"

//==============================================================
/**
 *  contains some of cells' config settings
 */

class CGraphicsItemConfig
{
public:
  CGraphicsItemConfig(int  statesC  = STATES_COUNT_DEFAULT,
                      BYTE defState = CELL_STATE_EMPTY,
                      bool edit     = false);

  void SetStatesCount(int sc);
  int  GetStatesCount();

  void SetDefState(BYTE ds);
  BYTE GetDefState();

  void SetEditable(bool e);
  bool GetEditable();

  void SetCellActState(BYTE as);
  BYTE GetCellActState();

private:
  unsigned int iCellStatesCount;  //!< states count
  BYTE         byCellDefState;    //!< default stace
  bool         bCellEditable;     //!< are cells ediable?

  BYTE         byCellActState;    //!< actual state on which cell will be set after click
};

//==============================================================

#endif // GRAPHICSITEMCONFIG_H

//==============================================================

