#include <iostream>
#include <vector>
#include <map>

#define DEBUG (0)

class Node
{
public:

    Node(size_t parent):
        parent_id_(parent),
        childs_()
         {}
//    unsigned getDiameter() const;
    void addChild(size_t child_id);
//    unsigned getId() const { return id_; }
private:
    size_t parent_id_;
    std::vector<size_t> childs_;
//    unsigned getMaxDepth() const;
};

void Node::addChild(const size_t child_id)
{
    childs_.push_back(child_id);
}

//unsigned Node::getMaxDepth() const
//{
//    unsigned max = 0;
//    if (DEBUG) std::cout << "Get Max depth for id = " << id_ << std::endl;
//    for (std::vector<const Node *>::const_iterator it = childs_.begin(); it != childs_.end(); ++it)
//    {
//        unsigned tmp = (*it)->getMaxDepth();
//        if (DEBUG) std::cout << "  Max depth for child id [" << (*it)->id_  << "] = " << tmp << std::endl;
//        if (tmp > max) max = tmp;
//    }
//    if (!childs_.empty())
//    {
//        max++;
//    }
//    return max;
//}

//unsigned Node::getDiameter() const
//{
//    if (DEBUG) std::cout << "Get Diameter for id = " << id_ << std::endl;
//    if (childs_.empty())
//    {
//        return 0;
//    }
//    unsigned firstLength = 0;
//    unsigned secondLegth = 0;
//    for (std::vector<const Node *>::const_iterator it = childs_.begin(); it != childs_.end(); ++it)
//    {
//        unsigned tmp = (*it)->getMaxDepth() + 1;
//        if (DEBUG) std::cout << "  Max depth for child id [" << (*it)->id_  << "] = " << tmp << std::endl;

//        if (tmp > firstLength)
//        {
//            firstLength = tmp;
//        }
//        else if (tmp > secondLegth)
//        {
//            secondLegth = tmp;
//        }
//        if (DEBUG) std::cout << "    firstLength = " << firstLength << std::endl;
//        if (DEBUG) std::cout << "     secondLegth = " << secondLegth << std::endl;

//    }
//    return firstLength + secondLegth;
//}

class Graph
{
public:
    Graph(size_t n);
    ~Graph();

    size_t AddNode(const Node &node);
    const Node &getNode(size_t id) const;
    Node &getNode(size_t id);
    void calculateDiameter();

private:
    typedef std::vector<Node> graphStorage;
    graphStorage    graph_;
};

Graph::Graph(size_t n)
{
    graph_.reserve(n);
}

Graph::~Graph()
{
}

size_t Graph::AddNode(const Node &node)
{
    graph_.push_back(node);
    return graph_.size() - 1;
}

const Node & Graph::getNode(size_t id) const
{
    return graph_.at(id);
}

Node & Graph::getNode(size_t id)
{
    return graph_.at(id);
}

void Graph::calculateDiameter()
{
    unsigned diameter = 0;
    for (graphStorage::const_iterator it = graph_.begin(); it != graph_.end(); ++it)
    {
//        unsigned tmp = it->getDiameter();
//        if (DEBUG) std::cout << "diameter for " << it->first << " = " << (it->second)->getDiameter() << std::endl;
//        if (tmp > diameter) diameter = tmp;
    }
    std::cout << "<<<<<<Diameter=" << diameter << ">>>>>>" << std::endl;
}

int main()
{
    unsigned n = 0;
    std::cin >> n;

    Graph graph(n);
    Node root(0);
    graph.AddNode(root);

    for (unsigned i = 0; i < n; ++i)
    {
        unsigned parent = 0;
        std::cin >> parent;

        Node node(parent);
        Node &parentNode = graph.getNode(parent);
        size_t id = graph.AddNode(node);
        parentNode.addChild(id);

    }

    return 0;
}

