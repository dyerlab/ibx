#include "Graph.H"

Graph::Graph(QObject *parent) : QObject(parent)
{

}


int Graph::indexOf( Node* node ) {
    return( nodes.indexOf( node ) );
}

int Graph::indexOf( QString nodeLabel ){
    for( int i=0;i<nodes.count();++i){
        if( nodes.at(i)->getLabel() == nodeLabel )
            return i;
    }
    return -1;
}

QStringList Graph::nodeLabels() const {
    QStringList ret;
    foreach( Node *n, nodes){
        ret.append( n->getLabel() );
    }
    return ret;
}

QString Graph::toString() {
    QStringList ret;
    ret << "Graph:";

    ret << QString( "Node Set (K=%1):").arg(nodes.count());
    for(int i=0;i<nodes.count();i++)
        ret << QString(" - %1").arg( nodes.at(i)->toString());

    ret << QString( "Edge Set (J=%1):").arg(edges.count());
    for(int i=0;i<edges.count();i++)
        ret << QString(" - wt=%1").arg( edges.at(i)->getWeight());

    return ret.join("\n");
}

Node* Graph::getNode(int idx) {
    return nodes.at(idx);
}

Edge* Graph::getEdge(int idx) {
    return edges.at(idx);
}

bool Graph::addEdge( int source, int target, double weight ){
    if( source > nodes.count() || target > nodes.count())
        return false;

    Node *n1 = nodes.at(source);
    Node *n2 = nodes.at(target);

    if( n1 && n2 ) {
        Edge *e = new Edge(n1,n2,weight);
        n1->addEdge( e );
        n2->addEdge( e );
        edges.append(e);
        return true;
    }
    else
        return false;

}

bool Graph::addEdge( QString source, QString target, double weight) {
    int sidx = -1;
    int tidx = -1;
    for(int i=0;i<nodes.count();i++){
        if( nodes.at(i)->getLabel() == source )
            sidx = i;
        if( nodes.at(i)->getLabel() == target )
            tidx = i;
    }

    return (sidx*tidx>-1) ? addEdge(sidx,tidx,weight) : false;
}



gsl_matrix* Graph::asAdjacencyMatrix(){
    gsl_matrix *m = gsl_matrix_calloc( numNodes(), numNodes() );


    for(int i=0;i<numEdges();i++){
        Edge *e = edges.at(i);
        int x = nodes.indexOf( e->sourceNode() );
        int y = nodes.indexOf( e->targetNode() );
        double wt = e->getWeight();
        gsl_matrix_set(m,x,y,wt);
    }

    return m;

}


gsl_vector* Graph::centrality( CENTRALITY_TYPE type ){

    gsl_matrix *A = asAdjacencyMatrix();
    gsl_vector *ret = NULL;

    switch (type ) {

    case CENTRALITY_DEGREE:
        ret = degreeCentrality(nodes);
        break;

    case CENTRALITY_CLOSENESS:
        ret = closenessCentrality( A );
        break;

    case CENTRALITY_BETWEENESS:
        ret = betweennessCentrality( A );
        break;
    }

    gsl_matrix_free( A );

    return ret;
}


