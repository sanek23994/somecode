#include <iostream>
#include <vector>
#include <map>

#define DEBUG (0)

class Node
{
public:

    Node(unsigned id):
        id_(id),
        childs_()
         {}
    unsigned getDiameter() const;
    void addChild(const Node *child);
    unsigned getId() const { return id_; }
private:
    bool    root_;
    unsigned id_;
    std::vector<const Node *> childs_;
    unsigned getMaxDepth() const;
};

void Node::addChild(const Node *child)
{
    childs_.push_back(child);
}

unsigned Node::getMaxDepth() const
{
    unsigned max = 0;
    if (DEBUG) std::cout << "Get Max depth for id = " << id_ << std::endl;
    for (std::vector<const Node *>::const_iterator it = childs_.begin(); it != childs_.end(); ++it)
    {
        unsigned tmp = (*it)->getMaxDepth();
        if (DEBUG) std::cout << "  Max depth for child id [" << (*it)->id_  << "] = " << tmp << std::endl;
        if (tmp > max) max = tmp;
    }
    if (!childs_.empty())
    {
        max++;
    }
    return max;
}

unsigned Node::getDiameter() const
{
    if (DEBUG) std::cout << "Get Diameter for id = " << id_ << std::endl;
    if (childs_.empty())
    {
        return 0;
    }
    unsigned firstLength = 0;
    unsigned secondLegth = 0;
    for (std::vector<const Node *>::const_iterator it = childs_.begin(); it != childs_.end(); ++it)
    {
        unsigned tmp = (*it)->getMaxDepth() + 1;
        if (DEBUG) std::cout << "  Max depth for child id [" << (*it)->id_  << "] = " << tmp << std::endl;

        if (tmp > firstLength)
        {
            firstLength = tmp;
        }
        else if (tmp > secondLegth)
        {
            secondLegth = tmp;
        }
        if (DEBUG) std::cout << "    firstLength = " << firstLength << std::endl;
        if (DEBUG) std::cout << "     secondLegth = " << secondLegth << std::endl;

    }
    return firstLength + secondLegth;
}

typedef std::map<unsigned, Node*> graphStorage;

void calculateDiameter(const graphStorage &graph)
{
    unsigned diameter = 0;
    for (graphStorage::const_iterator it = graph.begin(); it != graph.end(); ++it)
    {
        unsigned tmp = (it->second)->getDiameter();
        if (DEBUG) std::cout << "diameter for " << it->first << " = " << (it->second)->getDiameter() << std::endl;
        if (tmp > diameter) diameter = tmp;
    }
    std::cout << "<<<<<<Diameter=" << diameter << ">>>>>>" << std::endl;
}

int main()
{
    unsigned n = 0;
    std::cin >> n;
    graphStorage graph;

    graph.insert(std::make_pair<int, Node*>(0, new Node(0)));
    for (unsigned i = 0; i < n; ++i)
    {
        unsigned current = 0;
        std::cin >> current;

        Node *child = new Node(graph.size());
        graph.insert(std::make_pair(graph.size(), child));

        std::map<unsigned, Node*>::iterator it = graph.find(current);
        if (it == graph.end())
        {
            std::cout << __LINE__ << std::endl;
            return -1;
        }

        Node *currentNode = it->second;
        if (currentNode == NULL)
        {
            std::cout << __LINE__ << std::endl;
            return -1;
        }

        currentNode->addChild(child);
        if (DEBUG) std::cout << "Added node with id [" << child->getId() << "] to Node with id [" << currentNode->getId() << "]" << std::endl;
        calculateDiameter(graph);
    }


    for (graphStorage::iterator it = graph.begin(); it != graph.end(); ++it)
    {
        delete it->second;
    }

    return 0;
}

