/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Population.H
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

#ifndef POPULATION_H
#define POPULATION_H


#include <QStringList>
#include <QString>
#include <QObject>
#include <QList>
#include <QHash>

#include "Globalz.H"
#include "Individual.H"

class Population : public QObject
{
    Q_OBJECT
public:
    explicit Population(QObject *parent = 0);

    void append( Individual *theInd );
    Individual* get( int idx );
    int count() const;
    QStringList keysForColumnType( COLUMN_TYPE type );
    QHash<QString,Population*> partition( QString stratum );



private:
    QList<Individual*> m_individuals;
};

#endif // POPULATION_H
