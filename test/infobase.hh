/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

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
