#include <iostream>
#include <vector>  
#include <fstream>
#include <set>
#include <list>
#include <map>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
//#include <boost/archive/text_oarchive.hpp>   
//#include <boost/archive/text_iarchive.hpp>   
//#include <boost/archive/xml_oarchive.hpp>   
//#include <boost/archive/xml_iarchive.hpp>   
//#include <boost/serialization/split_member.hpp>  

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/property_tree/info_parser.hpp>
#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"



class Info  
{  
private:  
    // Allow serialization to access non-public data members.  
  friend class boost::serialization::access;  

  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_NVP(m_int);
    ar & BOOST_SERIALIZATION_NVP(m_float);
    ar & BOOST_SERIALIZATION_NVP(m_string);
    ar & BOOST_SERIALIZATION_NVP(filenames);  
  }
  
  std::vector<std::string> filenames;
  int m_int;
  float m_float;
  std::string m_string;
   
public:
  bool operator==(const Info &other) const
  {
    if(&other == this) return true;
    return
      m_int == other.m_int &&
      m_float == other.m_float &&
      m_string == other.m_string &&
      filenames == other.filenames;
  }

  void AddFilename( const std::string& filename );      
  void Print() const;
  void set(int setint, float setfloat, std::string setstring)
    {
      m_int = setint;
      m_float = setfloat;
      m_string = setstring;
    }
};
  
   
void Info::Print() const 
{
  std::cout << "m_int = " << m_int << " m_float = " << m_float << " m_string = " << m_string << " fnames: [";
  std::copy(filenames.begin(),       
            filenames.end(),       
            std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << "]\n";
}

void Info::AddFilename( const std::string& filename )  
{  
  filenames.push_back( filename );
}


template <class A>
bool operator==(const boost::shared_ptr<A> &one, const boost::shared_ptr<A> &another)
{
  return (*one) == (*another);
}

struct TestAll
{
  bool operator==(const TestAll &other) const
  {
    if(&other == this) return true;
    return
      infs == other.infs &&
      infs0 == other.infs0 &&
      infosp == other.infosp &&
      info1 == other.info1 &&
      info2 == other.info2 &&
      setmaplistvector == other.setmaplistvector;
  }
  
  
  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int /* version */)
  {
    ar & BOOST_SERIALIZATION_NVP(info1);
    ar & BOOST_SERIALIZATION_NVP(info2);
    ar & BOOST_SERIALIZATION_NVP(infs);
    ar & BOOST_SERIALIZATION_NVP(infs0);
    ar & BOOST_SERIALIZATION_NVP(infosp);
    ar & BOOST_SERIALIZATION_NVP(setmaplistvector);    
  }
  
  std::vector<Info> infs, infs0;
  std::vector<boost::shared_ptr<Info> > infosp;
  Info info1, info2;
  std::set<std::map<std::list<std::string>, std::vector<std::string> > > setmaplistvector;
};

   
int main(int argc, char** argv)   
{
  TestAll test_all, test_all_restored;

    // populate test_all
  test_all.info1.AddFilename("ThisFile.txt" );  
  test_all.info1.AddFilename("ThatFile.txt" );  
  test_all.info1.AddFilename("OtherFile.txt");  
  test_all.info1.set(1, 1.1, "one norm");
    
  test_all.info2.AddFilename("ABC");
  test_all.info2.AddFilename("123");
  test_all.info2.AddFilename("XYZ");
  test_all.info2.set(2, 2.2, "two norm");
 
  test_all.infs.push_back(test_all.info1);
  test_all.infs.push_back(test_all.info2 );

  boost::shared_ptr<Info> infop1(new Info()), infop2(new Info());
  infop1->AddFilename( "ThisFile.txt" );  
  infop1->AddFilename( "ThatFile.txt" );  
  infop1->AddFilename( "OtherFile.txt" );  
  infop1->set(1, 1.1, "one ptr");
 
  infop2->AddFilename( "ABC" );
  infop2->AddFilename( "123" );
  infop2->AddFilename( "XYZ" );
  infop2->set(2, 2.2, "two ptr");
 
  test_all.infosp.push_back( infop1 );
  test_all.infosp.push_back( infop2 );

  std::map<std::list<std::string>, std::vector<std::string> > maplistvector1, maplistvector2;
  std::list<std::string>
    l_11a = boost::assign::list_of("11a")("11b")("11c"),
    l_12b = boost::assign::list_of("12b")("12c")("12d"),
    l_21a = boost::assign::list_of("21a")("21b")("21c"),
    l_21b = boost::assign::list_of("22b")("22c")("22d");
  std::vector<std::string>
    v_1b1 = boost::assign::list_of("1b1")("1c1")("1d1"),
    v_1a2 = boost::assign::list_of("1a2")("1b2")("1c2"),
    v_2b1 = boost::assign::list_of("2b1")("2c1")("2d1"),
    v_2a2 = boost::assign::list_of("2a2")("2b2")("2c2");
  maplistvector1[l_11a] = v_1b1;
  maplistvector1[l_12b] = v_1a2;
  maplistvector2[l_21a] = v_2b1;
  maplistvector2[l_21b] = v_2a2;
  std::set<std::map<std::list<std::string>, std::vector<std::string> > > setmaplistvector, restored_setmaplistvector;
  test_all.setmaplistvector.insert(maplistvector1);
  test_all.setmaplistvector.insert(maplistvector2);
    

    // save to ptree and json
  boost::property_tree::ptree pt;
  std::string outjson;
  {  
    BPT::ptree_oarchive jar(pt);

      // save the data
    jar & BOOST_SERIALIZATION_NVP(test_all);

      // get json
    std::ostringstream outjsonstream;
    write_json(outjsonstream, pt);
    outjson = outjsonstream.str();
  }

    // read from ptree
  {
    BPT::ptree_iarchive jar(pt);
   
      // Load the data  
    jar & boost::serialization::make_nvp("test_all"  , test_all_restored);
  }

  std::cout << "comparing objects:" << std::endl;
  if(test_all == test_all_restored)
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
    BPT::ptree_oarchive jar(pt2);

    jar & boost::serialization::make_nvp("test_all", test_all_restored);

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
