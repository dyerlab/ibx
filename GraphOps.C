/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphops
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

#include <QtGlobal>
#include "Graph.H"
#include "GraphOps.H"



void transferNodeLocations( Graph* fromGraph, Graph *toGraph ) {
    Q_ASSERT( fromGraph->numNodes() == toGraph->numNodes());

    for( int i=0;i<fromGraph->numNodes();i++){
        int idx = toGraph->indexOf( fromGraph->getNode(i)->getLabel());
        if( idx != -1 ){
            toGraph->getNode(idx)->setPos( fromGraph->getNode(i)->pos());
        }
        else {
            toGraph->getNode(idx)->setPos(400,400);
        }
    }
}



gsl_vector* degreeCentrality( QList<Node*> nodes) {
    int N = nodes.count();
    gsl_vector *vec = gsl_vector_calloc(N);

    for(int i=0;i<N;i++){
        gsl_vector_set( vec, i, (double)nodes.at(i)->degree() );
    }

    return vec;
}


gsl_vector* betweennessCentrality( gsl_matrix *A ) {
    Q_ASSERT( A->size1 == A->size2 );
    unsigned N = A->size1;
    gsl_matrix *D = gsl_matrix_calloc( N, N );
    double gMax = matrixSum( A );
    gsl_vector *btwn = gsl_vector_calloc(N);

    // Set up D
    for(unsigned i=0;i<N;++i){
        for( unsigned j=0;j<N;++j){
            if( i != j ) {
                double val = gsl_matrix_get(A,i,j);

                if( val > 0 )
                    gsl_matrix_set( D, i, j, val );

                else
                    gsl_matrix_set( D, i, j, gMax);

            }
        }
    }

    // Cycle through the Floyd Warshall Algorithm
    for( unsigned k=0;k<N;++k){
        for( unsigned i=0;i<N;++i){
            for( unsigned j=0;j<N;++j){
                if( i != j && i != k && j != k ){
                    double curDist = gsl_matrix_get(D,i,j);
                    double newDist = gsl_matrix_get(D,i,k) + gsl_matrix_get(D,k,j);

                    if( curDist < gMax && newDist < gMax ) {
                        if( curDist < newDist ){
                            gsl_matrix_set( D, i, j, curDist );
                        }
                        else {
                            gsl_vector_set( btwn, k, (gsl_vector_get( btwn, k) + 1.0) );
                            gsl_matrix_set( D, i, j, newDist );
                        }
                    }

                    else if( newDist < gMax )
                        gsl_matrix_set( D,i,j,newDist);
                }
            }
        }
    }

    gsl_matrix_free( D );
    gsl_vector_scale(btwn, (N-1.0)*(N-2)/2);

    return( btwn );
}


gsl_vector* closenessCentrality( gsl_matrix *A ) {
    unsigned N = A->size1;
    gsl_vector *close = gsl_vector_calloc(N);

    gsl_matrix *D = shortestPathFloydWarshall(A);
    for( size_t i=0;i<N;i++){
        for( size_t j=0;j<N;j++){
            double val = gsl_vector_get(close,i);
            double inc = gsl_matrix_get(D,i,j);
            if( inc != GSL_POSINF )
                gsl_vector_set( close, i, val+inc );
        }
    }
    gsl_matrix_free( D );
    return close;
}


double matrixSum( gsl_matrix *A ) {
    double ret = 0.0;

    for( size_t i=0;i<A->size1;++i){
        for(size_t j=0;j<A->size2;++j){
            double val = gsl_matrix_get(A,i,j);
            if( val != GSL_POSINF)
                ret += val;
        }
    }

    return ret;
}


gsl_matrix* shortestPathFloydWarshall( gsl_matrix *A ){
    Q_ASSERT( A->size1 > 0 );
    Q_ASSERT( A->size1 == A->size2 );

    unsigned N = A->size1;
    gsl_matrix *D = gsl_matrix_calloc( N, N );
    double gMax = matrixSum( A );

    // Set up D
    for(unsigned i=0;i<N;++i){
        for( unsigned j=0;j<N;++j){
            if( i != j ) {
                double val = gsl_matrix_get(A,i,j);

                if( val > 0 )
                    gsl_matrix_set( D, i, j, val );

                else
                    gsl_matrix_set( D, i, j, gMax);

            }
        }
    }

    // Cycle through the Floyd Warshall Algorithm
    for( unsigned k=0;k<N;++k){

        for( unsigned i=0;i<N;++i){
            for( unsigned j=0;j<N;++j){
                double curDist = gsl_matrix_get(D,i,j);
                double newDist = gsl_matrix_get(D,i,k) + gsl_matrix_get(D,k,j);

                if( curDist < gMax && newDist < gMax )
                    gsl_matrix_set( D, i, j, qMin( curDist, newDist )  );

                else if( newDist < gMax )
                    gsl_matrix_set( D,i,j,newDist);
            }
        }
    }

    // Set unreached connections to a VERY LARGE NUMBER
    for(unsigned i=0;i<N;i++){
        for(unsigned j=0;j<N;j++){
            if( gsl_matrix_get(D,i,j) == gMax )
                gsl_matrix_set( D, i, j, GSL_POSINF );
        }
    }

    return D;
}


