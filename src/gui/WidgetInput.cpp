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

#include "WidgetInput.h"
#include "ui_WidgetInput.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWidgetInput::CWidgetInput(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetInput)
{
  bApplyed   = false;
  bInitDone  = false;

  iSizeX     = SPACE_SIZE_X_DEFAULT;
  iSizeY     = SPACE_SIZE_Y_DEFAULT;
  iTmpSizeX  = iSizeX;
  iTmpSizeY  = iSizeY;

  iStates    = STATES_COUNT_DEFAULT;
  iTmpStates = iStates;

  iOutputSizeX   = 0;
  iOutputSizeY   = 0;
  iOutputMapPosX = 0;
  iOutputMapPosY = 0;
  bOutputApplyed = false;


  grid   = NULL;
  view   = NULL;
  //layout = NULL;

  ui->setupUi(this);

  ui->spinBox_x->setMinimum(SPACE_INPUT_SIZE_X_MIN);
  ui->spinBox_x->setMaximum(SPACE_INPUT_SIZE_X_MAX);
  ui->spinBox_y->setMinimum(SPACE_INPUT_SIZE_Y_MIN);
  ui->spinBox_y->setMaximum(SPACE_INPUT_SIZE_Y_MAX);
  ui->spinBox_s->setMinimum(STATES_COUNT_MIN);
  ui->spinBox_s->setMaximum(STATES_COUNT_MAX);

  ui->spinBox_x->setValue(iSizeX);
  ui->spinBox_y->setValue(iSizeY);
  ui->spinBox_s->setValue(iStates);

  ui->buttonSize->setEnabled(false);
  ui->buttonStates->setEnabled(false);


  //CellActStateChanged(CELL_STATE_LIVE_1);
  //EnableStateButtons(1);


  ui->buttonCancel->setEnabled(false);

  connect(ui->buttonSize,   SIGNAL(pressed()),         this, SLOT(SizeChangeUsed()));
  connect(ui->spinBox_x,    SIGNAL(valueChanged(int)), this, SLOT(SizeChangedX(int)));
  connect(ui->spinBox_y,    SIGNAL(valueChanged(int)), this, SLOT(SizeChangedY(int)));

  connect(ui->buttonStates, SIGNAL(pressed()),         this, SLOT(StatesChandeUsed()));
  connect(ui->spinBox_s,    SIGNAL(valueChanged(int)), this, SLOT(StatesChanged(int)));

  connect(ui->buttonImport, SIGNAL(pressed()),         this, SLOT(ImportPressed()));

  /*
  connect(ui->checkBoxEmpty, SIGNAL(stateChanged(int)), this, SLOT(CheckBoxEmptyPressed(int)));
  connect(ui->checkBoxLive1, SIGNAL(stateChanged(int)), this, SLOT(CheckBoxLive1Pressed(int)));
  connect(ui->checkBoxLive2, SIGNAL(stateChanged(int)), this, SLOT(CheckBoxLive2Pressed(int)));
  connect(ui->checkBoxLive3, SIGNAL(stateChanged(int)), this, SLOT(CheckBoxLive3Pressed(int)));
  */

  connect(ui->buttonApply,  SIGNAL(pressed()),         this, SLOT(ApplyPressed()));
  connect(ui->buttonCancel, SIGNAL(pressed()),         this, SLOT(CancelPressed()));

  //layout = new QGridLayout;
  //ui->frameGrid->setLayout(layout);

  SetupInputView();
}

//==============================================================
/**
 *  class destructor
 */

