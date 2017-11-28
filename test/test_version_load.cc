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

//#define XML_ARCHIVE 1
#ifdef XML_ARCHIVE
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif // XML_ARCHIVE

#include "ptree_oarchive.hh"
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

#ifdef XML_ARCHIVE
    // load from xml file
  {
    boost::filesystem::ifstream inxmlstream("test_version.xml");
    boost::archive::xml_iarchive tar(inxmlstream);

      // load the data
    tar & BOOST_SERIALIZATION_NVP(a1);
    tar & BOOST_SERIALIZATION_NVP(a2);
  }
#endif

    // load from file->json->ptree
  {
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("test_version.json");
    read_json(injsonstream, pt);
    write_json(std::cout, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar & BOOST_SERIALIZATION_NVP(a1);
    jar & BOOST_SERIALIZATION_NVP(a2);

  }

  return 0;
}
