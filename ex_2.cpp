#include <iostream>
using namespace std;
  class Client{
private:
    char nom[40];
    char CIN[20];
    int idC;

public:
    Client(const char*N="",const char*C="",int ID=0){
        for(int i=0; i< 39;i++){
            if (N[i]!='\0')
                nom[i]=N[i];
            else {
             nom[i]='\0';
            break;
            }
        }
        for(int i =0;i<19;i++){
            if (C[i]!='\0')
                CIN[i]=C[i];
            else {
                 CIN[i]='\0';
            break;
            }
        }
        idC =ID;
    }
    void afficherInfos() const {
        cout<<"Client:"<<nom<<",CIN:"<<CIN<<",ID:"<<idC<< endl;
    }
    friend class CompteBancaire;
    friend class Banque;
    friend class AgentBancaire;
};

  class CompteBancaire{
 private:
    int numCompte;
    double solde;
    int codeSecret;
    Client*proprietaire;

 public:
    CompteBancaire(int num =0, double S=0.0,int code=0, Client*C=nullptr){
        numCompte = num;
        solde = S;
        codeSecret = code;
        proprietaire = C;
    }

    void deposer(double montant){
        if (montant>0) {
            solde += montant;
            cout <<"Dépôt de"<<montant<<"effectué. le Nouveau solde:"<<solde<< endl;
        }
    }

    void retirer(double montant) {
        if (montant <= solde && montant>0){
            solde -= montant;
            cout <<"Retrait de "<<montant<<" effectué. le Nouveau solde: "<<solde<< endl;
        } else{
            cout <<"Retrait impossible : solde insuffisant." << endl;
        }
    }

    void afficherPublic() const {
        cout <<"Compte n°:"<<numCompte<< " - Solde:"<<solde<< endl;
    }
    friend class AgentBancaire;
    friend class Banque;
};

  class AgentBancaire {
 private:
    char nom[30];
    int idAgent;

 public:
    AgentBancaire(const char* N="",int id=0) {
        for (int i=0;i<29;i++){
            if (N[i]!='\0')
             nom[i]=N[i];
            else {
             nom[i] ='\0';
             break;
             }
        }
        idAgent = id;
    }

    void afficherInfos() const {
        cout <<"Agent: "<<nom<<"(ID:"<<idAgent<<")"<< endl;
    }

    void consulterCodeSecret(const CompteBancaire&C) const{
        cout <<"Agent autorisé - Code secret du compte "<< C.numCompte <<":" << C.codeSecret<< endl;
    }

    void transfert(CompteBancaire &source,CompteBancaire &dest, double montant) const {
        cout << " Transfert de:" << montant << " du compte: " << source.numCompte << " vers le compte "<< dest.numCompte<< endl;
        if (montant > 0 && source.solde >= montant) {
            source.solde -= montant;
            dest.solde += montant;
            cout << "Transfert réussi." << endl;
        } else {
            cout << "Transfert échoué (solde insuffisant)." << endl;
        }
    }

    friend class Banque;
};
  class Banque {
private:
    CompteBancaire*comptes[10];
    Client*clients[10];
    int nbClients;
    int nbComptes;

public:
    Banque(){
        nbClients=0;
        nbComptes=0;
    }

    void ajouterClient(Client*C){
        if(nbClients < 10){
            clients[nbClients++]=C;
        }
    }

    void ajouterCompte(CompteBancaire*C){
        if (nbComptes < 10){
            comptes[nbComptes++]=C;
        }
    }

    void afficherTousLesComptes() const {
        cout << "Liste des comptes " << endl;
        for (int i = 0; i< nbComptes; i++) {
            comptes[i]->afficherPublic();
        }
    }

    void auditInterne() const {
        cout << "Audit interne confidentiel " << endl;
        for (int i=0; i < nbComptes; i++) {
            CompteBancaire*C= comptes[i];
            cout << "Compte n°:" << C->numCompte<< "_ Solde: " << C->solde<< " _ Code secret: " << C->codeSecret << endl;
            cout << "- Propriétaire: " << C->proprietaire->nom<< " (" << C->proprietaire->CIN << ")\n";
        }
    }
};

int main() {

    Client c1("MOKHLISS", "LIN123",1);
    Client c2("SONDOUS", "LKG456", 2);

    CompteBancaire compte1(1001,5000.0, 1111, &c1);
    CompteBancaire compte2(1002, 9000.0, 2222, &c2);

    AgentBancaire agent("AHMED",10);
    Banque banque;

    banque.ajouterClient(&c1);
    banque.ajouterClient(&c2);
    banque.ajouterCompte(&compte1);
    banque.ajouterCompte(&compte2);

    banque.afficherTousLesComptes();

    cout << endl;
    compte1.deposer(3500);
    compte2.retirer(700);

    agent.transfert(compte1, compte2, 2500);
    agent.consulterCodeSecret(compte1);

    banque.auditInterne();
return 0;
}
