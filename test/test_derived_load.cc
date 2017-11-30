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

#include "infobase.hh"
#include "derived_cast.hh"

int main(int argc, char** argv)
{
    // load from file->json->ptree
  {
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("derived.json");
    read_json(injsonstream, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar & BOOST_SERIALIZATION_NVP(baseptr1);
    jar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }

  return 0;
}
