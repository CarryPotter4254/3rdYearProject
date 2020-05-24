#include<bits/stdc++.h>
using namespace std;

string to_string(int val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}


void test(int no){
    string in="./benchmark/benchmark1000/cnf"+to_string(no)+".txt";
    string out="> ./benchmark/benchmark1000/out"+to_string(no)+".txt";
    string command="timeout 800 minisat "+in+" -no-luby -rinc=1.5 -phase-saving=0 -rnd-freq=0.02 "+out;
    system(command.c_str());


}

int main(){
    ios_base::sync_with_stdio(false);

    for(int i=1;i<=100;++i){
        test(i);
    }
}
