#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "node.h"

void mapInput(std::vector<std::string> words, std::unordered_map<std::string, Node> &resources)
{
    std::string resourceName;
    std::string dependency;
    if(words.size() > 0)
    {
        resourceName = words[0];//the first string in words should be the resource name
    }
    if(resources.count(resourceName) == 0)//if resource is not already in the map
    {
         resources[resourceName] = Node(resourceName);
    }
    for(int i = 1; i < words.size(); i++)//iterate through dependencies, check if they are already in map, then set the dependencies
    {
        dependency = words[i];
        if(resources.count(dependency) == 0)
        {
            resources[dependency] = Node(dependency);
        }
        resources.at(resourceName).setDependency(resources[dependency]);//set dependency and dependants
        resources.at(dependency).setDependent(resources[resourceName]);
    }
    
    
}

void readFile(std::string fileName, std::unordered_map<std::string, Node> &resources)
{
    std::fstream fileReader;//filereading setup
    fileReader.open(fileName.c_str(), std::ios::in);
    std::string curline;
    std::size_t space;

    if(fileReader.is_open())
    {
        while(fileReader.good() && !fileReader.eof())//read in file while there is data
        {
            getline(fileReader, curline, '\n');//reads in the line
            curline.erase(std::remove(curline.begin(), curline.end(), '\n'), curline.end());//removes \r\n in case the txt is a DOS file
            curline.erase(std::remove(curline.begin(), curline.end(), '\r'), curline.end());

            std::vector<std::string> words;

            //if space isn't found, returns pos
            while((space = curline.find(' ')) != std::string::npos)//finds space delimiter and loops through each word
            {

                    words.push_back(curline.substr(0, space)); // reads in the first resource name
                    curline = curline.substr(space + 1);//removes the first word from the line to continue reading in words
            }

            // Read in last word and make sure empty line wasn't read
            if(curline.compare("\n") != 0)
            {
                words.push_back(curline);
            }
            mapInput(words, resources);//inputs the words in the map to preserve uniqueness and establishes dependency links
            
        }
        fileReader.close();
    }
}

void printGraph(std::unordered_map<std::string, Node> &resources)
{
    std::vector<std::string> dependencyList;
    std::cout << "CURRENT USABLE RESOURCES: " << std::endl;
    std::cout << std::endl;
    for(auto n = resources.begin(); n != resources.end(); ++n)
    {
        if(n->second.Active())//if the node has not been deleted display as usable
        {
            std::cout << "RESOURCE: " << n->second.getText() << std::endl;
            if(n->second.Usable())//shows whether the resource is usable or not
            {
                std::cout << "USABLE: Yes" << std::endl;
            }
            else
            {
                std::cout << "USABLE: No" << std::endl;
            }
            for(int i = 0; i < n->second.getDependency().size(); i++)//demonstrates dependency link
            {
                std::cout << "dependency link: " << n->second.getText() << "->" << n->second.getDependency()[i].getText() << std::endl;
            }
            std::cout << std::endl;
        }
    }
}


void updateUsability(std::unordered_map<std::string, Node> &resources)
{
    for(auto n = resources.begin(); n != resources.end(); ++n)
    {
        if(n->second.Active())
        {
            for(int i = 0; i < n->second.getDependency().size(); i++)
            {
                if(!resources[n->second.getDependency()[i].getText()].Usable())
                {
                    resources[n->second.getText()].toggleUsable();
                    
                }
            }
        }
    }
}

void deleteNode(std::unordered_map<std::string, Node> &resources, Node& delNode)
{
    for(int i = 0; i < delNode.getDependents().size(); i++)
    {

        resources[delNode.getDependents()[i].getText()].toggleUsable();//have to do it through resources map so the toggled usability actually shows
    }
    delNode.toggleActive();//I didn't want to delete data just in case the resource is needed later but not sure of the parameters of this project
    updateUsability(resources);
}



int main()
{
    bool flag = false;
    std::string input;
    std::unordered_map<std::string, Node> resources;//I use an unordered_map for average constant lookup time when keeping the set of nodes unique
    readFile("resource.txt", resources);
    std::cout << "Here are the current usable nodes: " << std::endl;
    printGraph(resources);
    while(flag == false)
    {
        std::cout << "Please select a node to delete (q to quit): ";
        std::cin >> input;
        if(input == "q")
        {
            std::cout << "Thank you for using this resource manager!" << std::endl;
            flag = true;
        }
        else
        {
            deleteNode(resources, resources[input]);
            printGraph(resources);
        }
    }

    
    
    return 0;
}

