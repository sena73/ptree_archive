/* Copyright (C) 2017 Sergey Spiridonov
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * bpta is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * bpta is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bpta.  If not, see <http://www.gnu.org/licenses/>.
 * */

#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/config.hpp>

#include "ptree_oarchive.hh"
#include <boost/archive/detail/archive_serializer_map.hpp>
//#include <boost/archive/detail/auto_link_archive.hpp>
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


namespace bpta {


  ptree_oarchive::ptree_oarchive(boost::property_tree::ptree &pt, unsigned int flags) :
    boost::archive::detail::common_oarchive<ptree_oarchive>(flags),
    m_pt(pt), m_cur_pt(&m_pt), m_optimize0(true), m_optimizeJson(true)
  {
    if(m_optimize0)
    {
      m_opt0.insert(ptree_archive_object_id);
      m_opt0.insert(ptree_archive_object_reference);
      m_opt0.insert(ptree_archive_class_id);
      m_opt0.insert(ptree_archive_class_id_reference);
      m_opt0.insert(ptree_archive_tracking);
      m_opt0.insert(ptree_archive_version);
      m_opt0.insert(boost_internal_item_version);
    }

    m_reserved.insert(ptree_archive_object_id);
    m_reserved.insert(ptree_archive_object_reference);
    m_reserved.insert(ptree_archive_class_id);
    m_reserved.insert(ptree_archive_class_id_reference);
    m_reserved.insert(ptree_archive_class_name);
    m_reserved.insert(ptree_archive_tracking);
    m_reserved.insert(ptree_archive_version);
    m_reserved.insert(ptree_archive_signature);
    m_reserved.insert(boost_internal_count);
    m_reserved.insert(boost_internal_item);

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


  void ptree_oarchive::save_override(const boost::archive::object_id_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_object_id, uival);
  }

  void ptree_oarchive::save_override(const boost::archive::object_reference_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_object_reference, val);
  }


  void ptree_oarchive::save_override(const boost::archive::version_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    const unsigned int uival = val;
    write_attribute(ptree_archive_version, uival);
  }

  void ptree_oarchive::save_override(const boost::archive::class_id_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    write_attribute(ptree_archive_class_id, val);
  }

  void ptree_oarchive::save_override(const boost::archive::class_id_reference_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    write_attribute(ptree_archive_class_id_reference, val);
  }


  void ptree_oarchive::save_override(const boost::archive::class_id_optional_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    write_attribute(ptree_archive_class_id, val);
  }


  void ptree_oarchive::save_override(const boost::archive::class_name_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
  {
    const char * chval = val;
    write_attribute(ptree_archive_class_name, chval);
  }

  void ptree_oarchive::save_override(const boost::archive::tracking_type & val OVERRIDE_OLD_PARAM_TYPE_EMPTY)
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

} // namespace bpta

namespace boost {
  namespace archive {

    template class detail::archive_serializer_map<bpta::ptree_oarchive>;
//    template class basic_text_iarchive<text_iarchive> ;
//    template class text_iarchive_impl<text_iarchive> ;
			//template class ptree_oarchive_impl<ptree_oarchive> ;

  } // namespace archive
} // namespace boost
