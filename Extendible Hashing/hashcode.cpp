#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<int>> v(2048);
int loc_dep[2048];
int glo_dep=1;
int direc_size=2;
int bucket_size;

void insert(int num)
{
	int index=num%direc_size;
	// cout<<loc_dep[index]<<" "<<glo_dep<<endl;
	if(v[index].size()<bucket_size)
	{
		if(loc_dep[index]==glo_dep)
			v[index].push_back(num);
		else
		{
			ll power=pow(2,loc_dep[index]);
			int index2=num%power;
			v[index2].push_back(num);
			while(index2+power<direc_size)
			{
				v[index2+power].push_back(num);
				index2=index2+power;
			}
		}
	}
	else
	{
		if(loc_dep[index]<glo_dep)
		{
			vector<int> temp;
			for(int i=0;i<v[index].size();i++)
				temp.push_back(v[index][i]);
			ll power=pow(2,loc_dep[index]);
			index=num%power;
			loc_dep[index]++;
			v[index].clear();
			while(index+power<direc_size)
			{
				loc_dep[index+power]++;
				index+=power;
				v[index].clear();
			}
			power=pow(2,loc_dep[index]);
			int newmod=pow(2,loc_dep[index]);
			for(int i=0;i<temp.size();i++)
			{
				int tempIndex=temp[i]%newmod;
				v[tempIndex].push_back(temp[i]);
				while(tempIndex+power<direc_size)
				{
					v[tempIndex+power].push_back(temp[i]);
					tempIndex+=power;
				}
			}
			insert(num);
		}
		else
		{
			for(int i=0;i<direc_size;i++)
			{
				if(i!=index)
				{
					v[i+direc_size].clear();
					vector<int> temp;
					for(int j=0;j<v[i].size();j++)
						temp.push_back(v[i][j]);
					for(int j=0;j<temp.size();j++)
						v[i+direc_size].push_back(temp[j]);
				}
				else
				{
					vector<int> temp;
					for(int j=0;j<v[i].size();j++)
						temp.push_back(v[i][j]);
					// temp.push_back(num);
					int newmod=pow(2,glo_dep+1);
					v[index].clear();
					v[index+direc_size].clear();
					for(int j=0;j<temp.size();j++)
						v[temp[j]%newmod].push_back(temp[j]); 
					loc_dep[index]=glo_dep+1;
					loc_dep[index+direc_size]=glo_dep+1;
				}
			}
			glo_dep++;
			direc_size*=2;
			insert(num);
		}
	}
}

void showHash()
{
	for(int i=0;i<direc_size;i++)
	{
		cout<<"Bucket "<<i<<" : ";
		for(int j=0;j<v[i].size();j++)
		{
			if(j!=v[i].size()-1)
				cout<<v[i][j]<<" -> ";
			else
				cout<<v[i][j];
		}
		cout<<endl;
	}
}

void searchNum(int num)
{
	int index=num%direc_size;
	ll power=pow(2,loc_dep[index]);
	index=num%power;
	cout<<"Present in Buckets: ";
	int flag=0;
	while(index<direc_size)
	{
		if(flag==1)
		{
			cout<<index<<" ";
			index=index+power;
			continue;
		}
		for(int i=0;i<v[index].size();i++)
		{
			if(v[index][i]==num)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			cout<<index<<" ";
			index=index+power;
		}
		else
			break;
	}
	cout<<endl;
}

bool searchNum2(int num)
{
	int index=num%direc_size;
	ll power=pow(2,loc_dep[index]);
	index=num%power;
	int flag=0;
	while(index<direc_size)
	{
		if(flag==1)
			return true;
		for(int i=0;i<v[index].size();i++)
		{
			if(v[index][i]==num)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
			return true;
		else
			return false;
	}
}

void deleteNum(int num)
{
	int index=num%direc_size;
	ll power=pow(2,loc_dep[index]);
	index=num%power;
	int flag=0;
	while(index<direc_size)
	{
		if(flag==1)
		{
			for(int i=0;i<v[index].size();i++)
			{
				if(v[index][i]==num)
				{
					v[index].erase(v[index].begin()+i);
					break;
				}
			}
			index=index+power;
			continue;
		}
		for(int i=0;i<v[index].size();i++)
		{
			if(v[index][i]==num)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			cout<<"Number does not exist\n";
			break;
		}
	}
}

int main()
{
	cout<<"Enter the bucket size that you want\n";
	cin>>bucket_size;
	for(int i=0;i<2048;i++)
	{
		loc_dep[i]=1;
		v[i].clear();
	}
	while(1)
	{
		int choice;
		cout<<"Press 1 for inserting element\n";
		cout<<"Press 2 for searching element\n";
		cout<<"Press 3 for deleting element\n";
		cout<<"Press 4 for showing the status of the hash table\n";
		cout<<"Press any other key for exiting\n";
		cin>>choice;
		if(choice==1)
		{
			int num;cin>>num;
			if(!searchNum2(num))
				insert(num);
		}
		else if(choice==2)
		{
			int num;cin>>num;
			searchNum(num);
		}
		else if(choice==3)
		{
			int num;cin>>num;
			deleteNum(num);
		}
		else if(choice==4)
		{
			showHash();
		}
		else
			return 0;
	}
}