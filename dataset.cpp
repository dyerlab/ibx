/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  dataset.cpp
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


#include "dataset.h"

#include <QSet>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QDataStream>

DataSet::DataSet() {
}


DataSet::~DataSet() {

}

/*
DataSet::DataSet(QList<Individual*> theInds) {
    if( theInds.count() ) {
        headers = theInds.at(0)->keys();
        for(int i=0;i<headers.count();i++)
            dataTypes.append(DATA_TYPE_UNDEF);
        this->individuals = theInds;
    }

    results = new ResultsDocument();

}

DataSet::DataSet(const DataSet& other){
    this->headers = other.headers;
    this->dataTypes = other.dataTypes;
    this->results = other.results;
    this->individuals = other.individuals;
}


DataSet::~DataSet() {
    delete results;
}

int DataSet::numberOfIndividuals() const {
    return individuals.count();
}

int DataSet::numberOfDataColumns() const {
    return headers.count();
}


Individual* DataSet::getIndividual( const int idx ) const {
    return individuals.at(idx);
}


void DataSet::addIndividual(Individual *theInd) {
    individuals.append(theInd);
}

void DataSet::orderHeaders( QStringList vals ) {
    headers = vals;
    for(int i=0;i<headers.count();i++)
        dataTypes.append(DATA_TYPE_UNDEF);
}

QVariant DataSet::getHeaderForColumn( int column) {
    return column < headers.count() ? QVariant(headers.at(column)) : QVariant();
}

QVariant DataSet::getDataForKey(int row, QString key) {
    return headers.contains(key) ? QVariant(individuals.at(row)->getData(key)) : QVariant();
}

QVariant DataSet::getDataForColumn(int row, int column ) {
    return getDataForKey(row,headers.at(column));
}

DATA_TYPE DataSet::getDataTypeForColumn( int idx ) const {
    return dataTypes.at(idx);
}

void DataSet::setColumnToType( QString key, DATA_TYPE type ) {
    int idx = headers.indexOf(key);
    QStringList errors;

    if( idx != -1 ) {

        for( int i=0;i<individuals.count();i++){
            QVariant was = individuals.at(i)->getData(key);
            QVariant is;

            if( type == DATA_TYPE_COORDINATE){               
                bool ok;
                double val = was.toDouble(&ok);

                if( !ok){
                    errors.append(QString("Cannot convert %1 to coordinate.").arg(i));
                }
                else {
                    is = QVariant( val );
                }
            }
            else if( type == DATA_TYPE_STRATUM ){
                is = was;
            }
            else if( type == DATA_TYPE_LOCUS ){
                QStringList alleles = was.toString().split(":",QString::SkipEmptyParts, Qt::CaseSensitive);
                alleles.sort();
                qDebug() << "Alleles: " << alleles;
                is = QVariant( alleles );
            }
            individuals.at(i)->setData(key,is,type);

        }

        dataTypes[idx] = type;
        qDebug() << "Seeting " << key << " to " << type;
        if( errors.count())
            qDebug() << "Errors" << errors.join("\n");
    }
}

void DataSet::setColumnToType( int idx, DATA_TYPE type){
    this->setColumnToType(headers.at(idx), type);
}



ResultsDocument* DataSet::getResults() const {
    return results;
}

void DataSet::appendToResults( QString val ) {
    results->addResult(val);
}

bool DataSet::saveToFile( QString path) {
    QFile file(path);
    if( !file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_8);

    // The columns
    out << headers;

    // The data types
    out << dataTypes.count();
    foreach(DATA_TYPE type, dataTypes)
        out << (qint32)type;

    // The individuals
    out << individuals.count();
    foreach( Individual *ind, individuals ) {
        foreach( QString key, headers){
            out << ind->getData(key);
        }
    }

    // The results
    out << results->rawContents();



    return true;
}

bool DataSet::loadFromFile( QString path) {
    QFile file(path);
    if( !file.open(QIODevice::ReadOnly))
        return false;

    return true;
}


*/





