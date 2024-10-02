#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

class IOinterface
{
public:
    virtual istream &read(istream &in) = 0;
    virtual ostream &write(ostream &out) const = 0;
};

class Store : public IOinterface
{
protected:
    const int id;

    string city, foundingDate, founderName;
    int numberOfClients;
    static int counter;

public:
    Store() : id(counter++)
    {
        this->city = "anonim";
        this->foundingDate = "00/00/0000";
        this->founderName = "anonim";
        this->numberOfClients = 0;
    }

    Store(string city, string foundingDate, string founderName, int numberOfClients) : id(counter++)
    {
        this->city = city;
        this->foundingDate = foundingDate;
        this->founderName = founderName;
        this->numberOfClients = numberOfClients;
    }

    Store(const Store &p) : id(p.counter)
    {
        this->city = p.city;
        this->foundingDate = p.foundingDate;
        this->founderName = p.founderName;
        this->numberOfClients = p.numberOfClients;
    }

    Store &operator=(const Store &p)
    {
        if (this != &p)
        {
            this->city = p.city;
            this->foundingDate = p.foundingDate;
            this->founderName = p.founderName;
            this->numberOfClients = p.numberOfClients;
        }
        return *this;
    }

    istream &read(istream &in)
    {
        cout << "City:\n";
        in >> this->city;
        cout << "Founding date:\n";
        in >> this->foundingDate;
        cout << "Founder name:\n";
        in >> this->founderName;
        cout << "Number of clients:\n";
        in >> this->numberOfClients;
        return in;
    }

    friend istream &operator>>(istream &in, Store &p)
    {
        return p.read(in);
    }

    ostream &write(ostream &out) const
    {
        out << "City: " << this->city << endl;
        out << "Founding date: " << this->foundingDate << endl;
        out << "Founder Name: " << this->founderName << endl;
        out << "Number Of Clients: " << this->numberOfClients << endl;
        return out;
    }

    friend ostream &operator<<(ostream &out, const Store &p)
    {
        return p.write(out);
    }

    const int getId()
    {
        return this->id;
    }

    virtual void setfounderName(string founderName)
    {
        this->founderName = founderName;
    }

    int getNumberOfClients()
    {
        return this->numberOfClients;
    }

    string getCity()
    {
        return this->city;
    }

    virtual int getNumberOfVeganProducts() {
        return 0;
    }

    string getFounderName()
    {
        return this->founderName;
    }

    ~Store() {}
};
int Store::counter = 0;

class VeganStore : public Store
{
protected:
    int numberOfVeganProducts;

public:
    VeganStore() : Store()
    {
        this->numberOfVeganProducts = 0;
    }

    VeganStore(string city, string foundingDate, string founderName, int numberOfClients, int numberOfVeganProducts) : Store(city, foundingDate, founderName, numberOfClients)
    {
        this->numberOfVeganProducts = numberOfVeganProducts;
    }

    VeganStore(const VeganStore &p) : Store(p)
    {
        this->numberOfVeganProducts = p.numberOfVeganProducts;
    }

    VeganStore &operator=(const VeganStore &p)
    {
        if (this != &p)
        {
            Store::operator=(p);
            this->numberOfVeganProducts = p.numberOfVeganProducts;
        }
        return *this;
    }

    istream &read(istream &in)
    {
        Store::read(in);
        cout << "Number of vegan products:\n";
        in >> this->numberOfVeganProducts;
        return in;
    }

    ostream &write(ostream &out) const
    {
        Store::write(out);
        out << "Number of vegan products: " << this->numberOfVeganProducts << endl;
        return out;
    }

    int getNumberOfVeganProducts()
    {
        return this->numberOfVeganProducts;
    }
};

class OnlineVeganStore : public VeganStore
{
private:
    int deliveryRadius;

public:
    OnlineVeganStore() : VeganStore()
    {
        this->deliveryRadius = 0;
    }

    OnlineVeganStore(string city, string foundingDate, string founderName, int numberOfClients, int capacitate, int deliveryRadius) : VeganStore(city, foundingDate, founderName, numberOfClients, capacitate)
    {
        this->deliveryRadius = deliveryRadius;
    }

    OnlineVeganStore(const OnlineVeganStore &p) : VeganStore(p)
    {
        this->deliveryRadius = p.deliveryRadius;
    }

    OnlineVeganStore &operator=(const OnlineVeganStore &p)
    {
        if (this != &p)
        {
            VeganStore::operator=(p);
            this->deliveryRadius = p.deliveryRadius;
        }
        return *this;
    }

