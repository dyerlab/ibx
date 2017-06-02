/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  chartops
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

#include <QtAlgorithms>
#include <QDebug>
#include <QList>
#include "Charts.H"

QChart* histogram( gsl_vector *data , QString title){
    int mn = (int)gsl_vector_min(data);
    int mx = (int)gsl_vector_max(data);

    gsl_vector *v = gsl_vector_calloc( 1 + (mx-mn) );
    for( size_t i=0;i<data->size;i++){
        double x = gsl_vector_get( data, i);
        gsl_vector_set( v, (x-mn), (gsl_vector_get(v, (x-mn))+ 1 ));
    }
    QStringList labels;
    for(int i=mn; i<= mx; i++)
        labels << QString("%1").arg(i);

    QChart *chart = barChart( v, labels, title);
    gsl_vector_free( v );

    return chart;
}


QChart* barChart( gsl_vector *data, QStringList labels, QString title, bool legend ) {
    QBarSet *set = new QBarSet("");

    for(size_t i=0;i<data->size;i++){
        set->append( gsl_vector_get(data,i) );
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries( series );
    if( title.count() )
        chart->setTitle( title );

    if( labels.count() ){
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(labels);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);
        axis->setLabelsAngle(270);
        QFont font;
        font.setFamily(font.defaultFamily());
        font.setPixelSize(10);
        axis->setLabelsFont(font);
        QAbstractAxis *axisY = chart->axisY();
        axisY->setLabelsFont(font);

    }

    chart->legend()->setVisible(legend);

    chart->setAnimationOptions( QChart::SeriesAnimations );
    return chart;
}
