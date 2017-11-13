/* Copyright (C) 2017 Sergey Spiridonov
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * bpta is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * bpta is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bpta.  If not, see <http://www.gnu.org/licenses/>.
 * */

#ifndef __EXTENDED_INFO2_HH__
#define __EXTENDED_INFO2_HH__

#include "infobase.hh"

class ExtendedInfo2 : public InfoBase
{
public:
  ExtendedInfo2(int setint, float setfloat, std::string setstring, const std::string &einfo);
  ExtendedInfo2();
  virtual ~ExtendedInfo2();

  virtual bool operator==(const ExtendedInfo2 &other) const;
//  virtual void Print() const;
  void eset(int setint, float setfloat, const std::string &setstring, const std::string &seteinfo);
private:
    // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(InfoBase);
    ar & BOOST_SERIALIZATION_NVP(m_einfo2);
  }

  std::string m_einfo2;
};

BOOST_CLASS_EXPORT_KEY(ExtendedInfo2);

#endif
