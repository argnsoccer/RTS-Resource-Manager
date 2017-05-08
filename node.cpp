#include "node.h"

Node::Node()
{
}

Node::Node(std::string rs)
{
    resource = rs;
    usable = true;
    active = true;
    dependencies.clear();
    dependents.clear();
}

Node::~Node()
{

}

std::vector<Node> Node::getDependency()
{
    return dependencies;
}

std::vector<Node> Node::getDependents()
{
    return dependents;
}

void Node::setDependency(Node& newDep)
{
    dependencies.push_back(newDep);
}

void print(const int &tabs)const
{
    
}

void Node::setDependent(Node& newDep)
{
    dependents.push_back(newDep);
}

std::string Node::getText()
{
    return resource;
}

void Node::setText(std::string rs)
{
    resource = rs;
}

void Node::toggleUsable()
{
    if(usable == true)
    {
        usable = false;
    }
    else{
        usable = true;
    }
}

bool Node::Usable()
{
    return usable;
}

void Node::toggleActive()
{
    active = false;
}

bool Node::Active()
{
    return active;
}