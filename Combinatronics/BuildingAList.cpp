#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    scanf("%d",&t);
    for(int i=0; i<t; i++)
    {
        int len;
        scanf("%d",&len);
        string s;
        cin>>s;
        vector<int> count(26);
        for(int j=0; j<26; j++)
            count[j]=0;
        for(int j=0; j<len; j++)
            count[s[j]-'a']++;

        vector<vector<string> > val;
        vector<string> temp_vec, temp_vec2;

        char ch='z';
        for(int j=25; j>=0; j--)
        {
            string s=(string)""+ch;
            if(count[j]!=0)
            {
                temp_vec.clear();
                temp_vec.push_back(s);
                temp_vec2.clear();
                for(int k=1; k<count[j]; k++)
                    temp_vec.push_back(temp_vec[k-1]+ch);
                for(int k=0; k<count[j]; k++)
                    temp_vec2.push_back(temp_vec[k]);

                for(int k=count[j]-1; k>=0; k--)
                {
                    int len1=val.size();
                    for(int a=len1-1; a>=0; a--)
                    {
                        int len2=val[a].size();
                        for(int b=0; b<len2; b++)
                        {
                            temp_vec2.push_back(temp_vec[k]+val[a][b]);
                        }
                    }
                }

                val.push_back(temp_vec2);
             }
            ch--;
        }

        int len1=val.size();
        for(int a=len1-1; a>=0; a--)
        {
            int len2=val[a].size();
            for(int b=0; b<len2; b++)
            {
                cout<<val[a][b]<<"\n";
            }
        }
    }
    return 0;
}
