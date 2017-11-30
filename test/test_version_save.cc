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

#include "ptree_oarchive.hh"

struct A
{
  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int version )
  {
     ar & BOOST_SERIALIZATION_NVP(field);
     if(version > 0)
     {
       ar & BOOST_SERIALIZATION_NVP(field2);
     }
  }
  int field;
  int field2;
};

#if BOOST_VERSION > 104400
BOOST_CLASS_VERSION(A, 1)
#endif

int main(int argc, char** argv)
{

  A a1, a2;
  a1.field = 1;
  a2.field = 2;
  a1.field2 = 21;
  a2.field2 = 22;

    // save to ptree->json->file
  {
    boost::property_tree::ptree pt;
    std::string outjson;
    bpta::ptree_oarchive jar(pt);

      // save the data
    jar & BOOST_SERIALIZATION_NVP(a1);
    jar & BOOST_SERIALIZATION_NVP(a2);

      // get json
    boost::filesystem::ofstream outjsonstream("version.json");
    write_json(outjsonstream, pt);
  }

  return 0;
}
