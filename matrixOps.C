/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  matrixOps
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

#include "matrixOps.H"

gsl_matrix* frequencyMatrix( QList<Frequencies*> freqs ) {
    QStringList alleles;
    foreach(Frequencies *f, freqs)
        alleles.append( f->alleles() );
    alleles = alleles.toSet().toList();
    std::sort(alleles.begin(),alleles.end());

    gsl_matrix* m = gsl_matrix_calloc(freqs.count(),alleles.count());

    for(int i=0;i<freqs.count();i++){
        gsl_vector *v = freqs.at(i)->toVector(alleles);
        for(size_t j=0;j<v->size;j++)
            gsl_matrix_set(m,i,j, gsl_vector_get(v,j));
    }

    return m;
}

