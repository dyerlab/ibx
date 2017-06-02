/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphview.h
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

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QTimer>
#include <QObject>
#include <QPanGesture>
#include <QGraphicsView>
#include <QGestureEvent>
#include <QPinchGesture>
#include "GraphScene.H"


typedef enum {
    ZOOM_IN,
    ZOOM_OUT
} ZOOM_DIRECTION;


class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(GraphScene *scene);

    void itemMoved();
    void resetLayout();

protected:
    void timerEvent( QTimerEvent *event) override;
    void keyPressEvent( QKeyEvent *event) override;
    bool event(QEvent *event) override;

private:
    double temperature;
    int timerID;
    bool canMove;

    void shuffleNodes();
    void toggleLabels();
    void scaleNodes( double val );
    void zoom( ZOOM_DIRECTION direction );

    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture *pan);
    void pinchTriggered(QPinchGesture *pinch);
};

#endif // GRAPHVIEW_H
