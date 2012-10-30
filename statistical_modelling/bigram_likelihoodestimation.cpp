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
  ifstream unigram,bigram,vocab;
  ofstream output;
  unigram.open("unigram.txt");
  bigram.open("bigram.txt");
  vocab.open("vocab.txt");
  output.open("1b.txt");
  vector<vector<double> > pb(502,vector<double>(502,0));
  vector<vector<double> > copypb(502,vector<double>(502,0));
  vector<double> count(502);
  vector<double> topten(502);
  map<int,string> voc; //map to store the index and the vocab word
  string line;
  double k=1;double val;
  
  if(unigram.is_open()){
    while(unigram.good()){
      getline(unigram,line);
      istringstream (line) >> val;
      count[k]=val;
      k++;
    }
  }
  
  double index1,index2,count3;
  k=1;
  if(bigram.is_open()){
    while(bigram.good()){
      getline(bigram,line);
      istringstream (line) >> index1 >> index2 >> count3;
      cout.setf(ios::fixed,ios::floatfield);        
      pb[index1][index2]=count3/count[index1];  //matrix pb holds the maximum likelihood estimate of the bigram distribution pb(w'/w) 
      k++; 
      }
  }  
    int id=1,the_index;
    if(vocab.is_open()){
      while(vocab.good()){
	getline(vocab,line);
	voc.insert(pair<int,string>(id,line));
	if(line.compare("THE")==0){
	  the_index = id;  
	}
      id++;
    }
  }
  
  copypb.swap(pb);
  double maxp=0, mwindex;
  for(int i=0;i<10;i++)
  {
    for(int j=1;j<=500;j++){
      if(copypb[the_index][j]>maxp){
	mwindex = j;
	maxp = copypb[the_index][j];
      }  
    }
    cout<<voc.find(mwindex)->second<<"\t"<<maxp<<endl;
    output<<voc.find(mwindex)->second<<"\t"<<maxp<<endl; // prints the top 10 most likely word to follow "THE" with their bigram probabilities.
    copypb[the_index][mwindex]=0;
    maxp=0;
  }
  vocab.close();
  bigram.close();
  unigram.close();
  return 0;
}   