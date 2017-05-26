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
#include <QDebug>

Individual::Individual(QObject *parent) : QObject(parent) {

}


void Individual::setData(QString key, QVariant value, COLUMN_TYPE type) {
    m_data.insert(key,value);
    m_data_type.insert(key,type);
}

QVariant Individual::getData( QString key ) {
    return m_data.value(key, QVariant(QString("")));
}

void Individual::setData(QString key, Locus *theLoc ) {
    QVariant value = qVariantFromValue( (void*)theLoc );
    m_data.insert( key, value );
    m_data_type.insert( key, COLUMN_TYPE_LOCUS );
}

Locus* Individual::getLocus( QString key) {
    QVariant v = m_data.value(key);
    Locus *theLoc = (Locus*) v.value<void*>();
    return theLoc;
}

QStringList Individual::keys() const {
    return m_data.keys();
}

COLUMN_TYPE Individual::typeForKey(QString key) const{
    return m_data_type.value(key);
}

int Individual::count() const {
    return m_data.count();
}


QStringList Individual::locusNames() {
    QStringList ret;
    foreach( QString key, m_data_type.keys()){
        if( m_data_type.value(key) == COLUMN_TYPE_LOCUS)
            ret << key;
    }
    return ret;
}


int Individual::numLoci() {
    return locusNames().count();
}

QString Individual::toString() {
    QStringList strata;
    QStringList external;
    QStringList loci;

    foreach( QString key, m_data.keys() ){
        COLUMN_TYPE type = m_data_type.value(key);
        switch(type){
        case COLUMN_TYPE_STRATUM:
            strata << key;
            break;
        case COLUMN_TYPE_EXTERNAL:
            external << key;
            break;
        case COLUMN_TYPE_LOCUS:
            loci << key;
            break;
        default:
            break;
        }
    }
    std::sort( strata.begin(), strata.end());
    std::sort( external.begin(), external.end());
    std::sort( loci.begin(), loci.end());
    QStringList ret;
    foreach( QString key, strata )
        ret << m_data.value(key).toString();
    foreach( QString key, external )
        ret << m_data.value(key).toString();
    foreach( QString key, loci ){
        ret << getLocus(key)->toString();
    }
    return (ret.join(", "));
}



