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

#include <QtGui/QApplication>
#include "gui/WindowMain.h"

//==============================================================
/**
 *  main function, no comment needed
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CWindowMain win;
    win.show();

    return app.exec();
}

//==============================================================

