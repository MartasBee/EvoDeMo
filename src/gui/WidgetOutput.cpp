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

#include "WidgetOutput.h"
#include "ui_WidgetOutput.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent wodget
 */

CWidgetOutput::CWidgetOutput(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetOutput)
{
  iSizeX   = SPACE_SIZE_X_DEFAULT;
  iSizeY   = SPACE_SIZE_Y_DEFAULT;
  iMapPosX = 0;
  iMapPosY = 0;

  iOutputArrayType = SPACE_TYPE_TORUS;

  bApplyed        = false;
  bInitDone       = false;


  ui->setupUi(this);


  ui->comboBoxType->insertItem(SPACE_TYPE_GRID,  "Grid");
  ui->comboBoxType->insertItem(SPACE_TYPE_TORUS, "Torus");
  ui->comboBoxType->setCurrentIndex(iOutputArrayType);

  ui->spinBoxSizeX->setMinimum(SPACE_OUTPUT_SIZE_X_MIN);
  ui->spinBoxSizeX->setMaximum(SPACE_OUTPUT_SIZE_X_MAX);
  ui->spinBoxSizeY->setMinimum(SPACE_OUTPUT_SIZE_Y_MIN);
  ui->spinBoxSizeY->setMaximum(SPACE_OUTPUT_SIZE_Y_MAX);
  ui->spinBoxPosX->setMinimum(0);
  ui->spinBoxPosX->setMaximum(iSizeX - 1);
  ui->spinBoxPosY->setMinimum(0);
  ui->spinBoxPosY->setMaximum(iSizeY - 1);

  ui->spinBoxSizeX->setValue(iSizeX);
  ui->spinBoxSizeY->setValue(iSizeY);
  ui->spinBoxPosX->setValue(0);
  ui->spinBoxPosY->setValue(0);


  ui->buttonCancel->setEnabled(false);


  connect(ui->spinBoxSizeX, SIGNAL(valueChanged(int)), this, SLOT(SizeChangedX(int)));
  connect(ui->spinBoxSizeY, SIGNAL(valueChanged(int)), this, SLOT(SizeChangedY(int)));

  connect(ui->spinBoxPosX,  SIGNAL(valueChanged(int)), this, SLOT(PosChangedX(int)));
  connect(ui->spinBoxPosY,  SIGNAL(valueChanged(int)), this, SLOT(PosChangedY(int)));

  connect(ui->comboBoxType, SIGNAL(currentIndexChanged(int)), this, SLOT(ArrayTypeChanged(int)));

  connect(ui->buttonApply,  SIGNAL(pressed()), this, SLOT(ApplyPressed()));
  connect(ui->buttonCancel, SIGNAL(pressed()), this, SLOT(CancelPressed()));
}

//==============================================================
/**
 *  class destructor
 */

