#ifndef __BASIC_PTREE_ARCHIVE_HH__
#define __BASIC_PTREE_ARCHIVE_HH__

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

