/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphitem.h
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

#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QPen>
#include <QFont>
#include <QBrush>
#include <QDebug>
#include <QtGlobal>
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsItem>
#include <QAbstractGraphicsShapeItem>

typedef enum {
    GRAPHIC_TYPE_UNDEF = QAbstractGraphicsShapeItem::UserType + 1,
    GRAPHIC_TYPE_EDGE,
    GRAPHIC_TYPE_NODE
} GRAPHIC_TYPE;


class GraphicItem : public QGraphicsItem {

public:
    GraphicItem( QGraphicsItem *parent = 0);

    int type() const                        { return GRAPHIC_TYPE_UNDEF; }

    inline QColor getColor()                { return brush.color(); }
    inline void setPen( QPen p)             { pen = p; }
    inline void setBrush( QBrush b)         { brush = b; }

protected:
    QPen pen;
    QBrush brush;
};

#endif // GRAPHITEM_H

