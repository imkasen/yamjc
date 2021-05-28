#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"

class Variable : public Record
{
    private:
        string record = "variable";

    public:
        Variable();
        Variable(string id, string type);
};

#endif