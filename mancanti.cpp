#include <vector>

using namespace std;

/*La complessità è data dai tre cicli for,ognuno di complessità lineare, ed è quindi O(n).*/
void trovaMancanti(const vector<int>& arr, int n, int k, vector<int>& ris){
    int first = n*n+1;
    int last = n*n+n;
    int len = last-first+1;
    int supp[len];
    for(int i=0;i<len;i++){
        supp[i]=0;
    }
    for(int i=0;i<(n-k);i++){
        int j = arr[i]-first;
        supp[j]=1;
    }
    for(int i=0;i<len;i++){
        if(supp[i]==0){
            ris.push_back(first+i);
        }
    }

}