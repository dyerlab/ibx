/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  ResultsText.C
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

#include "DataResults.H"

DataResults::DataResults(QString label, DataBase *parent) : DataBase(label,parent) {
    m_type = DATA_TYPE_RESULTS;
    m_textEdit = new QTextEdit();
    m_textEdit->setReadOnly( true );
    QFile style(QString(":/media/ibx_results.css"));
    if( style.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&style);
        QString styles = in.readAll();
        m_textEdit->document()->setDefaultStyleSheet( styles );
        style.close();
    }
}

DataResults::~DataResults() {
    delete m_textEdit;
}

DATA_TYPE DataResults() {
    return DATA_TYPE_RESULTS;
}

QTextDocument* DataResults::getTextDocument(){
    return m_textEdit->document();
}


void DataResults::appendHeader( QString text ){
    QString current = m_textEdit->document()->toHtml();
    m_textEdit->document()->setHtml( current + QString("<h1>%1</h1>").arg(text ));
}

void DataResults::appendSubHeader( QString text ){
    QString current = m_textEdit->document()->toHtml();
    m_textEdit->document()->setHtml( current + QString("<h2>%1</h2>").arg(text ));
}

void DataResults::appendSubSubHeader( QString text ){
    QString current = m_textEdit->document()->toHtml();
    m_textEdit->document()->setHtml( current + QString("<h3>%1</h3>").arg(text ));
}

void DataResults::appendText( QString text ){
    QString current = m_textEdit->document()->toHtml();
    m_textEdit->document()->setHtml( current + QString("<p>%1</p>").arg(text ));
}

void DataResults::appendErrorMessage( QString msg ) {
    QString hdr = QObject::tr("<font color=\"red\">ERRORS:</font>");
    QString para = QString(QObject::tr("The following error was encountered."));
    QString msgs = QString("<table align=\"center\" width=\"80\%\"><tr><td>%1</td></tr></table>").arg(msg );
    appendHeader( hdr );
    appendText( para );
    appendText( msgs );
}


void DataResults::appendList( QStringList lines, bool isUnordered ) {
    QString current = m_textEdit->document()->toHtml();
    current += ( isUnordered) ? QString("<ul>") : QString("<ol>");
    foreach( QString line, lines )
        current += QString("<li>%1</li>").arg(line );
    current += ( isUnordered) ? QString("<ul>") : QString("<ol>");
    m_textEdit->document()->setHtml( current + "<p></p>");
}

void DataResults::appendTable( QString caption, gsl_matrix *content, QStringList rowHeaders, QStringList colHeaders ){
    Q_ASSERT( content->size1 == (size_t)rowHeaders.count() );
    Q_ASSERT( content->size2 == (size_t)colHeaders.count() );

    QString doc = m_textEdit->document()->toHtml();

    doc += QString("<table border=1>\n");

    if( !caption.isEmpty() )
        doc += QString("<caption>%1</caption>").arg(caption);

    if( colHeaders.count()){
        doc += QString("<tr>");
        if( colHeaders.count())
            doc += QString("<th>&nbsp;</th>");
        foreach(QString hdr, colHeaders )
            doc += QString("<th>%1</th>").arg(hdr);
        doc += QString("</tr>");
    }

    for(size_t i=0; i<content->size1;i++){
        doc += QString("<tr>");
        if( i < rowHeaders.count())
            doc += QString("<th>%1</th>").arg(rowHeaders.at(i));

        for( size_t j=0;j<content->size2;j++){
            double val = gsl_matrix_get(content,i,j);
            if( val )
                doc += QString("<td>%1</td>").arg(val, 0, 'g', 4);
            else
                doc += QString("<td></td>");
        }
        doc += QString("</tr>");
    }

    doc += QString("</table>");
    m_textEdit->document()->setHtml( doc );
}

void DataResults::appendTable( QString header, QList<QStringList> contents, QString colHeader, QString caption) {
    QString doc = m_textEdit->document()->toHtml();
    int numRows = contents.count();
    int numCols = contents[0].count();

    doc += QString("<h3>%1</h3>").arg( header );

    if( caption.count() )
        doc += QString("<p>%1</p>").arg(caption);

    doc += QString("<table>\n");

    if( !colHeader.isEmpty() && numCols > 1 )
        doc += QString("<tr><td></td><td align=\"center\" colspan=%1>%2</td></tr>").arg(numCols-1).arg(colHeader);

    for(int i=0;i<numRows;i++){
        doc += QString("\n<tr>");
        for(int j=0;j<numCols;j++){
            if( i==0 )	  doc += QString("<th nowrap>");
            else if(j==0) doc += QString("<th align=\"left\">");
            else		  doc += QString("<td align=\"center\">");
            doc += contents[i][j];
            if( i==0 || j==0 ) doc += QString("</th>");
            else			   doc += QString("</td>");
        }
        doc += QString("</tr>");
    }
    doc += QString("<table>\n<p></p>");
    m_textEdit->document()->setHtml( doc );
}

void DataResults::addResource( int type, QUrl url, QVariant var ) {
    m_textEdit->document()->addResource(type,url,var);
    m_resources.append( qMakePair( type, url ) );

}

void DataResults::scrollToTop() {
    m_textEdit->moveCursor( QTextCursor::Start, QTextCursor::MoveAnchor );
    qApp->processEvents();
}
