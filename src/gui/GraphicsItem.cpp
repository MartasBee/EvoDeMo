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

#include "GraphicsItem.h"

//==============================================================
/**
 *  class constructor
 */

CGraphicsItem::CGraphicsItem()
{
  iGridPosX = 999;
  iGridPosY = 999;
  byState   = -1;

  iStatesCount = 2;
  bEditable = false;

  config = NULL;
}

//==============================================================
/**
 *  class constructor
 *
 *  @param posX         x coord of cell
 *  @param posY         y coord of cell
 *  @param states       states count
 *  @param defState     default state
 */

CGraphicsItem::CGraphicsItem(int posX, int posY, int states, BYTE defState)
{
  if(posX < 0)
    posX = 0;
  if(posY < 0)
    posY = 0;

  iGridPosX = (unsigned)posX;
  iGridPosY = (unsigned)posY;
  byState   = defState;

  iStatesCount = states;
  bEditable    = true;

  config = NULL;

  setZValue((qreal)((posX + posY) % 2));

  if(bEditable)
    setFlags(ItemIsSelectable);
}

//==============================================================
/**
 *  class constructor
 *
 *  @param posX         x coord of cell
 *  @param posY         y coord of cell
 *  @param *c           pointer to CGraphicsItemConfig class
 */

CGraphicsItem::CGraphicsItem(int posX, int posY, CGraphicsItemConfig *c)
{
  if(posX < 0)
    posX = 0;
  if(posY < 0)
    posY = 0;

  iGridPosX = (unsigned)posX;
  iGridPosY = (unsigned)posY;

  config = c;

  setZValue((qreal)((posX + posY) % 2));
  if(config != NULL)
  {
    byState = config->GetDefState();

    if(config->GetEditable())
    {
      setFlags(ItemIsSelectable);
      bEditable = true;
    }
    else
      bEditable = false;
  }
  else
  {
    byState   = CELL_STATE_EMPTY;
    bEditable = false;
  }
}

//==============================================================
//==============================================================
/**
 *  returns rectangle which represets a cell
 */

QRectF CGraphicsItem::boundingRect() const
{
  return QRectF(0, 0, 64, 64);
}

//==============================================================
/**
 *  draws cell
 *
 *  @param *painter     pointer to QPainter class
 *  @param *option      pointet to QStyleOptionGraphicsItem class
 *  @param *widget      pointer to parent widget class
 */

void CGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

  // set color of cell
  if(byState == CELL_STATE_EMPTY)
  {
    color = Qt::white;
  }
  else if(byState == CELL_STATE_LIVE_1)
  {
    color = Qt::red;
  }
  else if(byState == CELL_STATE_LIVE_2)
  {
    color = Qt::green;
  }
  else if(byState == CELL_STATE_LIVE_3)
  {
    color = Qt::blue;
  }
  else if(byState == CELL_STATE_ERR)
  {
    color = Qt::yellow;
  }
  else
  {
    color = Qt::gray;
  }

  // if cell is selected - clicked
  if(option->state & QStyle::State_Selected)
    color = color.darker(250);

  const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

  // draw cell using painter in mode whoch dependes on Lovel Of Detail
  if(lod < 0.125)
  {
    painter->fillRect(QRect(0, 0, 64, 64), color);
  }
  else if(lod < 0.25)
  {
    QBrush b = painter->brush();
    painter->setBrush(color);
    painter->drawRect(2, 2, 62, 62);
    painter->setBrush(b);
  }
  else
  {
    QPen oldPen = painter->pen();
    QPen pen = oldPen;

    int width = 0;
    if(option->state & QStyle::State_Selected)
      width += 2;

    pen.setWidth(width);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
    painter->drawRect(QRect(2, 2, 62, 62));
    painter->setBrush(b);
  }

  // draw text
  if(lod > 0.9)
  {
    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    //painter->scale(0.8, 0.8);

    painter->drawText(10, 20, QString("[ %1 , %2 ]").arg(iGridPosX).arg(iGridPosY));

    if(byState == CELL_STATE_EMPTY)
      painter->drawText(10, 35, QString("Empty"));
    else if(byState == CELL_STATE_LIVE_1)
      painter->drawText(10, 35, QString("Live1"));
    else if(byState == CELL_STATE_LIVE_2)
      painter->drawText(10, 35, QString("Live2"));
    else if(byState == CELL_STATE_LIVE_3)
      painter->drawText(10, 35, QString("Live3"));
    else
      painter->drawText(10, 35, QString("Error"));

    painter->restore();
  }

  return;
}

//==============================================================
/**
 *  sets cell state
 *
 *  @param s            new state
 */

void CGraphicsItem::SetState(BYTE s)
{
  byState = s;
  update();
}

//==============================================================
/**
 *  returns cell state
 */

BYTE CGraphicsItem::GetState()
{
  return byState;
}

//==============================================================
/**
 *  sets if cell is editable - clickable
 *
 *  @param b            is editable?
 */

void CGraphicsItem::SetEditable(bool b)
{
  bEditable = b;
}

//==============================================================
/**
 *  returns if cell is editable
 */

bool CGraphicsItem::IsEditable()
{
  return bEditable;
}

//==============================================================
/**
 *  returns cell's x coord
 */

int CGraphicsItem::GetPosX()
{
  return (signed)iGridPosX;
}

//==============================================================
/**
 *  returns cell's y coord
 */

int CGraphicsItem::GetPosY()
{
  return (signed)iGridPosY;
}

//==============================================================
/**
 *  sets states count
 *
 *  @param sc           states count
 */

void CGraphicsItem::SetStatesCount(int sc)
{
  iStatesCount = sc;
}

//==============================================================
/**
 *  returns states count
 */

int CGraphicsItem::GetStatesCount()
{
  return iStatesCount;
}

//==============================================================
//==============================================================
/**
 *  reaction on mouse move
 *
 *  @param event        mouse event
 */

void CGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseMoveEvent(event);
}

//==============================================================
/**
 *  reaction on mouse button press event
 *
 *  @param event        mouse event
 */

void CGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if(config != NULL)
  {
    // if cell is editable, change cell's state
    if(config->GetEditable())
    {
      //if(config->GetCellActState() == CELL_STATE_ERR)
        byState = ((byState + 1) % config->GetStatesCount());
      //else
      //  byState = config->GetCellActState();
    }
  }
  else if(bEditable)
  {
    byState = ((byState + 1) % iStatesCount);
  }

  QGraphicsItem::mousePressEvent(event);
  update();
}

//==============================================================
/**
 *  reaction on mouse button release event
 *
 *  @param event        mouse event
 */

void CGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  //update();
}

//==============================================================

