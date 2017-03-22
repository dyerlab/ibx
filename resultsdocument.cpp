#include "resultsdocument.h"

ResultsDocument::ResultsDocument() {
    header = "<html><head><title>IBX Results</title></head><body><h1>IBX</h1>";
    footer = "<p>&copy; 2017 R.J. Dyer</p></body>";
}


void ResultsDocument::addResult(QString val) {
    contents.append(QString("<p>%1</p>").arg(val));
}


void ResultsDocument::addHeader(QString val) {
    contents.append(QString("<h1>%1</h1>").arg(val));
}


void ResultsDocument::addSubheading( QString val ) {
    contents.append(QString("<h2>%1</h2>").arg(val));
}


void ResultsDocument::addOrderedList( QStringList vals) {
    QString res = "<ol>";
    foreach( QString entry, vals) {
        res.append( QString("<li>%1</li>").arg(entry) );
    }
    res.append( "</ol>" );
    contents.append(res);
}


void ResultsDocument::addUnorderedList( QStringList vals) {
    QString res = "<ul>";
    foreach( QString entry, vals) {
        res.append( QString("<li>%1</li>").arg(entry) );
    }
    res.append( "</ul>" );
    contents.append(res);
}



QString ResultsDocument::getResults() const {
    QString allContents = contents.join("</hr>");
    QString res = QString("%1\n%2\n%3").arg(header).arg(allContents).arg(footer);
    return res;
}

QStringList ResultsDocument::rawContents() {
    return contents;
}
