/* Copyright (C) 2017 Sergey Spiridonov <sena@s73.work>
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

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
