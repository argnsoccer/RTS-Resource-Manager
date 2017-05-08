#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Node{
    public:
        Node();
        Node(std::string rs);
        virtual ~Node();
        std::vector<Node> getDependency();
        std::vector<Node> getDependents();
        void setDependency(Node& newDep);
        void setDependent(Node& newDep);
        std::string getText();
        void setText(std::string rs);
        bool Usable();
        void toggleUsable();
        void toggleActive();
        bool Active();
        
    private:
        std::vector<Node> dependencies;//this is a vector instead of a Node* to allow for multiple resource dependencies
        std::vector<Node> dependents;
        std::vector<std::string> usableDeps;
        std::string resource;
        bool usable;
        bool active;

};

