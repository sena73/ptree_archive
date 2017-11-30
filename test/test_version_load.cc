/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

#include "ptree_iarchive.hh"


struct A
{
  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int version )
  {
     ar & BOOST_SERIALIZATION_NVP(field);
  }

  int field;
};

int main(int argc, char** argv)
{
  A a1, a2;

    // load from file->json->ptree
  {
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("version.json");
    read_json(injsonstream, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar & BOOST_SERIALIZATION_NVP(a1);
    jar & BOOST_SERIALIZATION_NVP(a2);

  }

  return 0;
}
