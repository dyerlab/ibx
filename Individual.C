/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Individual.C
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

#include "Individual.H"

Individual::Individual(QObject *parent) : QObject(parent)
{

}


void Individual::setData(QString key, QVariant value) {
    m_data.insert(key,value);
}

QVariant Individual::getData( QString key ) {
    return m_data.value(key, QVariant(QString("")));
}

void Individual::setData(QString key, Locus *theLoc ) {
    QVariant value = qVariantFromValue( (void*)theLoc );
    m_data.insert(key,value);
}

Locus* Individual::getLocus( QString key) {
    if( m_data.keys().contains(key)){
        QVariant v = m_data.value(key);
        Locus *theLoc = (Locus*) v.value<void*>();
        return theLoc;
    }
    else {
        return new Locus();
    }
}

QStringList Individual::keys() const {
    return m_data.keys();
}

int Individual::count() const {
    return m_data.count();
}
