/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphscene.h
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

#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include "Node.H"
#include "Edge.H"
#include "Graph.H"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = 0);

    int count() const;
    QList<Node*> getNodes();
    QList<Edge*> getEdges();

    bool calculateNodeForces( double temperature );
    void setGraph( Graph *graph);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void scaleNodes( int value );

private:
    QColor backgroundColor;
    Graph *theGraph;

};

#endif // GRAPHSCENE_H
