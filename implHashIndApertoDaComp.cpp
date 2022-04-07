#include "dizionario.hpp"
#include <vector>

constexpr int hashsize = 13;
constexpr int hashaux = 11;

using namespace std;

struct Elem{
    int key;
    int info;
    int index;
};

/* DEL e' un elemento fittizio che rappresenta un elemento cancellato */
struct Dizionario::Impl{
  vector<PElem> content;
  int numchiavi;
  PElem DEL;
};

int funHash(int val, int i){
  return (val%hashsize + i*(1+val%hashaux))%hashsize;
}


/*La complessità è data dal tempo necessario per inizializzare il vettore ed è quindi O(n).*/
/*post: costruisce un dizionario vuoto */
Dizionario::Dizionario():pimpl(new Impl{vector<PElem>(hashsize,nullptr),0,new Elem}){
}

/*La complessità è data dal numero di iterazioni del ciclo for  ed è quindi O(n) dove n è hashsize.*/
/*post: rimuove il dizionario */
Dizionario::~Dizionario(){
    for(int i=0;i<hashsize;i++){
        delete pimpl->content[i];
    }
    delete pimpl;
}    

/* La complessità è data dal numero di iterazioni del ciclo while che dipende dal numero di volte in cui risulta necessario ricalcolare il valore di hash.
 * Nel migliore dei casi la funzione termina alla prima iterazione e la complessità è O(1), nel caso peggiore le iterazioni proseguono fino a che la variabile i raggiunge il valore
 * di hashsize e la complessità è quindi O(n) dove n è hashsize. In media,assumendo il caso di hashing uniforme, è necessario ricalcolare il valore di hash non più di 1/(1-α) volte
 * e la complessità è O(1/(1-α)) dove per α si intente il valore del fattore di carico che è dato dal rapporto n/m tra il numero n di elementi e il numero m di slot presenti
 * nella tabella hash.*/
/*pre: k non e' presente nel dizionario*/
/*post: associa il valore val alla chiave k nel dizionario*/
void Dizionario::inserisci(int k, int val){
    int i = 0;
    while(i!=hashsize){
        int hash = funHash(k,i);
        if(pimpl->content[hash]==nullptr || pimpl->content[hash]==pimpl->DEL){
            PElem e = new Elem{k,val,hash};
            pimpl->content[hash]=e;
            pimpl->numchiavi++;
            return;
        }
        i++;
    }
}

/* Le operazioni richiedono un tempo costante e la complessità è quindi O(1).*/
/*pre: l'elemento x e' contenuto nel dizionario*/
/*post: rimuove l'elemento x dal dizionario */
void Dizionario::cancella(PElem x){
    int supp = x->index;
    delete x;
    pimpl->content[supp] = pimpl->DEL;
    pimpl->numchiavi--;
 }


/* La complessità è data dal numero di iterazioni del ciclo while che dipende dal numero di volte in cui risulta necessario ricalcolare il valore di hash.
 * Nel migliore dei casi la funzione termina alla prima iterazione e la complessità è O(1), nel caso peggiore le iterazioni proseguono fino a che la variabile i raggiunge il valore
 * di hashsize e la complessità è quindi O(n) dove n è hashsize. In media, assumendo il caso di hashing uniforme, è necessario ricalcolare il valore di hash non più di 1/(1-α) volte
 * e la complessità è  O(1/(1-α)) dove per α si intente il valore del fattore di carico che è dato dal rapporto n/m tra il numero n di elementi e il numero m di slot presenti nella tabella hash.*/
/*post: restituisce un elemento con chiave k se esiste, nullptr altrimenti */
PElem Dizionario::cerca(int k){
    int i = 0;
    int hash = funHash(k,i);
    PElem curr = pimpl->DEL;
    while(curr!=nullptr && i!=hashsize){
        int hash = funHash(k,i);
        PElem curr = pimpl->content[hash];
        if(curr->key==k){
            return curr;
        }
        i++;
    }
    return nullptr;
 }

/*Complessità costante O(1).*/
/*post: restituisce il numero di chiavi nel dizionario*/
int Dizionario::numChiavi(){
  return pimpl->numchiavi;
 }

/*Complessità costante O(1).*/
/*pre: l'elemento x e' contenuto nel dizionario */
/*post: restituisce la chiave di x*/
int Dizionario::leggiChiave(PElem x){
  return x->key;
}

/*Complessità costante O(1).*/
/*pre: l'elemento x e' contenuto nel dizionario */
/*post: restituisce il valore di x*/
int Dizionario::leggiInfo(PElem x){
    return x->info;
}

/*La complessità è data dal numero di iterazioni del ciclo for  ed è quindi O(n) dove n è hashsize.*/
/*post: stampa il contenuto del dizionario */
void Dizionario::stampa(){
    for(int i=0;i<hashsize;i++){
        if(pimpl->content[i]==nullptr){
            cout<<i<<": empty\n";
        }
        else if(pimpl->content[i]==pimpl->DEL){
            cout<<i<<": deleted\n";
        }
        else{
            cout<<i<<": (k:"<<pimpl->content[i]->key<<", v:"<<pimpl->content[i]->info<<")\n";
        }
    }
}    



