/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  graphwidget.cpp
*
*  Created: 5 2017 by rodney
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

#include "GraphWidget.H"
#include "Charts.H"

#include <gsl/gsl_statistics.h>

#include <QDebug>
#include <QChartView>
#include <QGridLayout>
#include <QVBoxLayout>


GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {

    graphScene = new GraphScene();
    graphView = new GraphView(graphScene);
    graphView->setAttribute(Qt::WA_MacShowFocusRect, false);

    tabWidget = new QTabWidget();


    // Edit Widget
    QWidget *editWidget = new QWidget();
    QVBoxLayout *editLayout = new QVBoxLayout( editWidget );

    // Add Slider
    QHBoxLayout *sliderLayout = new QHBoxLayout();
    sliderLayout->addWidget( new QLabel("Scale Nodes:"));
    nodeScaleSlider = new QSlider(Qt::Horizontal);
    nodeScaleSlider->setMaximum(100);
    nodeScaleSlider->setMinimum(-100);
    nodeScaleSlider->setValue(0);
    nodeScaleSlider->setTickPosition( QSlider::NoTicks );
    connect( nodeScaleSlider, SIGNAL(valueChanged(int)), graphScene, SLOT(scaleNodes(int)));
    sliderLayout->addWidget( nodeScaleSlider );


    editLayout->addWidget( new QLabel("Node Properties") );
    nodePropertiesTable = new QTableWidget();
    editLayout->addWidget(nodePropertiesTable);


    editLayout->addLayout( sliderLayout );
    //editLayout->addStretch(1);



    tabWidget->addTab(editWidget,QString("Edit"));

    // Summary Widget
    QWidget *chartWidget = new QWidget();
    QVBoxLayout *chartLayout = new QVBoxLayout( chartWidget );
    chartLayout->addWidget( new QLabel(tr("<b>Graph Parameters</b>")) );

    QGridLayout *gridLayout = new QGridLayout();

    gridLayout->addWidget( new QLabel("File:"),0,0);
    fileLabel = new QLabel(tr("-"));
    gridLayout->addWidget( fileLabel,0,1 );

    gridLayout->addWidget( new QLabel(tr("# Nodes:")),1,0);
    numNodesLabel = new QLabel("-");
    gridLayout->addWidget(numNodesLabel,1,1);

    gridLayout->addWidget( new QLabel(tr("# Edges:")),2,0);
    numEdgesLabel = new QLabel("-");
    gridLayout->addWidget(numEdgesLabel,2,1);

    gridLayout->addWidget( new QLabel(tr("Mean Degree:")),3,0);
    degreeLabel = new QLabel("-");
    gridLayout->addWidget(degreeLabel,3,1);

    gridLayout->addWidget( new QLabel(tr("Diameter:")),4,0);
    diameterLabel = new QLabel("-");
    gridLayout->addWidget(diameterLabel,4,1);

    chartLayout->addLayout( gridLayout );

    // Add Chart parts.
    degreeChart = new QChartView();
    chartLayout->addWidget( degreeChart );
    closenessChart = new QChartView();
    chartLayout->addWidget( closenessChart );
    betweennessChart = new QChartView();
    chartLayout->addWidget( betweennessChart );
    chartLayout->addStretch(1);

    tabWidget->addTab( chartWidget, "Summary");







    mainSplitter = new QSplitter(Qt::Horizontal,this);
    mainSplitter->setContentsMargins(0,0,0,0);
    mainSplitter->addWidget( graphView );
    mainSplitter->addWidget( tabWidget );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    //mainLayout->setMargin(0);
    mainLayout->addWidget( mainSplitter );
    this->setLayout( mainLayout );

}




void GraphWidget::setGraph( Graph *graph ) {

    graphScene->setGraph( graph );

    QStringList labels = graph->nodeLabels();



    // Set the values
    fileLabel->setText( graph->path());
    numNodesLabel->setText( QString("%1").arg(graph->numNodes()) );
    numEdgesLabel->setText( QString("%1").arg(graph->numEdges()) );

    gsl_vector *vDegree = graph->centrality( CENTRALITY_DEGREE );
    double val = gsl_stats_mean( vDegree->data, vDegree->size, 1 );
    degreeLabel->setText( QString("%1").arg(val));
    degreeChart->setChart( barChart( vDegree, labels, "Degree" ) );

    gsl_vector *vClose = graph->centrality( CENTRALITY_CLOSENESS );
    closenessChart->setChart( barChart( vClose, labels, "Closeness")  );

    gsl_vector *vBetween = graph->centrality( CENTRALITY_BETWEENESS );
    betweennessChart->setChart( barChart( vBetween, labels, "Betweenness") );

    // Set the Edit table stuff
    QStringList headers = graph->getNode(0)->propertyKeys();
    headers.removeAt(  headers.indexOf("Label") );
    std::sort( headers.begin(), headers.end() );
    headers.insert(0,"Label");

    nodePropertiesTable->setRowCount( labels.count() );
    nodePropertiesTable->setColumnCount( headers.count() );
    nodePropertiesTable->setHorizontalHeaderLabels(headers);
    nodePropertiesTable->horizontalHeader()->setStretchLastSection(true);
    nodePropertiesTable->verticalHeader()->hide();

    if( labels.count()){
        for(int i=0;i<labels.count();i++){
            for( int j=0;j<headers.count();j++){
                QVariant val = graph->getNode(i)->getProperty( headers.at(j) );
                qDebug() << headers.at(j) << val.toString();
                QTableWidgetItem *propertyItem = new QTableWidgetItem( val.toString() );
                nodePropertiesTable->setItem(i,j, propertyItem );
            }
        }
    }


    graphView->resetLayout();

    gsl_vector_free( vClose );
    gsl_vector_free( vBetween );
    gsl_vector_free(vDegree);
}
