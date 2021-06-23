#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>

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
	size_t id;
	std::string type, value;

public:
	std::list<Node *> children;

	Node();
	Node(std::string t, std::string v);

	void printAST(size_t depth = 0);
	void saveAST(std::ofstream *outStream, size_t depth = 0);
	void generateAST(size_t &count, std::ofstream *outStream);

	virtual ~Node() = default;
};

#endif