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

#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

//==============================================================

#include <QGraphicsItem>
#include <QColor>
#include <QRect>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include "../Defines.h"
#include "GraphicsItemConfig.h"

//==============================================================
/**
 *  class represents one cell in gui space
 */

class CGraphicsItem : public QGraphicsItem
{
public:
  CGraphicsItem();
  CGraphicsItem(int posX, int posY, int states, BYTE defState);
  CGraphicsItem(int posX, int posY, CGraphicsItemConfig *c);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  void SetState(BYTE s);
  BYTE GetState();

  void SetEditable(bool b);
  bool IsEditable();

  int GetPosX();
  int GetPosY();

  int  GetStatesCount();
  void SetStatesCount(int sc);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
  unsigned int iGridPosX;       //!< x coord of cell in space
  unsigned int iGridPosY;       //!< y coord of cell in space

  BYTE byState;                 //!< current state of cell
  bool bEditable;               //!< is cell editable/clickable?

  int iStatesCount;             //!< states count

  CGraphicsItemConfig *config;  //!< pointer to cells' config class

  QColor color;                 //!< color of cell in gui
};

//==============================================================

#endif // GRAPHICSITEMCELL_H

//==============================================================

