#pragma once
#include <iostream>
#include <string>
#include <vector>
class binary_tree_exception {
private:
	std::string exception;
public:
	binary_tree_exception(std::string message) : exception(message) {}
};
class BinaryTree {
private:
	struct TreeNode {
		int info;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : left(nullptr), right(nullptr), info(0) {

		}
	};
	TreeNode* root;
public:
	BinaryTree() {
		root = nullptr;
	}
	BinaryTree(const BinaryTree& tree) : BinaryTree() {
		root = copyTree(tree.root);
	}
	TreeNode* copyTree(const TreeNode* root) {
		if (!root) {
			return nullptr;
		}
		TreeNode* rootCopy = new TreeNode();
		rootCopy->info = root->info;
		try {
			rootCopy->left = copyTree(root->left);
			rootCopy->right = copyTree(root->right);
		}
		catch (std::bad_alloc) {
			clear(rootCopy);
			throw binary_tree_exception("Error:copy tree");
		}
	}
	BinaryTree(BinaryTree&& tree) {
		this->root = tree.root;
		tree.root = nullptr;
	}
	~BinaryTree() {
		clear(root);
		delete root;
	}
	void clear(TreeNode*& root) {
		clearElems(this->root);
		this->root = nullptr;
	}
	void clearElems(TreeNode* root) {
		if (!root) return;
		clearElems(root->left);
		clearElems(root->right);
		delete root;
	}
	BinaryTree& operator= (const BinaryTree& tree) {
		if (this == &tree) return *this;
		this->root = copyTree(tree.root);
		return *this;
	}
	BinaryTree& operator= (BinaryTree&& tree) {
		if (this == &tree) return *this;
		this->root = tree.root;
		tree.root = nullptr;
		return *this;
	}
	void put(int x, std::vector<int> arr) {
		TreeNode** temp_root = &root;
		for (int i : arr) {
			if (!*temp_root) {
				throw binary_tree_exception("Error:put\n");
			}
			if (i == 0) {
				temp_root = &(*temp_root)->left;
			}
			else if (i == 1) {
				temp_root = &(*temp_root)->right;
			}
			else {
				throw binary_tree_exception("Error:put\n");
			}
		}
		if (*temp_root) {
			(*temp_root)->info = x;
		}
		else {
			(*temp_root) = new TreeNode();
			(*temp_root)->info = x;
		}
	}
	int numberOfEvenElements(TreeNode* root) {
		if (!root) {
			return 0;
		}
		return root->info % 2 == 0 + numberOfEvenElements(root->left) + numberOfEvenElements(root->left);
	}
	int numberOfElements(TreeNode* root) {
		if (!root) {
			return 0;
		}
		return 1 + numberOfElements(root->left) + numberOfElements(root->left);
	}
	bool isPositive(TreeNode* root) {
		if (!root) {
			return true;
		}
		return root->info >= 0 && isPositive(root->left) && isPositive(root->right);
	}
	void deleteLeaves() {
		clearLeaves(this->root);
	}
	void clearLeaves(TreeNode*& root) {
		if (!root) {
			return;
		}
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			root = nullptr;
		}
		else {
			clearLeaves(root->left);
			clearLeaves(root->right);
		}
	}
	int getSum(TreeNode* root) {
		if (!root) {
			return 0;
		}
		return root->info + getSum(root->left) + getSum(root->right);
	}
	double getAverage() {
		return getSum(this->root) * 1.0 / numberOfElements(this->root);
	}
	std::vector<int> find(int x) {
		TreeNode* root = this->root;
		if (!root) {
			throw binary_tree_exception("Error:find\n");
		}
		std::vector<int> temp;
		while (root) {
			if (root->info == x) {
				return temp;
			}
			else if (inTree(x, root->left)) {
				root = root->left;
				temp.push_back(0);
			}
			else if (inTree(x, root->right)) {
				root = root->right;
				temp.push_back(1);
			}
			else {
				throw binary_tree_exception("Error:find\n");
			}
		}
	}
	bool inTree(int x, TreeNode* root) {
		if (!root) {
			return false;
		}
		if (root->info == x) {
			return true;
		}
		else {
			return inTree(x, root->left) + inTree(x, root->right);
		}
	}
	bool isBinaryTree(TreeNode* root) {
		if (!root) {
			return true;
		}
		return (root->left == nullptr || root->info > root->left->info)
			&& (root->right == nullptr || root->info < root->right->info)
			&& isBinaryTree(root->left)
			&& isBinaryTree(root->right);
	}
	std::string toString(TreeNode* root) {
		if (!root) {
			return "";
		}
		return toString(root->left) + " " + std::to_string(root->info) + " " + toString(root->right);
	}
	std::string toLevelString(TreeNode* root, int tab) {
		if (!root) {
			return "";
		}
		std::string temp;
		for (int i = 0; i < tab; ++i) {
			temp += " ";
		}
		return temp + std::to_string(root->info) + "\n"
			+ toLevelString(root->left, tab + 1)
			+ toLevelString(root->right, tab + 1);
	}
	TreeNode* getRoot() {
		return this->root;
	}
};
