/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataSet.C
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

#include "DataGenotypes.H"

DataGenotypes::DataGenotypes() : DataBase() {
    m_type = DATA_TYPE_GENOTYPES;
}

DataGenotypes::~DataGenotypes() {
    delete m_genotypeTableModel;
    delete m_tableView;
}

void DataGenotypes::setPopulation(Population *thePop) {
    m_population = thePop;
    m_genotypeTableModel = new GenotypeTableModel( m_population );
    m_tableView = new QTableView();
    m_tableView->setModel( m_genotypeTableModel );
    m_genotypeTableModel->setDelegates( m_tableView );
}

Population* DataGenotypes::getPopulation() {
    return m_population;
}

GenotypeTableModel* DataGenotypes::getGenotypeTableModel() const {
    return m_genotypeTableModel;
}
