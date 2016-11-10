//
//  user_node.cpp
//  Insight Code Challenge
//
//  Class implementation for User Node.  Connections are
//  check by a breadth first search up to 4 nodes away from
//  the originating node.
//

#include "user_node.h"
#include <queue>
#include <iostream>

bool User_Node::addAdjUser(User_Node* u) {
    bool result = false;
    if (_adj_users.count(u) == 0) {
        _adj_users.insert(u);
        result = true;
    }
    return result;    
}

bool User_Node::hasConnection(User_Node* u) {
    if (_adj_users.count(u) == 0) return false;
    return true;
}

int User_Node::verifyUser(int user) {
    // initialize function variables
    std::set<User_Node*> visited;
    std::queue<std::pair<User_Node*, int> > q;
    User_Node* to_user = (*_users)[user];
    int lvl_found = 0;
    
    // Add all first degree users
    std::set<User_Node*>::iterator it;
    for (it = _adj_users.begin(); it != _adj_users.end(); it++) {
      std::pair<User_Node*, int> p(*it, 1);
      q.push(p);
      visited.insert(*it);
    }
    
    // BFS to find up to 4th degree match
    while (!q.empty()) {
      std::pair<User_Node*, int> p = q.front();
      q.pop();

      // check if match
      if (p.first == to_user) {
        lvl_found = p.second;
        break;
      } 

      // If still searching for match
      if (p.second < MAX_DEGREE) {
        // add all of users 1 degree connections if not already visited
        for (it = (p.first)->_adj_users.begin(); it != (p.first)->_adj_users.end(); it++) {
           if (visited.count(*it) == 0) {
             std::pair<User_Node*, int> p_new(*it, p.second+1);
             q.push(p_new);
             visited.insert(*it);
           }
        }
      }          
    }
    return lvl_found;
}


