// Kur-kur.cpp: определяет точку входа для консольного приложения.
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
	node(int keyV) { key = keyV; left = right = 0; height = 1; }
};

unsigned char height(node* tree)
{
	return tree ? tree->height : 0;
}

int bfactor(node* tree)
{
	return height(tree->right) - height(tree->left);
}

void fixheight(node* tree)
{
	unsigned char hightLeft = height(tree->left);
	unsigned char hightRight = height(tree->right);
	tree->height = (hightLeft>hightRight ? hightLeft : hightRight) + 1;
}

node* rotateright(node* tree) // правый поворот вокруг tree
{
	node* oTree = tree->left;
	tree->left = oTree->right;
	oTree->right = tree;
	fixheight(tree);
	fixheight(oTree);
	return oTree;
}

node* rotateleft(node* oTree) // левый поворот вокруг oTree
{
	node* tree = oTree->right;
	oTree->right = tree->left;
	tree->left = oTree;
	fixheight(oTree);
	fixheight(tree);
	return tree;
}
const int depth = 2;
node* balance(node* tree) // балансировка узла tree
{
	fixheight(tree);
	if (bfactor(tree) == depth)
	{
		if (bfactor(tree->right) < 0)
			tree->right = rotateright(tree->right);
		return rotateleft(tree);
	}
	if (bfactor(tree) == -depth)
	{
		if (bfactor(tree->left) > 0)
			tree->left = rotateleft(tree->left);
		return rotateright(tree);
	}
	return tree; // балансировка не нужна
}

node* insert(node* tree, int keyV) // вставка ключа keyV в дерево с корнем tree
{
	if (!tree) return new node(keyV);
	if (keyV<tree->key)
		tree->left = insert(tree->left, keyV);
	else
		tree->right = insert(tree->right, keyV);
	return balance(tree);
}

node* findmin(node* tree) // поиск узла с минимальным ключом в дереве tree 
{
	return tree->left ? findmin(tree->left) : tree;
}

node* removemin(node* tree) // удаление узла с минимальным ключом из дерева tree
{
	if (tree->left == 0)
		return tree->right;
	tree->left = removemin(tree->left);
	return balance(tree);
}

node* remove(node* tree, int keyV) // удаление ключа keyV из дерева tree
{
	if (!tree) return 0;
	if (keyV < tree->key)
		tree->left = remove(tree->left, keyV);
	else if (keyV > tree->key)
		tree->right = remove(tree->right, keyV);
	else //  keyV == tree->key 
	{
		node* oTree = tree->left;
		node* rTree = tree->right;
		delete tree;
		if (!rTree) return oTree;
		node* min = findmin(rTree);
		min->right = removemin(rTree);
		min->left = oTree;
		return balance(min);
	}
	return balance(tree);
}

void print_tree(node **root) {
	if (*root != nullptr) {
		cout << (*root)->key << endl;
		print_tree(&(*root)->left);
		print_tree(&(*root)->right);
	}
}
int main()
{
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
	system("pause");
	return 0;
}

