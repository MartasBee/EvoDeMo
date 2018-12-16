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

#ifndef WIDGETOUTPUT_H
#define WIDGETOUTPUT_H

//==============================================================

#include <QWidget>
#include <QMessageBox>

#include "../Defines.h"

//==============================================================

namespace Ui
{
  class CWidgetOutput;
}

//==============================================================
/**
 *  output sapce settings
 */

class CWidgetOutput : public QWidget
{
  Q_OBJECT

public:
  CWidgetOutput(QWidget *parent = 0);
  ~CWidgetOutput();

  int GetOutputGridSizeX();
  int GetOutputGridSizeY();

  int GetOutputMapPosX();
  int GetOutputMapPosY();

  int GetOutputArrayType();

  bool IsApplyed();
  void SetInitDone(bool id);

  void SetInputSizeX(int x);
  void SetInputSizeY(int y);
  void SetInputApplyed(bool a);


  void SetOutputGridSizeX(int x);
  void SetOutputGridSizeY(int y);

  void SetOutputMapPosX(int x);
  void SetOutputMapPosY(int y);

  void SetOutputArrayType(int st);

signals:
  void SignalWidgetOutputApplyed(bool);

protected:
  void changeEvent(QEvent *e);

private slots:
  void SizeChangedX(int x);
  void SizeChangedY(int y);

  void PosChangedX(int x);
  void PosChangedY(int y);

  void ArrayTypeChanged(int at);

  void ApplyPressed();
  void CancelPressed();

private:
  Ui::CWidgetOutput *ui;      //!< pointer to widget (gui of this class)

  unsigned int iSizeX;        //!< output space width
  unsigned int iSizeY;        //!< output space height
  unsigned int iMapPosX;      //!< mapping coord x
  unsigned int iMapPosY;      //!< mapping coord y

  int iOutputArrayType;       //!< output space type - 2d grid || torus

  unsigned int iInputSizeX;   //!< input space width
  unsigned int iInputSizeY;   //!< input space height
  bool bInputApplyed;         //!< is input widget applyed?

  bool bApplyed;              //!< is this widget applyed?
  bool bInitDone;             //!< is app core init?

  bool CheckSize(int x, int y);
  bool CheckPos(int x, int y);
};

//==============================================================

#endif // WIDGETOUTPUT_H

//==============================================================

