// fundamental and interesting problem. DFS or BFS
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<int, Node*> built;
        Node* res;
        if (node == NULL)
            return res;
        
        res = new Node(node->val, node->neighbors);
        built.emplace(node->val, res);

        DFS_build(res, built);
        return res;
    }

    void DFS_build(Node* source, unordered_map<int, Node*>& built){
        for (Node*& nodePt : source->neighbors){  // Note use reference as we need to modify the origial value
            if (built.find(nodePt->val) == built.end()){
                nodePt = new Node(nodePt->val, nodePt->neighbors);
                built.emplace(nodePt->val, nodePt);
                DFS_build(nodePt, built);
            }
            else
                nodePt = built[nodePt->val];
        }
    }
};
