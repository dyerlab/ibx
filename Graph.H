#ifndef GRAPH_H
#define GRAPH_H


#include "Node.H"
#include "Edge.H"
#include "GraphOps.H"

#include <QList>
#include <QObject>

#include <gsl/gsl_matrix.h>

class Graph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_path READ path WRITE setPath );

public:
    explicit Graph(QObject *parent = 0);

    inline int numNodes() { return nodes.count(); }
    inline void addNode(Node *node) { nodes.append( node ); }
    Node* getNode( int idx );
    int indexOf( Node* node );
    int indexOf( QString nodeLabel );

    inline int numEdges() { return edges.count(); }
    bool addEdge( int source, int target, double weight );
    bool addEdge( QString source, QString target, double weight);
    Edge* getEdge( int idx );

    QString toString();
    QStringList nodeLabels() const;

    gsl_matrix* asAdjacencyMatrix();
    gsl_vector* centrality( CENTRALITY_TYPE type );


    inline void setPath(QString path)   { m_path = path; }
    inline QString path()               { return m_path; }

protected:
    QList<Node*> nodes;
    QList<Edge*> edges;

    QString m_path;
};

#endif // GRAPH_H
