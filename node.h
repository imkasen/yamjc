#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <memory>

using std::string;
using std::cout;
using std::endl;

class Node
{
	public:
		int id;
		string type, value;
		std::list<Node *> children;

		Node();
		Node(string t, string v);

		void print_tree(int depth = 0);
		void generate_tree(int &count, std::ofstream *outStream);
};

#endif