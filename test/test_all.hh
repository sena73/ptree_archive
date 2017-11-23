/* Copyright (C) 2017 Sergey Spiridonov <sena@s73.work>
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#ifndef __TESTALL_HH__
#define __TESTALL_HH__

#include <set>
#include <vector>
#include <list>
#include <map>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "extended_info.hh"

template <class A>
bool operator==(const boost::shared_ptr<A> &one, const boost::shared_ptr<A> &another)
{
  return (*one) == (*another);
}

class TestAll
{
public:
  bool operator==(const TestAll &other) const;

  void populate_with_test_data();

  template<class Archive>
  void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_NVP(info1);
    ar & BOOST_SERIALIZATION_NVP(info2);
    ar & BOOST_SERIALIZATION_NVP(einfo);
    ar & BOOST_SERIALIZATION_NVP(infs);
    ar & BOOST_SERIALIZATION_NVP(infs0);
    ar & BOOST_SERIALIZATION_NVP(infosp);
    ar & BOOST_SERIALIZATION_NVP(setmaplistvector);
  }

  std::vector<InfoBase> infs, infs0;
  std::vector<boost::shared_ptr<InfoBase> > infosp;
  InfoBase info1, info2;
  ExtendedInfo einfo;
  std::set<std::map<std::list<std::string>, std::vector<std::string> > > setmaplistvector;
};


#endif
