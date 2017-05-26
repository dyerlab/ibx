/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  GenotypeTableModel.C
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
#include "GenotypeTableModel.H"

GenotypeTableModel::GenotypeTableModel(Population *thePop) {
    m_population = thePop;

    // populate the headers and such.
    if( m_population->count()){
        Individual *ind = thePop->get(0);

        QStringList keys = ind->keys();
        QStringList strata;
        QStringList external;
        QStringList loci;
        foreach( QString key, keys ){
            COLUMN_TYPE type = ind->typeForKey(key);
            m_dataTypes.insert(key,type);
            switch( type ) {
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

        m_headers << strata;
        m_headers << external;
        m_headers << loci;


    }


}



Qt::ItemFlags GenotypeTableModel::flags ( const QModelIndex & index ) const {
    Q_UNUSED( index );
    return Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

int GenotypeTableModel::rowCount( const QModelIndex & parent ) const {
    Q_UNUSED( parent );
    return m_population->count();
}

int GenotypeTableModel::columnCount( const QModelIndex & parent ) const {
    Q_UNUSED( parent );
    return m_headers.count();
}

QVariant GenotypeTableModel::data( const QModelIndex & index, int role) const {
    QString key = m_headers.at(index.column());
    if( role == Qt::DisplayRole ) {
        Individual *ind = m_population->get( index.row() );

        COLUMN_TYPE type = m_dataTypes.value( m_headers.at(index.column()));
        if( type == COLUMN_TYPE_LOCUS ){
            Locus *theLoc = ind->getLocus(key);
            return QVariant(theLoc->toString());
        }
        else
            return ind->getData(key);
    }
    else if( role == Qt::ForegroundRole ){
        switch (m_dataTypes.value(key)){
        case COLUMN_TYPE_STRATUM:
            return qVariantFromValue(QColor(Qt::darkBlue));
            break;
        case COLUMN_TYPE_EXTERNAL:
            return qVariantFromValue(QColor(Qt::darkGreen));
            break;
        case COLUMN_TYPE_LOCUS:
            return qVariantFromValue( QColor( Qt::darkRed ));
            break;
        default:
            return qVariantFromValue( QColor( Qt::black ));
            break;
        }
    }
    else
        return QVariant();

}

bool GenotypeTableModel::setData ( const QModelIndex & index, const QVariant & value, int role) {
    Q_UNUSED( value );
    Q_UNUSED( role );
    int row = index.row();
    QString key = m_headers.at(index.column() );
    COLUMN_TYPE type = m_dataTypes.value( key );
    if( type == COLUMN_TYPE_LOCUS ){
        QStringList alleles = value.toString().split(":");
        m_population->get(row)->getLocus(key)->setAlleles(alleles);
    }
    else
        m_population->get(row)->setData(key,value,type);
    return( true );
}

QVariant GenotypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if( role == Qt::DisplayRole ) {
        if( orientation == Qt::Horizontal )
            return QVariant( m_headers.at(section) );
        else
            return QVariant( section );
    }
    else
        return QVariant();
}

bool GenotypeTableModel::setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role ){
    Q_UNUSED( section );
    Q_UNUSED( orientation );
    Q_UNUSED( value );
    Q_UNUSED( role );
    return false ;
}
