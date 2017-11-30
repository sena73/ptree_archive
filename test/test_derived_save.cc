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

#include "infobase.hh"
#include "derived_cast.hh"

int main(int argc, char** argv)
{
    // save to ptree->json->file
  {
    boost::shared_ptr<InfoBase>
      baseptr1(createExtendedInfo ()),
      baseptr2(createExtendedInfo2());
    boost::property_tree::ptree pt;
    bpta::ptree_oarchive jar(pt);

      // save the data
    jar & BOOST_SERIALIZATION_NVP(baseptr1);
    jar & BOOST_SERIALIZATION_NVP(baseptr2);

      // get json
    boost::filesystem::ofstream outjsonstream("derived.json");
    write_json(outjsonstream, pt);
  }

  return 0;
}
