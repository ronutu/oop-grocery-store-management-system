#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

class IOinterface {
public:
    virtual istream& citire(istream& in)=0;
    virtual ostream& afisare(ostream& out)const=0;
};

class Pizzerie: public IOinterface {
protected:
    const int id;

    string locatie, dataFondarii, fondator;
    int clienti;
    static int contor;
public:
    Pizzerie(): id(contor++) {
        this->locatie = "anonim";
        this->dataFondarii = "00/00/0000";
        this->fondator = "anonim";
        this->clienti = 0;
    }

    Pizzerie(string locatie, string dataFondarii, string fondator, int clienti): id(contor++) {
        this->locatie = locatie;
        this->dataFondarii = dataFondarii;
        this->fondator = fondator;
        this->clienti = clienti;
    }

    Pizzerie(const Pizzerie& p): id(p.contor) {
        this->locatie = p.locatie;
        this->dataFondarii = p.dataFondarii;
        this->fondator = p.fondator;
        this->clienti = p.clienti;
    }

    Pizzerie& operator = (const Pizzerie& p) {
        if(this != &p) {
            this->locatie = p.locatie;
            this->dataFondarii = p.dataFondarii;
            this->fondator = p.fondator;
            this->clienti = p.clienti;
        }
        return *this;
    }

    istream& citire(istream& in) {
        cout << "Introdu locatia:\n";
        in >> this->locatie;
        cout << "Introdu data fondarii:\n";
        in >> this->dataFondarii;
        cout << "Introdu numele fondatorului:\n";
        in >> this->fondator;
        cout << "Introdu cati clienti are in medie aceasta pizzerie pe zi:\n";
        in >> this->clienti;
        return in;
    }

    friend istream& operator >> (istream& in, Pizzerie& p) {
        return p.citire(in);
    }

    ostream& afisare(ostream& out)const {
        out << "Locatie: " << this->locatie << endl;
        out << "Data fondarii: " << this->dataFondarii << endl;
        out << "Fondator: " << this->fondator << endl;
        out << "Clienti: " << this->clienti << endl;
        return out;
    }

    friend ostream& operator << (ostream& out, const Pizzerie& p) {
        return p.afisare(out);
    }

    const int getId() {
        return this->id;
    }

    virtual void setFondator(string fondator) {
        this->fondator = fondator;
    }

    int getClienti() {
        return this->clienti;
    }

    string getLocatie() {
        return this->locatie;
    }

    int getNrOspatari() {}

    string getFondator() {
        return this->fondator;
    }

    ~Pizzerie() {}
};
int Pizzerie::contor = 0;

class PizzerieTerasa: public Pizzerie {
protected:
    int nrOspatari;
public:
    PizzerieTerasa(): Pizzerie() {
        this->nrOspatari = 0;
    }

    PizzerieTerasa(string locatie, string dataFondarii, string fondator, int clienti, int nrOspatari): Pizzerie(locatie, dataFondarii, fondator, clienti) {
        this->nrOspatari = nrOspatari;
    }

    PizzerieTerasa(const PizzerieTerasa& p): Pizzerie(p) {
        this->nrOspatari = p.nrOspatari;
    }

    PizzerieTerasa& operator = (const PizzerieTerasa& p) {
        if(this != &p) {
            Pizzerie::operator=(p);
            this->nrOspatari = p.nrOspatari;
        }
        return *this;
    }

    istream& citire(istream& in) {
        Pizzerie::citire(in);
        cout << "Introdu cati ospatari sunt:\n";
        in >> this->nrOspatari;
        return in;
    }

    ostream& afisare(ostream& out)const {
        Pizzerie::afisare(out);
        out << "Numar ospatari: " << this->nrOspatari << endl;
        return out;
    }

    int getNrOspatari() {
        return this->nrOspatari;
    }

};

class PizzerieFull: public PizzerieTerasa {
private:
    int nrLivratori;
public:
   PizzerieFull(): PizzerieTerasa() {
       this->nrLivratori = 0;
   }

   PizzerieFull(string locatie, string dataFondarii, string fondator, int clienti, int capacitate, int nrLivratori): PizzerieTerasa(locatie, dataFondarii, fondator, clienti, capacitate) {
       this->nrLivratori = nrLivratori;
   }

   PizzerieFull(const PizzerieFull& p): PizzerieTerasa(p) {
       this->nrLivratori = p.nrLivratori;
    }

   PizzerieFull& operator = (const PizzerieFull& p) {
       if(this != &p) {
            PizzerieTerasa::operator=(p);
            this->nrLivratori = p.nrLivratori;
       }
       return *this;
   }

   istream& citire(istream& in) {
       PizzerieTerasa::citire(in);
       cout << "Introdu cati livratori sunt:\n";
       in >> this->nrLivratori;
       return in;
   }

