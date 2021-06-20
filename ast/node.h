#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <memory>

/*
 * The basic class in abstract syntax tree.
 *
 * Goal : Node
 * MainClass : Node
 * ...
 * Identifier : Node
 */
class Node
{
protected:
	int id;
	std::string type, value;

public:
	std::list<Node *> children;

	Node();
	Node(std::string t, std::string v);

	void printAST(int depth = 0);
	void saveAST(std::ofstream *outStream, int depth = 0);
	void generateAST(int &count, std::ofstream *outStream);
};

#endif