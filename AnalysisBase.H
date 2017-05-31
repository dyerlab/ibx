/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  AnalysisBase.H
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

#ifndef ANALYSISBASE_H
#define ANALYSISBASE_H

#include "Globalz.H"
#include "DataResults.H"
#include "DialogDoubleInput.H"

#include <QWidget>
#include <QStringList>
#include <QProgressDialog>


class AnalysisBase
{
public:
    AnalysisBase();
    ~AnalysisBase() {;}

    virtual void run() = 0;

    void initProgress( QString msg, int min, int max);
    void finishProgress();

    inline QStringList getWarnings() { return m_warnings; }
    inline DataResults* getResults() { return m_results; }

    void setUpDoubleSelection(QString title, QString msg1, QStringList list1, QString msg2, QStringList list2 );

protected:
    DataResults *m_results;
    QStringList m_warnings;
    QProgressDialog *m_progress;
    QDialog *m_input_dlg;


};

#endif // ANALYSISBASE_H
