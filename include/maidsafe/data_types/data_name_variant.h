/***************************************************************************************************
 *  Copyright 2012 maidsafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use. The use of this code is governed by the licence file licence.txt found in the root of     *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit written *
 *  permission of the board of directors of MaidSafe.net.                                          *
 **************************************************************************************************/

#ifndef MAIDSAFE_DATA_TYPES_DATA_NAME_VARIANT_H_
#define MAIDSAFE_DATA_TYPES_DATA_NAME_VARIANT_H_

#include <utility>

#include "boost/variant/static_visitor.hpp"
#include "boost/variant/variant.hpp"

#include "maidsafe/common/tagged_value.h"
#include "maidsafe/common/types.h"
#include "maidsafe/passport/types.h"

#include "maidsafe/data_types/immutable_data.h"
#include "maidsafe/data_types/mutable_data.h"
#include "maidsafe/data_types/detail/data_type_values.h"


namespace maidsafe {

typedef boost::variant<passport::PublicAnmid::name_type,
                       passport::PublicAnsmid::name_type,
                       passport::PublicAntmid::name_type,
                       passport::PublicAnmaid::name_type,
                       passport::PublicMaid::name_type,
                       passport::PublicPmid::name_type,
                       passport::Mid::name_type,
                       passport::Smid::name_type,
                       passport::Tmid::name_type,
                       passport::PublicAnmpid::name_type,
                       passport::PublicMpid::name_type,
                       ImmutableData::name_type,
                       MutableData::name_type> DataNameVariant;


namespace detail {

struct GetTagValue : public boost::static_visitor<DataTagValue> {
  template<typename T, typename Tag>
  result_type operator()(const TaggedValue<T, Tag>&) const {
    return TaggedValue<T, Tag>::tag_type::kEnumValue;
  }
};

struct GetIdentity : public boost::static_visitor<Identity> {
  template<typename T, typename Tag>
  result_type operator()(const TaggedValue<T, Tag>& t) const {
    return t.data;
  }
};

struct GetTagValueAndIdentity : public boost::static_visitor<std::pair<DataTagValue, Identity>> {
  template<typename T, typename Tag>
  result_type operator()(const TaggedValue<T, Tag>& t) const {
    return std::make_pair(TaggedValue<T, Tag>::tag_type::kEnumValue, t.data);
  }
};

}  // namespace detail

}  // namespace maidsafe

#endif  // MAIDSAFE_DATA_TYPES_DATA_NAME_VARIANT_H_