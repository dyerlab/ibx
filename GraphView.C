/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphview.cpp
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
#include <QKeyEvent>
#include "GraphView.H"

GraphView::GraphView(GraphScene *scene) : QGraphicsView(scene) {
    resetLayout();
    setInteractive(true);
    setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing );

    // set up gesture grabbing
    viewport()->grabGesture(Qt::PanGesture);
    viewport()->grabGesture(Qt::PinchGesture);
    temperature = 100.0;

}



void GraphView::itemMoved() {
    if( !timerID )
        timerID = startTimer( 1000/25 );
}

void GraphView::resetLayout() {
    timerID = 0;
    canMove = true;
    temperature = 100.0;
    itemMoved();
}

/*********************  EVENTS *************************/

void GraphView::timerEvent(QTimerEvent *event) {
    Q_UNUSED( event );

    // bail on moving if necessary
    if( !canMove ){
        return;
    }

    // grab nodes
    temperature = (temperature > 0.5 ) ? 0.999 * temperature : 0.45;
    GraphScene *theScene = static_cast<GraphScene*>(this->scene());
    if( theScene ) {
        if( !theScene->calculateNodeForces( temperature ) ){
            killTimer(timerID);
            timerID = 0;
        }
    }

    this->update();

}


void GraphView::keyPressEvent(QKeyEvent *event) {
    switch( event->key() ){
    case Qt::Key_R:
        shuffleNodes();
        break;

    case Qt::Key_L:
        toggleLabels();
        break;

    case Qt::Key_Escape:
        canMove = !canMove;
        itemMoved();
        break;

    case Qt::Key_PageDown:
        scaleNodes( 1.0/1.2 );
        break;

    case Qt::Key_PageUp:
        scaleNodes( 1.2 );
        break;

    case Qt::Key_Plus:
        zoom( ZOOM_IN );
        break;

    case Qt::Key_Minus:
        zoom( ZOOM_OUT );
        break;

    default:
        break;
    }
}




bool GraphView::event(QEvent *event) {
    if( event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event) );
    return QGraphicsView::event(event);
}

void GraphView::shuffleNodes() {
    GraphScene *scene = qobject_cast<GraphScene*>( this->scene() );
    QList<Node*> nodes = scene->getNodes();
    foreach(Node* node, nodes )
        node->setPos( qrand() % (int)scene->height(),
                      qrand() % (int)scene->height() );
    itemMoved();
}


void GraphView::toggleLabels() {
    GraphScene *scene = qobject_cast<GraphScene*>( this->scene() );
    QList<Node*> nodes = scene->getNodes();
    foreach(Node* node, nodes )
        node->toggleLabel();
    update();
}

void GraphView::scaleNodes(double val) {
    GraphScene *scene = qobject_cast<GraphScene*>( this->scene() );
    QList<Node*> nodes = scene->getNodes();
    foreach(Node* node, nodes ) {
        double newSize = node->getSize() * val;
        if( newSize > 4 && newSize < 26 )
            node->setSize(newSize);
    }
    update();
}

void GraphView::zoom(ZOOM_DIRECTION direction) {
    if( direction == ZOOM_OUT )
        scale(1.2,1.2);
    else
        scale(1/1.2, 1/1.2);
}

bool GraphView::gestureEvent(QGestureEvent *event) {
    qDebug() << "gestureEvent()" << event;

    if( QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture*>(pinch));
    else if( QGesture *pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture*>(pan));
    return true;
}

void GraphView::panTriggered(QPanGesture *pan){
    qDebug() << "panTriggered()" << pan;
}

void GraphView::pinchTriggered(QPinchGesture *pinch) {
    qDebug() << "pinchTriggered()" << pinch;
}





