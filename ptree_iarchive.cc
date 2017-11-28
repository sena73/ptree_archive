/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/config.hpp>

#include "ptree_iarchive.hh"
#include <boost/archive/archive_exception.hpp>

#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>

#include <istream>
#include <string>
#include <exception>

// explicitly instantiate for this type of ptree
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_text_iprimitive.ipp>

#include "basic_ptree_archive.hh"

namespace bpta {

  ptree_iarchive::ptree_iarchive(const boost::property_tree::ptree &pt, unsigned int flags) :
    boost::archive::detail::common_iarchive<ptree_iarchive>(flags),
    m_pt(pt), m_cur_pt(&m_pt), m_item_assoc_it(m_pt.not_found()), m_it_nf(m_pt.not_found())
  {
    boost::optional<int> optval = m_cur_pt->get_optional<int>(ptree_archive_version);
    if(optval)
    {
      set_library_version(boost::archive::library_version_type(*optval));
    }
  }

  void ptree_iarchive::read_attribute(const char *attr_name, const char *alt_attr_name, int &retval)
  {
    static const int default_val = 0;
    retval = default_val;

      // TODO: default val==0 is OK only for "optimized-0" values (defined now in ptree_oarchive.cc ctor)
    if(attr_name == 0)
    {
      throw std::logic_error("attr_name is 0");
    }

    boost::optional<int> optval = m_cur_pt->get_optional<int>(attr_name);
    if(!optval && alt_attr_name)
    {
      optval = m_cur_pt->get_optional<int>(alt_attr_name);
    }

    if(optval)
    {
      retval = *optval;
    }
  }


  void ptree_iarchive::read_attribute(const char *attribute_name, std::string &key)
  {
    if(attribute_name == 0)
    {
      throw std::logic_error("attribute_name is 0");
    }

    key = m_cur_pt->get<std::string>(attribute_name, std::string(""));
  }


  void ptree_iarchive::load_override(boost::archive::object_id_type &val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    int ival;
    read_attribute(ptree_archive_object_id, ptree_archive_object_reference, ival);
    val = boost::archive::object_id_type(ival);
  }

    // not needed: void ptree_iarchive::load_override(boost::archive::object_reference_type & t) ...

  void ptree_iarchive::load_override(boost::archive::version_type &val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    int ival;
    read_attribute(ptree_archive_version, 0, ival);
    val = boost::archive::version_type(ival);
  }

  void ptree_iarchive::load_override(boost::archive::class_id_type &val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    int ival;
    read_attribute(ptree_archive_class_id, ptree_archive_class_id_reference, ival);
    val = boost::archive::class_id_type(ival);
  }

  void ptree_iarchive::load_override(boost::archive::class_id_optional_type & OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
     // empty in xml_iarchive... not sure what is it for? - sena
  }

  void ptree_iarchive::load_override(boost::archive::class_name_type &val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    std::string sval;
    sval.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
    read_attribute(ptree_archive_class_name, sval);
    if(sval.size() > (BOOST_SERIALIZATION_MAX_KEY_SIZE - 1))
        boost::serialization::throw_exception(
					boost::archive::archive_exception(boost::archive::archive_exception::invalid_class_name)
        );
    std::strncpy(val, sval.c_str(), sval.size()+1);
  }

  void ptree_iarchive::load_override(boost::archive::tracking_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    int ival;
    read_attribute(ptree_archive_tracking, 0, ival);
    val = boost::archive::tracking_type(ival);
  }

  void
  ptree_iarchive::init()
  {
  }


  class load_bin : public boost::archive::basic_text_iprimitive<std::istringstream>
  {

  public:
    load_bin(std::istringstream &iss)
      : boost::archive::basic_text_iprimitive<std::istringstream>(iss, true)
      {}

    ~load_bin()
      {}
  };


  void ptree_iarchive::load_binary(void *address, std::size_t count)
  {
    std::istringstream iss(m_cur_pt->get_value<std::string>());
    load_bin lb(iss);
    lb.load_binary(address, count);
  }

  ptree_iarchive::~ptree_iarchive()
  {
    if(std::uncaught_exception())
      return;
  }

} // namespace bpta

namespace boost {
  namespace archive {
    template class detail::archive_serializer_map<bpta::ptree_iarchive>;
  } // namespace archive
} // namespace boost
