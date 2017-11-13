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

#include "basic_ptree_archive.hh"

namespace bpta {

  const char *ptree_archive_object_id          = "__oi" ;
  const char *ptree_archive_object_reference   = "__or" ;
  const char *ptree_archive_class_id           = "__ci" ;
  const char *ptree_archive_class_id_reference = "__cr" ;
  const char *ptree_archive_class_name         = "__cn" ;
  const char *ptree_archive_tracking           = "__t"  ;
  const char *ptree_archive_version            = "__v"  ;
  const char *ptree_archive_signature          = "__s"  ;

    // internal boost::serialization names
  const char *boost_internal_count             = "count";
  const char *boost_internal_item              = "item";
  const char *boost_internal_item_version      = "item_version";
  const char *boost_internal_px                = "px";
}
