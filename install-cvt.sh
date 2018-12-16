#!/bin/bash

################################################################
#
#  Project:      EvoDeMo - Bachelor Thesis
#  Date:         May 10, 2010 (estimated)
##
#  Author:       Martin Balaz
#  Contact:      balaz.marti@gmail.com
#                xbalaz00@stud.fit.vutbr.cz
##
#  Institution:  Brno University of Technology
#                Faculty of Information Technology
#                www.fit.vutbr.cz
##
#  Copyright (c) 2010 by Martin Balaz
#
################################################################

# setting path for Qt 4.6.2 in CVT FIT BUT Brno
# http://www.fit.vutbr.cz/CVT/index.php

echo "setting path..."

PATH=/usr/local/share/Qt-4.6.2/qt/bin:$PATH

################################################################

echo "starting compilation..."

make -f Makefile 

################################################################

