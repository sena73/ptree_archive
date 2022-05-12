# ptree_archive

Moded to https://gitlab.com/sena73/ptree_archive

Archive for boost::serialization which is able to serialize to the
boost::property_tree and allows forward (upward) compatibility. Use it as any other boost archive, except for you
should use boost::property_tree::ptree instead of iostream.

Serialization to property_tree is done in a way suitable for json
serialization. Just call write_json() for the resulting ptree.
