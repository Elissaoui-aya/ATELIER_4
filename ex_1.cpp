#include <iostream>
using namespace std;
 class Ressource{
protected:
    int id;
    char titre[20];
    char auteur[20];
    int annee;

public:
    Ressource(int i=0,const char*t ="",const char*a= "",int an=0){
        id=i;
        for(int j=0;j<19;j++){
          if (t[j]!='\0')
            titre[j]=t[j];
          else
            break;
        }
          titre[19]='\0';
        for(int j=0;j<19;j++){
          if(a[j]!='\0')
           auteur[j]=a[j];
          else
            break;
        }
          auteur[19]='\0';
        annee=an;
    };



    virtual void afficherInfos() const {
        cout <<"ID: "<< id <<",Titre: "<<titre
             <<",Auteur: "<< auteur <<",Année: "<<annee<< endl;
    }

    virtual void telecharger() const {
        cout << "Téléchargement des éléments de la ressource:" <<titre << endl;
    }
    int getId() const {return id;}
    const char* getTitre() const{return titre;}
    const char* getAuteur() const{return auteur;}
    int getAnnee() const {return annee;}

    bool operator==(const Ressource&autre) const {
        return id == autre.id;
    }
};

class Telechargeable {
public:
    virtual void telecharger() const {
        cout << "Téléchargement via Telechargeable" << endl;
    }

    void afficherMessage() const {
        cout << "Ressource prête à être téléchargée." << endl;
    }
};
class Livre : public Ressource, public Telechargeable {
    int nbPages;

public:
    Livre(int id, const char* t, const char* a, int an, int nb)
        : Ressource(id, t, a, an), nbPages(nb) {}

    void afficherInfos() const override {
        cout << "[Livre] ";
        Ressource::afficherInfos();
        cout << "Nombre de pages: " << nbPages << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement du livre : " << getTitre()
             <<"("<<nbPages<<"pages)"<< endl;
    }
};

class Magazine : public Ressource, public Telechargeable {
    int numero;

public:
    Magazine(int id, const char* t, const char* a, int an, int num)
        : Ressource(id, t, a, an), numero(num) {}

    void afficherInfos() const override {
        cout << "[Magazine] ";
        Ressource::afficherInfos();
        cout << "Numéro: " << numero << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement du magazine :"<< getTitre()
             <<"(n°"<< numero<<")"<<endl;
    }
};

class Video : public Ressource, public Telechargeable {
    double duree;

public:
    Video(int id, const char* t, const char* a, int an, double d)
        : Ressource(id, t, a, an), duree(d) {}

    void afficherInfos() const override{
        cout << "[Vidéo] ";
        Ressource::afficherInfos();
        cout <<"Durée: "<<duree<<" minutes" << endl;
    }

    void telecharger() const override {
        cout << "Téléchargement de la vidéo : " << getTitre()
             << " (" << duree << " min)" << endl;
    }
};
class Mediatheque {
    Ressource*ressources[10];
    int nb;//le nombre de ressources actuellement stockées dans la médiathèque

public:
    Mediatheque():nb(0){}

    void ajouter(Ressource* r) {
        if (nb < 10) {
            ressources[nb++] = r;
        } else
            cout << "Médiathèque pleine !" << endl;
        }

    void afficherToutes() const {
        cout << "le Contenu de la médiathèque:" << endl;
        for (int i=0; i< nb;i++) {
            ressources[i]->afficherInfos();
        }
    }

    void rechercher(const char* titre) const {
        cout << "Recherche par titre : "<< titre << endl;
        for (int i=0;i<nb;i++){
            const char*t= ressources[i]->getTitre();
            int j=0;
            bool identique=true;
            while (titre[j]!='\0'||t[j]!='\0'){
                if (titre[j]!= t[j]) {
                 identique = false;
                break;
                }
                j++;
            }
            if (identique)
              ressources[i]->afficherInfos();
        }
    }

    void rechercher(int annee) const {
        cout << "Recherche par année:" <<annee << endl;
        for (int i=0; i<nb;i++) {
            if(ressources[i]->getAnnee()==annee)
                ressources[i]->afficherInfos();
        }
    }

    void rechercher(const char* auteur, int annee) const {
        cout <<"Recherche par auteur et année : "<< auteur <<","<< annee << endl;
        for (int i=0;i<nb;i++){
            const char*a=ressources[i]->getAuteur();
            int j=0;
            bool identique =true;
            while (auteur[j]!='\0'||a[j]!='\0'){
                if (auteur[j]!=a[j]){
                  identique=false;
                break;
                 }
                j++;
            }
            if (identique && ressources[i]->getAnnee()==annee)
                ressources[i]->afficherInfos();
        }
    }
};
int main(){
    Livre l1(1, "POO_C++","EL IMRANI", 2023,550);
    Magazine m1(2,"DEV_WEB", "EL MRABET", 2022,27);
    Video v1(3, "BASE_DON", "ELKHALDI", 2021,90);

    l1.afficherInfos();
    m1.afficherInfos();
    v1.afficherInfos();

    cout << endl;
    l1.Telechargeable::afficherMessage();
    l1.telecharger();
    m1.telecharger();
    v1.telecharger();

    cout << endl;
    Livre l2(1, "POO_C++", "EL IMRANI", 2023,550);
    cout << "Comparaison l1 et l2 : "
         << ((l1 == l2) ? "Identiques" : "Différents") << endl;

    Mediatheque media;
    media.ajouter(&l1);
    media.ajouter(&m1);
    media.ajouter(&v1);

    media.afficherToutes();

    media.rechercher("DEV_WEB");
    media.rechercher(2022);
    media.rechercher("EL KHALDI", 2021);

    return 0;
}
