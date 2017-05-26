/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  FileIO
*
*  Created: 5 2017 by rodney
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

#include <QDebug>
#include <QStringList>
#include "Individual.H"
#include "FileIO.H"
#include "Locus.H"



Population* importPopulationFromFile(QStringList headers, QList<QStringList> lines, LOCUS_TYPE locusType, QHash<QString,COLUMN_TYPE> columnTypes) {
    Population *thePop = new Population();




    foreach( QStringList line, lines ){

        int col = 0;
        QString key;
        QString value;
        COLUMN_TYPE colType;

        Individual *theInd = new Individual();

        while( col < line.count()){

            key = headers.at(col);
            value = line.at(col);
            colType = columnTypes.value(key);

            if( colType == COLUMN_TYPE_LOCUS ){
                Locus *theLoc = new Locus();
                QStringList alleles;

                switch( locusType ){
                case LOCUS_TYPE_HAPLOID:
                    alleles << value;
                    break;
                case LOCUS_TYPE_SEPARATED:
                    alleles = value.split(":");
                    break;
                case LOCUS_TYPE_2_COLUMN:
                    alleles << value;
                    col++;
                    alleles << line.at(col);
                    break;
                default:
                    qCritical() << "Error, you should not be getting this error.";
                    break;
                }

                theLoc->setAlleles(alleles);
                theInd->setData(key,theLoc);
            }
            else
                theInd->setData(key,value,colType);

            col++;
        }
        thePop->append( theInd );
    }


    return thePop;
}