Graph* createLopho() {
    Graph* lopho = new Graph();

    lopho->addNode( new Node("BaC",12.8707) );
    lopho->addNode( new Node("Ctv",3.381395) );
    lopho->addNode( new Node("LaV",4.00305) );
    lopho->addNode( new Node("Lig",5.0032) );
    lopho->addNode( new Node("PtC",5.4503) );
    lopho->addNode( new Node("PtP",11.3172) );
    lopho->addNode( new Node("SLG",6.41525) );
    lopho->addNode( new Node("SnE",12.53715) );
    lopho->addNode( new Node("SnF",7.004) );
    lopho->addNode( new Node("SnI",5.8391) );
    lopho->addNode( new Node("StR",7.1324) );
    lopho->addNode( new Node("TsS",5.9387) );
    lopho->addNode( new Node("CP",7.8462) );
    lopho->addNode( new Node("LF",6.06715) );
    lopho->addNode( new Node("PL",7.1986) );
    lopho->addNode( new Node("SenBas",10.27315) );
    lopho->addNode( new Node("Seri",2.5) );
    lopho->addNode( new Node("SG",11.73435) );
    lopho->addNode( new Node("SI",11.84485) );
    lopho->addNode( new Node("SN",8.64935) );
    lopho->addNode( new Node("TS",14.85345) );

    lopho->addEdge("BaC", "LaV", 5);
    lopho->addEdge("BaC", "Lig", 5);
    lopho->addEdge("BaC", "PtP", 5);
    lopho->addEdge("BaC", "SnE", 5);
    lopho->addEdge("BaC", "SnI", 5);
    lopho->addEdge("BaC", "StR", 5);
    lopho->addEdge("BaC", "SenBas", 5);
    lopho->addEdge("Ctv", "PtP", 5);
    lopho->addEdge("Ctv", "SLG", 5);
    lopho->addEdge("Ctv", "SnF", 5);
    lopho->addEdge("Ctv", "SenBas", 5);
    lopho->addEdge("LaV", "Lig", 5);
    lopho->addEdge("LaV", "SnE", 5);
    lopho->addEdge("LaV", "SnF", 5);
    lopho->addEdge("LaV", "TsS", 5);
    lopho->addEdge("Lig", "PtC", 5);
    lopho->addEdge("Lig", "SnE", 5);
    lopho->addEdge("Lig", "SnI", 5);
    lopho->addEdge("Lig", "StR", 5);
    lopho->addEdge("PtC", "SnE", 5);
    lopho->addEdge("PtC", "StR", 5);
    lopho->addEdge("PtC", "TsS", 5);
    lopho->addEdge("PtP", "SnF", 5);
    lopho->addEdge("PtP", "SnI", 5);
    lopho->addEdge("PtP", "SenBas", 5);
    lopho->addEdge("SLG", "SnF", 5);
    lopho->addEdge("SLG", "SnI", 5);
    lopho->addEdge("SnE", "StR", 5);
    lopho->addEdge("SnE", "TsS", 5);
    lopho->addEdge("SnF", "SnI", 5);
    lopho->addEdge("SnI", "StR", 5);
    lopho->addEdge("StR", "TsS", 5);
    lopho->addEdge("StR", "SenBas", 5);
    lopho->addEdge("CP", "LF", 5);
    lopho->addEdge("CP", "Seri", 5);
    lopho->addEdge("CP", "SG", 5);
    lopho->addEdge("CP", "SN", 5);
    lopho->addEdge("CP", "TS", 5);
    lopho->addEdge("LF", "PL", 5);
    lopho->addEdge("LF", "SG", 5);
    lopho->addEdge("LF", "SI", 5);
    lopho->addEdge("PL", "SenBas", 5);
    lopho->addEdge("PL", "SG", 5);
    lopho->addEdge("PL", "SI", 5);
    lopho->addEdge("Seri", "SG", 5);
    lopho->addEdge("Seri", "SN", 5);
    lopho->addEdge("SG", "SI", 5);
    lopho->addEdge("SI", "SN", 5);
    lopho->addEdge("SI", "TS", 5);
    lopho->addEdge("SN", "TS", 5);

    return lopho;
}