CWidgetInput::~CWidgetInput()
{
  DeleteInputGui();
  //delete layout;
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetInput::changeEvent(QEvent *e)
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
 *  returns pointer to input space scene
 */

CGraphicsScene *CWidgetInput::GetGrid()
{
  return grid;
}

//==============================================================
/**
 *  is input widget applyed?
 */

bool CWidgetInput::IsApplyed()
{
  return bApplyed;
}

//==============================================================
/**
 *  button init changed state - enable/disable any changes in widget
 */

void CWidgetInput::SetInitDone(bool id)
{
  bInitDone = id;

  if(bInitDone)
  {
    ui->buttonApply->setEnabled(false);
    ui->buttonCancel->setEnabled(false);
  }
  else
  {
    //ui->buttonApply->setEnabled(true);
    ui->buttonCancel->setEnabled(true);
  }
}

//==============================================================
/**
 *  sets output space width
 *
 *  @param x            output space width
 */

void CWidgetInput::SetOutputSizeX(int x)
{
  iOutputSizeX = (unsigned)x;
}

//==============================================================
/**
 *  sets output space height
 *
 *  @param y            output space height
 */

void CWidgetInput::SetOutputSizeY(int y)
{
  iOutputSizeY = (unsigned)y;
}

//==============================================================
/**
 *  sets output space x mapping position
 *
 *  @param x            x mapping coord
 */

void CWidgetInput::SetOutputMapPosX(int x)
{
  iOutputMapPosX = (unsigned)x;
}

//==============================================================
/**
 *  sets output space y mapping position
 *
 *  @param y            y mapping coord
 */

void CWidgetInput::SetOutputMapPosY(int y)
{
  iOutputMapPosY = (unsigned)y;
}

//==============================================================
/**
 *  sets, when output widget apply state changed
 *
 *  @param a            output widget apply state
 */

void CWidgetInput::SetOutputApplyed(bool a)
{
  bOutputApplyed = a;
}

//==============================================================
//==============================================================
/**
 *  spinbox with space width changed value
 *
 *  @param x            new space width
 */

void CWidgetInput::SizeChangedX(int x)
{
  if(iTmpSizeX != x)
  {
    iTmpSizeX = x;

    if(!ui->buttonSize->isEnabled())
      ui->buttonSize->setEnabled(true);
  }
}

//==============================================================
/**
 *  spinbox with space height changed value
 *
 *  @param y            new space height
 */

void CWidgetInput::SizeChangedY(int y)
{
  if(iTmpSizeY != y)
  {
    iTmpSizeY = y;

    if(!ui->buttonSize->isEnabled())
      ui->buttonSize->setEnabled(true);
  }
}

//==============================================================
/**
 *  space size change was applyed - set button was pressed
 */

void CWidgetInput::SizeChangeUsed()
{
  if((iTmpSizeX != (signed)iSizeX) || (iTmpSizeY != (signed)iSizeY))
  {
    // is possible to map input to output ?
    if(!CheckSize(iTmpSizeX, iTmpSizeY) || !CheckPos(iTmpSizeX, iTmpSizeY))
    {
      iTmpSizeX = (signed)iSizeX;
      iTmpSizeY = (signed)iSizeY;

      ui->spinBox_x->setValue(iTmpSizeX);
      ui->spinBox_y->setValue(iTmpSizeY);

      ui->buttonSize->setEnabled(false);

      return;
    }

    int iRC = QMessageBox::Yes;//QMessageBox::question(this,
                               //     tr("Grid Size"),
                               //     tr("Changing this value will cause lost of all data in grid.\nContinue?"),
                               //     QMessageBox::Yes | QMessageBox::Cancel);
    if(iRC == QMessageBox::Yes)
    {
      iSizeX = (unsigned)iTmpSizeX;
      iSizeY = (unsigned)iTmpSizeY;

      //SetupInputView();
      ReinitInputView();

      ui->buttonSize->setEnabled(false);

      // set spinboxes
      if(grid != NULL)
      {
        if(iSizeX != (unsigned)grid->GetWidth())
        {
          iSizeX = grid->GetWidth();
          iTmpSizeX = (signed)iSizeX;
          ui->spinBox_x->setValue(iSizeX);
        }
        if(iSizeY != (unsigned)grid->GetHeight())
        {
          iSizeY = grid->GetHeight();
          iTmpSizeY = iSizeY;
          ui->spinBox_y->setValue(iSizeY);
        }
      }
    }
    // "no" was pressed
    else
    {
      iTmpSizeX = (signed)iSizeX;
      iTmpSizeY = (signed)iSizeY;

      ui->spinBox_x->setValue(iTmpSizeX);
      ui->spinBox_y->setValue(iTmpSizeY);

      ui->buttonSize->setEnabled(false);
    }
  }
}

//==============================================================
/**
 *  spinbox with states count changed value
 *
 *  @param s            new states count
 */

void CWidgetInput::StatesChanged(int s)
{
  if(iTmpStates != s)
  {
    iTmpStates = s;

    ui->buttonStates->setEnabled(true);
  }
}

//==============================================================
/**
 *  count of space was changed - set button was pressed
 */

void CWidgetInput::StatesChandeUsed()
{
  if(iTmpStates != (signed)iStates)
  {
    int iRC = 0;

    // new space count is lower then old one
    if(iTmpStates < (signed)iStates)
    {
      QString msg = "Changing this value will cause lost of all cells which state is higher that new states count.\nContinue?";
      iRC = QMessageBox::question(this,
                                  "Cell States",
                                  msg,
                                  QMessageBox::Yes | QMessageBox::Cancel);
      if(iRC == QMessageBox::Yes)
      {
        // "delete" all cell with higher state than current
        iStates = (unsigned)iTmpStates;
        //SetupInputView();
        if(grid != NULL)
          grid->GetCellConfig()->SetStatesCount(iStates);
        for(int j = 0; j < (signed)iSizeY; j++)
          for(int i = 0; i < (signed)iSizeX; i++)
            if((int)grid->GetCell(i,j)->GetState() >= (signed)iStates)
              grid->GetCell(i,j)->SetState(CELL_STATE_EMPTY);

        ui->buttonStates->setEnabled(false);
      }
      // "no" was pressed
      else
      {
        ui->spinBox_s->setValue(iStates);
        ui->buttonStates->setEnabled(false);
        iTmpStates = (signed)iStates;
      }
    }
    // new states count is higher than old one
    else
    {
      iStates = (unsigned)iTmpStates;
      if(grid != NULL)
        grid->GetCellConfig()->SetStatesCount(iStates);

      ui->buttonStates->setEnabled(false);
    }
  }
}

//==============================================================
//==============================================================
/**
 *  sets input space width - used as extern call - when settings are loaded from file
 *
 *  @param x            new input space width
 */

void CWidgetInput::SetInputGridSizeX(int x)
{
  if(x < SPACE_INPUT_SIZE_X_MIN)
    x = SPACE_INPUT_SIZE_X_MIN;
  if(x > SPACE_INPUT_SIZE_X_MAX)
    x = SPACE_INPUT_SIZE_X_MAX;

  ui->spinBox_x->setValue(x);

  SizeChangedX(ui->spinBox_x->value());
  SizeChangeUsed();
}

//==============================================================
/**
 *  sets input space height - used as extern call - when settings are loaded from file
 *
 *  @param y            new input space height
 */

void CWidgetInput::SetInputGridSizeY(int y)
{
  if(y < SPACE_INPUT_SIZE_Y_MIN)
    y = SPACE_INPUT_SIZE_Y_MIN;
  if(y > SPACE_INPUT_SIZE_Y_MAX)
    y = SPACE_INPUT_SIZE_Y_MAX;

  ui->spinBox_y->setValue(y);

  SizeChangedY(ui->spinBox_y->value());
  SizeChangeUsed();
}

//==============================================================
/**
 *  sets input space size - used as extern call - when settings are loaded from file
 *
 *  @param x            new input space width
 *  @param y            new input space height
 */

void CWidgetInput::SetInputGridSize(int x, int y)
{
  if(x < SPACE_INPUT_SIZE_X_MIN)
    x = SPACE_INPUT_SIZE_X_MIN;
  if(x > SPACE_INPUT_SIZE_X_MAX)
    x = SPACE_INPUT_SIZE_X_MAX;
  if(y < SPACE_INPUT_SIZE_Y_MIN)
    y = SPACE_INPUT_SIZE_Y_MIN;
  if(y > SPACE_INPUT_SIZE_Y_MAX)
    y = SPACE_INPUT_SIZE_Y_MAX;

  ui->spinBox_x->setValue(x);
  ui->spinBox_y->setValue(y);

  SizeChangedX(ui->spinBox_x->value());
  SizeChangedY(ui->spinBox_y->value());

  SizeChangeUsed();
}

//==============================================================
//==============================================================
/**
 *  sets states count - used as extern call - when settings are loaded from file
 *
 *  @param s            new states count
 */

void CWidgetInput::SetStatesCount(int s)
{
  if(s < STATES_COUNT_MIN)
    s = STATES_COUNT_MIN;
  if(s > STATES_COUNT_MAX)
    s = STATES_COUNT_MAX;

  ui->spinBox_s->setValue(s);

  StatesChanged(ui->spinBox_s->value());
  StatesChandeUsed();
}

//==============================================================
//==============================================================
/**
 *  imports spce from png file
 */

void CWidgetInput::ImportPressed()
{
  // select file
  QString im = QFileDialog::getOpenFileName(this,
                                            tr("Import CA space"),
                                            QDir::currentPath(),
                                            tr("PNG files (*.png)"));

  if(!im.isEmpty())
  {
    QImage import;

    if(!import.load(im,"PNG"))
    {
      QMessageBox::critical(this,
                            "Import Space",
                            "Failed to import space",
                            QMessageBox::Ok);

      return;
    }

    int xTmp = import.width();
    int yTmp = import.height();

    // check if is possible to map new input spce to output one
    if(!CheckSize(xTmp, yTmp) || !CheckPos(xTmp, yTmp))
      return;

    if((xTmp < SPACE_INPUT_SIZE_X_MIN) || (xTmp > SPACE_INPUT_SIZE_X_MAX) ||
       (yTmp < SPACE_INPUT_SIZE_Y_MIN) || (yTmp > SPACE_INPUT_SIZE_Y_MAX))
    {
      QMessageBox::critical(this,
                            "Import Space",
                            "Import space is too big",
                            QMessageBox::Ok);
      return;
    }

    // set spinboxes
    iTmpSizeX = xTmp;
    iTmpSizeY = yTmp;

    ui->spinBox_x->setValue(iTmpSizeX);
    ui->spinBox_y->setValue(iTmpSizeY);

    iSizeX = (unsigned)iTmpSizeX;
    iSizeY = (unsigned)iTmpSizeY;

    // create new input space
    SetupInputView();

    ui->buttonSize->setEnabled(false);

    if(grid != NULL)
    {
      if(iSizeX != (unsigned)grid->GetWidth())
      {
        iSizeX = grid->GetWidth();
        iTmpSizeX = (signed)iSizeX;
        ui->spinBox_x->setValue(iSizeX);
      }
      if(iSizeY != (unsigned)grid->GetHeight())
      {
        iSizeY = grid->GetHeight();
        iTmpSizeY = iSizeY;
        ui->spinBox_y->setValue(iSizeY);
      }

      bool bL2 = false;
      bool bL3 = false;

      // map png into space - 1 pixel = 1 cell
      for(unsigned int j = 0; j < iSizeY; j++)
        for(unsigned int i = 0; i < iSizeX; i++)
        {
          BYTE tmp = CELL_STATE_EMPTY;
          QRgb pix = import.pixel(i,j);

          if(pix == CELL_COLOR_E)
            tmp = CELL_STATE_EMPTY;
          else if(pix == CELL_COLOR_L1)
            tmp = CELL_STATE_LIVE_1;
          else if(pix == CELL_COLOR_L2)
          {
            tmp = CELL_STATE_LIVE_2;
            bL2 = true;
          }
          else if(pix == CELL_COLOR_L3)
          {
            tmp = CELL_STATE_LIVE_3;
            bL3 = true;
          }
          else
            tmp = CELL_STATE_EMPTY;

          grid->GetCell(i,j)->SetState(tmp);
        }

      // check num of colors in png and set new states count
      if(bL2 && iStates < 3)
      {
        iTmpStates = 3;
        StatesChandeUsed();
        ui->spinBox_s->setValue(iStates);
      }
      if(bL3 && iStates < 4)
      {
        iTmpStates = 4;
        StatesChandeUsed();
        ui->spinBox_s->setValue(iStates);
      }
    }
  }
}

//==============================================================
//==============================================================
//==============================================================
/**
 *  when apply is pressed disable all functional tools in widget
 */

void CWidgetInput::ApplyPressed()
{
  if(!bInitDone)
  {
    if(!bApplyed)
    {
      if(!CheckSize(iSizeX, iSizeY))
        return;
      if(!CheckPos(iSizeX, iSizeY))
        return;

      if(iTmpSizeX != (signed)iSizeX)
      {
        iTmpSizeX = (signed)iSizeX;
        ui->spinBox_x->setValue(iTmpSizeX);
      }
      if(iTmpSizeY != (signed)iSizeY)
      {
        iTmpSizeY = (signed)iSizeY;
        ui->spinBox_y->setValue(iTmpSizeY);
      }
      if(iTmpStates != (signed)iStates)
      {
        iTmpStates = (signed)iStates;
        ui->spinBox_s->setValue(iTmpStates);
      }

      bApplyed = true;

      ui->buttonSize->setEnabled(false);
      ui->buttonStates->setEnabled(false);
      ui->buttonImport->setEnabled(false);

      ui->spinBox_x->setEnabled(false);
      ui->spinBox_y->setEnabled(false);
      ui->spinBox_s->setEnabled(false);

      if(grid != NULL)
        if(grid->GetCellConfig() != NULL)
          grid->GetCellConfig()->SetEditable(false);

      ui->buttonCancel->setEnabled(true);
      ui->buttonApply->setEnabled(false);

      emit(SignalWidgetInputApplyed(true));
    }
  }
  else
  {
    QMessageBox::information(this,
                             tr("Apply"),
                             tr("Initialization of Cellular Automata is done.\nDelete Cellular Automata first."),
                             QMessageBox::Ok);
  }
}

//==============================================================
/**
 *  when cancel is pressed, enable all functional tools in widget
 */

void CWidgetInput::CancelPressed()
{
  if(!bInitDone)
  {
    if(bApplyed)
    {
      bApplyed = false;

      ui->spinBox_x->setEnabled(true);
      ui->spinBox_y->setEnabled(true);
      ui->spinBox_s->setEnabled(true);

      if(grid != NULL)
        if(grid->GetCellConfig() != NULL)
          grid->GetCellConfig()->SetEditable(true);

      ui->buttonImport->setEnabled(true);

      ui->buttonCancel->setEnabled(false);
      ui->buttonApply->setEnabled(true);

      emit(SignalWidgetInputApplyed(false));
    }
  }
  else
  {
    QMessageBox::information(this,
                             tr("Cancel"),
                             tr("Cellular Automata is running.\nStop Cellular Automata first."),
                             QMessageBox::Ok);
  }
}

//==============================================================
/**
 *  creates input space scene
 *  used when application starts
 */

void CWidgetInput::SetupInputView()
{
  DeleteInputGui();

  //if(layout == NULL)
  //  return;
  if(ui->layoutFrameGrid == NULL)
    return;

  // create new scene and view to scene
  grid = new CGraphicsScene(iSizeX, iSizeY, iStates, CELL_STATE_EMPTY, true);
  view = new CGraphicsView(this);

  if((grid == NULL) || (view == NULL))
  {
    QMessageBox::critical(this,
                          "Widget Input",
                          "Lattice initialization failed\nTry again",
                          QMessageBox::Ok);
    DeleteInputGui();
    return;
  }

  view->view()->setScene(grid->GetScene());


  ui->layoutFrameGrid->addWidget(view);

  //layout->addWidget(view);
  //ui->frameGrid->setLayout(layout);
}

//==============================================================
/**
 *  reinits input space scene
 *  used when size of scene was changed
 */

void CWidgetInput::ReinitInputView()
{
  CGraphicsScene *gridTmp = new CGraphicsScene(iSizeX,iSizeY,iStates,CELL_STATE_EMPTY,true);
  if(gridTmp == NULL)
  {
    QMessageBox::critical(this,
                          "Widget Input",
                          "Lattice reinit failed\nTry again",
                          QMessageBox::Ok);
    return;
  }

  int iXSizeTmp = 0;
  int iYSizeTmp = 0;

  if(iSizeX <= (unsigned)grid->GetWidth())
    iXSizeTmp = iSizeX;
  else
    iXSizeTmp = grid->GetWidth();

  if(iSizeY <= (unsigned)grid->GetHeight())
    iYSizeTmp = iSizeY;
  else
    iYSizeTmp = grid->GetHeight();

  // set cell in new grid to values from old grid
  for(int j = 0; j < iYSizeTmp; j++)
    for(int i = 0; i < iXSizeTmp; i++)
      gridTmp->GetCell(i,j)->SetState(grid->GetCell(i,j)->GetState());

  DeleteInputGui();

  grid = gridTmp;
  view = new CGraphicsView(this);

  if(view == NULL)
  {
    QMessageBox::critical(this,
                          "Widget Input",
                          "Lattice re-initialization failed\nTry again",
                          QMessageBox::Ok);
    DeleteInputGui();
    return;
  }

  view->view()->setScene(grid->GetScene());

  ui->layoutFrameGrid->addWidget(view);


  //layout->addWidget(view);
  //ui->frameGrid->setLayout(layout);
}

//==============================================================
/**
 *  deletes input space scene
 */

void CWidgetInput::DeleteInputGui()
{
  //if((layout != NULL) && (view != NULL))
  //  layout->removeWidget(view);
  if(view != NULL)
    ui->layoutFrameGrid->removeWidget(view);

  if(view != NULL)
    delete view;
  if(grid != NULL)
    delete grid;

  view = NULL;
  grid = NULL;
}

//==============================================================
/**
 *  checks if is input grid is smaller or same as output
 *  output widget was applyed before input
 *
 *  @param x            width of input grid
 *  @param y            height of input grid
 */

bool CWidgetInput::CheckSize(int x, int y)
{
  if(bOutputApplyed)
  {
    if((x > (signed)iOutputSizeX) || (y > (signed)iOutputSizeY))
    {
      QMessageBox::information(this,
                               tr("Input Grid Size"),
                               tr("Input Grid Size is too big.\nUnable to map input grid to output."),
                               QMessageBox::Ok);

      return false;
    }
  }
  
  return true;
}

//==============================================================
/**
 *  checks if is possible to map input grid to output from given position
 *  output widget was applyed before input
 *
 *  @param x            x coord of mapping
 *  @param y            y coord of mapping
 */

bool CWidgetInput::CheckPos(int x, int y)
{
  if(bOutputApplyed)
  {
    if((x > signed(iOutputSizeX - iOutputMapPosX)) ||
        (y > signed(iOutputSizeY - iOutputMapPosY)))
    {
      QMessageBox::information(this,
                               tr("Input Grid Size"),
                               tr("Input Grid Size is too big.\nUnable to map input grid to output."),
                               QMessageBox::Ok);

      return false;
    }
  }
  
  return true;
}

//==============================================================
//==============================================================

