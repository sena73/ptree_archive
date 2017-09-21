#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"

#include "infobase.hh"
#include "test_derived_cast.hh"
   
int main(int argc, char** argv)   
{
  boost::shared_ptr<InfoBase> baseptr1(createExtendedInfo ());
  boost::shared_ptr<InfoBase> baseptr2(createExtendedInfo2());

    // save to text file
  {
    boost::filesystem::ofstream outtxtstream("test_output.txt");
    boost::archive::text_oarchive tar(outtxtstream);

      // save the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);
  }


    // save to ptree->json->file
  boost::property_tree::ptree pt;
  std::string outjson;
  {  
    bpta::ptree_oarchive jar(pt);

      // save the data
    jar & BOOST_SERIALIZATION_NVP(baseptr1);
    jar & BOOST_SERIALIZATION_NVP(baseptr2);

      // get json
    boost::filesystem::ofstream outjsonstream("test_output.json");
    write_json(outjsonstream, pt);
  }
  
  return 0;  
}
