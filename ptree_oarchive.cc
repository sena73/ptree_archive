//#define BOOST_ARCHIVE_SOURCE
//#include <boost/serialization/config.hpp>
#include "ptree_oarchive.hh"
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>

// explicitly instantiate for this type of ptree
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_text_oprimitive.ipp>

#include "basic_ptree_archive.hh"

#include <ostream>
#include <iomanip>
#include <algorithm> // std::copy
#include <string>
#include <exception>

#include <cstring> // strlen
#include <boost/archive/iterators/ostream_iterator.hpp>


namespace BPT {


  ptree_oarchive::ptree_oarchive(boost::property_tree::ptree &pt, unsigned int flags) :
    boost::archive::detail::common_oarchive<ptree_oarchive>(flags),
    m_pt(pt), m_cur_pt(&m_pt), m_optimize0(true), m_optimizeJson(true)
  {
    m_opt0.insert(ptree_archive_object_id);
    m_opt0.insert(ptree_archive_object_reference);
    m_opt0.insert(ptree_archive_class_id);
    m_opt0.insert(ptree_archive_class_id_reference);
    m_opt0.insert(ptree_archive_tracking);
    m_opt0.insert(ptree_archive_version);
    m_opt0.insert(boost_internal_item_version);

      // we do need so big signature - just remove it or make it shorter?
      // write_attribute(ptree_archive_signature, boost::archive::BOOST_ARCHIVE_SIGNATURE());
    write_attribute(ptree_archive_version, boost::archive::BOOST_ARCHIVE_VERSION());
  }
  
  
  void ptree_oarchive::write_attribute(const char *attribute_name, int val)
  {
    if(val != 0 || !m_optimize0)
    {
      m_cur_pt->put(attribute_name, val);
    }
  }


  void ptree_oarchive::write_attribute(const char *attribute_name, const char *key)
  {
    if(key != 0 && key[0] != 0)
    {
      m_cur_pt->put(attribute_name, key);
    }
  }


  void ptree_oarchive::save_override(const boost::archive::object_id_type & val)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_object_id, uival);
  }


  void ptree_oarchive::save_override(const boost::archive::object_reference_type & val)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_object_reference, val);
  }


  void ptree_oarchive::save_override(const boost::archive::version_type & val)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_version, uival);
  }


  void ptree_oarchive::save_override(const boost::archive::class_id_type & val)
  {
    write_attribute(ptree_archive_class_id, val);
  }


  void ptree_oarchive::save_override(const boost::archive::class_id_reference_type & val)
  {
    write_attribute(ptree_archive_class_id_reference, val);
  }


  void ptree_oarchive::save_override(const boost::archive::class_id_optional_type & val)
  {
    write_attribute(ptree_archive_class_id, val);
  }
 

  void ptree_oarchive::save_override(const boost::archive::class_name_type & val)
  {
    const char * chval = val;
    write_attribute(ptree_archive_class_name, chval);
  }


  void
  ptree_oarchive::save_override(const boost::archive::tracking_type & val)
  {
    write_attribute(ptree_archive_tracking, val.t);
  }



  class save_bin : public boost::archive::basic_text_oprimitive<std::ostringstream>
  { 
  public:
    save_bin(std::ostringstream &oss)
      : boost::archive::basic_text_oprimitive<std::ostringstream>(oss, true)
      {}

    ~save_bin()
      {}
  };
    
  
  void
  ptree_oarchive::save_binary(const void *address, std::size_t count)
  {
    std::ostringstream oss;
    save_bin sb(oss);
    sb.save_binary(address, count);
    m_cur_pt->put_value(oss.str());
  }

  ptree_oarchive::~ptree_oarchive()
  {
    if(std::uncaught_exception()) return;
  }

} // namespace BPT

namespace boost {
  namespace archive {

    template class detail::archive_serializer_map<BPT::ptree_oarchive>;
      //template class ptree_oarchive_impl<ptree_oarchive> ;
  
  } // namespace archive
} // namespace boost
