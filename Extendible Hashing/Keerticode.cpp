# include <bits/stdc++.h>
using namespace std;

int s;

class bucket
{
public:
  vector<int> val;
  int local_depth;
  int size;
  void print_bucket()
  {
    for(int i=0;i<(this->val).size();i++)
    {
      cout<<this->val[i]<<" ";
    }
    cout<<endl;
  }
  bucket(int i)
  {
    this->local_depth=1;
    this->size=i;
    // cout<<"enter "<<i<<" values\n";
    // for(int j=0;j<i;j++)
    // {
    //   cin>>val[j];
    // }
  }
};

class directory
{
public:
  int global_depth;
  vector<bucket *> entries;
  void print_directory()
  {
    for(int i=0;i<pow(2,this->global_depth);i++)
    {
      cout<<"entry "<< i << " is ";
      this->entries[i]->print_bucket();
      cout<<endl;
    }
    cout<<endl;
  }
  directory()
  {
    this->global_depth=1;
    (this->entries).resize(2);
    this->entries[0]=new bucket(s);
    this->entries[1]=new bucket(s);
  }
};

directory *d;

int hash(int num)
{
  int t=pow(2,d->global_depth);
  return num%t;
}

void split(bucket *b,int num)
{
  if(b->local_depth == d->global_depth)
  {
    int t=hash(num) + pow(2,d->global_depth);
    d->global_depth++;
    b->local_depth++;
    (d->entries).resize(pow(2,d->global_depth));
    for(int i=pow(2,d->global_depth - 1);i<pow(2,d->global_depth);i++)
    {
      d->entries[i]=d->entries[i-pow(2,d->global_depth - 1)];
    }
    bucket *b1=new bucket(s);
    b1->local_depth=b->local_depth;
    d->entries[t]=b1;
    vector<int> temp;
    for(int i=0;i<b->size;i++)
    {
      temp.push_back(b->val[i]);
    }
    temp.push_back(num);
    (b->val).clear();
    for(int i=0;i<temp.size();i++)
    {
      int h=hash(temp[i]);
      (d->entries[h]->val).push_back(temp[i]);
    }
  }
  else
  {
    int t=hash(num);
    int p,q;
    if(t<pow(2,b->local_depth))
    {
      p=t;
      t+=pow(2,b->local_depth);
      q=t;
    }
    else
    {
      q=t;
      p=t-pow(2,b->local_depth);
    }
    b->local_depth++;
    bucket *b1=new bucket(s);
    b1->local_depth=b->local_depth;
    d->entries[t]=b1;
    for(int i=p;i<pow(2,d->global_depth);i+=pow(2,b->local_depth))
    {
      d->entries[i]=b;
    }
    for(int i=q;i<pow(2,d->global_depth);i+=pow(2,b->local_depth))
    {
      d->entries[i]=b1;
    }
    vector<int> temp;
    for(int i=0;i<b->size;i++)
    {
      temp.push_back(b->val[i]);
    }
    temp.push_back(num);
    (b->val).clear();
    for(int i=0;i<temp.size();i++)
    {
      int h=hash(temp[i]);
      (d->entries[h]->val).push_back(temp[i]);
    }
  }
}

bool search(int num)
{
  int h=hash(num);
  for(int i=0;i<(d->entries[h]->val).size();i++)
  {
    if(d->entries[h]->val[i] == num) return true;
  }
  return false;
}

void insert(int num)
{
  if(search(num))
  {
    cout<<"Already present\n";
    return;
  }
  int h=hash(num);
  bucket *b=d->entries[h];
  if((b->val).size() < b->size)
  {
    (b->val).push_back(num);
  }
  else
  {
    split(b,num);
  }
}

// In this part I assume that no duplicates are there (only need to delete 1 occurrence)
void remove(int num)
{
  int h=hash(num);
  int p=(d->entries[h]->val).size();
  for(int i=0;i<p;i++)
  {
    if(d->entries[h]->val[i] == num)
    {
      if(i==p-1)
      {
        (d->entries[h]->val).pop_back();
        return;
      }
      int temp=d->entries[h]->val[p-1];
      d->entries[h]->val[i]=temp;
      (d->entries[h]->val).pop_back();
      return;
    }
  }
  cout<<"Not present, can't delete\n";
}

int main()
{
  cout<<"enter bucket size\n";
  cin>>s;
  d=new directory();
  int choice;
  while(1)
  {
    cout<<"1 to insert, 2 to search, 3 to delete, 4 to print, 5 to leave\n";
    cin>>choice;
    int n;
    switch (choice)
    {
      case 1: cout<<"enter value to insert\n";
              cin>>n;
              insert(n);
              break;
      case 2: cout<<"enter value to search\n";
              cin>>n;
              if(search(n))
              {
                cout<<"present\n";
              }
              else
              {
                cout<<"absent\n";
              }
              break;
      case 3: cout<<"enter value to delete\n";
              cin>>n;
              remove(n);
              break;
      case 5: return 0;
      case 4:
      default:break;
    }
    d->print_directory();
  }
  return 0;
}
