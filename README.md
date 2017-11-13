# ptree_archive
Archive for boost::serialization which is able to serialize to the
boost::property_tree. Use it as any other boost archive, except for you
should use boost::property_tree::ptree instead of the iostream.

Serialization to property_tree is done in a way suitable for json
(de)serialization. Just call read/write_json() for the ptree.

You can find some examples in test directory.
