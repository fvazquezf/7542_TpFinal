#ifndef MATCH_H_
#define MATCH_H_
#include <unordered_map>

class Match {
 public:
  Match();
  //void addUser(const std::string &nickname, User* user);
  void removeUser(const std::string &nickname);
  void removeUsers();
  ~Match();
 private:
    //std::unordered_map<std::string, User*> users;
};

#endif
