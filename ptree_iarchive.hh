/* Copyright (C) 2017 Sergey Spiridonov (sena at s73 dot work)
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#ifndef __PTREE_IARCHIVE_HH__
#define __PTREE_IARCHIVE_HH__

#include <ostream>
#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/version.hpp>
#if BOOST_VERSION <= 105500
#include <boost/archive/shared_ptr_helper.hpp>
#elif BOOST_VERSION <= 105800
#include <boost/serialization/shared_ptr_helper.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include "basic_ptree_archive.hh"

namespace bpta {

  template <typename T>
  void setInt(T&, int)
  {
    throw std::logic_error(std::string("default setInt is called with type ") + typeid(T).name());
  }

  template <>
  inline void setInt(boost::serialization::item_version_type& val, int toset)
  {
    val = boost::serialization::item_version_type(toset);
  }

  template <>
  inline void setInt(boost::serialization::collection_size_type& sz, int toset)
  {
    sz = toset;
  }


  class ptree_iarchive : public boost::archive::detail::common_iarchive<ptree_iarchive>
#if BOOST_VERSION <= 105500
	, public boost::archive::detail::shared_ptr_helper
#endif
  {
    typedef boost::archive::detail::common_iarchive<ptree_iarchive> detail_common_iarchive;
    friend class boost::archive::detail::interface_iarchive<ptree_iarchive>;
    friend class boost::archive::load_access;

    const boost::property_tree::ptree &m_pt;
    const boost::property_tree::ptree *m_cur_pt;
    boost::property_tree::ptree::const_assoc_iterator m_item_assoc_it, m_it_nf;
      //    boost::property_tree::ptree::const_iterator m_item_std_it;

    void init();
    void read_attribute(const char *attribute_name, const char *alt_attribute_name, int &t);
    void read_attribute(const char *attribute_name, std::string &val);

      // Anything not an attribute and not a name-value pair is an
      // error and should be trapped here.
    template<class T>
    void load_override(T & t OVERRIDE_OLD_PARAM_TYPE)
      {
          // If your program fails to compile here, its most likely due to
          // not specifying an nvp wrapper around the variable to
          // be serialized.
        BOOST_MPL_ASSERT((boost::serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t OVERRIDE_OLD_PARAM_PASS);
      }

      // special treatment for name-value pairs.
    template<class T>
    void load_override(
      const ::boost::serialization::nvp< T > & t OVERRIDE_OLD_PARAM_TYPE
                       ){
      std::string tname((t.name() == 0 || t.name()[0] == 0) ? boost_internal_item : t.name());
      if(tname == boost_internal_count)
      {
          // count boost_internal_item children or item entries
        m_item_assoc_it = m_cur_pt->find(boost_internal_item);
        m_it_nf = m_cur_pt->not_found();
        if(m_item_assoc_it == m_it_nf)
        {
          setInt<T>(t.value(), 0);
          return;
        }
          // else
          // is it ptree-json array?
        if(!m_item_assoc_it->second.empty() && m_item_assoc_it->second.begin()->first == "")
        {
          // it it is ptree-json array - simple children count
          setInt<T>(t.value(), m_item_assoc_it->second.size());
          m_item_assoc_it = m_item_assoc_it->second.find("");
          m_it_nf = m_item_assoc_it->second.not_found();
          return;
        }
          // else
        // it is lot of 'item' entries
        setInt<T>(t.value(), m_cur_pt->count(boost_internal_item));
        return;
      }
        // else
      if(tname == boost_internal_item && m_item_assoc_it != m_it_nf)
      {
        // if(m_item_assoc_it == m_it_nf)
        // {
        //   std::cout << "Single item - not a collection!" << std::endl;
        //   m_item_assoc_it = m_cur_pt->find(boost_internal_item);
        //   m_it_nf = m_cur_pt->not_found();
        //   if(m_item_assoc_it == m_it_nf)
        //   {
        //     throw std::logic_error("Asked for 'item', but can not find it!");
        //     return;
        //   }
        // }

          // it is array
        const boost::property_tree::ptree *save_cur_pt = m_cur_pt;
        m_cur_pt = &m_item_assoc_it->second;
        boost::property_tree::ptree::const_assoc_iterator save_item_it = m_cur_pt->not_found();
        boost::property_tree::ptree::const_assoc_iterator save_it_nf = m_cur_pt->not_found();
        std::swap(save_item_it, m_item_assoc_it);
        std::swap(save_it_nf  , m_it_nf        );
        this->detail_common_iarchive::load_override(t.value() OVERRIDE_OLD_PARAM_PASS);
        std::swap(save_item_it, m_item_assoc_it);
        std::swap(save_it_nf, m_it_nf);
        m_item_assoc_it++;
        m_cur_pt = save_cur_pt;
        return;
      }

      // normal entry
      boost::property_tree::ptree::const_assoc_iterator it = m_cur_pt->find(tname);
      if(it == m_cur_pt->not_found())
      {
        if(tname == boost_internal_item_version)
        {
          setInt<T>(t.value(), 0);
          return;
        }
        throw std::logic_error("Asked for not-existing std item '" + tname + "'!");
      }

      boost::property_tree::ptree::const_assoc_iterator save_item_it = m_cur_pt->not_found();
      boost::property_tree::ptree::const_assoc_iterator save_it_nf = m_cur_pt->not_found();
      std::swap(save_item_it, m_item_assoc_it);
      std::swap(save_it_nf  , m_it_nf        );
      const boost::property_tree::ptree *save_cur_pt = m_cur_pt;
      m_cur_pt = &it->second;
      this->detail_common_iarchive::load_override(t.value() OVERRIDE_OLD_PARAM_PASS);
      std::swap(save_item_it, m_item_assoc_it);
      std::swap(save_it_nf, m_it_nf);
      m_cur_pt = save_cur_pt;
    }

      // specific overrides for attributes - not name value pairs so we
      // want to trap them before the above "fall through"
    void load_override(boost::archive::class_id_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void load_override(boost::archive::class_id_optional_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
      //  void load_override(boost::archive::class_id_reference_type & t);
    void load_override(boost::archive::object_id_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
      //    void load_override(boost::archive::object_reference_type & t);
    void load_override(boost::archive::version_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void load_override(boost::archive::class_name_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);
    void load_override(boost::archive::tracking_type & t OVERRIDE_OLD_PARAM_TYPE_EMPTY);

  public:
    ptree_iarchive(const boost::property_tree::ptree &pt, unsigned int flags = 0);
    ~ptree_iarchive();

    template<class T>
    void load(T & t) {
      t = m_cur_pt->get_value<T>();
    }

    void load_binary(void *address, std::size_t count);
  };

}

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(bpta::ptree_iarchive)

#endif // __PTREE_IARCHIVE_HH__
