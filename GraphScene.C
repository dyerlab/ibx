/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphscene.cpp
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

#include <cmath>
#include <QDebug>
#include "GraphScene.H"
#include "GraphOps.H"

GraphScene::GraphScene(QObject *parent) : QGraphicsScene(parent)
{
    backgroundColor = Qt::white;
    setBackgroundBrush( backgroundColor);
    setSceneRect(0,0,1000,1000);
    theGraph = NULL;
}

QList<Node*> GraphScene::getNodes() {
    QList<Node*> ret;
    foreach(QGraphicsItem *item, items() ){
        Node *node = qgraphicsitem_cast<Node*>(item);
        if( node )
            ret.append( node );
    }
    return ret;
}

QList<Edge *> GraphScene::getEdges() {
    QList<Edge*> ret;
    foreach( QGraphicsItem *item, items() ){
        Edge *edge = qgraphicsitem_cast<Edge*>(item);
        if( edge )
            ret.append(edge);
    }
    return ret;
}

int GraphScene::count() const {
    return items().count();
}


void GraphScene::setGraph(Graph *graph){
    if( theGraph != NULL ){
        // put in part here to give corridents of old graph to new graph.
        transferNodeLocations(theGraph,graph);
    }

    while( this->items().count()){
        removeItem( items().at(0));
    }
    theGraph = graph;
    for( int i=0;i<graph->numEdges();++i){
        this->addItem( graph->getEdge(i) );
    }
    for( int i=0;i<graph->numNodes(); ++i){
        this->addItem( graph->getNode(i) );
    }

}


void GraphScene::scaleNodes( int value ) {
    QList<Node*> nodes = this->getNodes();
    foreach( Node* node, nodes ){
        node->setScale(value);
    }
    this->update();
}




bool GraphScene::calculateNodeForces( double temperature ) {
   bool ret = false;
   if( theGraph ){

       int K = items().count();
       K = qRound(sqrt( 1.0*((this->width() * this->height() )/K )) * 50.0) ;

       for( int i=0; i<theGraph->numNodes(); i++ ){
           Node *n1 = theGraph->getNode(i);
           double xvel = 0.0;
           double yvel = 0.0;

           // Repulsive Forces
           if( n1 != mouseGrabberItem() ){
               for( int j=0;j<theGraph->numNodes(); j++) {
                   if( i != j ){
                       Node *n2 = theGraph->getNode(j);
                       QLineF line( n1->mapFromItem(n2,0,0), QPointF(0,0));
                       double dX = line.dx();
                       double dY = line.dy();
                       double l = (dX*dX + dY*dY) * 4;
                       if( l > 0 ){
                           xvel += (dX/l) * (K*K/l);
                           yvel += (dY/l) * (K*K/l);
                       }
                   }
               }
           }


           // Attractive Forces
           for(int i=0;i<n1->degree();i++){
               Edge *e = n1->getEdge(i);
               if( e ){
                   Node *n2 = qgraphicsitem_cast<Node*>( e->otherNode(n1) );
                   if( n2 ){
                       QPointF here = n1->mapFromItem(n2,0,0);
                       double wt = e->getWeight() * 10.0;
                       xvel += here.x() / wt;
                       yvel += here.y() / wt;
                   }
               }
           }

           // Correct for out-of-scene stuff
           if( qAbs(xvel) > temperature )
               xvel = temperature * xvel/qAbs(xvel);
           if( qAbs(yvel) > temperature )
               yvel = temperature * yvel/qAbs(yvel);


           // set flag for still moving if any movement of any node.
           if( xvel != 0 || yvel != 0)
               ret = true;

           QRectF sceneRect = this->sceneRect();
           xvel += n1->pos().x();
           yvel += n1->pos().y();

           xvel = qMin(qMax(xvel, sceneRect.left() + 10), sceneRect.right() - 10);
           yvel = qMin(qMax(yvel, sceneRect.top() + 10), sceneRect.bottom() - 10);

           n1->nudge(xvel,yvel);
       }
   }

   return ret;
}



void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent( event );
}
