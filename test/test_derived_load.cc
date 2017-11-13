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

#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

#ifdef TEXT_ARCHIVE
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif // TEXT_ARCHIVE

#include "ptree_oarchive.hh"
#include "ptree_iarchive.hh"


#include "infobase.hh"
#include "test_derived_cast.hh"

int main(int argc, char** argv)
{


#ifdef TEXT_ARCHIVE
    // load from text file
  {
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::filesystem::ifstream intextstream("test_output.txt");
    boost::archive::text_iarchive tar(intextstream);

      // load the data
    tar & BOOST_SERIALIZATION_NVP(baseptr1);
    tar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }
#endif

    // load from file->json->ptree
  {
    boost::shared_ptr<InfoBase> baseptr1, baseptr2;
    boost::property_tree::ptree pt;
    boost::filesystem::ifstream injsonstream("test_output.json");
    read_json(injsonstream, pt);
    write_json(std::cout, pt);
    bpta::ptree_iarchive jar(pt);

      // load the data
    jar & BOOST_SERIALIZATION_NVP(baseptr1);
    jar & BOOST_SERIALIZATION_NVP(baseptr2);

    checkExtendedInfoCast(baseptr1);
    checkExtendedInfo2Cast(baseptr2);
  }

  return 0;
}
