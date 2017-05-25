/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DialogImportGenotypes.H
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

#ifndef DIALOGIMPORTGENOTYPES_H
#define DIALOGIMPORTGENOTYPES_H

#include <QHash>
#include <QString>
#include <QDialog>
#include <QListWidget>
#include "Globalz.H"




namespace Ui {
class DialogImportGenotypes;
}

class DialogImportGenotypes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImportGenotypes(QWidget *parent = 0);
    ~DialogImportGenotypes();

    void setHeaders(QStringList headers);

    LOCUS_TYPE getLocusType() const ;
    QHash<QString,COLUMN_TYPE> dataTypes();


private:
    Ui::DialogImportGenotypes *ui;


private slots:

    void slotHeader2Strata();
    void slotHeader2External();
    void slotHeader2Loci();
    void slotStrata2Header();
    void slotExternal2Header();
    void slotLoci2Header();
};

#endif // DIALOGIMPORTGENOTYPES_H
