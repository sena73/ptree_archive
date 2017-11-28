/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#ifndef __PTREE_OARCHIVE_HH__
#define __PTREE_OARCHIVE_HH__


#include <ostream>
#include <cstddef> // size_t
#include <set>
#include <map>

#include <boost/mpl/assert.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/property_tree/ptree.hpp>
#include "basic_ptree_archive.hh"

namespace bpta {

  class ptree_oarchive : public boost::archive::detail::common_oarchive<ptree_oarchive>
  {
    typedef boost::archive::detail::common_oarchive<ptree_oarchive> detail_common_oarchive;
    friend class boost::archive::detail::interface_oarchive<ptree_oarchive>;
    friend class boost::archive::save_access;

    boost::property_tree::ptree &m_pt;
    boost::property_tree::ptree *m_cur_pt;
    bool m_optimize0; ///< if true, then do not store integer attributes (like class_id) which are equal to 0
    bool m_optimizeJson; ///< if true , then store containers in json-friendly way (list of values with empty name), otherwise store container in xml-friendly way (list of values with the name equal to 'item')
    std::set<std::string> m_opt0;
    std::set<std::string> m_reserved; ///< reserved names (not allowed to use as field name)

    void init();
    void write_attribute(const char *attribute_name, int t);
    void write_attribute(const char *attribute_name, const char *key);

      // Anything not an attribute and not a name-value pair is an
      // error and should be trapped here.
    template<class T>
    void save_override(T & t OVERRIDE_OLD_PARAM_TYPE)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
      BOOST_MPL_ASSERT((boost::serialization::is_wrapper< T >));
      this->detail_common_oarchive::save_override(t OVERRIDE_OLD_PARAM_PASS);
    }

      // special treatment for name-value pairs.
    template<class T>
    void save_override(
      const ::boost::serialization::nvp< T > & t OVERRIDE_OLD_PARAM_TYPE
                       )
    {
      boost::property_tree::ptree item;
      boost::property_tree::ptree *save_cur_pt = m_cur_pt;
      m_cur_pt = &item;
      this->detail_common_oarchive::save_override(t.const_value() OVERRIDE_OLD_PARAM_PASS);
      m_cur_pt = save_cur_pt;
      std::string tname((t.name() == 0) ? boost_internal_item : t.name());

        // If we would like to serialize this ptree to json, then we can
        // not just insert lot of "item" elements - json does not allow this.
        // We can create an array "item" : [...], which is a list of unnamed elements in ptree
        // One can also consult "count" attribute which is written just before any array - it is
        // not needed because we can reuse ptree::count()
      bool normal_insert = true;
      if(tname == boost_internal_item && m_optimizeJson)
      {
          // check count attr and/or existence of another "item"
        boost::property_tree::ptree::assoc_iterator it = m_cur_pt->find(boost_internal_item);
        if(it != m_cur_pt->not_found())
        {
          normal_insert = false;
            // it can be already converted to "array"...
          if(it->second.empty() || it->second.begin()->first != "")
          {
              // no, convert it to array first
            boost::property_tree::ptree existing_item;
            std::swap(existing_item, it->second);
            it->second.push_back(std::make_pair("", existing_item));
          }
            // add one more item
          it->second.push_back(std::make_pair("", item));
        }
      }
      if(normal_insert)
      {
        if(tname != boost_internal_count && (m_opt0.find(tname) == m_opt0.end()  || ((item.get_value<std::string>() != "0") || !m_optimize0)))
        {
          m_cur_pt->push_back(std::make_pair(tname, item));
        }
      }
    }


      // specific overrides for attributes - not name value pairs so we
      // want to trap them before the above "fall through"
    void save_override(const boost::archive::class_id_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::class_id_optional_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::class_id_reference_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::object_id_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::object_reference_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::version_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::class_name_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void save_override(const boost::archive::tracking_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);

  public:
    ptree_oarchive(boost::property_tree::ptree &pt, unsigned int flags = 0);
    ~ptree_oarchive();

    template<class T>
    void save(const T & t) {
      m_cur_pt->put_value(t);
    }

    void save_binary(const void *address, std::size_t count);
  };

}

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(bpta::ptree_oarchive)

#endif // __PTREE_OARCHIVE_HH__
