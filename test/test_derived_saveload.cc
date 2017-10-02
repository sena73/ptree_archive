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

    // save to text file
  {
    boost::shared_ptr<InfoBase> baseptr1(createExtendedInfo ()), baseptr2(createExtendedInfo2());
    boost::filesystem::ofstream outtxtstream("test_output.txt");
    boost::archive::text_oarchive tar(outtxtstream);

      // save the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);
  }

    // load from text file
  {  
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::filesystem::ifstream intextstream("test_output.txt");
    boost::archive::text_iarchive tar(intextstream);

      // load the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }

    // save to ptree->json->file
  {  
    boost::shared_ptr<InfoBase> baseptr1(createExtendedInfo ()), baseptr2(createExtendedInfo2());
    boost::property_tree::ptree pt;
    bpta::ptree_oarchive tar(pt);

      // save the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);

      // get json
    boost::filesystem::ofstream outjsonstream("test_output.json");
    write_json(outjsonstream, pt);
  }
  
    // load from json file
  {  
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::filesystem::ifstream intextstream("test_output.json");
    boost::property_tree::ptree pt;
    read_json(intextstream, pt);
    bpta::ptree_iarchive tar(pt);

      // load the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }
  return 0;
}
