/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  dataset.h
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

#ifndef DATASET_H
#define DATASET_H

#include "individual.h"
#include "resultsdocument.h"

class DataSet {

public:
    DataSet();
    DataSet(QList<Individual *> theInds);
    DataSet(const DataSet& other);
    ~DataSet();

    int numberOfIndividuals() const;
    int numberOfDataColumns() const;
    void addIndividual( Individual *theInd );
    Individual* getIndividual( const int idx ) const;
    void orderHeaders( QStringList vals );

    QVariant getHeaderForColumn( int column);
    QVariant getDataForKey(int row, QString key);
    QVariant getDataForColumn(int row, int column );

    void setColumnToType( QString key, DATA_TYPE type );
    void setColumnToType( int idx, DATA_TYPE type);

    DATA_TYPE getDataTypeForColumn( int idx ) const;

    ResultsDocument* getResults() const;
    void appendToResults( QString val );

    bool saveToFile( QString path);
    bool loadFromFile( QString path);

private:
    QStringList headers;
    QList<DATA_TYPE> dataTypes;
    QList<Individual*> individuals;
    ResultsDocument *results;


};


#endif // DATASET_H

