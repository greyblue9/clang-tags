#pragma once

#include "storage.hxx"
#include "clangTags/index.hxx"
#include <boost/thread/thread.hpp>

namespace ClangTags {
class Watch {
public:
  Watch (Storage & storage, Cache & cache);
  ~Watch ();

  void update ();

  // Required for the callable concept
  void operator() ();

private:
  void addWatchDescriptor (const std::string & fileName, int wd);
  std::string fileName (int wd);

  Storage & storage_;
  Index index_;
  int fd_inotify_;
  int fd_update_[2];
  std::map<std::string, int> wd_;
  std::map<int, std::string> file_;
  boost::mutex mtx_;
};
}