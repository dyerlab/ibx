#include "Node.H"
#include "Edge.H"

Node::Node(QString name, double size, GraphicItem *parent) : GraphicItem(parent)
{
    //this->label = name;
    //this->size = size;
    properties.insert("Label",QVariant(name));
    properties.insert("Size",QVariant(size));
    this->scale = 1;
    showLabel = true;
    setPos( QPointF( qrand() % 800, qrand() % 800 ));

    setFlag( QGraphicsItem::ItemIsMovable, true );
    setFlag( QGraphicsItem::ItemIsSelectable, true );
    setFlag( QGraphicsItem::ItemSendsGeometryChanges, true);

    setPen( QPen(Qt::black));
    setBrush( Qt::darkRed );
    setZValue(3);
}


QString Node::getLabel() const {
    return properties.value("Label").toString();
}

double Node::getSize() const  {
    return properties.value("Size").toDouble();
}

void Node::setSize( double val ) {
    properties.insert("Size",QVariant(val));
}

QString Node::toString() {
    return QString("Node: %1: size=%2").arg(label).arg(getSize());
}


void Node::stopMoving() {
    newPosition = pos();
}

void Node::nudge(double dX, double dY){
    setPos( QPointF(dX,dY) );
}


void Node::setScale( int val ) {
    if( val < 0 )
        scale = 1.0 / ((qreal)val/10.0);
    else
        scale = 1.0 * ((qreal)val/10.0);
}


/****************   Overrides for Plotting *******************/
QRectF Node::boundingRect() const {
    double size = properties.value("Size").toDouble();
    double sz = size * scale;

    QRectF bRect = QRectF(-sz/2,-sz/2,sz,sz);

    /*

    QFont font("Helvetica [Cronyx]", 12, QFont::Normal);
    QFontMetrics metrics(font);
    QRect fontRect = metrics.boundingRect(label);

    bRect.setLeft( -size/2 );
    if( size < fontRect.height())
        bRect.setTop(fontRect.height() + size/2 + 4);
    else
        bRect.setTop(-size/2);
    bRect.setWidth( size + 4 + fontRect.width() );
    bRect.setHeight( size + 4 + fontRect.height() );
    */

    return bRect;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED( option );
    Q_UNUSED( widget );
    painter->setPen( pen );
    painter->setBrush( brush );

    double size = properties.value("Size").toDouble();
    qreal sz = size * scale;

    // set up the gradient
    QRadialGradient gradient(-sz/8,-sz/8,sz/2);
    gradient.setColorAt(0, brush.color().lighter(250));
    gradient.setColorAt(1, brush.color().darker(150));

    painter->setBrush( gradient);
    painter->drawEllipse(-sz/2,-sz/2,sz,sz);

    // show the label if necessary
    /*
    if( showLabel ) {
        painter->setFont( QFont("Helvetica [Cronyx]", 12, QFont::Normal) );
        //painter->drawText(size/2+2,size/2, label);
        painter->drawText(size/2+2,0, label);
    }
    */
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch( change ) {
    case ItemPositionChange:
        foreach( Edge *edge, edges )
            edge->adjust();
        break;

    default:
        break;
    }

    return QGraphicsItem::itemChange( change, value );
}

QPainterPath Node::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

bool Node::shouldAdvance() {
    if( newPosition == pos() )
        return false;
    setPos(newPosition);
    return true;
}


void Node::setProperty( QString key, QVariant val ) {
    properties.insert(key,val);
}

QVariant Node::getProperty( QString key ) const {
    return properties.value(key);
}


QStringList Node::propertyKeys() const {
    return properties.keys();
}







