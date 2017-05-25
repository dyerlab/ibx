/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  Locus.C
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

#include "Locus.H"
#include <QSet>


Locus::Locus(QObject *parent) : QObject(parent) {

}


QStringList Locus::alleles() const {
  return m_alleles;
}

void Locus::setAlleles( QStringList alleles ) {
  m_alleles = alleles;
  std::sort(m_alleles.begin(), m_alleles.end());
}

int Locus::ploidy() const {
  return m_alleles.count();
}

bool Locus::isHeterozygote() const {
  return m_alleles.toSet().count() > 1;
}

bool Locus::isEmpty() const {
  return ploidy()==0;
}

bool Locus::operator ==(Locus *other) {
  return m_alleles == other->m_alleles;
}

bool Locus::operator !=(Locus *other) {
  return !(this==other);
}
