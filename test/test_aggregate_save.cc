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
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"

#include "aggregate.hh"


int main(int argc, char** argv)
{
  Aggregate aggregate, aggregate_restored;

  aggregate.populate_with_test_data();

    // save to ptree and json
  boost::property_tree::ptree pt;
  std::string outjson;
  {
    bpta::ptree_oarchive jar(pt);

      // save the data
    jar << BOOST_SERIALIZATION_NVP(aggregate);

      // get json
    boost::filesystem::ofstream outjsonfstream("aggregate.json");
    write_json(outjsonfstream, pt);

    std::ostringstream outjsonsstream;
    write_json(outjsonsstream, pt);
    outjson = outjsonsstream.str();
  }

  // std::cout << "resulting JSON: " << outjson;

    // read from ptree
  {
    bpta::ptree_iarchive jar(pt);

      // Load the data
    jar & boost::serialization::make_nvp("aggregate"  , aggregate_restored);
  }

  std::cout << "comparing objects:" << std::endl;
  if(aggregate == aggregate_restored)
  {
    std::cout << "original and loaded are equal" << std::endl;
  }
  else
  {
    std::cout << "original and loaded are NOT equal" << std::endl;
  }


  std::cout << "comparing ptrees:" << std::endl;
  boost::property_tree::ptree pt2;
  std::string outjson2;
  {
    bpta::ptree_oarchive jar(pt2);

    jar & boost::serialization::make_nvp("aggregate", aggregate_restored);

    std::ostringstream outjsonstream;
    write_json(outjsonstream, pt2);
    outjson2 = outjsonstream.str();
  }

  if(pt == pt2)
  {
    std::cout << "ptrees are equal" << std::endl;
  }
  else
  {
    std::cout << "ptrees are NOT equal" << std::endl;
  }

  std::cout << "comparing jsons:" << std::endl;
  if(outjson == outjson2)
  {
    std::cout << "jsons are equal" << std::endl;
  }
  else
  {
    std::cout << "jsons are NOT equal!\n";
    std::cout << "json1:\n" << outjson << "\n";
    std::cout << "json2:\n" << outjson2 << "\n";
  }

  return 0;
}
