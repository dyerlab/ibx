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


    m_results->setLabel( "Allele Frequencies" );




}

void AnalysisAlleleFrequencies::run() {
    QStringList strata = m_pop->keysForColumnType( COLUMN_TYPE_STRATUM );
    strata.push_front( QObject::tr("All"));
    QStringList loci = m_pop->keysForColumnType( COLUMN_TYPE_LOCUS );
    loci.push_front( QObject::tr("All"));
    QString title = "Allele Frequenices";
    QString msg1 = "Strata:";
    QString msg2 = "Loci:";

    if( !loci.count() ) {
        m_warnings << QObject::tr("You need to have some loci in the dataset before you can estiamte allele frequencies.");
        m_pop = NULL;
    }

    if( !m_pop ){
        m_results->appendErrorMessage( m_warnings.join("\n"));
        return;
    }

    setUpDoubleSelection(title, msg1, strata, msg2, loci );
    if( m_input_dlg->exec() == QDialog::Rejected )
        return;
    DialogDoubleInput *dlg = static_cast<DialogDoubleInput*>(m_input_dlg);
    QString lvl_strata = strata.at( dlg->getFirstIndex() );
    QString lvl_loci = loci.at( dlg->getSecondIndex() );



}
