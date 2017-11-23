/* Copyright (C) 2017 Sergey Spiridonov <sena@s73.work>
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"
#include "extended_info2.hh"



ExtendedInfo2::ExtendedInfo2(int setint, float setfloat, std::string setstring, const std::string &einfo)
  : InfoBase(setint, setfloat, setstring), m_einfo2(einfo)
{
}

ExtendedInfo2::ExtendedInfo2()
  : InfoBase(), m_einfo2("")
{
}

ExtendedInfo2::~ExtendedInfo2()
{}


bool ExtendedInfo2::operator==(const ExtendedInfo2 &other) const
{
  if(&other == this) return true;

  return
    InfoBase::operator==(other) &&
    m_einfo2 == other.m_einfo2;
}

void ExtendedInfo2::eset(int setint, float setfloat, const std::string &setstring, const std::string &seteinfo)
{
  InfoBase::set(setint, setfloat, setstring);
  m_einfo2 = seteinfo;
}


//==== begin of the code that is needed to register ExtendedInfo2 class ====
//BOOST_CLASS_EXPORT_GUID(ExtendedInfo2, "ExtendedInfo2");
BOOST_CLASS_EXPORT_IMPLEMENT(ExtendedInfo2);

//==== end of the code that is needed to register ExtendedInfo2 class ====
