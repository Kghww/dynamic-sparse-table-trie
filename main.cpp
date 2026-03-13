#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Node {
    Node** children;
    int key;
};

struct Info {
    int cases;
    int min, max;
    int n, k;
};

void Insert(Node* node, const int value, const Info& info, int remapped = -1) {
    Node* current = node;
    int current_depth = 0;
    int current_remapped = (remapped == -1) ? value : remapped;

    while (true) {
        if (current->key == -1) {
            current->key = value;
            return;
        }

        if (current->key == value) {
            printf("%d exist\n", value);
            return;
        }

        int child_count = (current_depth == 0) ? info.n : info.k;
        int index = current_remapped % child_count;
        int next_remap = current_remapped / child_count;

        if (current->children == nullptr) {
            current->children = new Node * [child_count]();
        }

        if (current->children[index] == nullptr) {
            current->children[index] = new Node;
            current->children[index]->key = -1;
            current->children[index]->children = nullptr;
        }

        current = current->children[index];
        current_remapped = next_remap;
        current_depth++;
    }
}

void Look(Node* node, const int value, const Info& info, int depth = 0, int remapped = -1) {
    if (remapped == -1)
        remapped = value;

    if (node->key == value) {
        printf("%d exist\n", value);
        return;
    }

    if (node->children == nullptr) {
        printf("%d not exist\n", value);
        return;
    }

    int child_count = (depth == 0) ? info.n : info.k;
    int index = remapped % child_count;
    int next_remap = remapped / child_count;

    if (node->children[index] != nullptr) {
        Look(node->children[index], value, info, depth + 1, next_remap);
    }
    else {
        printf("%d not exist\n", value);
        return;
    }

}

int FindLeafLeftmost(Node* node, const Info& info, const int depth) {
    bool isRootLevel = (depth == 0);

    int index = -1;
    Node* parent = nullptr;
    Node* current = node;

    while (current->children != nullptr) {
        bool found = false;
        int child_count_here = (isRootLevel) ? info.n : info.k;
        for (int i = 0; i < child_count_here; i++) {
            if (current->children[i] != nullptr) {
                parent = current;
                index = i;
                current = current->children[i];
                found = true;
                if (isRootLevel) {
                    isRootLevel = false;
                }
                break;
            }
        }
        if (!found) {
            break;
        }
    }

    int newKey = current->key;
    if (parent != nullptr) {
        parent->children[index] = nullptr;
        delete current;
    }
    else {
        node->key = -1;
    }
    return newKey;
}

void Delete(Node* root, const int value, const Info& info) {
    Node* current = root;
    Node* parent = nullptr;
    int index_in_parent = -1;
    int depth = 0;
    int remapped = value;

    while (current->key != value) {
        if (current->children == nullptr) {
            printf("%d not exist\n", value);
            return;
        }

        int child_count = (depth == 0) ? info.n : info.k;
        int index = remapped % child_count;
        remapped = remapped / child_count;

        if (current->children[index] == nullptr) {
            printf("%d not exist\n", value);
            return;
        }

        parent = current;
        current = current->children[index];
        index_in_parent = index;
        depth++;
    }

    bool isLeaf = true;
    if (current->children != nullptr) {
        int child_count = (depth == 0) ? info.n : info.k;
        for (int i = 0; i < child_count; i++) {
            if (current->children[i] != nullptr) {
                isLeaf = false;
                break;
            }
        }
    }

    if (isLeaf) {
        if (parent == nullptr) {
            current->key = -1;
        }
        else {
            parent->children[index_in_parent] = nullptr;
            delete current;
        }
    }
    else {
        int newKey = FindLeafLeftmost(current, info, depth);
        current->key = newKey;
    }
}

void Print(Node* node, int n, int k) {
    int value = node->key;
    if (value != -1) {
        printf("%d ", value);
    }

    if (node->children == nullptr) {
        return;
    }

    for (int i = 0; i < n; i++) {
        if (node->children[i] != nullptr) {
            Print(node->children[i], k, k);
        }
    }
}

int main() {
    Info info;
    int c, min, max, n, k;
    scanf("%d %d %d %d %d", &c, &min, &max, &n, &k);
    info.cases = c;
    info.min = min;
    info.max = max;
    info.n = n;
    info.k = k;

    Node* root = new Node;
    root->children = nullptr;
    root->key = -1;

    char op;
    int value;
    while (c--) {
        scanf(" %c", &op);
        switch (op) {
        case 'I':
            scanf("%d", &value);
            Insert(root, value, info);
            break;
        case 'L':
            scanf("%d", &value);
            Look(root, value, info);
            break;
        case 'D':
            scanf("%d", &value);
            Delete(root, value, info);
            break;
        case 'P':
            Print(root, info.n, info.k);
            printf("\n");
            break;
        }
    }
    return 0;
}