#include "Edge.H"
#include "Node.H"

#include <QPen>
#include <QPainter>

Edge::Edge(Node *source, Node *target, double weight, GraphicItem *parent) : GraphicItem(parent) {
    this->source = source;
    this->target = target;
    this->weight = weight;

    setZValue(1);
}


/*******************   Visualization Stuff    ************************/
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED( widget );
    Q_UNUSED( option );

    QLineF line( source->pos(), target->pos() );
    if( qFuzzyCompare( line.length(),qreal(0.0)))
        return;

    painter->setPen(pen);
    painter->drawLine( line );
}

Node* Edge::otherNode(Node *node) {
    if( node == source )
        return target;
    else if( node == target )
        return source;
    else
        return Q_NULLPTR;
}

void Edge::adjust() {
    if( !source || !target )
        return;

    QLineF line( mapFromItem(source,0,0), mapFromItem(target,0,0));
    this->prepareGeometryChange();
}

QRectF Edge::boundingRect() const {

    if( !source || !target )
        return QRectF(0,0,0,0);
    QPointF pt1 = source->pos();
    QPointF pt2 = target->pos();

    QPointF pt( pt1.x() < pt2.x() ? pt1.x() : pt2.x(),
                pt1.y() < pt2.y() ? pt1.y() : pt2.y());
    QSizeF sz( qAbs( pt1.x()-pt2.x()), qAbs(pt1.y()-pt2.y()));
    return QRectF(pt,sz);
}