CWidgetOutput::~CWidgetOutput()
{
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  returns space width
 */

int CWidgetOutput::GetOutputGridSizeX()
{
  return iSizeX;
}

//==============================================================
/**
 *  returns space height
 */

int CWidgetOutput::GetOutputGridSizeY()
{
  return iSizeY;
}

//==============================================================
/**
 *  returns x mapping coord
 */

int CWidgetOutput::GetOutputMapPosX()
{
  return iMapPosX;
}

//==============================================================
/**
 *  returns y mapping coord
 */

int CWidgetOutput::GetOutputMapPosY()
{
  return iMapPosY;
}

//==============================================================
/**
 *  returns output space type
 */

int CWidgetOutput::GetOutputArrayType()
{
  return iOutputArrayType;
}

//==============================================================
/**
 *  is outpu widget applyed?
 */

bool CWidgetOutput::IsApplyed()
{
  return bApplyed;
}

//==============================================================
/**
 *  button init changed state - enable/disable any changes in widget
 */

void CWidgetOutput::SetInitDone(bool id)
{
  bInitDone = id;

  if(bInitDone)
  {
    ui->buttonApply->setEnabled(false);
    ui->buttonCancel->setEnabled(false);
  }
  else
  {
    ui->buttonCancel->setEnabled(true);
  }
}

//==============================================================
/**
 *  sets input space width
 *
 *  @param x            input space width
 */

void CWidgetOutput::SetInputSizeX(int x)
{
  iInputSizeX = x;
}

//==============================================================
/**
 *  sets input space height
 *
 *  @param y            input space height
 */

void CWidgetOutput::SetInputSizeY(int y)
{
  iInputSizeY = y;
}

//==============================================================
/**
 *  sets input widget apply state
 *
 *  @param a            input widget apply
 */

void CWidgetOutput::SetInputApplyed(bool a)
{
  bInputApplyed = a;
}

//==============================================================
//==============================================================
/**
 *  sets output space width - used as extern call - when settings are loaded from file
 *
 *  @param x            new output space width
 */

void CWidgetOutput::SetOutputGridSizeX(int x)
{
  if((x < SPACE_OUTPUT_SIZE_X_MIN) ||
     (x > SPACE_OUTPUT_SIZE_X_MAX))
    return;

  ui->spinBoxSizeX->setValue(x);

  SizeChangedX(ui->spinBoxSizeX->value());
}

//==============================================================
/**
 *  sets output space height - used as extern call - when settings are loaded from file
 *
 *  @param y            new output space height
 */

void CWidgetOutput::SetOutputGridSizeY(int y)
{
  if((y < SPACE_OUTPUT_SIZE_Y_MIN) ||
     (y > SPACE_OUTPUT_SIZE_Y_MAX))
    return;

  ui->spinBoxSizeY->setValue(y);

  SizeChangedY(ui->spinBoxSizeY->value());
}

//==============================================================
//==============================================================
/**
 *  sets x mapping coord - used as extern call - when settings are loaded from file
 *
 *  @param x            new x mapping coord
 */

void CWidgetOutput::SetOutputMapPosX(int x)
{
  if((x < 0) ||
     (x > signed(iSizeX - 1)))
    return;

  ui->spinBoxPosX->setValue(x);

  PosChangedX(ui->spinBoxPosX->value());
}

//==============================================================
/**
 *  sets y mapping coord - used as extern call - when settings are loaded from file
 *
 *  @param y            new y mapping coord
 */

void CWidgetOutput::SetOutputMapPosY(int y)
{
  if((y < 0) ||
     (y > signed(iSizeY - 1)))
    return;

  ui->spinBoxPosY->setValue(y);

  PosChangedY(ui->spinBoxPosY->value());
}

//==============================================================
//==============================================================
/**
 *  sets output space type - used as extern call - when settings are loaded from file
 *
 *  @param st           new output space type
 */

void CWidgetOutput::SetOutputArrayType(int st)
{
  if((st != SPACE_TYPE_GRID) &&
     (st != SPACE_TYPE_TORUS))
    return;

  ui->comboBoxType->setCurrentIndex(st);

  ArrayTypeChanged(ui->comboBoxType->currentIndex());
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetOutput::changeEvent(QEvent *e)
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
 *  output sapce width was changed
 *
 *  @param x            output space width from spinbox
 */

void CWidgetOutput::SizeChangedX(int x)
{
  if(iSizeX != (unsigned)x)
  {
    iSizeX = (unsigned)x;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  output space height was changed
 *
 *  @param y            output space height from spinbox
 */

void CWidgetOutput::SizeChangedY(int y)
{
  if(iSizeY != (unsigned)y)
  {
    iSizeY = (unsigned)y;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  x mapping position was changed
 *
 *  @param x            x mapping position from spinbox
 */

void CWidgetOutput::PosChangedX(int x)
{
  if(iMapPosX != (unsigned)x)
  {
    iMapPosX = (unsigned)x;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  y mapping coord was changed
 *
 *  @param y            y mapping coord from spinbox
 */

void CWidgetOutput::PosChangedY(int y)
{
  if(iMapPosY != (unsigned)y)
  {
    iMapPosY = (unsigned)y;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  ca space type was changed
 *
 *  @param at           new array type from combobox
 */

void CWidgetOutput::ArrayTypeChanged(int at)
{
  if(iOutputArrayType != at)
  {
    iOutputArrayType = at;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  when apply is pressed disable all functional tools in widget
 */

void CWidgetOutput::ApplyPressed()
{
  if(!bInitDone)
  {
    if(!bApplyed)
    {
      if(!CheckSize(iSizeX, iSizeY))
        return;
      if(!CheckPos(iMapPosX, iMapPosY))
        return;

       bApplyed = true;

      ui->spinBoxSizeX->setEnabled(false);
      ui->spinBoxSizeY->setEnabled(false);

      ui->spinBoxPosX->setEnabled(false);
      ui->spinBoxPosY->setEnabled(false);

      ui->comboBoxType->setEnabled(false);

      ui->buttonCancel->setEnabled(true);
      ui->buttonApply->setEnabled(false);

      emit(SignalWidgetOutputApplyed(true));
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

void CWidgetOutput::CancelPressed()
{
  if(!bInitDone)
  {
    if(bApplyed)
    {
      bApplyed = false;

      ui->spinBoxSizeX->setEnabled(true);
      ui->spinBoxSizeY->setEnabled(true);

      ui->spinBoxPosX->setEnabled(true);
      ui->spinBoxPosY->setEnabled(true);

      ui->comboBoxType->setEnabled(true);

      ui->buttonCancel->setEnabled(false);
      ui->buttonApply->setEnabled(true);

      emit(SignalWidgetOutputApplyed(false));
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
//==============================================================
/**
 *  checks if is input grid is smaller or same as output
 *  input widget was applyed before output
 *
 *  @param x            width of input grid
 *  @param y            height of input grid
 */

bool CWidgetOutput::CheckSize(int x, int y)
{
  if(bInputApplyed)
  {
    if((x < (signed)iInputSizeX) || (y < (signed)iInputSizeY))
    {
      QMessageBox::information(this,
                               tr("Output Grid Size"),
                               tr("Output Grid must have bigger or same size that Input Grid"),
                               QMessageBox::Ok);

      return false;
    }
  }

  return true;
}

//==============================================================
/**
 *  checks if is possible to map input grid to output from given position
 *  input widget was applyed before output
 *
 *  @param x            x coord of mapping
 *  @param y            y coord of mapping
 */

bool CWidgetOutput::CheckPos(int x, int y)
{
  if(bInputApplyed)
  {
    if((iInputSizeX > (iSizeX - x)) || (iInputSizeY > (iSizeY - y)))
    {
      QMessageBox::information(this,
                               tr("Map position"),
                               tr("Position mapping point is too big.\nUnable to map input grid to Output.\n"),
                               QMessageBox::Ok);

      return false;
    }
  }

  return true;
}

//==============================================================

