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

#ifndef WIDGETRUN_H
#define WIDGETRUN_H

//==============================================================

#include <QWidget>
#include <QMessageBox>

#include "../Defines.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"

//==============================================================

namespace Ui
{
  class CWidgetRunCA;
}

//==============================================================
/**
 *  simulator's ca space widget - gui
 */

class CWidgetRunCA : public QWidget
{
  Q_OBJECT

public:
  CWidgetRunCA(QWidget *parent = 0);
  ~CWidgetRunCA();

  CGraphicsScene *GetGrid();

  void InitRunGrid(int sizeX, int sizeY, int states);
  void DeleteRun();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::CWidgetRunCA *ui;   //!< pointer to widget (gui of this class)

  CGraphicsScene *grid;   //!< pointer to scene class
  CGraphicsView  *view;   //!< pointer to view class

  unsigned int iSizeX;    //!< space width
  unsigned int iSizeY;    //!< space height
  unsigned int iStates;   //!< ca states count

  void SetRunGridSizeX(int x);
  void SetRunGridSizeY(int y);
  void SetRunGridStates(int s);

  void SetupRunGridView();
  void DeleteRunGridView();
};

//==============================================================

#endif // WIDGETRUN_H

//==============================================================

