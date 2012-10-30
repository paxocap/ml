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
  output.open("1e.txt");
  vector<double> pu(502);
  vector<vector<double> > pb(502,vector<double>(502,0));
  vector<double> count(502);
  map<int,string> voc; //map to store the index and the vocab word
  map<string,double> vocabuprob; //map to store the word and its unigram probability
  map<string,int> vocabindex; //map to store the index and the vocab wor
  vector<double> logmix(105);
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
  double plogmixgram = 1.00,logmixgram,opt=-10000,optlambda;
  int r=0;
 //given sentence "The agency ofﬁcials sold securities."
 for(double lambda = 0.00; lambda <= 1.00; lambda=lambda+0.01){
   plogmixgram = plogmixgram * (lambda*(vocabuprob.find("THE")->second) + (1-lambda)*pb[(vocabindex.find("<s>")->second)][(vocabindex.find("THE")->second)]); 
   plogmixgram = plogmixgram * (lambda*(vocabuprob.find("AGENCY")->second) + (1-lambda)*pb[(vocabindex.find("THE")->second)][(vocabindex.find("AGENCY")->second)]); 
   plogmixgram = plogmixgram * (lambda*(vocabuprob.find("OFFICIALS")->second) + (1-lambda)*pb[(vocabindex.find("AGENCY")->second)][(vocabindex.find("OFFICIALS")->second)]); 
   plogmixgram = plogmixgram * (lambda*(vocabuprob.find("SOLD")->second) + (1-lambda)*pb[(vocabindex.find("OFFICIALS")->second)][(vocabindex.find("SOLD")->second)]);
   plogmixgram = plogmixgram * (lambda*(vocabuprob.find("SECURITIES")->second) + (1-lambda)*pb[(vocabindex.find("SOLD")->second)][(vocabindex.find("SECURITIES")->second)]); 
   logmix[r] = log(plogmixgram);  //this holds the log likelihood value of unigram model for the given sentence.
   if(opt<logmix[r]){
     opt=logmix[r];
     optlambda=lambda;
    }
   output<<lambda<<" "<<logmix[r]<<endl;
   r++;
   plogmixgram = 1.00; 
  }
  rep(i,r)
    cout<<logmix[i]<<"\t";
  cout<<endl;
  cout<<"optmix val = "<<opt<<"\t optlambda val= "<<optlambda;
 
  output.close();
  vocab.close();
  bigram.close();
  unigram.close();
  return 0;
}   