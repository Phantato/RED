#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

set<int> clousure(vector<vector<int>> EdgeList, set<int> ori)
{
    bool flag = 1;
    while(flag)
    {
        flag = 0;
        for(vector<vector<int>>::iterator i = EdgeList.begin(); i != EdgeList.end(); i++)
        {
            if(ori.find((*i)[0]) != ori.end() && ori.find((*i)[1]) == ori.end() & (*i)[2] == 0)
            {
                ori.insert((*i)[1]);
                flag = 1;
            }
        }
    }
    return ori;
}

vector<vector<int>> reduce(vector<vector<int>> EdgeList, set<int> alphabeta,  int s, int e, set<int>& ending)
{
    bool flag=1;
    int NodeID=1;
    set<int> ori, nxt;
    vector<int> edge;
    vector<vector<int>> NewEdgeList;
    vector<set<int>> NodeStack;
    map<set<int>, int> NodeSet;
    ori.insert(s);
    ori = clousure(EdgeList, ori);
    if(ori.find(e) != ori.end())
    {
        ending.insert(0);
    }
    NodeSet.insert(pair<set<int>, int>(ori, 0));
    NodeStack.push_back(ori);
    while(!NodeStack.empty())
    {
        ori = NodeStack.back();
        NodeStack.pop_back();
        for(set<int>::iterator i = alphabeta.begin(); i != alphabeta.end(); i++)
        {
            nxt.clear();
            for(vector<vector<int>>::iterator j = EdgeList.begin(); j != EdgeList.end(); j++)
            {
                if(ori.find((*j)[0]) != ori.end() && (*j)[2] == *i)
                {
                    nxt.insert((*j)[1]);
                }
            }
            if(!nxt.empty())
            {
                nxt = clousure(EdgeList, nxt);
                if(NodeSet.find(nxt) == NodeSet.end())
                {
                    NodeSet.insert(pair<set<int>, int>(nxt, NodeID));
                    NodeStack.push_back(nxt);
                    if(nxt.find(e) != nxt.end())
                    {
                        ending.insert(NodeID);
                    }
                    NodeID++;
                }
                edge.clear();
                edge.push_back(NodeSet[ori]);
                edge.push_back(NodeSet[nxt]);
                edge.push_back(*i);
                NewEdgeList.push_back(edge);
            }
        }
    }
    return NewEdgeList;
}

int main()
{
    int temp, letter;
    vector<int> Edge;
    vector<vector<int>> EdgeList;
    set<int> alphabeta, ending;
    string filename, reg;
    ifstream fin;
	cin>>filename;
    fin.open(filename);
    if(fin.fail())
    {
        cout<<"Unable to Open this File!"<<endl;
        return 0;
    }
	fin>>temp;
    for(int i = 0; i < temp; i++)
    {
        fin>>letter;
        alphabeta.insert(letter);
    }
	fin>>temp;
    Edge.assign(3, 0);
    EdgeList.resize(temp);
    for(int i = 0; i < temp; i++)
    {
        fin>>Edge[0]>>Edge[1]>>Edge[2];
        EdgeList[i] = Edge;
    }
    fin>>temp>>letter;

    EdgeList = reduce(EdgeList , alphabeta, temp, letter, ending);
    for(vector<vector<int>>::iterator i = EdgeList.begin(); i != EdgeList.end(); i++)
    {
        cout<<(*i)[0]<<"-- "<<(char)((*i)[2])<<" ->"<<(*i)[1]<<endl;
    }
    for(set<int>::iterator i = ending.begin(); i != ending.end(); i++)
    {
        cout<<(*i)<<' ';
    }
    cout<<endl;
	return 0;
}
