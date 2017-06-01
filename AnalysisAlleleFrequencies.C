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
#include "Frequencies.H"
#include "matrixOps.H"


AnalysisAlleleFrequencies::AnalysisAlleleFrequencies(DataGenotypes *theData) : AnalysisBase() {
     m_pop = theData->getPopulation();
     if( !m_pop )
         qCritical() << "HELP, population is nill in AlleleFrequencies";


    m_results->setLabel( "Allele Frequencies" );
}

AnalysisAlleleFrequencies::~AnalysisAlleleFrequencies() {

}


bool AnalysisAlleleFrequencies::run() {
    QStringList strata = m_pop->keysForColumnType( COLUMN_TYPE_STRATUM );
    strata.push_front( QObject::tr("All"));
    QStringList loci = m_pop->keysForColumnType( COLUMN_TYPE_LOCUS );
    loci.push_front( QObject::tr("All"));
    QString title = "Allele Frequenices";
    QString msg1 = "Strata:";
    QString msg2 = "Loci:";

    if( !loci.count() ) {
        m_warnings << QObject::tr("You need to have some loci in the dataset before you can estimate allele frequencies.");
        m_pop = NULL;
    }

    if( !m_pop ){
        m_results->appendErrorMessage( m_warnings.join("\n"));
        return false;
    }

    setUpDoubleSelection(title, msg1, strata, msg2, loci );
    if( m_input_dlg->exec() == QDialog::Rejected )
        return false;

    // Figure out the stratum and loci to use.
    DialogDoubleInput *dlg = static_cast<DialogDoubleInput*>(m_input_dlg);
    int lvl_strata = dlg->getFirstIndex();

    if( dlg->getSecondIndex() )
        loci = QStringList( loci.at(dlg->getSecondIndex() ) );
    else
        loci.pop_front();

    // Partition by stratum
    QHash<QString,Population*> pop;
    if( lvl_strata )
        pop = m_pop->partition(strata.at(lvl_strata) );
    else
        pop.insert(QObject::tr("All"),m_pop);

    // Iterate across strata
    QStringList keys = pop.keys();
    std::sort(keys.begin(),keys.end());
    m_results->appendHeader(QObject::tr("Allele Frequencies"));
    foreach( QString locus, loci ){
        QList<Frequencies*> freqs;
        QStringList allAlleles;
        foreach( QString level, keys){
            Frequencies *f = new Frequencies();
            for(int i=0;i<pop.value(level)->count();i++)
                f->addLocus( pop.value(level)->get(i)->getLocus(locus));
            freqs.append(f);
            allAlleles.append( f->alleles() );
        }
        gsl_matrix* m = frequencyMatrix( freqs );
        m_results->appendTable(QString("Locus: %1").arg(locus),m,strata,allAlleles);
        gsl_matrix_free( m );
        qDeleteAll(freqs);
    }
    m_results->scrollToTop();
    return true;
}
