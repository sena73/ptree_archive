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

#ifndef __BASIC_PTREE_ARCHIVE_HH__
#define __BASIC_PTREE_ARCHIVE_HH__

#include <boost/version.hpp>

#if BOOST_VERSION <= 105800
 #define OVERRIDE_OLD_PARAM_TYPE_EMPTY , int
 #define OVERRIDE_OLD_PARAM_TYPE , int override_old_param
 #define OVERRIDE_OLD_PARAM_PASS , override_old_param
// #define OVERRIDE_OLD_PARAM_PASS0 , 0
#else
 #define OVERRIDE_OLD_PARAM_TYPE_EMPTY
 #define OVERRIDE_OLD_PARAM_TYPE
 #define OVERRIDE_OLD_PARAM_PASS
 #define OVERRIDE_OLD_PARAM_PASS0
#endif


namespace bpta {
// constant strings used in ptree i/o

  extern const char *ptree_archive_object_id;
  extern const char *ptree_archive_object_reference;
  extern const char *ptree_archive_class_id;
  extern const char *ptree_archive_class_id_reference;
  extern const char *ptree_archive_class_name;
  extern const char *ptree_archive_tracking;
  extern const char *ptree_archive_version;
  extern const char *ptree_archive_signature;

    // internal boost::serialization names
  extern const char *boost_internal_count;
  extern const char *boost_internal_item;
  extern const char *boost_internal_item_version;
  extern const char *boost_internal_px;
}

#endif // __BASIC_PTREE_ARCHIVE_HH__
