/******************************************************
 * File: main.cpp
 * Author: TODO: Your name here!
 *
 * TODO: Describe your implementation here.
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "GraphVisualizer.h"
using namespace std;

const double Pi=3.14159265358979323;
const double Kr=0.001,Ka=0.001;

void Welcome() {
	cout << "Welcome to CS106L GraphViz!" << endl;
	cout << "This program uses a force-directed graph layout algorithm" << endl;
	cout << "to render sleek, snazzy pictures of various graphs." << endl;
	cout << endl;
}
	


int main(){
	Welcome();
	
	

	/* TODO: Your implementation goes here! */

	int n,k;
	
	double elapsedTime;
	char name[100];
	
	double sum;
	int i,t,j=0;
	SimpleGraph s1;
	
	
	Edge *edge=new Edge[1000];
	double *X=new double[1000];
	double *Y=new double[1000];
	while(1){
	InitGraphVisualizer();
	cout<<"Please enter the name of the file\n";
	cin>>name;
	ifstream infile(name);

	if(!infile)
	{
		cout<<"Fail\n"<<endl;
		continue;
	}
    cout<<"Please enter the time(seconds)\n";
	cin>>sum;

    infile>>n;
	Node *node=new Node[n];
	for(i=0;i<n;i++)
		s1.nodes.push_back(node[i]);
	
    for(i=0;i<n;i++)
	{
		s1.nodes[i].x=cos(2*Pi*(i+1)/n);
		s1.nodes[i].y=sin(2*Pi*(i+1)/n);
	}
	 
	
	
    int j=0,count=0;
	bool p=1;
	double Fa,Fr;
	
	
	for(i=0;i<n;i++)
	{
		X[i]=0.0;
		Y[i]=0.0;
	}
	
	time_t startTime=time(NULL);



	while(1){
    for( i=0;i<n-1;i++)
	{
		for( j=i+1;j<n;j++)
		{
			Fr=Kr/sqrt((s1.nodes[i].x-s1.nodes[j].x)*(s1.nodes[i].x-s1.nodes[j].x)+(s1.nodes[i].y-s1.nodes[j].y)*(s1.nodes[i].y-s1.nodes[j].y));
			X[i]-=Fr*cos(atan2((s1.nodes[j].y-s1.nodes[i].y),(s1.nodes[j].x-s1.nodes[i].x)));
			Y[i]-=Fr*sin(atan2((s1.nodes[j].y-s1.nodes[i].y),(s1.nodes[j].x-s1.nodes[i].x)));
			X[j]+=Fr*cos(atan2((s1.nodes[j].y-s1.nodes[i].y),(s1.nodes[j].x-s1.nodes[i].x)));
			Y[j]+=Fr*sin(atan2((s1.nodes[j].y-s1.nodes[i].y),(s1.nodes[j].x-s1.nodes[i].x)));
		}
	}

    j=0;
	
	if(count==0){
		
	  while(infile>>edge[j].start>>edge[j].end)
	  {
		   
           Fa=Ka*((s1.nodes[edge[j].start].x-s1.nodes[edge[j].end].x)*(s1.nodes[edge[j].start].x-s1.nodes[edge[j].end].x)+(s1.nodes[edge[j].start].y-s1.nodes[edge[j].end].y)*(s1.nodes[edge[j].start].y-s1.nodes[edge[j].end].y));
           X[edge[j].start]+=Fa*cos(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   Y[edge[j].start]+=Fa*sin(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   X[edge[j].end]-=Fa*cos(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   Y[edge[j].end]-=Fa*sin(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		  
		   j++;
	       
		}
	   for(t=0;t<j;t++)
	  	 s1.edges.push_back(edge[t]);
	   
	   k=j;
	   infile.close();
	}
	
	else
	{
		for(j=0;j<k;j++)
		{
           Fa=Ka*((s1.nodes[edge[j].start].x-s1.nodes[edge[j].end].x)*(s1.nodes[edge[j].start].x-s1.nodes[edge[j].end].x)+(s1.nodes[edge[j].start].y-s1.nodes[edge[j].end].y)*(s1.nodes[edge[j].start].y-s1.nodes[edge[j].end].y));
           X[edge[j].start]+=Fa*cos(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   Y[edge[j].start]+=Fa*sin(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   X[edge[j].end]-=Fa*cos(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		   Y[edge[j].end]-=Fa*sin(atan2((s1.nodes[edge[j].end].y-s1.nodes[edge[j].start].y),(s1.nodes[edge[j].end].x-s1.nodes[edge[j].start].x)));
		}
	}

    for(i=0;i<n;i++)
	{
		s1.nodes[i].x+=X[i];
	    s1.nodes[i].y+=Y[i];

	}
	 
	elapsedTime=difftime(time(NULL),startTime);
	

	if(elapsedTime>sum)
		break;
	
    DrawGraph(s1);
	count++;
	for(i=0;i<n;i++)
	{
		X[i]=0.0;
		Y[i]=0.0;
	}
	
}
	cout<<"Do you want to continue? Y for yes,N for no\n";
	char Judge;
	cin>>Judge;
	j=n;
	s1.nodes.clear();
	s1.edges.clear();
	if(Judge=='N')
	{
		 delete []node;
	     delete []edge;
	     delete []X;
	     delete []Y;
		 break;
	}
}

	
  
	
	return 0;
}
