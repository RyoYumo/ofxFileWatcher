#ifndef OFX_FILE_WATCHER_H_
#define OFX_FILE_WATCHER_H_

#include "ofMain.h"
namespace ofx {
template<typename T>
class FileWatcher : public T {
public:
  template<typename... Args>
  void load(Args&&... args){
    ofAddListener(ofEvents().update, this, &FileWatcher::watch);
    setTargetFiles(args...);
    T::load(std::forward<Args>(args)...);
  }

  ofEvent<void>& getFileChangeEvent(){ return file_change_event_; }
  const std::vector<std::string> getTargetFiles() {
    std::vector<std::string> ret;
    for(const auto& f : time_stamp_map_) {
        ret.push_back(f.first);
    }
    return ret;
}


private:
  template<typename Head, typename... Tails>
  void setTargetFiles(Head&& head, Tails&&... tails){
    std::string file_name = head;
    if(!file_name.empty()) {
      ofFile file {file_name};
      time_stamp_map_[file_name] = std::filesystem::last_write_time(file);
    }
    setTargetFiles(tails...);
  }
  void setTargetFiles(){}


void watch(ofEventArgs&){
    if ( ofGetFrameNum() % 100 == 1 ) {
      auto is_changed = [](const auto& last_time_stamp){
        ofFile file {last_time_stamp.first};
        auto   time_stamp = std::filesystem::last_write_time(file);
        return time_stamp != last_time_stamp.second ? true : false;
      };
      auto is_any_file_changed = std::any_of(time_stamp_map_.begin(), time_stamp_map_.end(), is_changed);
      if(is_any_file_changed){
        ofNotifyEvent(file_change_event_);
      }
    }
  }
  std::unordered_map<std::string, std::time_t> time_stamp_map_;
  ofEvent<void> file_change_event_;
};
} // namespace ofx

template<typename T>
using ofxFileWatcher = ofx::FileWatcher<T>;

#endif // OFX_FILE_WATCHER_H_
