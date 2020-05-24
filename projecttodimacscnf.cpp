#include<bits/stdc++.h>
using namespace std;

int n,k,c;
int p=2;// the number of player
fstream of;


/*n represents the number of beads
k represents the number of maximum cut allowed
c represents the number of colors*/

int colour[100000];
//c[i] represents the number at position i in the necklace

int nocolour[10000];
//nocolour[i] represents the number of beads with color i (no of index j such that c[j]=i)

map<pair<int,int>,int> allocated,nocut;
map<pair<int,pair<int,int> >,int> nocolour1;

int novar=0;

vector<vector<int> > result;



int printallocated(int i, int j, bool negative){
    if(!allocated[make_pair(i,j)]){
            allocated[make_pair(i,j)]=novar+1;
            ++novar;
    }

    if(negative) return -allocated[make_pair(i,j)];
    else return allocated[make_pair(i,j)];

}

int printnocut(int i,int j,bool negative){
    if(!nocut[make_pair(i,j)]){
            nocut[make_pair(i,j)]=novar+1;
            ++novar;
    }

    if(negative) return -nocut[make_pair(i,j)];
    else return nocut[make_pair(i,j)];

}

int printnocolour(int i,int j,int q,bool negative){
    if(!nocolour1[make_pair(i,make_pair(j,q))]){
            nocolour1[make_pair(i,make_pair(j,q))]=novar+1;
            ++novar;
    }

    if(negative) return -nocolour1[make_pair(i,make_pair(j,q))];
    else return nocolour1[make_pair(i,make_pair(j,q))];

}

vector<int> clause;

void printbelongonegroup(){
    /* We use propositional variable allocated[i][j] to represent that if allocated[i][j]=true then bead i belongs to player j*/
    for(int i=1;i<=n;++i){

        clause.push_back(printallocated(i,1,false));
        clause.push_back(printallocated(i,2,false));

        result.push_back(clause);
        clause.clear();

        clause.push_back(printallocated(i,1,true));
        clause.push_back(printallocated(i,2,true));


        result.push_back(clause);
        clause.clear();

    }
}

void printlimitnocut(){
    /*we used nocut[i][j] to represent that if nocut[i][j]=true then there has been j cut between position 1 and i*/
    for(int i=2;i<=n;++i){
        for(int j=0;j<=k+1;++j){

            for(int p1=1;p1<=2;++p1){
                for(int p2=1;p2<=2;++p2){
                    if(p1==p2){
                        clause.push_back(printnocut(i-1,j,true));
                        clause.push_back(printallocated(i-1,p1,true));
                        clause.push_back(printallocated(i,p2,true));
                        clause.push_back(printnocut(i,j,false));

                        result.push_back(clause);
                        clause.clear();
                    }
                    else{
                        if(j==0) continue;

                        clause.push_back(printnocut(i-1,j-1,true));
                        clause.push_back(printallocated(i-1,p1,true));
                        clause.push_back(printallocated(i,p2,true));
                        clause.push_back(printnocut(i,j,false));
                        result.push_back(clause);
                        clause.clear();
                    }
                }
            }

        }
    }
    clause.push_back(printnocut(1,0,false));
    result.push_back(clause);
    clause.clear();

    for(int i=0;i<=k;++i){ clause.push_back(printnocut(n,i,false)); }
    result.push_back(clause);
    clause.clear();

    for(int i=1;i<=n;++i){
        clause.push_back(printnocut(i,k+1,true));
        result.push_back(clause);
        clause.clear();

    }
}


void printconstraintcolor(){
    /*Use nocolor[i][j][k]=true means at position i, player 1 have k beads of color j*/
    //cerr<<n*c*(*max_element(nocolour+1,nocolour+k+1))/2;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=c;++j){
           // cerr<<i<<" "<<j<<endl;
            for(int q=0;q<=((int)((nocolour[j]/2)));++q){

                if(j!=colour[i]){
                        clause.push_back(printnocolour(i-1,j,q,true));
                        clause.push_back(printnocolour(i,j,q,false));
                        result.push_back(clause);
                        clause.clear();
                }
                else{
                        clause.push_back(printnocolour(i-1,j,q,true));
                        clause.push_back(printallocated(i,1,true));
                        clause.push_back(printnocolour(i,j,q+1,false));
                        result.push_back(clause);
                        clause.clear();

                        clause.push_back(printnocolour(i-1,j,q,true));
                        clause.push_back(printallocated(i,2,true));
                        clause.push_back(printnocolour(i,j,q,false));
                        result.push_back(clause);
                        clause.clear();

                }
            }
        }
    }
  //  cerr<<"done this part";
    for(int i=1;i<=c;++i){
            clause.push_back(printnocolour(0,i,0,false));
            result.push_back(clause);
                        clause.clear();
    }
    for(int j=1;j<=c;++j){
            int q=nocolour[j]/2;
            clause.push_back(printnocolour(n,j,q,false));
            result.push_back(clause);
                        clause.clear();
        }

    for(int i=1;i<=n;++i){
        for(int j=1;j<=c;++j){
            clause.push_back(printnocolour(i,j,(nocolour[j]/2)+1,true));
            result.push_back(clause);
                        clause.clear();
        }
    }
    for(int j=1;j<=c;++j){
        for(int q=0;q<(int)((nocolour[j]/2));++q){
            clause.push_back(printnocolour(n,j,q,true));
            result.push_back(clause);
                        clause.clear();
        }
    }

}


string to_string(int val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}

void test(){
    for(int ii=1;ii<=100;++ii){
        string inpfile=to_string(ii)+".txt";
        of.open(inpfile.c_str(),ios::in);
        of>>n>>k>>c;
        for(int i=1;i<=n;++i){
            of>>colour[i];
            ++nocolour[colour[i]];
        }
        for(int i=1;i<=n;++i){
            allocated[make_pair(i,1)]=i;
            ++novar;
        }
        of.close();

        printbelongonegroup();
        printlimitnocut();
        printconstraintcolor();
        string outfile="cnf"+to_string(ii)+".txt";
        of.open(outfile.c_str(),ios::out);
        of<<"p cnf "<<novar<<" "<<result.size()<<endl;
        for(int i=0;i<result.size();++i){
        for(int j=0;j<result[i].size();++j) of<<result[i][j]<<" ";
        of<<0<<endl;

     }
        of.close();
        allocated.clear();
        nocut.clear();
        nocolour1.clear();
        result.clear();
        novar=0;
        for(int i=1;i<=n;++i) colour[i]=0;
        for(int i=1;i<=c;++i) nocolour[i]=0;

    }
}



int main(){
    ios_base::sync_with_stdio(false);
    test();



}
