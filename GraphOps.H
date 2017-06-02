/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  GraphOps.
*
*  Created: 4 2017 by rodney
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

#ifndef GRAPHOPS_H
#define GRAPHOPS_H


class Graph;

#include <QList>
#include "Node.H"
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>



typedef enum {
    CENTRALITY_DEGREE,
    CENTRALITY_BETWEENESS,
    CENTRALITY_CLOSENESS
} CENTRALITY_TYPE;



Graph *createLopho();
void transferNodeLocations( Graph* fromGraph, Graph *toGraph );



// Centrality characteristics
gsl_vector* degreeCentrality( QList<Node*> nodes );
gsl_vector* betweennessCentrality( gsl_matrix *A );
gsl_vector* closenessCentrality( gsl_matrix *A );

double matrixSum( gsl_matrix *A );
gsl_matrix* shortestPathFloydWarshall( gsl_matrix *A );




#endif // GRAPHOPS_H
