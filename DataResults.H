/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  ResultsText.H
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

#ifndef RESULTSTEXT_H
#define RESULTSTEXT_H

#include <QUrl>
#include <QPair>
#include <QList>
#include <QString>
#include <QTextEdit>
#include <QTextDocument>

#include "DataBase.H"

class DataResults : public DataBase {

public:
    DataResults(QString label, DataBase *parent=0);
    ~DataResults();

    inline QWidget* getWidget() { return m_textEdit; }
    QTextDocument* getTextDocument();

    void appendHeader( QString text );
    void appendSubHeader( QString text );
    void appendSubSubHeader( QString text );
    void appendText( QString text );
    void appendList( QStringList lines, bool isUnordered=true );
    void appendTable( QString header, QList<QStringList> contents, QString colHeader, QString caption);
    void addResource( int type, QUrl url, QVariant var );
    void appendErrorMessage( QString msg );


private:

    QTextEdit *m_textEdit;
    QList< QPair<int, QUrl> > m_resources;


};

#endif // RESULTSTEXT_H
