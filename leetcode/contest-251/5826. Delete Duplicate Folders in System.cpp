#include <bits/stdc++.h>
using namespace std;
class Solution {
   private:
    typedef map<vector<pair<string, int>>, int> hash_store;

    struct TreeNode {
        string name;
        map<string, TreeNode *> children;
        int hash_value;

        TreeNode(string _name) : name(_name) {}

        ~TreeNode() {
            for (auto kv : children) {
                TreeNode *child = kv.second;
                delete child;
            }
        }

        void insert(vector<string> &paths, int idx = 0) {
            if (idx == paths.size()) return;

            if (!children.count(paths[idx])) {
                children[paths[idx]] = new TreeNode(paths[idx]);
            }

            children[paths[idx]]->insert(paths, idx + 1);
        }

        void refresh_hash(hash_store &H, unordered_map<int, int> &counter) {
            vector<pair<string, int>> V;

            for (auto kv : children) {
                string child_name = kv.first;
                TreeNode *child = kv.second;
                child->refresh_hash(H, counter);
                V.push_back({child_name, child->hash_value});
            }

            if (!H.count(V)) {
                H[V] = H.size();
            }

            hash_value = H[V];
            counter[hash_value]++;
        }

        void delete_duplicates(unordered_map<int, int> &hash_counter) {
            for (auto &kv : children) {
                TreeNode *child = kv.second;

                if (child->children.empty()) {
                    continue;
                }

                if (hash_counter[child->hash_value] > 1) {
                    kv.second = NULL;
                    delete child;
                } else {
                    child->delete_duplicates(hash_counter);
                }
            }
        }

        void all_paths(vector<string> &path, vector<vector<string>> &paths) {
            if (!path.empty()) {
                paths.push_back(path);
            }

            for (auto &kv : children) {
                string child_name = kv.first;
                TreeNode *child = kv.second;
                if (child == NULL) continue;

                path.push_back(child->name);
                child->all_paths(path, paths);
                path.pop_back();
            }
        }

        vector<vector<string>> all_paths() {
            vector<vector<string>> paths;
            vector<string> curr_path;
            all_paths(curr_path, paths);
            return paths;
        }
    };

   public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &paths) {
        TreeNode *root = new TreeNode("/");

        for (vector<string> path : paths) {
            root->insert(path);
        }

        hash_store H;
        unordered_map<int, int> counter;
        root->refresh_hash(H, counter);
        root->delete_duplicates(counter);
        vector<vector<string>> res_paths = root->all_paths();
        delete root;

        return res_paths;
    }
};
