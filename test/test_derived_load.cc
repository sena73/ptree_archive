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
#include "extended_info.hh"
#include "extended_info2.hh"
#include "test_derived_cast.hh"

//BOOST_SERIALIZATION_ASSUME_ABSTRACT(InfoBase);


int main(int argc, char** argv)   
{


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

  
    // load from file->json->ptree
  {  
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("test_output.json");
    read_json(injsonstream, pt);
    write_json(std::cout, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar & BOOST_SERIALIZATION_NVP(baseptr1);
    jar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }
  
  return 0;  
}
