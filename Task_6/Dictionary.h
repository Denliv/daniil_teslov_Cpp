#pragma once
#include <iostream>
#include <string>
class dictionary_exception {
private:
	std::string exception;
public:
	dictionary_exception(std::string message) : exception(message) {}
};
class Dictionary {
private:
	struct BalTreeNode {
		std::string word;
		int frequency;
		int balance;
		BalTreeNode* left;
		BalTreeNode* right;
		BalTreeNode(std::string theWord = "",
			int theFrequency = 0,
			int theBalance = 0,
			BalTreeNode* theLeft = nullptr,
			BalTreeNode* theRight = nullptr) :
			word(theWord),
			frequency(theFrequency),
			balance(theBalance),
			left(theLeft),
			right(theRight) {}
	};
	BalTreeNode* root;
public:
	Dictionary() {
		root = nullptr;
	}
	Dictionary(const Dictionary& copyable) : Dictionary() {
		this->root = copyTree(copyable.root);
	}
	BalTreeNode* copyTree(const BalTreeNode* root) {
		if (!root) {
			return nullptr;
		}
		BalTreeNode* rootCopy = new BalTreeNode(root->word, root->frequency, root->balance);
		try {
			rootCopy->left = copyTree(root->left);
			rootCopy->right = copyTree(root->right);
		}
		catch (std::bad_alloc) {
			clear(rootCopy);
			throw dictionary_exception("Error:copy tree");
		}
		return rootCopy;
	}
	Dictionary(Dictionary&& relocable) {
		this->root = relocable.root;
		relocable.root = nullptr;
	}
	~Dictionary() {
		clear(root);
		delete root;
	}
	void clear(BalTreeNode*& root) {
		clearElems(this->root);
		this->root = nullptr;
	}
	void clearElems(BalTreeNode* root) {
		if (!root) return;
		clearElems(root->left);
		clearElems(root->right);
		delete root;
	}
	Dictionary& operator= (const Dictionary& tree) {
		if (this == &tree) return *this;
		this->root = copyTree(tree.root);
		return *this;
	}
	Dictionary& operator= (Dictionary&& tree) {
		if (this == &tree) return *this;
		this->root = tree.root;
		tree.root = nullptr;
		return *this;
	}
	bool addWord(BalTreeNode*& root, std::string word) {
		if (!root) {
			root = new BalTreeNode(word);
			root->frequency++;
			return true;
		}
		if (word < root->word) {
			if (addWord(root->left, word)) {
				return balanceInsertToLeft(root);
			}
			return false;
		}
		else if (word > root->word) {
			if (addWord(root->right, word)) {
				return balanceInsertToRight(root);
			}
			return false;
		}
		root->frequency++;
		return false;
	}
	bool balanceInsertToLeft(BalTreeNode*& root) {
		if (root->balance == 1) {
			root->balance = 0;
			return false;
		}
		else if (root->balance == 0) {
			root->balance = -1;
			return true;
		}
		else {
			if (root->left->balance < 0) {
				return RRotation(root, false);
			}
			return LRRotation(root, false);
		}
	}
	bool balanceInsertToRight(BalTreeNode*& root) {
		if (root->balance == -1) {
			root->balance = 0;
			return false;
		}
		else if (root->balance == 0) {
			root->balance = 1;
			return true;
		}
		else {
			if (root->right->balance > 0) {
				return LRotation(root, false);
			}
			return RLRotation(root, false);
		}
	}
	bool balanceDeleteToLeft(BalTreeNode*& root) {
		if (root->balance == -1) {
			root->balance = 0;
			return true;
		}
		else if (root->balance == 0) {
			root->balance = 1;
			return false;
		}
		else {
			if (root->right->balance >= 0) {
				return LRotation(root, true);
			}
			return RLRotation(root, true);
		}
	}
	bool balanceDeleteToRight(BalTreeNode*& root) {
		if (root->balance == 1) {
			root->balance = 0;
			return true;
		}
		else if (root->balance == 0) {
			root->balance = -1;
			return false;
		}
		else {
			if (root->left->balance <= 0) {
				return RRotation(root, true);
			}
			return LRRotation(root, true);
		}
	}
	bool RRotation(BalTreeNode*& root, bool deleteMethod) {
		BalTreeNode* rootB = root->left;
		rootB->balance -= 1;
		root->balance = -rootB->balance;
		root->left = rootB->right;
		rootB->right = root;
		root = rootB;
		return deleteMethod && !(std::abs(rootB->balance));
	}
	bool LRotation(BalTreeNode*& root, bool deleteMethod) {
		BalTreeNode* rootB = root->right;
		rootB->balance = root->balance = 0;
		root->right = rootB->left;
		rootB->left = root;
		root = rootB;
		return deleteMethod && !(std::abs(rootB->balance));
	}
	bool LRRotation(BalTreeNode*& root, bool deleteMethod) {
		BalTreeNode* rootB = root->left;
		BalTreeNode* rootC = rootB->right;
		if (rootC->balance < 0) {
			rootC->balance = rootB->balance = 0;
			root->balance = 1;
		}
		else if (rootC->balance > 0) {
			rootC->balance = root->balance = 0;
			rootB->balance = -1;
		}
		else {
			rootC->balance = 0;
			root->balance = -1;
			rootB->balance = 1;
		}
		root->left = rootC->right;
		rootB->right = rootC->left;
		rootC->left = rootB;
		rootC->right = root;
		root = rootC;
		return deleteMethod;
	}
	bool RLRotation(BalTreeNode*& root, bool deleteMethod) {
		BalTreeNode* rootB = root->right;
		BalTreeNode* rootC = rootB->left;
		if (rootC->balance < 0) {
			rootC->balance = root->balance = 0;
			rootB->balance = 1;
		}
		else if (rootC->balance > 0) {
			rootC->balance = rootB->balance = 0;
			root->balance = -1;
		}
		else {
			rootC->balance = 0;
			root->balance = -1;
			rootB->balance = 1;
		}
		root->right = rootC->left;
		rootB->left = rootC->right;
		rootC->left = root;
		rootC->right = rootB;
		root = rootC;
		return deleteMethod;
	}
	bool deleteWord(BalTreeNode*& root, std::string word) {
		if (!root) {
			return false;
		}
		if (word < root->word) {
			if (deleteWord(root->left, word)) {
				return balanceDeleteToLeft(root);
			}
			return false;
		}
		else if (word > root->word) {
			if (deleteWord(root->right, word)) {
				return balanceDeleteToRight(root);
			}
			return false;
		}
		root->frequency--;
		if (root->frequency > 0) {
			return false;
		}
		BalTreeNode* temp = root;
		if (!root->left) {
			root = root->right;
		}
		else if (!root->right) {
			root = root->left;
		}
		else {
			//deleteTwoSubtrees(root->left, temp);
			BalTreeNode* leftSubTree = root->left;
			while (leftSubTree->right != nullptr) {
				leftSubTree = leftSubTree->right;
			}
			BalTreeNode* newRoot = new BalTreeNode();
			newRoot->word = leftSubTree->word;
			newRoot->frequency = leftSubTree->frequency;
			deleteWord(root, leftSubTree->word);
			root->word = newRoot->word;
			root->frequency = newRoot->frequency;
			delete newRoot;
			return true;
			/*delete temp;
			balanceDeleteToLeft(root);
			return true;*/
		}
		delete temp;
		return true;
	}
	void deleteTwoSubtrees(BalTreeNode*& leftSubTree, BalTreeNode*& root) {
		if (leftSubTree->right) {
			deleteTwoSubtrees(leftSubTree->right, root);
			//balanceDeleteToRight(root);
		}
		else {
			root->word = leftSubTree->word;
			root->frequency = leftSubTree->frequency;
			root = leftSubTree;
			leftSubTree = leftSubTree->left;
		}
	}
	int findWord(std::string word) {
		if (!this->root) {
			return 0;
		}
		BalTreeNode* root = this->root;
		while (root) {
			if (root->word == word) {
				return root->frequency;
			}
			else if (word < root->word) {
				root = root->left;
			}
			else if (word > root->word) {
				root = root->right;
			}
		}
		return 0;
	}
	int numberOfWords(BalTreeNode* root) {
		if (!root) {
			return 0;
		}
		return root->frequency + numberOfWords(root->left) + numberOfWords(root->right);
	}
	BalTreeNode* getRootCopy() {
		return this->root;
	}
	BalTreeNode*& getRoot() {
		return this->root;
	}
	std::string toString(BalTreeNode* root) {
		if (!root) {
			return "";
		}
		return toString(root->left) + " "
			+ root->word + "::" + std::to_string(root->frequency)
			+ " " + toString(root->right);
	}
	std::string toLevelString(BalTreeNode* root, int tab) {
		if (!root) {
			return "";
		}
		std::string temp;
		for (int i = 0; i < tab; ++i) {
			temp += " ";
		}
		return temp + root->word + "::" + std::to_string(root->frequency) + "\n"
			+ toLevelString(root->left, tab + 1)
			+ toLevelString(root->right, tab + 1);
	}
};