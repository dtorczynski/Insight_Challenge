//
//  user_node.h
//  Insight Code Challenge
//
//  Class definition for a graph node. Edges are maintained
//  in an adjacent users set. Verify user will check the input
//  user id against this nodes edges.
//

#ifndef user_node_h
#define user_node_h

#include <stdio.h>
#include <map>
#include <set>

const int MAX_DEGREE = 4;

class User_Node {
public:
    User_Node(std::map<int, User_Node*>* users) : _users(users){};
    int verifyUser(int user);
    bool addAdjUser(User_Node* u);
    bool hasConnection(User_Node* u);
private:
    // Member variables
    std::map<int, User_Node*>* _users;
    std::set<User_Node*> _adj_users; 
};


#endif /* user_node_h */
