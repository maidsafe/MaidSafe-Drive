/*  Copyright 2013 MaidSafe.net limited

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

#ifndef MAIDSAFE_DRIVE_DIRECTORY_H_
#define MAIDSAFE_DRIVE_DIRECTORY_H_

#include <string>
#include <vector>

#include "boost/filesystem/path.hpp"

#include "maidsafe/common/config.h"
#include "maidsafe/common/tagged_value.h"
#include "maidsafe/common/types.h"

#include "maidsafe/drive/config.h"
#include "maidsafe/drive/file_context.h"

namespace maidsafe {

namespace drive {

namespace detail {

class Directory;
struct MetaData;
struct ParentIdTag;

namespace test {

void DirectoriesMatch(const Directory& lhs, const Directory& rhs);
class DirectoryTest;

}  // namespace test

class Directory {
 public:
  typedef TaggedValue<Identity, ParentIdTag> ParentId;
  Directory();
  Directory(ParentId parent_id, DirectoryId directory_id);
  Directory(Directory&& other);
  Directory& operator=(Directory other);
  ~Directory() {}

  Directory(ParentId parent_id, const std::string& serialised_directory);
  std::string Serialise() const;

  bool HasChild(const boost::filesystem::path& name) const;
  void GetChild(const boost::filesystem::path& name, MetaData& meta_data) const;
  bool GetChildAndIncrementItr(MetaData& meta_data);
  void AddChild(const MetaData& child);
  void RemoveChild(const MetaData& child);
  void UpdateChild(const MetaData& child);
  void ResetChildrenIterator() { children_itr_position_ = 0; }
  bool empty() const;
  DirectoryId directory_id() const { return directory_id_; }


  friend void swap(Directory& lhs, Directory& rhs) MAIDSAFE_NOEXCEPT;
  friend void test::DirectoriesMatch(const Directory& lhs, const Directory& rhs);
  friend class test::DirectoryTest;

 private:
  ParentId parent_id_;
  DirectoryId directory_id_;
  MaxVersions max_versions_;
  std::vector<FileContext> children_;
  size_t children_itr_position_;
};

bool operator<(const Directory& lhs, const Directory& rhs);

}  // namespace detail

}  // namespace drive

}  // namespace maidsafe

#endif  // MAIDSAFE_DRIVE_DIRECTORY_H_
