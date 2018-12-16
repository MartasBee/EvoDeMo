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

#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

//==============================================================

#include <QMainWindow>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>

#include "../Defines.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "WidgetInput.h"
#include "WidgetOutput.h"
#include "WidgetEvolution.h"
#include "WidgetExport.h"
#include "WidgetRunCA.h"
#include "WidgetRunEvo.h"

#include "../ExportConfig.h"
#include "../ImportConfig.h"
#include "../Core.h"

//==============================================================

namespace Ui
{
  class CWindowMain;
}

//==============================================================
/**
 *  main window off app, this class use all other gui classes
 */

class CWindowMain : public QMainWindow
{
  Q_OBJECT

public:
  CWindowMain(QWidget *parent = 0);
  ~CWindowMain();

protected:
  void changeEvent(QEvent *e);

private slots:
  // settings widgets apply slots
  void WidgetInputApplyed(bool a);
  void WidgetOutputApplyed(bool a);
  void WidgetEvolutionApplyed(bool a);
  void WidgetExportApplayed(bool a);

  // button pressed slots
  void InitPressed();
  void DeletePressed();
  void EvoStartPressed();
  void RunPressed();
  void StepPressed();
  void StopPressed();
  void TerminatePressed();

  // slots
  void EvolutionInit();
  void EvolutionRunning(bool r);

  void CellularAutomatonRunning(bool r);
  void CellularAutomatonStep();
  void SimulationDelete();

  // core slots
  void CoreCheckInitDone(int ccid);
  void CoreDataMapToGui();

  // menu actions slota
  void MenuActionAbout();
  void MenuActionExportRunConfig();
  void MenuActionImportRunConfig();

  // timer slot
  void GuiDisplayCaMove();

private:
  Ui::CWindowMain *ui;                    //!< pointer to widget (gui of this class)

  QTimer *timer;                          //!< pointer to timer class

  CWidgetInput     *widgetI;              //!< pointer to input widget
  CWidgetOutput    *widgetO;              //!< pointer to output widget
  CWidgetEvolution *widgetE;              //!< pointer to evolution widget
  CWidgetExport    *widgetEx;             //!< pointer to export widget
  CWidgetRunCA     *widgetRCA;            //!< pointer to run-ca widget
  CWidgetRunEvo    *widgetREvo;           //!< pointer to run-evo widget

  CCore            *core;                 //!< pointer to core class
  CExportConfig    exportConfig;          //!< class for exporting all settings
  CImportConfig    importConfig;          //!< class for importing all settings

  bool bWidgetInputApplyed;               //!< is input widget applyed?
  bool bWidgetOutputApplyed;              //!< is output widget applyed?
  bool bWidgetEvolutionApplyed;           //!< is evolution wodget applyed?
  bool bWidgetExportApplyed;              //!< is export widget applyed?

  bool bSimInitDone;                      //!< is core init done?
  bool bEvoRunning;                       //!< is evolution running?
  bool bCaRunning;                        //!< is simulator running?

  bool bOutputDone;                       //!< is some output done?

  unsigned int iGuiDisplayModeCaTimeout;  //!< simulator animation timeout


  // core functions
  bool InitCore();
  void DeleteCore();


  // check if all settings are applyed and show info on statusbar
  void CheckSettingApplyValidity();


  // check all layouts created in namespace ui
  bool CheckUiLayouts();


  /*
  // menu functions & vars
  void createActions();
  void createMenus();

  QMenu *menuFile;
  QMenu *menuHelp;

  QAction *actionExit;
  QAction *actionAbout;
  */
};

//==============================================================

#endif // WINDOWMAIN_H

//==============================================================

