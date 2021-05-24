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
	private:
		int id;
		string type, value;

	public:
		std::list<Node *> children;

		Node();
		Node(string t, string v);

		void printTree(int depth = 0);
		void saveTree(std::ofstream *outStream, int depth = 0);
		void generateTree(int &count, std::ofstream *outStream);
};

#endif