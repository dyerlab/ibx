/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Population.C
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

#include "Population.H"

Population::Population(QObject *parent) : QObject(parent)
{

}


void Population::append(Individual *theInd) {
    m_individuals.append(theInd);
}

Individual* Population::get(int idx) {
    return m_individuals.at(idx);
}

int Population::count() const {
    return m_individuals.count();
}


QStringList Population::keysForColumnType(COLUMN_TYPE type) {
    QStringList ret;

    if( count() ) {
        QStringList keys = m_individuals.at(0)->keys();
        foreach(QString key, keys){
            if( m_individuals.at(0)->typeForKey(key) == type )
                ret << key;
        }
    }

    std::sort(ret.begin(),ret.end());

    return ret;
}


QHash<QString,Population*> Population::partition( QString stratum ) {
    QHash<QString, Population*> ret;

    foreach( Individual *ind, m_individuals ){
        QString strata = ind->getData( stratum ).toString();
        if( !ret.keys().contains(strata) )
            ret.insert(strata, new Population() );
        ret.value(strata)->append( ind );
    }
    return ret;
}
