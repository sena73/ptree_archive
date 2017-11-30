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

#include "ptree_iarchive.hh"
#include "aggregate.hh"


int main(int argc, char** argv)
{
  Aggregate aggregate;

    // load from file->json->ptree
  {
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("aggregate.json");
    read_json(injsonstream, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar >> BOOST_SERIALIZATION_NVP(aggregate);
  }

  Aggregate aggregate_orig;
  aggregate_orig.populate_with_test_data();
  
  if(!(aggregate == aggregate_orig))
  {
    throw std::runtime_error("original and loaded objects are NOT equal");
  }

  return 0;  
}
