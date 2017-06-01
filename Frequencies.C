/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Frequencies.C
*
*  Created: 6 2017 by rodney
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


#include "Frequencies.H"
#include <gsl/gsl_blas.h>

Frequencies::Frequencies()
{
    m_N = m_Ho = m_NHo = 0;
}

void Frequencies::addLocus(Locus *theLoc) {
    if( !theLoc->isEmpty() ){
        foreach( QString allele, theLoc->alleles() ){
            m_counts.insert(allele, 1.0 + m_counts.value(allele,0.0));
        }
        int p = theLoc->ploidy();
        m_N += p;
        if( p > 1 ) {
            if( theLoc->isHeterozygote())
                m_Ho++;
            m_NHo++;
        }
    }
}


double Frequencies::frequency(QString allele) {
    double ct = m_counts.keys().contains(allele) ? m_counts.value(allele) : 0.0;
    if( m_N )
        return ct / m_N;
    else
        return 0.0;
}


gsl_vector* Frequencies::toVector(QStringList alleles) {
    QStringList cts;
    if( alleles.count() )
        cts = alleles ;
    else {
        cts = m_counts.keys();
        std::sort( cts.begin(), cts.end() );
    }

    gsl_vector *v = gsl_vector_calloc( cts.count() );
    for(int i=0;i<cts.count();i++){
        gsl_vector_set( v, i, frequency(cts.at(i)));
    }

    return v;
}

QList<double> Frequencies::toList( QStringList alleles ) {
    QList<double> ret;
    if(!alleles.count())
        alleles = this->alleles();
    foreach(QString allele, alleles)
        ret.append( frequency(allele) );

    return ret;
}


QString Frequencies::toString() {
    QString ret = "Frequencies = { ";
    QStringList alleles = m_counts.keys();
    std::sort( alleles.begin(), alleles.end() );
    foreach( QString allele, alleles ){
        ret += QString("%1:%2 ").arg(allele).arg(frequency(allele));
    }
    ret += " }";


    return ret;
}


QStringList Frequencies::alleles() {
    QStringList alleles = m_counts.keys();
    std::sort( alleles.begin(), alleles.end() );
    return alleles;
}



double Frequencies::Ho() {
    if( m_NHo > 0 ) {
        return m_Ho / m_NHo;
    }
    else
        return 0.0;

}



double Frequencies::He()  {
    gsl_vector *v = toVector( m_counts.keys() );
    gsl_vector_mul(v,v);
    double he = gsl_blas_dasum(v);
    gsl_vector_free(v);
    return he;
}




