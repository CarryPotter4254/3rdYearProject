#include<bits/stdc++.h>
using namespace std;
fstream in;
vector<double> ti,me;

void create()
{
    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("report.csv", ios::out | ios::trunc);

    double timee;
    double memm;
    string s;
    string l;
    // Read the input
    for (int i = 0; i < 1000; i++) {
        string s,l;
        in >> timee>>s;//>>memm>>l;
        ti.push_back(timee);
        me.push_back(memm);
    }
    for(int i=0;i<ti.size();++i){
        //if(ti[i]>=60) continue;
        // Insert the data to file
        fout << ti[i] //<< ", "
            // << me[i] << ", "
             << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    in.open("big.txt");
    create();
    in.close();
}
