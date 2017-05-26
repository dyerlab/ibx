/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  GenotypeTableModel.H
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

#ifndef GENOTYPETABLEMODEL_H
#define GENOTYPETABLEMODEL_H

#include "Globalz.H"
#include "Population.H"

#include <QColor>
#include <QString>
#include <QAbstractTableModel>


class GenotypeTableModel : public QAbstractTableModel
{
public:
    GenotypeTableModel(Population *thePop);

    // TabelModelStuff
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    int rowCount( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role );

private:
    Population *m_population;
    QHash<QString,COLUMN_TYPE> m_dataTypes;
    QStringList m_headers;

};

#endif // GENOTYPETABLEMODEL_H
