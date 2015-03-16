#include <iostream>
#include <vector>
#include <map>

#define DEBUG (1)

class Node
{
public:
    typedef std::vector<unsigned> ChildsType;
    Node(unsigned parent, bool root):
        parent_id_(parent),
        childs_(),
        depth_(0),
        root_(root)
         {}

    void addChild(unsigned child_id);
    unsigned getParentId() const { return parent_id_; }
    const ChildsType &getChildsId() const { return childs_; }
    bool isRoot() const { return root_; }

    unsigned getDepth() const { return depth_; }
    void setDepth(unsigned depth) { depth_ = depth; }
private:
    size_t      parent_id_;
    ChildsType  childs_;
    unsigned    depth_;
    bool        root_;
};

void Node::addChild(const size_t child_id)
{
    childs_.push_back(child_id);
}

class Graph
{
public:
    Graph(size_t n);
    ~Graph();

    size_t AddNode(const Node &node);
    const Node &getNode(size_t id) const;
    Node &getNode(size_t id);

    unsigned getDiameterForNode(const Node& node);
private:
    typedef std::vector<Node> graphStorage;
    graphStorage    graph_;
    unsigned        diameter_;
};

Graph::Graph(size_t n) :
    graph_(),
    diameter_(0)
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

unsigned Graph::getDiameterForNode(const Node& node)
{
    const Node::ChildsType &childs = node.getChildsId();
    unsigned first_max_depth = 0;
    unsigned second_max_depth = 0;
    for (Node::ChildsType::const_iterator it = childs.begin(); it != childs.end(); ++it)
    {
        const Node &node = getNode(*it);
        const unsigned node_depth = node.getDepth();
        if (DEBUG) std::cout << "Depth for node with id [" << *it << "] = " << node_depth << std::endl;
        if (node_depth > first_max_depth)
        {
            first_max_depth = node_depth;
        }
        else if (node_depth > second_max_depth)
        {
            second_max_depth = node_depth;
        }
    }
    return first_max_depth + second_max_depth;
}

int main()
{
    unsigned n = 0;
    std::cin >> n;

    Graph graph(n);
    Node root(0, true);

    graph.AddNode(root);
    unsigned diameter = 0;

    for (unsigned i = 0; i < n; ++i)
    {
        unsigned parent = 0;
        std::cin >> parent;

        Node node(parent, false);
        Node &parentNode = graph.getNode(parent);
        size_t id = graph.AddNode(node);
        parentNode.addChild(id);
        unsigned tmpDiameter = graph.getDiameterForNode(parentNode);
        if (tmpDiameter > diameter) diameter = tmpDiameter;
        while (!parentNode.isRoot() && (parentNode.getDepth() < node.getDepth() + 1))
        {
            parentNode.setDepth(node.getDepth() + 1);
            tmpDiameter = graph.getDiameterForNode(parentNode);
            if (tmpDiameter > diameter) diameter = tmpDiameter;
            node = parentNode;
            parentNode = graph.getNode(parentNode.getParentId());
        }
        std::cout << diameter << std::endl;
    }

    return 0;
}

