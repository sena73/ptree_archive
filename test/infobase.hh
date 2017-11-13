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

#ifndef __INFOBASE_HH__
#define __INFOBASE_HH__

#include <string>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

class InfoBase
{
public:
  InfoBase(int setint, float setfloat, const std::string &setstring);
  InfoBase();
  virtual ~InfoBase();
  virtual bool operator==(const InfoBase &other) const;
  void AddFilename( const std::string& filename );
//  virtual void Print() const;
  void set(int setint, float setfloat, const std::string &setstring);

private:
    // Allow serialization to access non-public data members.
  friend class boost::serialization::access;


  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_NVP(m_int);
    ar & BOOST_SERIALIZATION_NVP(m_float);
    ar & BOOST_SERIALIZATION_NVP(m_string);
    ar & BOOST_SERIALIZATION_NVP(filenames);
  }

  std::vector<std::string> filenames;
  int m_int;
  float m_float;
  std::string m_string;
};

BOOST_CLASS_EXPORT_KEY(InfoBase);

#endif
