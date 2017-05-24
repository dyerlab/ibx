#ifndef RESULTSDOCUMENT_H
#define RESULTSDOCUMENT_H

#include <QString>
#include <QStringList>

class ResultsDocument
{
public:
    ResultsDocument();

    QString getResults() const;

    void addResult( QString val );
    void addHeader(QString val);
    void addSubheading( QString val );
    void addOrderedList( QStringList vals);
    void addUnorderedList( QStringList vals);

    QStringList rawContents();

private:
    QString header;
    QString footer;
    QStringList contents;
};


#endif // RESULTSDOCUMENT_H
