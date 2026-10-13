#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int weight;
    struct Node *left, *right;
} Node;

Node* newNode(int w) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->weight = w;
    node->left = node->right = NULL;
    return node;
}

// Merge two nodes
Node* merge(Node* a, Node* b) {
    Node* parent = newNode(a->weight + b->weight);
    parent->left = a;
    parent->right = b;
    return parent;
}

// Compute weighted depth sum
int computeCost(Node* root, int depth) {
    if (!root->left && !root->right) return root->weight * depth;
    int cost = 0;
    if (root->left) cost += computeCost(root->left, depth+1);
    if (root->right) cost += computeCost(root->right, depth+1);
    return cost;
}

int main() {
    int weights[] = {5, 2, 4, 3};
    int n = sizeof(weights)/sizeof(weights[0]);

    // Initial leaves
    Node* nodes[100];
    for (int i = 0; i < n; i++) nodes[i] = newNode(weights[i]);

    int size = n;
    while (size > 1) {
        // Find best adjacent pair to merge (greedy)
        int bestIdx = 0, bestSum = nodes[0]->weight + nodes[1]->weight;
        for (int i = 1; i < size-1; i++) {
            int sum = nodes[i]->weight + nodes[i+1]->weight;
            if (sum < bestSum) {
                bestSum = sum;
                bestIdx = i;
            }
        }
        Node* merged = merge(nodes[bestIdx], nodes[bestIdx+1]);

        // Shift array
        for (int j = bestIdx+1; j < size-1; j++) nodes[j] = nodes[j+1];
        nodes[bestIdx] = merged;
        size--;
    }

    int cost = computeCost(nodes[0], 0);
    printf("Optimal alphabetic tree cost: %d\n", cost);

    return 0;
}
