#include<bits/stdc++.h>
using namespace std;
string to_string(int val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}


void readfile1(int i)
{
    string file="out"+to_string(i)+".txt";
    string out="smallout"+to_string(i)+".txt";
   ifstream inf (file.c_str());
    ofstream of(out.c_str());
    bool check=false;
    while (inf)
    {
        std::string strInput;
        getline(inf, strInput);
        string timee="c total process time since initialization: ";
        if(strInput.rfind(timee,0)==0){
                check=true;
            of<<strInput.substr(timee.size(),strInput.size())<<endl;
        }
        string memm="c maximum resident set size of process:                 : ";
        if(strInput.rfind(memm,0)==0){
            of<<strInput.substr(memm.size(),strInput.size())<<endl;
        }

    }
    if(!check){ of<<"800 seconds"<<endl;
    //of<<"0 MB"<<endl;
    }

    of.close();
    inf.close();

}


int main()
{
    for(int i=1;i<=1000;++i) readfile1(i);
}

