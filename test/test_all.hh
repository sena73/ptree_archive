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
