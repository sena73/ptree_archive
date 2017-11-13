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

#include <boost/serialization/vector.hpp>
#include "infobase.hh"

InfoBase::InfoBase(int setint, float setfloat, const std::string &setstring)
{
  set(setint, setfloat, setstring);
}

InfoBase::InfoBase()
{
  set(0, 0., "");
}

InfoBase::~InfoBase()
{}

bool InfoBase::operator==(const InfoBase &other) const
{
  if(&other == this) return true;
  return
    m_int == other.m_int &&
    m_float == other.m_float &&
    m_string == other.m_string &&
    filenames == other.filenames;
}

void InfoBase::set(int setint, float setfloat, const std::string &setstring)
{
  m_int = setint;
  m_float = setfloat;
  m_string = setstring;
}

// void InfoBase::Print() const
// {
//   std::cout << "m_int = " << m_int << " m_float = " << m_float << " m_string = " << m_string << " fnames: [";
//   std::copy(filenames.begin(),
//             filenames.end(),
//             std::ostream_iterator<std::string>(std::cout, " "));
//   std::cout << "]\n";
// }


void InfoBase::AddFilename( const std::string& filename )
{
  filenames.push_back( filename );
}

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"

BOOST_CLASS_EXPORT_IMPLEMENT(InfoBase);
