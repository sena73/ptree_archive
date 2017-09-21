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

