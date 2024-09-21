//Link list Node
#include<bits/stdc++.h>
using namespace std;


struct Node {
    int data;
    Node *next;
    Node *random;

    Node(int x) {
        data = x;
        next = NULL;
        random = NULL;
    }
};


// Brute force Approach ---- 
// Time Complexity: O(2N) where N is the number of nodes in the linked list.
// The linked list is traversed twice, once for creating copies of each node 
//and for the second time to set the next and random pointers for each copied node.
// The time to access the nodes in the map is O(1) due to hashing.

// Space Complexity : O(N)+O(N)where N is the number of nodes in the linked list
// as all nodes are stored in the map to maintain mappings and the copied linked lists takes O(N) space as well.

class Solution {
  public:
    Node *copyList(Node *head) {
        // Write your code here
        Node* temp = head;
        unordered_map<Node*, Node*> mp;
        while(temp != NULL)
        {
            Node* newNode = new Node(temp->data);
            mp[temp] = newNode;
            temp = temp->next;
        }
        temp = head;
        while(temp != NULL)
        {
            Node* copyNode = mp[temp];
            copyNode->next = mp[temp->next];
            copyNode->random = mp[temp->random];
            temp = temp->next;
        }
        return mp[head];
    }
};


// Optimal Approach
// Time Complexity: O(3N)where N is the number of nodes in the linked list. The algorithm makes three traversals of the linked list,
// once to create copies and insert them between original nodes, then to set the random pointers
// of the copied nodes to their appropriate copied nodes and then to separate the copied and original nodes.

//Space Complexity : O(N) where N is the number of nodes in the linked list as the only extra additional space allocated it
// to create the copied list without creating any other additional data structures.
 
void insertCopyNode(Node* head)
{
    Node* temp = head;
    while(temp != NULL)
    {
        Node* copyNode = new Node(temp->data);
        copyNode->next = temp->next;
        temp->next = copyNode;
        temp = temp->next->next;
    }
}

void connectRandom(Node* head)
{
    Node* temp = head;
    
    while(temp != NULL)
    {
        Node* copyNode = temp->next;
        if(temp->random)
        {
            copyNode->random = temp->random->next;
        }
        else
        {
            copyNode->random = NULL;
        }
        temp = temp->next->next;
    }
}

Node* getDeepCopy(Node* head)
{
    Node* dummy = new Node(-1);
    Node* res = dummy;
    Node* temp = head;
    while(temp != NULL)
    {
        res->next = temp->next;
        res = res->next;
        
        temp->next = temp->next->next;
        temp = temp->next;
    }
    return dummy->next;
}
class Solution {
  public:
    Node *copyList(Node *head) {
        // Write your code here
        insertCopyNode(head);
        connectRandom(head);
        return getDeepCopy(head);
    }
};