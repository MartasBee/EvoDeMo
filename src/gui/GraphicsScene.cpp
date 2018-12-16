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

#include "GraphicsScene.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param sizeX        count of cells in x axes
 *  @param sizeY        count of cells in y axes
 *  @param states       count of states (for cell config class)
 *  @param defState     default state of cell (for cell config class)
 *  @param edit         cell editable (for cell config class)
 */

CGraphicsScene::CGraphicsScene(int sizeX, int sizeY, int states, BYTE defState, bool edit)
{
  scene = NULL;

  errCell = new CGraphicsItem(999, 999, 2, -1);

  SetConfigStatesCount(states);
  SetConfigDefState(defState);
  SetConfigEditable(edit);

  //vecItem.clear();  // causes crash

  BuildScene(sizeX, sizeY);
}

//==============================================================
/**
 *  class destructor
 */

CGraphicsScene::~CGraphicsScene()
{
  DeleteScene();

  if(errCell != NULL)
    delete errCell;
}

//==============================================================
//==============================================================
/**
 *  returns pointer to graphics scene which containes cells
 */

QGraphicsScene * CGraphicsScene::GetScene()
{
  return scene;
}

//==============================================================
/**
 *  returns scene "width" - count of cells in x axes
 */

int CGraphicsScene::GetWidth()
{
  return (signed)iSizeX;
}

//==============================================================
/**
 *  returns scene "height" - count of cells in y axes
 */

int CGraphicsScene::GetHeight()
{
  return (signed)iSizeY;
}

//==============================================================
//==============================================================
/**
 *  sets scene "width"
 *
 *  @param w            count of cell's in x axes
 */

void CGraphicsScene::SetWidth(int w)
{
  if(w < SPACE_SIZE_X_MIN)
    w = SPACE_SIZE_X_MIN;
  else if(w > SPACE_SIZE_X_MAX)
    w = SPACE_SIZE_X_MAX;

  iSizeX = (unsigned)w;
}

//==============================================================
/**
 *  sets scene height
 *
 *  @param h            count of cell's in y axes
 */

void CGraphicsScene::SetHeight(int h)
{
  if(h < SPACE_SIZE_Y_MIN)
    h = SPACE_SIZE_Y_MIN;
  else if(h > SPACE_SIZE_Y_MAX)
    h = SPACE_SIZE_Y_MAX;

  iSizeY = (unsigned)h;
}

//==============================================================
//==============================================================
/**
 *  returns pointer to cell in given coords
 *
 *  @param posX         x coord of cell
 *  @param posY         y coord of cell
 */

CGraphicsItem* CGraphicsScene::GetCell(int posX, int posY)
{
  if((posX < 0) || (posY < 0))
    return errCell;

  unsigned int index = (posY * iSizeX) + posX;

  if(index >= vecItem.size())
    return errCell;
  else
    return vecItem.at(index);
}

//==============================================================
/**
 *  returns pointer to cell config class
 */

CGraphicsItemConfig* CGraphicsScene::GetCellConfig()
{
  return &config;
}

//==============================================================
/**
 *  sets states cout
 *
 *  @param sc           states count
 */

void CGraphicsScene::SetConfigStatesCount(int sc)
{
  config.SetStatesCount(sc);
  iStatesCount = (unsigned)config.GetStatesCount();
}

//==============================================================
/**
 *  sets cell's default state
 *
 *  @param ds           default state
 */

void CGraphicsScene::SetConfigDefState(BYTE ds)
{
  config.SetDefState(ds);
  byDefState = config.GetDefState();
}

//==============================================================
/**
 *  sets if cells are editable
 *
 *  @param e            are editable?
 */

void CGraphicsScene::SetConfigEditable(bool e)
{
  config.SetEditable(e);
  bEditable = config.GetEditable();
}

//==============================================================
//==============================================================
/**
 *  builds scene with cells
 *
 *  @param sizeX        count of cells in x axes
 *  @param sizeY        count of cells in y axes
 */

void CGraphicsScene::BuildScene(int sizeX, int sizeY)
{
  SetWidth(sizeX);
  SetHeight(sizeY);

  // delete old scene
  DeleteScene();

  // alloc new scene
  scene = new QGraphicsScene;

  int posX = 0;
  int posY = 0;
  int count = 0;

  int rangeItemX = (64 + 6) * iSizeX;
  int rangeItemY = (64 + 6) * iSizeY;

  // for all cells in 2d matrix
  for(int j = -(rangeItemY / 2); j < (rangeItemY / 2); j += 70)
  {
    for(int i = -(rangeItemX / 2); i < (rangeItemX / 2); i += 70)
    {
      QGraphicsItem *item = NULL;

      // alloc new cell
      item = new CGraphicsItem(posX, posY, &config);

      // push cell into vector
      CGraphicsItem *cell = (CGraphicsItem*)item;
      vecItem.push_back(cell);

      // add cell to scene
      item->setPos(QPointF(i,j));
      scene->addItem(item);

      count += 1;
      posX  += 1;
    }
    posY += 1;
    posX  = 0;
  }
}

//==============================================================
/**
 *  deletes scene with cells
 */

void CGraphicsScene::DeleteScene()
{
  for(int i = 0; i < (signed)vecItem.size(); i++)
  {
    // delete memory with cells
    CGraphicsItem *cell = vecItem.at(i);
    if(cell != NULL)
    {
      delete cell;
      vecItem.at(i) = NULL;
    }
  }

  // clear vector with pointers to cells
  vecItem.clear();

  if(scene != NULL)
    delete scene;
}

//==============================================================

