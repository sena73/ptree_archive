/* Copyright (C) 2017 Sergey Spiridonov <sena@s73.work>
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#ifndef __EXTENDED_INFO_HH__
#define __EXTENDED_INFO_HH__

#include <boost/serialization/export.hpp>
#include "infobase.hh"

class ExtendedInfo : public InfoBase
{
public:
  ExtendedInfo(int setint, float setfloat, std::string setstring, const std::string &einfo);
  ExtendedInfo();
  virtual ~ExtendedInfo();

  virtual bool operator==(const ExtendedInfo &other) const;
//  virtual void Print() const;
  void eset(int setint, float setfloat, const std::string &setstring, const std::string &seteinfo);
private:
    // Allow serialization to access non-public data members.
  friend class boost::serialization::access;

  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(InfoBase);
    ar & BOOST_SERIALIZATION_NVP(m_einfo);
  }

  std::string m_einfo;
};

BOOST_CLASS_EXPORT_KEY(ExtendedInfo);

#endif
