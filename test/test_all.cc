#include <boost/assign/list_of.hpp>
#include "test_all.hh"


bool TestAll::operator==(const TestAll &other) const
  {
    if(&other == this) return true;
    return
      infs == other.infs &&
      infs0 == other.infs0 &&
      infosp == other.infosp &&
      info1 == other.info1 &&
      info2 == other.info2 &&
      einfo == other.einfo &&
      setmaplistvector == other.setmaplistvector;
  }


void TestAll::populate_with_test_data()
{
  info1.AddFilename("ThisFile.txt" );  
  info1.AddFilename("ThatFile.txt" );  
  info1.AddFilename("OtherFile.txt");  
  info1.set(1, 1.1, "one norm");
    
  info2.AddFilename("ABC");
  info2.AddFilename("123");
  info2.AddFilename("XYZ");
  info2.set(2, 2.2, "two norm");
 
  infs.push_back(info1);
  infs.push_back(info2 );

  einfo.AddFilename("eThisFile.txt" );
  einfo.AddFilename("eThatFile.txt" );
  einfo.AddFilename("eOtherFile.txt");
  einfo.set(10, 10.1, "einfo sample");

  boost::shared_ptr<InfoBase>
    infop1(new ExtendedInfo(1, 1.1, "one ptr", "extended1")),
    infop2(new ExtendedInfo(2, 2.2, "two ptr", "extended2"));

  infop1->AddFilename( "ThisFile.txt" );  
  infop1->AddFilename( "ThatFile.txt" );  
  infop1->AddFilename( "OtherFile.txt" );  
 
  infop2->AddFilename( "ABC" );
  infop2->AddFilename( "123" );
  infop2->AddFilename( "XYZ" );
 
  infosp.push_back( infop1 );
  infosp.push_back( infop2 );

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
  setmaplistvector.insert(maplistvector1);
  setmaplistvector.insert(maplistvector2);
}
