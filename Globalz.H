/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Globalz
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

#ifndef GLOBALZ_H
#define GLOBALZ_H

#include <gsl/gsl_rng.h>

typedef enum {
    LOCUS_TYPE_UNDEFINED,
    LOCUS_TYPE_HAPLOID,
    LOCUS_TYPE_SEPARATED,
    LOCUS_TYPE_2_COLUMN
} LOCUS_TYPE;


typedef enum {
    COLUMN_TYPE_UNDEFINED,
    COLUMN_TYPE_STRATUM,
    COLUMN_TYPE_EXTERNAL,
    COLUMN_TYPE_LOCUS
} COLUMN_TYPE;

typedef enum {
    DATA_TYPE_UNDEFINED,
    DATA_TYPE_GENOTYPES,
    DATA_TYPE_RESULTS,
    DATA_TYPE_NETWORK
} DATA_TYPE;



static gsl_rng *rng;


#endif // GLOBALZ_H
