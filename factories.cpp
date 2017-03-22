/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  factories
*
*  Created: 3 2017 by rodney
*
*  Copyright 2017 rodney.  All Rights Reserved.
*
* This file may be distributed under the terms of GNU Public License version
* 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
* license should have been included with this file, or the project in which
* this file belongs to. You may also find the details of GPL v3 at:
*
* http://www.gnu.org/licenses/gpl-3.0.txt
*
* If you have any questions regarding the use of this file, feel free to
* contact the author of this file, or the owner of the project in which
* this file belongs to.
*
******************************************************************************/

#include "factories.h"
#include <QDebug>

QList<Individual*> makeIndividualsFromCSV( QList<QStringList> raw ) {
    QList<Individual*> inds;
    QStringList header = raw.first();

    raw.pop_front();
    foreach(const QStringList row, raw  ){
        Individual *theInd = new Individual();
        for( int i=0;i<header.count(); i++){
            theInd->setData( header.at(i), row.at(i) );
        }
        inds.append( theInd );
    }
    return inds;
}

