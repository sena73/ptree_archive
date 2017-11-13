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

#ifndef __CREATE_EXTENDED_HH__
#define __CREATE_EXTENDED_HH__

#include <boost/shared_ptr.hpp>

extern boost::shared_ptr<InfoBase> createExtendedInfo ();
extern boost::shared_ptr<InfoBase> createExtendedInfo2();
extern void checkExtendedInfoCast (boost::shared_ptr<InfoBase> ptr1);
extern void checkExtendedInfo2Cast(boost::shared_ptr<InfoBase> ptr2);

#endif
