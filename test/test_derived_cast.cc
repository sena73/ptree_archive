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

#include <stdexcept>
#include "extended_info.hh"
#include "extended_info2.hh"
#include "test_derived_cast.hh"

boost::shared_ptr<InfoBase> createExtendedInfo ()
{
  return boost::shared_ptr<InfoBase>(new ExtendedInfo(3, 3.3, "3.3.3", "e333"));
}

boost::shared_ptr<InfoBase> createExtendedInfo2()
{
  return boost::shared_ptr<InfoBase>(new ExtendedInfo2(2, 2.2, "2.2.2", "e222"));
}


void checkExtendedInfoCast (boost::shared_ptr<InfoBase> ptr)
{
  if(0 == boost::dynamic_pointer_cast<ExtendedInfo>(ptr))
  {
    throw std::runtime_error("Failed to cast InfoBase* to ExtendedInfo*");
  }
}

void checkExtendedInfo2Cast(boost::shared_ptr<InfoBase> ptr)
{
  if(0 == boost::dynamic_pointer_cast<ExtendedInfo2>(ptr))
  {
    throw std::runtime_error("Failed to cast InfoBase* to ExtendedInfo2*");
  }
}
