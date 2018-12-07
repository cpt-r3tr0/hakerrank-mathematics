#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

struct node
{
  string data;
  int rem;
};
void bfs(int n)
{
  queue<node>Q;
  int vis[20010]={0};
  node temp;
  temp.data="9";
  temp.rem=9%n;
  vis[temp.rem]=1;
  Q.push(temp);
  while (!Q.empty())
  {
    node in;
    in=Q.front();
    Q.pop();
    if (in.rem==0)
    {
      cout << in.data << endl;
      break;
    }
    node re;

    re.rem=(in.rem*10)%n;
    re.data=in.data;
    if (vis[re.rem]==0)
    {
      vis[re.rem]=1;
      re.data+='0';
      Q.push(re);
    }

    re.rem=(in.rem*10+9)%n;
    re.data=in.data;
    if (vis[re.rem]==0)
    {
      vis[re.rem]=1;
      re.data+='9';
      Q.push(re);
    }
  }
  return ;
}
int main()
{
  int t;
  scanf("%d",&t);
  while (t--)
  {
    int n;
    scanf("%d",&n);
    bfs(n);
  }
  return 0;
}
