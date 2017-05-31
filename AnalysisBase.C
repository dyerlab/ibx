/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  AnalysisBase.C
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

#include "AnalysisBase.H"
#include <QApplication>
#include <QObject>



AnalysisBase::AnalysisBase() {
    m_results = new DataResults("Analysis Base");
}

void AnalysisBase::initProgress(QString msg, int min, int max){
    m_progress = new QProgressDialog( msg, QObject::tr("Cancel"), min, max, qApp->activeWindow());
    m_progress->setValue(min);
    m_progress->show();
    qApp->processEvents();
}

void AnalysisBase::finishProgress() {
    m_progress->setValue( m_progress->maximum() );
    m_progress->accept();
    delete m_progress;
}

void AnalysisBase::setUpDoubleSelection(QString title, QString msg1, QStringList list1, QString msg2, QStringList list2 ) {
    m_input_dlg = new DialogDoubleInput(title,msg1,list1,msg2,list2, qApp->activeWindow() );
}
