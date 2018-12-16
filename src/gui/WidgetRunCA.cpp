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

#include "WidgetRunCA.h"
#include "ui_WidgetRunCA.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWidgetRunCA::CWidgetRunCA(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetRunCA)
{
  ui->setupUi(this);

  grid = NULL;
  view = NULL;
}

//==============================================================
/**
 *  class destructor
 */

CWidgetRunCA::~CWidgetRunCA()
{
  DeleteRunGridView();
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetRunCA::changeEvent(QEvent *e)
{
  QWidget::changeEvent(e);
  switch (e->type())
  {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
      break;

    default:
      break;
  }
}

//==============================================================
//==============================================================
/**
 *  returns pointer tp ca space scene
 */

CGraphicsScene *CWidgetRunCA::GetGrid()
{
  return grid;
}

//==============================================================
/**
 *  inits simulator space
 *
 *  @param sizeX        space width
 *  @param sizeY        space height
 *  @param states       count of states
 */

void CWidgetRunCA::InitRunGrid(int sizeX, int sizeY, int states)
{
  SetRunGridSizeX(sizeX);
  SetRunGridSizeY(sizeY);
  SetRunGridStates(states);

  SetupRunGridView();
}

//==============================================================
/**
 *  public fc, which calls fc for deleting space
 */

void CWidgetRunCA::DeleteRun()
{
  DeleteRunGridView();
}

//==============================================================
//==============================================================
/**
 *  sets simulator space width
 *
 *  @param x            space width
 */

void CWidgetRunCA::SetRunGridSizeX(int x)
{
  if(x < SPACE_OUTPUT_SIZE_X_MIN)
    x = SPACE_OUTPUT_SIZE_X_MIN;
  else if(x > SPACE_OUTPUT_SIZE_X_MAX)
    x = SPACE_OUTPUT_SIZE_X_MAX;

  iSizeX = (unsigned)x;
}

//==============================================================
/**
 *  sets simulator space height
 *
 *  @param y            space height
 */

void CWidgetRunCA::SetRunGridSizeY(int y)
{
  if(y < SPACE_OUTPUT_SIZE_Y_MIN)
    y = SPACE_OUTPUT_SIZE_Y_MIN;
  else if(y > SPACE_OUTPUT_SIZE_Y_MAX)
    y = SPACE_OUTPUT_SIZE_Y_MAX;

  iSizeY = (unsigned)y;
}

//==============================================================
/**
 *  sets simulator sapce states count
 *
 *  @param s            states count
 */

void CWidgetRunCA::SetRunGridStates(int s)
{
  if(s < STATES_COUNT_MIN)
    s = STATES_COUNT_MIN;
  else if(s > STATES_COUNT_MAX)
    s = STATES_COUNT_MAX;

  iStates = (unsigned)s;
}

//==============================================================
/**
 *  creates simulator space
 */

void CWidgetRunCA::SetupRunGridView()
{
  DeleteRunGridView();

  grid = new CGraphicsScene(iSizeX, iSizeY, iStates, CELL_STATE_EMPTY, false);
  view = new CGraphicsView(this);
  view->view()->setScene(grid->GetScene());

  if(ui->gridLayoutRunCA != NULL)
    ui->gridLayoutRunCA->addWidget(view);
}

//==============================================================
/**
 *  deletes simulator space
 */

void CWidgetRunCA::DeleteRunGridView()
{
  if((ui->gridLayoutRunCA != NULL) && (view != NULL))
    ui->gridLayoutRunCA->removeWidget(view);

  if(view != NULL)
    delete view;
  if(grid != NULL)
    delete grid;

  view = NULL;
  grid = NULL;
}

//==============================================================

