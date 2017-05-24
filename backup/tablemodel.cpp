/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  datatablemodel.cpp
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

#include "tablemodel.h"
#include "individual.h"

#include <QFont>
#include <QBrush>

GenotypeTableModel::GenotypeTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    thePopulation = new Population();
}

int GenotypeTableModel::rowCount(const QModelIndex & /*parent*/ ) const {
    return thePopulation->count();
}

int GenotypeTableModel::columnCount(const QModelIndex &/*parent*/) const {
    return this->headers.count();
}

QVariant GenotypeTableModel::data(const QModelIndex &index, int role) const {

    if( role == Qt::DisplayRole){
        return thePopulation->getIndividual(index.row())->getData(this->headers.value(index.column()));
    }
    else if( role == Qt::BackgroundRole ){
        QBrush background;

        switch( dataTypes.value( index.column())){

        case DATA_TYPE_STRATUM:
            background = QBrush(QColor(242, 250, 255));
            break;

        case DATA_TYPE_COORDINATE:
            background = QBrush(QColor(250, 255, 247));
            break;

        case DATA_TYPE_LOCUS:
            background = QBrush(QColor(255, 250, 244));
            break;

        default:
            background = Qt::white;
            break;
        }

        return QVariant(background);
    }
    return QVariant();
}


QVariant GenotypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if( role == Qt::DisplayRole ) {

        if( orientation == Qt::Horizontal )
           return QVariant( headers.value(section) );
        else
           return QVariant(section);
    }
    else if( role == Qt::FontRole ){
        QFont font;
        font.setBold(true);
        return font;
    }

    return QVariant();
}


bool GenotypeTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if( role == Qt::EditRole ){

        thePopulation->getIndividual(index.row())->setData( headers.value(index.column()),
                                                            value,
                                                            dataTypes.value(index.column()));
    }

    return true;
}

Qt::ItemFlags GenotypeTableModel::flags(const QModelIndex &/*index*/) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}



