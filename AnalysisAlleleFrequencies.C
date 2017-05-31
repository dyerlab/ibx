/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  AnalysisAlleleFrequencies.C
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

#include "AnalysisAlleleFrequencies.H"

AnalysisAlleleFrequencies::AnalysisAlleleFrequencies(DataGenotypes *theData) : AnalysisBase() {
     m_pop = theData->getPopulation();
     if( !m_pop )
         qCritical() << "HELP, population is nill in AlleleFrequencies";

    QStringList strata = m_pop->keysForColumnType( COLUMN_TYPE_STRATUM );
    QStringList loci = m_pop->keysForColumnType( COLUMN_TYPE_LOCUS );
    m_results->setLabel( "Allele Frequencies" );


    if( !loci.count() ) {
        m_warnings << QObject::tr("You need to have some loci in the dataset before you can estiamte allele frequencies.");
        m_pop = NULL;
    }

}

void AnalysisAlleleFrequencies::run() {

    if( !m_pop ){
        m_results->appendErrorMessage( m_warnings.join("\n"));
        return;
    }


}
