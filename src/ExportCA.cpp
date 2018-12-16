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

#include "ExportCA.h"

//==============================================================
/**
 *  class constructor
 */

CExportCA::CExportCA()
{
  iErrFlag = 0;

  config = NULL;
}

//==============================================================
//==============================================================
/**
 *  exports ca space, using 10x zoom effect, into png
 *
 *  @param fileName     file path/name
 *  @param *space       pointer to ca space class
 */

void CExportCA::ExportCellularAutomaton(QString fileName, CSpace *space)
{
  if((config == NULL) || (space == NULL) || (fileName.isEmpty()))
  {
    return;
  }

  int zoom = 10;

  // create instance of QImage class with given dimensions (ca (x,y) size * zoom)
  QImage image((config->GetSpaceSizeX() * zoom),(config->GetSpaceSizeY() * zoom),QImage::Format_RGB32);

  // export cells as 10x10 pixel squares
  for(int jEx = 0; jEx < config->GetSpaceSizeY(); jEx++)
    for(int jIn = 0; jIn < zoom; jIn ++)
      if((jIn == 0) || (jIn == (zoom - 1)))
      {
        // write black horizontal line
        for(int tmp = 0; tmp < (config->GetSpaceSizeX() * zoom); tmp++)
          image.setPixel(tmp,((jEx * zoom) + jIn), 0xff000000);
      }
      else
      {
      for(int iEx = 0; iEx < config->GetSpaceSizeX(); iEx++)
        for(int iIn = 0; iIn < zoom; iIn++)

          // write black vertical line
          if((iIn == 0) || (iIn == (zoom -1)))
            image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xff000000);
          else
            switch(space->at(iEx,jEx))
            {
              case CELL_STATE_EMPTY:
                image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xffffffff);
                break;

              case CELL_STATE_LIVE_1:
                image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xffff0000);
                break;

              case CELL_STATE_LIVE_2:
                image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xff00ff00);
                break;

              case CELL_STATE_LIVE_3:
                image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xff0000ff);
                break;

              default:
                image.setPixel(((iEx * zoom) + iIn),((jEx * zoom) + jIn), 0xff888888);
              }
        }

  // export into png file
  if(!image.save(fileName,"PNG"))
  {
    {
      std::string msgErr  = "Class:    CExportCA\n";
      msgErr += "Function: ExportCellularAutomaton()\n";
      msgErr += "Error while saving png file ";
      msgErr += fileName.toStdString();

      if((config != NULL) && (config->GetExportLogCore() != NULL))
        config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }
  }
}

//==============================================================
/**
 *  this function is used for export input ca space from settings input ca tab
 *  does not using zoom effect, because these images can be later imported into app
 *
 *  @param fileName     file path/name
 *  @param *space       pointer to ca space class
 */

void CExportCA::ExportCellularAutomatonInput(QString fileName, CSpace *space)
{
  if((config == NULL) || (space == NULL) || (fileName.isEmpty()))
  {
    return;
  }

  // create instance of QImage class with given dimensions (ca (x,y) size)
  QImage image(config->GetSpaceSizeX(),config->GetSpaceSizeY(),QImage::Format_RGB32);

  // export cells as pixels
  for(int jEx = 0; jEx < config->GetSpaceSizeY(); jEx++)
    for(int iEx = 0; iEx < config->GetSpaceSizeX(); iEx++)
      switch(space->at(iEx,jEx))
      {
        case CELL_STATE_EMPTY:
          image.setPixel(iEx, jEx, CELL_COLOR_E);
          break;

        case CELL_STATE_LIVE_1:
          image.setPixel(iEx, jEx, CELL_COLOR_L1);
          break;

        case CELL_STATE_LIVE_2:
          image.setPixel(iEx, jEx, CELL_COLOR_L2);
          break;

        case CELL_STATE_LIVE_3:
          image.setPixel(iEx, jEx, CELL_COLOR_L3);
          break;

        default:
          image.setPixel(iEx, jEx, CELL_COLOR_ERR);
      }

  // export into png file
  if(!image.save(fileName,"PNG"))
  {
    {
      {
        std::string msgErr  = "Class:    CExportCA\n";
        msgErr += "Function: ExportCellularAutomatonInput()\n";
        msgErr += "Error while saving png file ";
        msgErr += fileName.toStdString();

        if((config != NULL) && (config->GetExportLogCore() != NULL))
          config->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }
    }
  }
}

//==============================================================
//==============================================================
/**
 *  sets config class
 */

void CExportCA::SetConfigCore(CConfigCore *cCore)
{
  config = cCore;
}

//==============================================================
//==============================================================
/**
 *  returns erro flag
 */

int CExportCA::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================

