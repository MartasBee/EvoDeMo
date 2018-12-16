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

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

//==============================================================

#include <QGraphicsScene>
#include <vector>

#include "GraphicsItem.h"
#include "GraphicsItemConfig.h"
#include "../Defines.h"

//==============================================================
/**
 *  contains graphics scene - scene with cells
 */

class CGraphicsScene
{
public:
  CGraphicsScene(int  sizeX    = SPACE_SIZE_X_DEFAULT,
                 int  sizeY    = SPACE_SIZE_Y_DEFAULT,
                 int  states   = STATES_COUNT_DEFAULT,
                 BYTE defState = STATE_DEFAULT,
                 bool edit     = false);
  ~CGraphicsScene();

  QGraphicsScene *GetScene();

  int GetWidth();
  int GetHeight();

  CGraphicsItem       *GetCell(int posX, int posY);
  CGraphicsItemConfig *GetCellConfig();

  void SetConfigStatesCount(int sc);
  void SetConfigDefState(BYTE s);
  void SetConfigEditable(bool e);

private:
  QGraphicsScene *scene;                //!< pointer to scene

  std::vector<CGraphicsItem*> vecItem;  //!< vector with pointers to cells

  CGraphicsItem       *errCell;         //!< error cell
  CGraphicsItemConfig config;           //!< cells' config class

  unsigned int iSizeX;                  //!< scene's width
  unsigned int iSizeY;                  //!< scene's height

  unsigned int  iStatesCount;           //!< states count
  BYTE          byDefState;             //!< default cell state
  bool          bEditable;              //!< are cells editable?s

  void SetWidth(int w);
  void SetHeight(int h);

  void BuildScene(int sizeX, int sizeY);
  void DeleteScene();
};

//==============================================================

#endif // GRAPHICSSCENEGRID_H

//==============================================================

