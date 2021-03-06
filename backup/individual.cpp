/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  individual.cpp
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

#include "individual.h"

Individual::Individual() {
}

Individual::Individual(Individual &other){
    this->data = other.data;
    this->dataTypes = other.dataTypes;
}

QStringList Individual::keys() const {
    return data.keys();
}

QVariant Individual::getData( QString key ) const {
    QVariant ret;
    if( data.keys().contains(key)){
        if( dataTypes.value(key) == DATA_TYPE_LOCUS)
            ret = QVariant( data.value(key).toStringList().join(":"));
        else
            ret = data.value(key);
        return ret;
    }
    else
        return QVariant();
}

void Individual::setData( QString key, QVariant value, DATA_TYPE type) {
    data.insert(key,value);
    dataTypes.insert(key,type);
}


