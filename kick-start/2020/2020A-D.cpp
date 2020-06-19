#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int t, n, k;
string s[100005];

const int ALPHABET_SIZE = 26;
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int cnt[ALPHABET_SIZE] = {0};

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

struct TrieNode *getNode(void) {
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
        pNode->cnt[i] = 0;
    }

    return pNode;
}
void insert(struct TrieNode *root, string key) {
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        (pCrawl->cnt[index])++;
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

int solve() {
    struct TrieNode *root = getNode();
    for (int i = 0; i < n; i++)
        insert(root, s[i]);

    int ans = 0;
    queue<TrieNode *> q;
    q.push(root);
    while (!q.empty()) {
        TrieNode *cur = q.front();
        q.pop();

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (cur->children[i] != NULL) {
                q.push(cur->children[i]);
                ans += cur->cnt[i] / k;
            }
        }
    }

    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}