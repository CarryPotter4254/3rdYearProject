#include<bits/stdc++.h>
#include <fstream>
using namespace std;

vector<int> co;
vector<int> afterward;
map<int,int> m;
map<int,int> cc;
int cnt=0;
vector<int> result;
int a[100000];
ofstream myfile;
int ntest=0;

int genrand(int limit){
    return rand()%limit;
}
string to_string(int val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}

void createonetest(int n,int k){

    string s="./benchmark/final/";
    s.append(to_string(ntest));
    s.append(".txt");
    myfile.open(s.c_str());
    //cout<<n<<k<<endl;

    for(int i=1;i<=k;++i){
        afterward.push_back(i);
        afterward.push_back(i);
    }
    for(int i=1;i<=(n-2*k);++i){
        int x=genrand(k)+1;
        ++m[x];
        afterward.push_back(x);
        if(m[x]%2==1){
            ++cnt;
        }
        else{
            --cnt;
        }
        if(cnt==(n-i)) break;
    }

    for(int i=1;i<=k;++i){
        if(m[i]%2==1) afterward.push_back(i);
    }
    //afterward now contains an array of possible coloring

    int cursize=afterward.size();

    //sort(afterward.begin(),afterward.end());
   // for(int i=1;i<=n;++i) cerr<<afterward[i-1]<<" ";
    //cout<<endl;
    //generate a permutation of afterward and push to result to ensure randomness
    while(cursize>0){
        int pos=genrand(cursize);
        result.push_back(afterward[pos]);
        --cursize;
        afterward[pos]=afterward[cursize];
        afterward[cursize]=0;
    }
    //cerr<<n<<" "<<k<<" "<<c<<endl;
   // for(int i=1;i<=n;++i) cerr<<result[i-1]<<" ";

    myfile<<n<<endl<<k<<endl<<k<<endl;
    for(int i=1;i<=n;++i){
        myfile<<result[i-1]<<" ";
    }
    myfile<<endl;
    co.clear();
    afterward.clear();
    m.clear();
    cc.clear();
    cnt=0;
    result.clear();
    myfile.close();

}



void createtest(int notest, int n,int k){
    for(int i=1;i<=notest;++i){
            cout<<i<<endl;
        int ndash=rand()%n+1;
    int kdash=rand()%k+1;

    while(ndash<(kdash*2)) ndash=rand()%n+1;
++ntest;
        createonetest(ndash,kdash);

    }
}


int main(){

    ios_base::sync_with_stdio(false);
    //freopen("benchmark100.txt","w",stdout);
    srand(time(NULL));

    createtest(1000,1250,30);

}
