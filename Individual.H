/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Individual.H
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

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QStringList>
#include <QVariant>
#include <QObject>
#include <QHash>

#include "Locus.H"
#include "Globalz.H"

class Individual : public QObject
{
    Q_OBJECT

public:
    explicit Individual(QObject *parent = 0);

    void setData(QString key, QVariant value, COLUMN_TYPE type);
    QVariant getData( QString key );

    void setData(QString key, Locus *theLoc );
    Locus* getLocus( QString key);
    QStringList locusNames();
    int numLoci();

    QStringList keys() const;
    COLUMN_TYPE typeForKey(QString key) const;
    int count() const;

    QString toString() ;

private:
    QHash<QString,QVariant> m_data;
    QHash<QString,COLUMN_TYPE> m_data_type;

};

#endif // INDIVIDUAL_H