    istream &read(istream &in)
    {
        VeganStore::read(in);
        cout << "Delivery radius:\n";
        in >> this->deliveryRadius;
        return in;
    }

    ostream &write(ostream &out) const
    {
        VeganStore::write(out);
        out << "Delivery radius: " << this->deliveryRadius << endl;
        return out;
    }
};

template <class T>
float calculateStoreProfit(T store)
{
    return 30 * (store.getNumberOfClients() * 40 - 0.03 * store.getNumberOfClients() * 40 * store.getNumberOfVeganProducts());
}

template <class T1, class T2>
void compareStoreProfit(T1 store1, T2 store2)
{
    if (calculateStoreProfit(store1) > calculateStoreProfit(store2))
        cout << "The first grocery store has a higher profit.\n";
    else if (calculateStoreProfit(store1) < calculateStoreProfit(store2))
        cout << "The second grocery store has a higher profit.\n";
    else
        cout << "Both grocery stores have the same profit.\n";
}

template <typename key, typename value>
ostream &operator<<(ostream &stream, const map<key, value> &myMap)
{
    for (const pair<key, value> &t : myMap)
    {
        stream << t.first << " " << t.second << " " << endl;
    }
    return stream;
}

class displayMenu
{
private:
    static displayMenu *ob;

public:
    static displayMenu *getInstance()
    {
        if (!ob)
            ob = new displayMenu();
        return ob;
    }

    void start()
    {
        vector<Store *> storeVector;
        list<string> founderNameList;
        set<string> citySet;
        set<int> numberOfClientsSet;
        map<string, int> citiesAndNumberOfClientsMap;
        int i = 1;
        while (i == 1)
        {
            cout << "\t0 - Exit\n";
            cout << "\t1 - Add a vegan store\n";
            cout << "\t2 - Add an online vegan store\n";
            cout << "\t3 - Display all store\n";
            cout << "\t4 - Display the average profit of a store in a month\n";
            cout << "\t5 - Compare 2 stores\n";
            cout << "\t6 - Display all the founders\n";
            cout << "\t7 - Display all the cities where there are stores\n";
            cout << "\t8 - Display the number of clients from every city\n";

            int a;
            cin >> a;
            switch (a)
            {
            case 0:
            {
                i = 0;
                break;
            }
            case 1:
            {
                VeganStore p;
                cin >> p;
                storeVector.push_back(new VeganStore(p));
                founderNameList.push_back(p.getFounderName());
                citySet.insert(p.getCity());
                citiesAndNumberOfClientsMap[p.getCity()] = p.getNumberOfClients();
                break;
            }
            case 2:
            {
                OnlineVeganStore p;
                cin >> p;
                storeVector.push_back(new OnlineVeganStore(p));
                founderNameList.push_back(p.getFounderName());
                citySet.insert(p.getCity());
                numberOfClientsSet.insert(p.getNumberOfClients());
                citiesAndNumberOfClientsMap[p.getCity()] = p.getNumberOfClients();
                break;
            }
            case 3:
            {
                vector<Store *>::iterator it;
                for (it = storeVector.begin(); it != storeVector.end(); it++)
                    cout << (**it).getId() << ". " << **it << endl;
                break;
            }
            case 4:
            {
                vector<Store *>::iterator it;
                for (it = storeVector.begin(); it != storeVector.end(); it++)
                    cout << (**it).getId() << ". " << **it << endl;
                cout << "Enter a shop number to view its profit:\n";
                int nr;
                cin >> nr;
                cout << "Shop " << nr << " has a profit of " << calculateStoreProfit(*storeVector[nr - 1]) << "$." << endl
                     << endl;
                break;
            }
            case 5:
            {
                vector<Store *>::iterator it;
                for (it = storeVector.begin(); it != storeVector.end(); it++)
                    cout << (**it).getId() << ". " << **it << endl;
                cout << "Enter the numbers of the two shops you want to compare:\n";
                int nr1, nr2;
                cin >> nr1 >> nr2;
                compareStoreProfit(*storeVector[nr1 - 1], *storeVector[nr2 - 1]);
                break;
            }
            case 6:
            {
                list<string>::iterator it;
                for (it = founderNameList.begin(); it != founderNameList.end(); it++)
                    cout << *it << endl;
                break;
            }
            case 7:
            {
                for (auto it = citySet.begin(); it != citySet.end(); it++)
                    cout << *it << endl;
                break;
            }
            case 8:
            {
                cout << citiesAndNumberOfClientsMap;
                break;
            }
            }
        }
    }
};
displayMenu *displayMenu::ob = 0;

int main()
{
    displayMenu *menu = menu->getInstance();
    menu->start();
    return 0;
}
