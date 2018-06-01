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

void fixheight(node* tree)
{
	unsigned char heightleft = height(tree->left);
	unsigned char heightright = height(tree->right);
	tree->height = (heightleft>heightright ? heightleft : heightright) + 1;
}

node* rotateright(node* tree) // правый поворот вокруг p
{
	node* otree = tree->left;
	tree->left = otree->right;
	otree->right = tree;
	fixheight(tree);
	fixheight(otree);
	return otree;
}

node* rotateleft(node* otree) // левый поворот вокруг otree
{
	node* tree = otree->right;
	otree->right = tree->left;
	tree->left = otree;
	fixheight(otree);
	fixheight(tree);
	return tree;
}

node* balance(node* tree) // балансировка узла p
{
	fixheight(tree);
	if (bfactor(tree) == 2)
	{
		if (bfactor(tree->right) < 0)
			tree->right = rotateright(tree->right);
		return rotateleft(tree);
	}
	if (bfactor(tree) == -2)
	{
		if (bfactor(tree->left) > 0)
			tree->left = rotateleft(tree->left);
		return rotateright(tree);
	}
	return tree; // балансировка не нужна
}

node* insert(node* tree, int key) // вставка ключа key в дерево с корнем p
{
	if (!tree) return new node(key);
	if (key<tree->key)
		tree->left = insert(tree->left, key);
	else
		tree->right = insert(tree->right, key);
	return balance(tree);
}

node* findmin(node* tree) // поиск узла с минимальным ключом в дереве p 
{
	return tree->left ? findmin(tree->left) : tree;
}

node* removemin(node* tree) // удаление узла с минимальным ключом из дерева p
{
	if (tree->left == 0)
		return tree->right;
	tree->left = removemin(tree->left);
	return balance(tree);
}

node* remove(node* tree, int key) // удаление ключа key из дерева p
{
	if (!tree) return 0;
	if (key < tree->key)
		tree->left = remove(tree->left, key);
	else if (key > tree->key)
		tree->right = remove(tree->right, key);
	else //  key == p->key 
	{
		node* otree = tree->left;
		node* rtree = tree->right;
		delete tree;
		if (!rtree) return otree;
		node* min = findmin(rtree);
		min->right = removemin(rtree);
		min->left = otree;
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
