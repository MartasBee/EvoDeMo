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

#ifndef WIDGETINPUT_H
#define WIDGETINPUT_H

//==============================================================

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QImage>

#include "../Defines.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "../InputCA.h"

//==============================================================

namespace Ui
{
  class CWidgetInput;
}

//==============================================================
/**
 *  input ca space settings
 */

class CWidgetInput : public QWidget
{
  Q_OBJECT
public:
  CWidgetInput(QWidget *parent = 0);
  ~CWidgetInput();

  CGraphicsScene *GetGrid();

  bool IsApplyed();
  void SetInitDone(bool id);

  void SetOutputSizeX(int x);
  void SetOutputSizeY(int y);
  void SetOutputMapPosX(int x);
  void SetOutputMapPosY(int y);
  void SetOutputApplyed(bool a);

  void SetInputGridSizeX(int x);
  void SetInputGridSizeY(int y);
  void SetInputGridSize(int x, int y);
  void SetStatesCount(int s);

signals:
  void SignalWidgetInputApplyed(bool);

protected:
  void changeEvent(QEvent *e);

private slots:
  void SizeChangedX(int x);
  void SizeChangedY(int y);
  void SizeChangeUsed();

  void StatesChanged(int s);
  void StatesChandeUsed();

  void ImportPressed();

  void ApplyPressed();
  void CancelPressed();

private:
  Ui::CWidgetInput *ui;           //!< pointer to widget (gui of this class)

  CGraphicsScene *grid;           //!< pointer to scene class
  CGraphicsView  *view;           //!< pointer to view class
  //QGridLayout    *layout;

  //CInputCA       inputCa;         // import ca space class

  unsigned int iSizeX;            //!< space width
  unsigned int iSizeY;            //!< space height
  unsigned int iStates;           //!< states count

  int iTmpSizeX;                  //!< tmp space width
  int iTmpSizeY;                  //!< tmp space height
  int iTmpStates;                 //!< tmp states count

  bool bApplyed;                  //!< is this widget applyed?
  bool bInitDone;                 //!< is app core init?

  unsigned int iOutputSizeX;      //!< output space width
  unsigned int iOutputSizeY;      //!< output space height
  unsigned int iOutputMapPosX;    //!< output space map coord x
  unsigned int iOutputMapPosY;    //!< output space map coord y
  bool bOutputApplyed;            //!< is output space widget applyed?

  void SetupInputView();
  void ReinitInputView();
  void DeleteInputGui();

  bool CheckSize(int x, int y);
  bool CheckPos(int x, int y);

  //void CellActStateChanged(int s);
  //void EnableStateButtons(int mode);
};

//==============================================================

#endif // WIDGETINPUT_H

//==============================================================