  ostream& afisare(ostream& out)const {
      PizzerieTerasa::afisare(out);
      out << "Numar livratori: " << this->nrLivratori << endl;
  }
};

template <class T>
float profit(T pizzerie) {
        return 30 * (pizzerie.getClienti() * 40 - 0.03 * pizzerie.getClienti() * 40 * pizzerie.getNrOspatari());
}

template <class T1, class T2>
void compara(T1 pizzerie1, T2 pizzerie2) {
    if(profit(pizzerie1) > profit(pizzerie2))
        cout << "Prima pizzerie are profitul mai mare.\n";
    else if(profit(pizzerie1) < profit(pizzerie2))
        cout << "A doua pizzerie are profitul mai mare.\n";
    else
        cout << "Cele 2 pizzerii au profitul egal.\n";
}

template<typename key, typename value>
ostream &operator<<(ostream &stream, const map<key, value> &myMap) {
    for(const pair<key, value >&t:myMap) {
        stream << t.first<< " " << t.second<< " "<<endl;
    }
    return stream;
}

class Meniu {
private:
    static Meniu *ob;
public:
    static Meniu* getInstance(){
        if(!ob)
            ob = new Meniu();
        return ob;
    }

    void start(){
        vector<Pizzerie*> vectorPizzerii;
        list<string> listaFondatori;
        set<string> setOrase;
        set<int> setClienti;
        map<string, int> mapaOraseSiClienti;
        int i = 1;
        while(i == 1) {
            cout << "\t0 - Inchide aplicatia\n";
            cout << "\t1 - Adauga o pizzerie doar cu terasa\n";
            cout << "\t2 - Adauga o pizzerie si cu terasa si cu livrare\n";
            cout << "\t3 - Afiseaza toate pizzeriile\n";
            cout << "\t4 - Afiseaza profitul mediu al unei pizzerii intr-o luna\n";
            cout << "\t5 - Compara profitul a 2 pizzerii\n";
            cout << "\t6 - Afiseaza toti fondatorii\n";
            cout << "\t7 - Afiseaza toate orasele in care exista pizzerii\n";
            cout << "\t8 - Afiseaza cati clienti sunt in fiecare oras\n";

            int a;
            cin >> a;
            switch(a){
                case 0: {
                    i = 0;
                    break;
                }
                case 1: {
                    PizzerieTerasa p;
                    cin >> p;
                    vectorPizzerii.push_back(new PizzerieTerasa(p));
                    listaFondatori.push_back(p.getFondator());
                    setOrase.insert(p.getLocatie());
                    mapaOraseSiClienti[p.getLocatie()] = p.getClienti();
                    break;
                }
                case 2: {
                    PizzerieFull p;
                    cin >> p;
                    vectorPizzerii.push_back(new PizzerieFull(p));
                    listaFondatori.push_back(p.getFondator());
                    setOrase.insert(p.getLocatie());
                    setClienti.insert(p.getClienti());
                    mapaOraseSiClienti[p.getLocatie()] = p.getClienti();
                    break;
                }
                case 3: {
                    vector<Pizzerie*>::iterator it;
                    for(it = vectorPizzerii.begin(); it != vectorPizzerii.end(); it++)
                        cout << (**it).getId() << ". " << **it << endl;
                    break;
                }
                case 4: {
                    vector<Pizzerie*>::iterator it;
                    for(it = vectorPizzerii.begin(); it != vectorPizzerii.end(); it++)
                        cout << (**it).getId() << ". " << **it << endl;
                    cout << "Introdu numarul pizzeriei la care vrei sa vezi profitul:\n";
                    int nr;
                    cin >> nr;
                    cout << "Profitul pizzeriei cu numarul " << nr << " este " << profit(*vectorPizzerii[nr-1]) << " lei." << endl << endl;
                    break;
                }
                case 5: {
                    vector<Pizzerie*>::iterator it;
                    for(it = vectorPizzerii.begin(); it != vectorPizzerii.end(); it++)
                        cout << (**it).getId() << ". " << **it << endl;
                    cout << "Introdu numerele pizzeriilor pe care vrei sa le compari:\n";
                    int nr1, nr2;
                    cin >> nr1 >> nr2;
                    compara(*vectorPizzerii[nr1-1], *vectorPizzerii[nr2-1]);
                    break;
                }
                case 6: {
                    list<string>::iterator it;
                    for(it = listaFondatori.begin(); it != listaFondatori.end(); it++)
                        cout << *it << endl;
                    break;
                }
                case 7: {
                    for(auto it=setOrase.begin(); it!= setOrase.end(); it++)
                        cout << *it << endl;
                    break;
                }
                case 8: {
                    cout<<mapaOraseSiClienti;
                    break;
                }
            }
        }
    }
};
Meniu* Meniu::ob=0;

int main()
{
    Meniu* menu = menu->getInstance();
    menu->start();
    return 0;
}
