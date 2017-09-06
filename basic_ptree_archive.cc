#include "basic_ptree_archive.hh"

namespace bpta {

  const char *ptree_archive_object_id          = "__oid" ;
  const char *ptree_archive_object_reference   = "__oidr";
  const char *ptree_archive_class_id           = "__cid" ;
  const char *ptree_archive_class_id_reference = "__cidr";
  const char *ptree_archive_class_name         = "__cn"  ;
  const char *ptree_archive_tracking           = "__tl"  ;
  const char *ptree_archive_version            = "__ver" ;
  const char *ptree_archive_signature          = "__sgn" ;

    // internal boost::serialization names
  const char *boost_internal_count             = "count";
  const char *boost_internal_item              = "item";
  const char *boost_internal_item_version      = "item_version";
  const char *boost_internal_px                = "px";
}
