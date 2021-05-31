#ifndef METHOD_H
#define METHOD_H

#include "record.h"
#include "variable.h"

#include <map>
using std::map;

class Method : public Record
{
private:
    string record = "method";

protected:
    map<string, Variable> parameters;
    map<string, Variable> variables;
    
public:
    Method();
    Method(map<string, Variable> parameters, map<string, Variable> variables);
        
    void addVariable();
    void addParameter();
};


#endif