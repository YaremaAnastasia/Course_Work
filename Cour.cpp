// Cour.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int key) { key = key; left = right = 0; height = 1; }
};

unsigned char height(node* tree)
{
	return tree ? tree ->height : 0;
}

int bfactor(node* tree)
{
	return height(tree->right) - height(tree->left);
}

void fixHeight(node* tree)
{
	unsigned char heightleft = height(tree->left);
	unsigned char heightright = height(tree->right);
	tree->height = (heightleft>heightright ? heightleft : heightright) + 1;
}

node* rotateRight(node* tree)
{
	node* otree = tree->left;
	tree->left = otree->right;
	otree->right = tree;
	fixHeight(tree);
	fixHeight(otree);
	return otree;
}

node* rotateLeft(node* otree) 
{
	node* tree = otree->right;
	otree->right = tree->left;
	tree->left = otree;
	fixHeight(otree);
	fixHeight(tree);
	return tree;
}

node* balance(node* tree) 
{
	fixHeight(tree);
	if (bfactor(tree) == 2)
	{
		if (bfactor(tree->right) < 0)
			tree->right = rotateRight(tree->right);
		return rotateLeft(tree);
	}
	if (bfactor(tree) == -2)
	{
		if (bfactor(tree->left) > 0)
			tree->left = rotateLeft(tree->left);
		return rotateRight(tree);
	}
	return tree; // балансировка не нужна
}

node* insert(node* tree, int key) // вставка ключа key в дерево с корнем tree
{
	if (!tree) return new node(key);
	if (key<tree->key)
		tree->left = insert(tree->left, key);
	else
		tree->right = insert(tree->right, key);
	return balance(tree);
}

node* findMin(node* tree) 
{
	return tree->left ? findMin(tree->left) : tree;
}

node* removeMin(node* tree) // удаление узла с минимальным ключом из дерева tree
{
	if (tree->left == 0)
		return tree->right;
	tree->left = removeMin(tree->left);
	return balance(tree);
}

node* remove(node* tree, int key) // удаление ключа key из дерева tree
{
	if (!tree) return 0;
	if (key < tree->key)
		tree->left = remove(tree->left, key);
	else if (key > tree->key)
		tree->right = remove(tree->right, key);
	else 
	{
		node* otree = tree->left;
		node* rtree = tree->right;
		delete tree;
		if (!rtree) return otree;
		node* min = findMin(rtree);
		min->right = removeMin(rtree);
		min->left = otree;
		return balance(min);
	}
	return balance(tree);
}

void print_tree(node **root) 
{
	if (*root != nullptr) {
		cout << (*root)->key << endl;
		print_tree(&(*root)->left);
		print_tree(&(*root)->right);
	}
}
int main(){
	node *root = new node(656);

	insert(root, 57575);
	insert(root, 577);
	insert(root, 57565655);
	insert(root, 535345);
	insert(root, 565);
	insert(root, 57575);
	insert(root, 5575);
	insert(root, 775);
	insert(root, 575);

	print_tree(&root);
	cout << "With remove" << endl;
	
	remove(root, 575);
	remove(root, 57575);
	remove(root, 535345);

	print_tree(&root);
	system("pause");
	return 0;
}
