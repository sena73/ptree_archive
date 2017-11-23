/* Copyright (C) 2017 Sergey Spiridonov <sena@s73.work>
 *
 * This file is part of bpta (ptree_archive) library.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file COPYING
 */

#ifndef __CREATE_EXTENDED_HH__
#define __CREATE_EXTENDED_HH__

#include <boost/shared_ptr.hpp>

extern boost::shared_ptr<InfoBase> createExtendedInfo ();
extern boost::shared_ptr<InfoBase> createExtendedInfo2();
extern void checkExtendedInfoCast (boost::shared_ptr<InfoBase> ptr1);
extern void checkExtendedInfo2Cast(boost::shared_ptr<InfoBase> ptr2);

#endif
