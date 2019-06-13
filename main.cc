#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include "vertex.h"
#include "edge.h"
#include "gplot.h"

using namespace std;

class Sh_path
{
public:
    string name;
    Sh_path *parent;
    int num;
    int index;
    Sh_path *next;
};

void vertex_name(Edge *);
void odd_path();
int shortest_pathnum(string ,string);
//vector <int> shortest_path();
void edge_pathnum(Edge *);
void sh_num(int **,int ,int *,int ,int,int,int *);
void sh_dfs(int ,int *,int,int);
void dfs_path(int ,int ,int *);

int **pathnum;
vector<string> vertexname;
vector<string> out_path;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();


int main(int argc, char** argv){

    nm->interpret("graph11.txt");

    vertex_name(nm->elist);

		int m=vertexname.size();
		pathnum = new int * [m];   
		for(int k=0; k<m; k++)
		{
        pathnum[k] = new int [m]();
		}
    
    for(int k=0; k<m; k++)
		{
        for(int w=0;w<m;w++)
          pathnum[k][w] = 0;
		}
    edge_pathnum(nm->elist);
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"all vertex: ";
    for(int i=0;i<vertexname.size();i++)
    {
        cout<<vertexname[i]<<" ";
    }
    cout<<"\n"<<endl;
    
    cout<<"adjacency matrix:"<<endl;
    cout<<"  ";
    for(int i=0;i<vertexname.size();i++)
    {
        cout<<vertexname[i]<<" ";
    }
    cout<<endl;
    for(int k=0; k<vertexname.size(); k++)
		{
        cout<<vertexname[k]<<" ";
        for(int w=0;w<vertexname.size();w++)
            cout<<pathnum[k][w]<<" ";
        cout<<endl;
		}
    cout<<endl;
    odd_path();
    
    
    
    cout<<"adjacency matrix:"<<endl;
    cout<<"  ";
    for(int i=0;i<vertexname.size();i++)
    {
        cout<<vertexname[i]<<" ";
    }
    cout<<endl;
    for(int k=0; k<vertexname.size(); k++)
		{
        cout<<vertexname[k]<<" ";
        for(int w=0;w<vertexname.size();w++)
            cout<<pathnum[k][w]<<" ";
        cout<<endl;
		}
    cout<<endl;
    
    int length_path=0;
    int * visit;                                                                           
		visit=new int[m]();
    for(int i=0;i<vertexname.size();i++)                                                   
    {                                                                                      
        int d=0;                                                                           
        for(int j=0;j<vertexname.size();j++)                                               
            d=d+pathnum[i][j];                                                             
        visit[i]=d/2;                                              
    }       
    for(int k=0; k<vertexname.size(); k++)
		{
        for(int w=0;w<vertexname.size();w++)
            length_path=length_path+pathnum[k][w];
		}
    visit[0]=visit[0]+1;
    dfs_path(0,length_path/2,visit);
    
    Edge *out_elist;
    Edge *tra_elist;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"result: "<<endl;
    cout<<vertexname[0];
    for(int i=0;i<out_path.size();i++)
    {
         Edge *e=new Edge();
         e->next=NULL;
         Vertex *vhead=new Vertex();
         Vertex *vtail=new Vertex();
         if(i==0)
         {
            out_elist=e;
            tra_elist=e;
            vhead->name=vertexname[0];
            tra_elist->head=vhead;    
            vtail->name=out_path[i];
            tra_elist->tail=vtail;
         }
         else
         {
            vhead->name=out_path[i-1];
            e->head=vhead;
            vtail->name=out_path[i];
            e->tail=vtail;
            tra_elist->next=e;
            tra_elist=tra_elist->next;
         }           
            cout<<"->"<<out_path[i];
    }
    cout<<endl;
    
    Gplot *gp = new Gplot();
    gp->gp_add(out_elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}


int ok;  
int mini=10000; 
void dfs_path(int s,int l,int *visit)
{
  ok=0;                                                                             
  visit[s]=visit[s]-1;                                                                       
	for(int i=0;i<vertexname.size();i++)                                              
	{                                                                                 
		if(pathnum[s][i]!=0&&visit[i]!=0)                                               
    {                                                                               
        pathnum[s][i]=pathnum[s][i]-1;                                              
        pathnum[i][s]=pathnum[i][s]-1;
        out_path.push_back(vertexname[i]);
        /*for(int k=0;k<out_path.size();k++)
        cout<<out_path[k]<<" ";
        cout<<endl;*/
        l=l-1;                                                                      
        if(l>0)                                                                     
        {                                                                           
          dfs_path(i,l,visit);                                                      
        }                                                                           
        else if(i==0)                                                               
        {                                                                           
            ok=1;                                                                   
            return;                                                                 
        }                                                                           
                                                                                    
        if(ok==1)  return;                                                          
                                                                                    
        l=l+1;                                                                      
        visit[i]=visit[i]+1;
        out_path.pop_back();        
        pathnum[s][i]=pathnum[s][i]+1;                                              
        pathnum[i][s]=pathnum[i][s]+1;                                              
    }                                                                               
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
void odd_path()                                                                              //
{                                                                                            //
    vector<string> oddname;                                                                  //
    for(int i=0;i<vertexname.size();i++)                                                     //
    {                                                                                        //
        int d=0;                                                                             //
        for(int j=0;j<vertexname.size();j++)                                                 //
            d=d+pathnum[i][j];                                                               //
        if(d%2==1)                                                                           //
          oddname.push_back(vertexname[i]);                                                  //
    }                                                                                        //
                                                                                             //
    int m=oddname.size();                                                                    //
    int **oddmap;                                                                            //
		oddmap = new int * [m];                                                                  //
		for(int k=0; k<m; k++)                                                                   //
		{                                                                                        //
        oddmap[k] = new int [m]();                                                           //
		}                                                                                        //
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"vertexs of odd degree: ";                                                         //
    for(int i=0;i<m;i++)                                                                     //
      cout<<oddname[i]<<" ";                                                                 //
    cout<<"\n"<<endl;                                                                        //
                                                                                             //
    for(int i=0;i<m;i++)                                                                     //
    {                                                                                        //
        oddmap[i][i]=0;                                                                      //
        for(int j=i+1;j<m;j++)                                                               //
        {                                                                                    //
            oddmap[i][j]=shortest_pathnum(oddname[i],oddname[j]);                            //
            oddmap[j][i]=oddmap[i][j];                                                       //
        }                                                                                    //
    }
    
    cout<<"length of Shortest path between vertex: "<<endl;                                     //
    cout<<"  ";
    for(int i=0;i<m;i++)                                                                     //
      cout<<oddname[i]<<" ";                                                                 //
    cout<<endl;    
    for(int i=0;i<m;i++)                                                                     //
    {                                                                                        //
        cout<<oddname[i]<<" ";
        for(int j=0;j<m;j++)                                                                 //
        {                                                                                    //
            cout<<oddmap[i][j]<<" ";                                                         //
        }                                                                                    //
        cout<<endl;                                                                          //
    }
    cout<<endl;                                                                                    //
    
    int * sh_visit;                                                                          //
    int * visit;                                                                             //
		visit=new int[m]();                                                                      //
    sh_visit=new int[m]();                                                                   //
    int * allvisit;                                                                          //
		allvisit=new int[vertexname.size()]();                                                   //
                                                                                             //
    int temp=0;                                                                              //
    sh_num(oddmap,0,visit,m,temp,1,sh_visit);                                                //
    cout<<"minimum length of Increased path: ";
    cout<<mini<<endl;                                                                        //
                                                                                             //
    /*for(int i=0;i<m;i++)                                                                     //
    {                                                                                        //
        cout<<sh_visit[i]<<" ";                                                              //
    }                                                                                        //
    cout<<endl;   */                                                                           //
                                                                                             //
    vector<int> se_index;                                                                    //
    cout<<"Pairing odd points: ";
    for(int k=1;k<=m/2;k++)                                                                  //
    {                                                                                        //
        for(int i=0;i<m;i++)                                                                 //
        {                                                                                    //
            if(sh_visit[i]==k)                                                               //
            {                                                                                //
                for(int j=0;j<vertexname.size();j++)                                         //
                {                                                                            //
                    if(oddname[i]==vertexname[j])                                            //
                    {                                                                        //
                      se_index.push_back(i);                                                 //
                      se_index.push_back(j);                                                 //
                    }                                                                        //
                }                                                                            //
            }                                                                                //
        }                                                                                    //
        
        cout<<"("<<vertexname[se_index[1]]<<","<<vertexname[se_index[3]]<<") ";                    //
        
        sh_dfs(se_index[1],allvisit,oddmap[se_index[0]][se_index[2]],se_index[3]);           //
        for(int j=0;j<vertexname.size();j++)                                                 //
          allvisit[j]=0;                                                                     //
        /*for(int j=0;j<vertexname.size();j++)                                                 //
        {                                                                                    //
            for(int w=0;w<vertexname.size();w++)                                             //
            cout<<pathnum[j][w]<<" ";                                                        //
            cout<<endl;                                                                      //
        }*/                                                                                    //
        se_index.clear();                                                                    //
    }  
    cout<<"\n"<<endl;                                                                                      //
}                                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
void sh_dfs(int s,int *visit,int l,int e)                                           //
{                                                                                   //
	ok=0;                                                                             //
  visit[s]=1;                                                                       //
	for(int i=0;i<vertexname.size();i++)                                              //
	{                                                                                 //
		if(pathnum[s][i]!=0&&visit[i]==0)                                               //
    {                                                                               //
        pathnum[s][i]=pathnum[s][i]+1;                                              //
        pathnum[i][s]=pathnum[i][s]+1;                                              //
        l=l-1;                                                                      //
        if(l>0)                                                                     //
        {                                                                           //
          sh_dfs(i,visit,l,e);                                                      //
        }                                                                           //
        else if(i==e)                                                               //
        {                                                                           //
            ok=1;                                                                   //
            return;                                                                 //
        }                                                                           //
                                                                                    //
        if(ok==1)  return;                                                          //
                                                                                    //
        l=l+1;                                                                      //
        visit[i]=0;                                                                 //
        pathnum[s][i]=pathnum[s][i]-1;                                              //
        pathnum[i][s]=pathnum[i][s]-1;                                              //
    }                                                                               //
	}                                                                                 //
}                                                                                   //
//////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
void sh_num(int **oddmap,int s,int *visit,int m,int temp,int n,int *sh_visit)              //
{                                                                                          //
    visit[s]=n;                                                                            //
    for(int i=0;i<m;i++)                                                                   //
    {                                                                                      //
        if(visit[i]==0)                                                                    //
        {                                                                                  //
          visit[i]=n;                                                                      //
          temp=temp+oddmap[s][i];                                                          //
          for(int j=0;j<m;j++)                                                             //
          {                                                                                //
              if(visit[j]==0)                                                              //
                  sh_num(oddmap,j,visit,m,temp,n+1,sh_visit);                              //
          }                                                                                //
          for(int j=0;j<m;j++)                                                             //
          {                                                                                //
              if(visit[j]==0)                                                              //
                  break;                                                                   //
              else if(j==m-1)                                                              //
              {                                                                            //
                  if(mini>temp)                                                            //
                  {                                                                        //
                      mini=temp;                                                           //
                      for(int k=0;k<m;k++)
                      {
                        sh_visit[k]=visit[k]; 
                      }                                      
                  }                                                                        //
              }                                                                            //
          }                                                                                //
          temp=temp-oddmap[s][i];                                                          //
          visit[i]=0;                                                                      //
        }                                                                                  //
    }                                                                                      //
    visit[s]=0;                                                                            //
}                                                                                          //
/////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
int shortest_pathnum(string start,string end)                                        //
{                                                                                    //
    Sh_path *sh_list;                                                                //
    for(int i=0;i<vertexname.size();i++)                                             //
    {                                                                                //
        if(vertexname[i]==start)                                                     //
        {                                                                            //
            sh_list=new Sh_path();                                                   //
            sh_list->next=NULL;                                                      //
            sh_list->num=0;                                                          //
            sh_list->index=i;                                                        //
            sh_list->parent=sh_list;                                                 //
        }                                                                            //
    }                                                                                //
    Sh_path *sh_traversal=sh_list;                                                   //
    while(sh_traversal!=NULL)                                                        //
    {                                                                                //
        for(int i=0;i<vertexname.size();i++)                                         //
        {                                                                            //
            if(pathnum[sh_traversal->index][i]==1)                                   //
            {                                                                        //
                if(vertexname[i]==end)                                               //
                    return sh_traversal->num+1;                                      //
                                                                                     //
                Sh_path *cur=sh_list;                                                //
                while(cur!=NULL)                                                     //
                {                                                                    //
                    if(cur->index==i)                                                //
                        break;                                                       //
                    else if(cur->next==NULL)                                         //
                    {                                                                //
                        cur->next=new Sh_path();                                     //
                        cur=cur->next;                                               //
                        cur->next=NULL;                                              //
                        cur->num=sh_traversal->num+1;                                //
                        cur->index=i;                                                //
                        cur->parent=sh_traversal;                                    //
                    }                                                                //
                    cur=cur->next;                                                   //
                }                                                                    //
            }                                                                        //
        }                                                                            //
        sh_traversal=sh_traversal->next;                                             //
    }                                                                                //
    return -1;                                                                       //
}                                                                                    //
///////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
void edge_pathnum(Edge *etraversal) //pathnum                                             //
{                                                                                         //
    while(etraversal!=NULL)                                                               //
    {                                                                                     //
        int head_index;                                                                   //
        int tail_index;                                                                   //
                                                                                          //
        for(int i=0;i<vertexname.size();i++)                                              //
        {                                                                                 //
            if(vertexname[i]==etraversal->head->name)                                     //
            {                                                                             //
              head_index=i;                                                               //
            }                                                                             //
            else if(vertexname[i]==etraversal->tail->name)                                //
            {                                                                             //
              tail_index=i;                                                               //
            }                                                                             //
        }                                                                                 //
        pathnum[head_index][tail_index]=1;                                                //
        pathnum[tail_index][head_index]=1;                                                //
        etraversal=etraversal->next;                                                      //
    }                                                                                     //
}                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
void vertex_name(Edge *etraversal)//vertex name列在vector vertexname中                    //
{                                                                                         //
    while(etraversal!=NULL)                                                               //
    {                                                                                     //
        int h=0;                                                                          //
        int t=0;                                                                          //                                                              
        for(int i=0;i<vertexname.size();i++)                                              //              
        {                                                                                 //
            if(etraversal->head->name==vertexname[i])                                     //
                h=1;                                                                      //
            else if(etraversal->tail->name==vertexname[i])                                //
                t=1;                                                                      //
        }                                                                                 //
                                                                                          //
        if(h==0)                                                                          //
            vertexname.push_back(etraversal->head->name);                                 //
                                                                                          //
        if(t==0)                                                                          //
            vertexname.push_back(etraversal->tail->name);                                 //
                                                                                          //
        etraversal=etraversal->next;                                                      //
    }                                                                                     //
                                                                                          //
}                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////


