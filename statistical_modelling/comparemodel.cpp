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
  output.open("1c.txt");
  vector<double> pu(502);
  vector<vector<double> > pb(502,vector<double>(502,0));
  vector<double> count(502);
  map<int,string> voc; //map to store the index and the vocab word
  map<string,double> vocabuprob; //map to store the word and its unigram probability
  map<string,int> vocabindex; //map to store the index and the vocab wor
  string line;
  double k=1;double val;
  ll sum=0;
  
  if(unigram.is_open()){
    while(unigram.good()){
      getline(unigram,line);
      istringstream (line) >> val;
      count[k]=val;
      sum+=val;
      k++;
    }
  }
  
  for(int i=1;i<=500;i++){
    pu[i]=count[i]/sum;   //vector pu holds the maximum likelihood estimate of all the unigrams
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
	vocabuprob.insert(pair<string,double>(line,pu[id]));
	vocabindex.insert(pair<string,int>(line,id));
	id++;
      }
    }

 
 //logic to compute log likelihood of unigram model
  double plogunigram=1,logunigram;
  plogunigram = plogunigram * (vocabuprob.find("THE")->second);
  plogunigram = plogunigram * (vocabuprob.find("STOCK")->second);
  plogunigram = plogunigram * (vocabuprob.find("MARKET")->second);
  plogunigram = plogunigram * (vocabuprob.find("FELL")->second);
  plogunigram = plogunigram * (vocabuprob.find("A")->second);
  plogunigram = plogunigram * (vocabuprob.find("HUNDRED")->second);
  plogunigram = plogunigram * (vocabuprob.find("POINTS")->second);
  plogunigram = plogunigram * (vocabuprob.find("ON")->second);	
  plogunigram = plogunigram * (vocabuprob.find("FRIDAY")->second);

  logunigram = log(plogunigram);  //this holds the log likelihood value of unigram model for the given sentence.
  cout<<"log likelihood val for unigram model = "<<logunigram<<endl;
  output<<"log likelihood val for unigram model = "<<logunigram<<endl;
 
 //logic to compute log likelihood of bigram model
  double plogbigram=1,logbigram;
  plogbigram = plogbigram * pb[(vocabindex.find("<s>")->second)][(vocabindex.find("THE")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("THE")->second)][(vocabindex.find("STOCK")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("STOCK")->second)][(vocabindex.find("MARKET")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("MARKET")->second)][(vocabindex.find("FELL")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("FELL")->second)][(vocabindex.find("A")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("A")->second)][(vocabindex.find("HUNDRED")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("HUNDRED")->second)][(vocabindex.find("POINTS")->second)];
  plogbigram = plogbigram * pb[(vocabindex.find("POINTS")->second)][(vocabindex.find("ON")->second)];	
  plogbigram = plogbigram * pb[(vocabindex.find("ON")->second)][(vocabindex.find("FRIDAY")->second)];

  logbigram = log(plogbigram);  //this holds the log likelihood value of unigram model for the given sentence.
  cout<<"log likelihood val for bigram model = "<<logbigram<<endl;
  output<<"log likelihood val for bigram model = "<<logbigram<<endl;
  
  if(logbigram > logunigram){
      cout << "Bigram model yields the highest log-likelihood"<<endl;
      output << "Bigram model yields the highest log-likelihood"<<endl;
  }
  else {
      cout << "Unigram model yields the highest log-likelihood"<<endl;
      output << "Unigram model yields the highest log-likelihood"<<endl;
  }

  output.close();
  vocab.close();
  bigram.close();
  unigram.close();
  return 0;
}   