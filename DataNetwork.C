/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataNetwork.C
*
*  Created: 6 2017 by rodney
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

#include "DataNetwork.H"

DataNetwork::DataNetwork(bool asLopho) : DataBase("Graph") {

    if( asLopho )
        m_graph = createLopho();
    else
        m_graph = new Graph();

    m_graphWidget = new GraphWidget();
    m_graphWidget->setGraph( m_graph );

    m_type = DATA_TYPE_NETWORK;



}


DataNetwork::~DataNetwork() {
    delete m_graphScene;
    delete m_graphWidget;
    delete m_graph;
}
