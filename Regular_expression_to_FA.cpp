#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string conRPN(string reg)
{
    bool flag=false;
    vector<char> SignStack;
    string RPN;
    SignStack.push_back('(');
    reg.push_back(')');
    for (string::iterator i = reg.begin(); i != reg.end(); ++i)
    {
        if(*i == '(')
        {
            if(flag)
            {
                while(SignStack.back() == '*')
                {
                    RPN.push_back(SignStack.back());
                    SignStack.pop_back();
                }
                SignStack.push_back('.');
            }
            flag = false;
            SignStack.push_back('(');
        }
        else if(*i == ')')
        {
            if(!flag)
            {
                SignStack.pop_back();
            }
            while(SignStack.back() != '(')
            {
                RPN.push_back(SignStack.back());
                SignStack.pop_back();
            }
            SignStack.pop_back();
        }
        else if(*i == '|')
        {
            while(SignStack.back() != '|' && SignStack.back() != '(')
            {
                RPN.push_back(SignStack.back());
                SignStack.pop_back();
            }
            SignStack.push_back('|');
            flag = false;
        }
        else if(*i == '*')
        {
            SignStack.push_back('*');
            flag = true;
        }
        else
        {
            if(flag)
            {
                while(SignStack.back() == '*')
                {
                    RPN.push_back(SignStack.back());
                    SignStack.pop_back();
                }
                SignStack.push_back('.');
            }
            RPN.push_back(*i);
            flag = true;
        }
    }
    return RPN;
}

vector<vector<int>> conMata(string RPN, int* s)
{
    int NodeID=0;
    vector<int> Mata[2], Edge;
    vector<vector<int>> MataStack, EdgeList;
    for(string::iterator i = RPN.begin(); i != RPN.end(); ++i)
    {
        if(*i == '.')
        {
            Mata[0] = MataStack.back();
            MataStack.pop_back();
            Mata[1] = MataStack.back();
            MataStack.pop_back();
            Edge.clear();
            Edge.push_back(Mata[1][1]);
            Edge.push_back(Mata[0][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(Mata[1][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(Mata[0][1]);
            Edge.push_back(NodeID+1);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
        }
        else if(*i == '*')
        {
            Mata[0] = MataStack.back();
            MataStack.pop_back();
            Edge.clear();
            Edge.push_back(Mata[0][1]);
            Edge.push_back(Mata[0][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(Mata[0][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(Mata[0][1]);
            Edge.push_back(NodeID+1);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(NodeID+1);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
        }
        else if(*i == '|')
        {
            Mata[0] = MataStack.back();
            MataStack.pop_back();
            Mata[1] = MataStack.back();
            MataStack.pop_back();
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(Mata[0][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(Mata[1][0]);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(Mata[0][1]);
            Edge.push_back(NodeID+1);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
            Edge.clear();
            Edge.push_back(Mata[1][1]);
            Edge.push_back(NodeID+1);
            Edge.push_back(0);
            EdgeList.push_back(Edge);
        }
        else
        {
            Edge.clear();
            Edge.push_back(NodeID);
            Edge.push_back(NodeID+1);
            Edge.push_back(*i);
            EdgeList.push_back(Edge);
        }
        Mata[0].clear();
        Mata[0].push_back(NodeID);
        Mata[0].push_back(NodeID+1);
        MataStack.push_back(Mata[0]);
        NodeID += 2;
    }
    *s = NodeID -2;
    return EdgeList;
}

void printMata(vector<vector<int>> EdgeList, int s)
{
    int NodeID;
    bool Nodes[s+2]={0};
    vector<int> NodeStack;
    NodeStack.push_back(s);
    Nodes[s]=1;
    while(!NodeStack.empty())
    {
        NodeID = NodeStack.back();
        NodeStack.pop_back();
        for(vector<vector<int>>::iterator i = EdgeList.begin(); i != EdgeList.end(); ++i)
        {
            if((*i)[0] == NodeID)
            {
                cout<<(*i)[0]<<"-- "<<(char)((*i)[2])<<" ->"<<(*i)[1]<<endl;
                if(!Nodes[(*i)[1]])
                {
                    Nodes[(*i)[1]] = 1;
                    NodeStack.push_back((*i)[1]);
                }
            }
        }
    }
    return;
}

int main()
{
    int temp;
    vector<vector<int>> EdgeList;
    set<int> alphabeta;
    string filename, reg;
    ifstream fin;
    ofstream fout;
    cout<<"Open File:"<<endl;
	cin>>filename;
    fin.open(filename);
    if(fin.fail())
    {
        cout<<"Unable to Open this File!"<<endl;
        return 0;
    }
    cout<<"Print to File:"<<endl;
    cin>>filename;
    fout.open(filename);

	fin>>reg;
    temp = 0;
    for(string::iterator i = reg.begin(); i != reg.end(); i++)
    {
        if(*i != '*' && *i != '|' && *i != '(' && *i != ')' && alphabeta.find(*i) == alphabeta.end())
        {
            alphabeta.insert(*i);
            temp++;
        }
    }
    fout<<temp<<endl;
    // print number of letter

    reg = conRPN(reg);
    EdgeList = conMata(reg, &temp);
    printMata(EdgeList, temp);

    for(set<int>::iterator i=alphabeta.begin(); i != alphabeta.end(); i++)
    {
        fout<<*i<<endl;
    }

    fout<<EdgeList.size()<<endl;
    for(vector<vector<int>>::iterator i = EdgeList.begin(); i != EdgeList.end(); ++i)
    {
        fout<<(*i)[0]<<" "<<(*i)[1]<<" "<<(*i)[2]<<endl;
    }
    fout<<temp<<' '<<temp+1<<endl;

    return 0;
}
