/*  Copyright 2014 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_VAULT_MANAGER_VAULT_CONFIG_H_
#define MAIDSAFE_VAULT_MANAGER_VAULT_CONFIG_H_

#include "boost/filesystem/path.hpp"

#include "maidsafe/common/types.h"
#include "maidsafe/passport/types.h"

#include "maidsafe/routing/bootstrap_file_operations.h"

namespace maidsafe {

namespace vault_manager {

struct VaultConfig {
  VaultConfig(const passport::Pmid& pmid_in,
              const boost::filesystem::path& chunkstore_path_in,
              const DiskUsage& max_disk_usage_in,
              routing::BootstrapContacts bootstrap_contacts_in);
  VaultConfig(const VaultConfig&);
  VaultConfig(VaultConfig&& other);
  VaultConfig& operator=(VaultConfig other);

  passport::Pmid pmid;
  boost::filesystem::path chunkstore_path;
  DiskUsage max_disk_usage;
#ifdef TESTING
  enum class TestType : int32_t {
    kNone,
    kKillConnection,
    kSendInvalidMessage,
    kStopProcess };

  struct TestConfig {
    TestConfig()
        : test_type(TestType::kNone),
          public_pmid_list()
//          keys_path (),
//          identity_index(-1)
    {}
    TestType test_type;
    std::vector<passport::PublicPmid> public_pmid_list;
//    boost::filesystem::path keys_path;
//    int identity_index;
  } test_config;
#endif

  routing::BootstrapContacts bootstrap_contacts;
};

void swap(VaultConfig& lhs, VaultConfig& rhs);


#ifdef TESTING
passport::Pmid GetPmidFromKeysFile(const boost::filesystem::path keys_path, size_t identity_index);

std::vector<passport::PublicPmid> GetPublicPmidsFromKeysFile(
    const boost::filesystem::path keys_path);
#endif

}  // namespace vault_manager

}  // namespace maidsafe

#endif  // MAIDSAFE_VAULT_MANAGER_VAULT_CONFIG_H_
