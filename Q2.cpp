#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

class graph
{
    int n;
    int no_edg;
    int edges[100][4],sets[100][10],top[100];

    public:
    int input();
    void initializeSpanT();
    void SortEdges();
    void KruskalAlgo();
    int FindNode(int);
};
int graph::input()
{
   
    cout<<"\nvertices:";
    cin>>n;
    no_edg=0;

    cout<<"\n weights of the following:\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            cout<<"edge "<<i<<" , "<<j<<" :";
            int w;
            cin>>w;
            if(w!=0)
            {
                no_edg++;

                edges[no_edg][1]=i;
                edges[no_edg][2]=j;
                edges[no_edg][3]=w;
            }
        }
    }
    cout<<"\n\n Edges:\n";
    for(int i=1;i<=no_edg;i++)
    {
        cout<<" < "<<edges[i][1]<<" , "<<edges[i][2]<<" > "<<edges[i][3]<<endl;
    }
}
void graph::SortEdges()
{
    for(int i=1;i<=no_edg-1;i++)
    {
        for(int j=1;j<=no_edg-i;j++)
        {
            if(edges[j][3]>edges[j+1][3])
            {
                int t=edges[j][1];
                edges[j][1]=edges[j+1][1];
                edges[j+1][1]=t;

                t=edges[j][2];
                edges[j][2]=edges[j+1][2];
                edges[j+1][2]=t;

                t=edges[j][3];
                edges[j][3]=edges[j+1][3];
                edges[j+1][3]=t;
            }
        }
    }
    cout<<"\n\nEdges:\n";
    for(int i=1;i<=no_edg;i++)
    cout<<""<<edges[i][1]<<" , "<<edges[i][2]<<" > ::"<<edges[i][3]<<endl;
}
void graph::KruskalAlgo()
{
    for(int i=1;i<=n;i++)
    {
        sets[i][1]=i;
        top[i]=1;
    }
    cout<<"\n********* THE MINIMUM SPANNING TREE IS**************";
    for(int i=1;i<=no_edg;i++)
    {
        int p1=FindNode(edges[i][1]);
        int p2=FindNode(edges[i][2]);

        if(p1!=p2)
        {
            cout<<"The edge included in MST is ::"<<" < "<<edges[i][1]<<" , "<<edges[i][2]<<" > "<<endl;
            for(int j=1;j<=top[p2];j++)
            {
                top[p1]++;
                sets[p1][top[p1]]=sets[p2][j];
            }
            top[p2]=0;
        }
        else
        {
            cout<<"Edge "<<" < "<<edges[i][1]<<" , "<<edges[i][2]<<" > "<<"is not included as it forms a cycle\n\n";
        }
    }
}
int graph::FindNode(int n)
{
    for(int i=1;i<=no_edg;i++)
    {
        for(int j=1;j<=top[i];j++)
        {
            if(n==sets[i][j])
                return i;
        }
    }
    return -1;
}
int main()
{
    graph obj;
    obj.input();
    obj.SortEdges();
    obj.KruskalAlgo();
    return 0;
}
