/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  individual.h
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

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QHash>
#include <QVariant>


typedef enum {
    DATA_TYPE_UNDEF,
    DATA_TYPE_STRATUM,
    DATA_TYPE_COORDINATE,
    DATA_TYPE_LOCUS
} DATA_TYPE;


class Individual {
public:
    Individual();
    Individual( Individual &other );

    QStringList keys() const;

    // Accessors for
    QVariant getData( QString key ) const;
    void setData( QString key, QVariant value, DATA_TYPE type = DATA_TYPE_UNDEF);

private:

    QHash<QString,QVariant> data;
    QHash<QString,DATA_TYPE> dataTypes;

};

#endif // INDIVIDUAL_H

