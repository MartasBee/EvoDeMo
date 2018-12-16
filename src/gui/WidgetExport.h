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

#ifndef WIDGETEXPORT_H
#define WIDGETEXPORT_H

//==============================================================

#include <QWidget>
#include <QFileDialog>
#include <QDir>

#include "../Defines.h"

//==============================================================

namespace Ui
{
  class CWidgetExport;
}

//==============================================================
/**
 *  export settings
 */

class CWidgetExport : public QWidget
{
  Q_OBJECT

public:
  CWidgetExport(QWidget *parent = 0);
  ~CWidgetExport();

  int GetGuiDataDisplayModeTimeout();
  int GetGuiDataDisplayModeCA();

  QString GetFileExportPath();

  int GetFileExportModeCA();
  int GetFileExportModeGA();

  void SetGuiDataDisplayModeTimeout(int to);
  void SetGuiDataDisplayModeCA(int dm);

  void SetFileExportModeCA(int mca);
  void SetFileExportModeGA(int mga);

  bool IsApplyed();
  void SetInitDone(bool id);

signals:
  void SignalWidgetExportApplyed(bool);

protected:
  void changeEvent(QEvent *e);

private slots:
  void GuiModeCATimeoutChanged(int t);
  void GuiModeCADisplayModeChanged(int ca);

  void FileExportPathChanged();
  void FileExportCAChanged(int index);
  void FileExportGAChanged(int index);

  void ApplyPressed();
  void CancelPressed();

private:
  Ui::CWidgetExport *ui;                //!< pointer to widget (gui of this class)

  unsigned int iGuiModeCA_Timeout;      //!< simulator's animation timeout
  int          iGuiModeCA_DisplayMode;  //!< simulator display mode

  QString actPath;                      //!< actual export path
  QString tmpPath;                      //!< tmp export path

  int iExportModeCA;                    //!< ca export mode
  int iExportModeGA;                    //!< ga export mode

  bool bApplyed;                        //!< is this widget applyed?
  bool bInitDone;                       //!< is app core init?
};

//==============================================================

#endif // WIDGETEXPORT_H

//==============================================================

