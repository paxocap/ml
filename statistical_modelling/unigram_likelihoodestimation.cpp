#include <cstdio>
#include <numeric>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <deque>
#include <fstream>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define y0 y3487465
#define y1 y8687969
#define fill(x,y) memset(x,y,sizeof(x))
                        
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef double D;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

template<class T> T abs(T x) { re x > 0 ? x : -x; }

int main()
{
  ifstream unigram,vocab;
  ofstream output;
  unigram.open("unigram.txt");
  vocab.open("vocab.txt");
  output.open("1a.txt");
  vector<double> p(501);
  vector<double> count(501);
  ll sum=0;
  int val;
  string line;
  int k=0;
  if(unigram.is_open()){
    while(unigram.good()){
      getline(unigram,line);
      istringstream (line) >> val;
      count[k]=val;
      k++;
      sum+=val;
    }
  }

  rep(i,500){
    p[i]=count[i]/sum;   //vector p holds the maximum likelihood estimate of all the unigrams
  }
    k=0;
  cout<<"**********************************"<<endl;
  cout<<"UNIGRAM WORD\t| PROBABILITY"<<endl;
  cout<<"**********************************"<<endl;
  if(vocab.is_open()){
    while(vocab.good()){
      getline(vocab,line);
      if(line[0]=='S'||line[0]=='s'){
	  cout<<line<<"\t\t"<<p[k]<<endl;
	  output<<line<<"\t\t"<<p[k]<<endl;
      }
      k++;
    }
  }
  output.close();
  vocab.close();
  unigram.close();
  return 0;
}   