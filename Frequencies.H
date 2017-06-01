/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Frequencies.H
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


#ifndef FREQUENCIES_H
#define FREQUENCIES_H

#include "Locus.H"
#include <QHash>
#include <QString>
#include <QStringList>

#include <gsl/gsl_vector.h>

class Frequencies
{
public:
    Frequencies();

    void addLocus(Locus *theLoc );

    double frequency( QString allele );

    QString toString();
    gsl_vector* toVector( QStringList alleles = QStringList());
    QStringList alleles();

    double He();
    double Ho();

private:

    double m_N;
    double m_Ho;
    double m_NHo;
    QHash<QString,double> m_counts;

};

#endif // FREQUENCIES_H
