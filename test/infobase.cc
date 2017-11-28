/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

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
