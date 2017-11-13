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

#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"

#include "extended_info.hh"



ExtendedInfo::ExtendedInfo(int setint, float setfloat, std::string setstring, const std::string &einfo)
  : InfoBase(setint, setfloat, setstring), m_einfo(einfo)
{
}

ExtendedInfo::ExtendedInfo()
  : InfoBase(), m_einfo("")
{
}

ExtendedInfo::~ExtendedInfo()
{}


bool ExtendedInfo::operator==(const ExtendedInfo &other) const
{
  if(&other == this) return true;

  return
    InfoBase::operator==(other) &&
    m_einfo == other.m_einfo;
}

void ExtendedInfo::eset(int setint, float setfloat, const std::string &setstring, const std::string &seteinfo)
{
  InfoBase::set(setint, setfloat, setstring);
  m_einfo = seteinfo;
}


//==== begin of the code that is needed to register ExtendedInfo class ====

//BOOST_CLASS_EXPORT_GUID(ExtendedInfo, "ExtendedInfo");
BOOST_CLASS_EXPORT_IMPLEMENT(ExtendedInfo);
//==== end of the code that is needed to register ExtendedInfo class ====
