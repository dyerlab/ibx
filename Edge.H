#ifndef EDGE_H
#define EDGE_H


#include "GraphicItem.H"

class Node;

class Edge : public GraphicItem
{

public:
    explicit Edge(Node *source, Node *target, double weight=1.0, GraphicItem *parent = 0);

    inline GRAPHIC_TYPE graphicType()      { return GRAPHIC_TYPE_EDGE; }

    inline Node* sourceNode() const    { return source; }
    inline Node* targetNode() const    { return target; }
    Node* otherNode(Node *node);
    inline double getWeight() const { return weight; }

    // Visualization stuff
    void adjust();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    Node *source;
    Node *target;
    double weight;
};

#endif // EDGE_H
