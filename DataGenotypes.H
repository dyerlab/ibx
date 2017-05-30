/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataSet.H
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

#ifndef DATASET_H
#define DATASET_H

#include "DataBase.H"
#include "Population.H"
#include "GenotypeTableModel.H"


class DataGenotypes : public DataBase {

public:
    DataGenotypes();
    ~DataGenotypes();

    void setPopulation( Population *thePop );
    Population* getPopulation();

    inline QWidget* getWidget() { return m_tableView; }

    GenotypeTableModel* getGenotypeTableModel() const;


private:

    Population *m_population;
    GenotypeTableModel *m_genotypeTableModel;
    QTableView *m_tableView;

};

#endif // DATASET_H
