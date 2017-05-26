/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Locus.H
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

#ifndef LOCUS_H
#define LOCUS_H

#include <QObject>

class Locus : public QObject {
  Q_OBJECT
  Q_PROPERTY(QStringList m_alleles READ alleles WRITE setAlleles )

public:
  Locus( QObject *parent = 0);

  QStringList alleles() const;
  void setAlleles( QStringList alleles );

  int ploidy() const;
  bool isHeterozygote() const;
  bool isEmpty() const ;

  bool operator==(Locus *other);
  bool operator!=(Locus *other);

  QString toString() const;

private:
  QStringList m_alleles;

};

typedef Locus* LocusPtr;
Q_DECLARE_METATYPE(LocusPtr)

#endif // LOCUS_H
