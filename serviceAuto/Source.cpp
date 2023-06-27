#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <list>
#include <map>
using namespace std;

class Exceptie
{
    string mesajExceptie;

public:
    Exceptie(string mesajExceptie)
    {
        this->mesajExceptie = mesajExceptie;
    }

    string getMesajExceptie()
    {
        return mesajExceptie;
    }
};

enum ClasaMasina { Mica, Mare, SUV, Toate };

class afisabil
{
public:
    //metoda virtuala pura
    virtual void afiseaza() = 0;
};

class detaliabil
{
public:
    virtual float detalii() = 0;
};

//cls abstracta
class Persoana : public afisabil
{
private:
    string nume;
    string prenume;
    string telefon;
public:
    Persoana()
    {
        nume = "Anonim";
        prenume = "Anonimus";
        telefon = "0000000000";
    }
    Persoana(string nume, string prenume, string telefon)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->telefon = telefon;
    }
    Persoana(string nume, string prenume)
    {
        this->nume = nume;
        this->prenume = prenume;
        telefon = "fara numar";
    }
    Persoana(const Persoana& p)
    {
        this->nume = p.nume;
        this->prenume = p.prenume;
        this->telefon = p.telefon;
    }
    virtual string getNume() const
    {
        return this->nume;
    }
    virtual void setNume(const string& nnou)
    {
        //        if(nnou > "a")
        nume = nnou;
        //        else
        //            throw Exceptie("Nu se poate modifica numele");
    }
    virtual string getPrenume() const
    {
        return prenume;
    }
    virtual void setPrenume(const string& p)
    {
        //        if(p.length() > 2)
        prenume = p;
        //        else
        //            throw Exceptie("Nu se poate modifica prenumele");
    }
    virtual string getTelefon() const
    {
        return telefon;
    }
    virtual void setTelefon(const string& t)
    {
        //        if(t.length() == 10)
        telefon = t;
        //        else
        //            throw Exceptie("Numar de telefon invalid!");
    }

    virtual string pozitie() = 0;
    virtual float procent() = 0;
    void afiseaza() override
    {
        cout << endl << "Nume si Prenume: " << nume << " " << prenume << endl << "Telefon: " << telefon;
    }
    friend ostream& operator<<(ostream& os, Persoana& p)
    {
        os << "Nume: " << p.nume << "\nPrenume: " << p.prenume << "\nTelefon: " << p.telefon << endl;
        return os;
    }
    virtual istream& read(istream&) = 0;
    friend ofstream& operator<<(ofstream& out, Persoana& p)
    {
        out << p.nume << "\n" << p.prenume << "\n" << p.telefon << "\n";
        return out;
    }
    virtual ifstream& read(ifstream&) = 0;

};

class Interventie : public detaliabil, public afisabil
{
private:
    ClasaMasina tipMasina;
    char* denumire;
    int cost;
    int durata; //zile
public:
    Interventie()
    {
        tipMasina = Toate;
        denumire = new char[strlen("necunoscut") + 1];
        strcpy(denumire, "necunoscut");
        cost = 0;
        durata = 0;
    }
    Interventie(ClasaMasina tipMasina, const char* denumire, int cost, int durata)
    {
        this->tipMasina = tipMasina;
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
        this->cost = cost;
        this->durata = durata;
    }
    Interventie(const Interventie& i)
    {
        this->tipMasina = i.tipMasina;
        this->denumire = new char[strlen(i.denumire) + 1];
        strcpy(this->denumire, i.denumire);
        this->cost = i.cost;
        this->durata = i.durata;
    }
    Interventie operator=(const Interventie& i)
    {
        this->tipMasina = i.tipMasina;
        if (this->denumire != NULL)
            delete[] this->denumire;
        this->denumire = new char[strlen(i.denumire) + 1];
        strcpy(this->denumire, i.denumire);
        this->cost = i.cost;
        this->durata = i.durata;
        return *this;
    }
    Interventie(const char* denumire, int cost, int durata)
    {
        tipMasina = Toate;
        this->denumire = new char[strlen(denumire) + 1];
        strcpy(this->denumire, denumire);
        this->cost = cost;
        this->durata = durata;
    }
    ~Interventie()
    {
        if (denumire != NULL)
            delete[] denumire;
    }
    //get si set
    ClasaMasina getTipMasina()
    {
        return tipMasina;
    }
    void setTipMasina(ClasaMasina c)
    {
        tipMasina = c;
    }
    char* getDenumire()
    {
        return denumire;
    }
    void setDenumire(const char* d)
    {
        if (strlen(d) > 3)
        {
            if (denumire != NULL)
                delete[] denumire;
            denumire = new char[strlen(d) + 1];
            strcpy(denumire, d);
        }
        else
            throw Exceptie("Denumirea este prea mica!");
    }
    int getCost()
    {
        return cost;
    }
    void setCost(int c)
    {
        if (c == cost)
            throw Exceptie("Nu se poate modifica!");
        else
            cost = c;
    }
    int getDurata()
    {
        return durata;
    }
    void setDurata(int d)
    {
        if (d != durata)
            durata = d;
        else
            throw Exceptie("Nu se poate modifica!");
    }
    friend ostream& operator<<(ostream& os, const Interventie& i)
    {
        os << "\nTip masina: ";
        switch (i.tipMasina)
        {
        case 0: os << "Mica" << endl; break;
        case 1: os << "Mare" << endl; break;
        case 2: os << "SUV" << endl; break;
        case 3: os << "Toate" << endl; break;
        default: break;
        }
        os << "Denumire: " << i.denumire;
        os << "\nCost: " << i.cost << "\nDurata: " << i.durata << " zile";
        return os;
    }
    friend istream& operator>>(istream& is, Interventie& i)
    {
        int aux;
        cout << "Tip Masina(0-Mica, 1-Mare, 2-SUV, 3-Toate): ";
        is >> aux;
        switch (aux)
        {
        case 0: i.tipMasina = Mica; break;
        case 1: i.tipMasina = Mare; break;
        case 2: i.tipMasina = SUV; break;
        case 3: i.tipMasina = Toate; break;
        default: break;
        };
        cout << "Denumirea interventiei: ";
        string a;
        is.ignore();
        getline(is, a);
        if (a.length() > 3) {
            if (i.denumire != nullptr)
                delete[] i.denumire;
            i.denumire = new char[a.length() + 1];
            strcpy(i.denumire, a.c_str());
        }
        else
            cout << "nume invalid";
        cout << "Cost: ";
        float c;
        is >> c;
        i.cost = c;
        int d;
        cout << "Durata: ";
        is >> d;
        i.durata = d;
        return is;
    }
    Interventie operator+=(const Interventie& i)
    {
        this->cost += i.cost;
        return *this;
    }
    Interventie operator++()
    {
        this->durata++;
        return *this;
    }
    Interventie operator++(int)
    {
        Interventie aux = *this;
        this->durata++;
        return aux;
    }
    bool operator==(Interventie i)
    {
        if (this->durata == i.durata && this->cost == i.cost && this->tipMasina == i.tipMasina && strcmp(this->denumire, i.denumire) == 0)
            return true;
        else
            return false;
    }
    bool operator>=(Interventie i)
    {
        if (this->cost >= i.cost)
            return true;
        else
            return false;
    }
    float detalii() override
    {
        //cost pe zi
        return (cost, durata);
    }
    void afiseaza() override
    {
        cout << "Denumire: " << denumire << "\nCost: " << cost;
    }
    //metode
    float manopera()
    {
        return cost * 0.5;
    }
    float ziLucrata()
    {
        return cost / durata;
    }
    bool verficaTip(ClasaMasina c)
    {
        if (tipMasina == c)
            return 1;
        else
            return 0;
    }

    friend ofstream& operator<<(ofstream& out, const Interventie& i)
    {
        out << i.tipMasina << "\n" << i.denumire << "\n" << i.cost << "\n" << i.durata;
        return out;
    }
    friend ifstream& operator>>(ifstream& in, Interventie& i)
    {
        int aux;
        in >> aux;
        switch (aux)
        {
        case 0: i.tipMasina = Mica; break;
        case 1: i.tipMasina = Mare; break;
        case 2: i.tipMasina = SUV; break;
        case 3: i.tipMasina = Toate; break;
        default: break;
        };
        string a;
        in.ignore();
        getline(in, a);
        if (i.denumire != nullptr)
            delete[] i.denumire;
        i.denumire = new char[a.length() + 1];
        strcpy(i.denumire, a.c_str());
        in >> i.cost;
        in >> i.durata;
        return in;
    }
};

class Masina : public afisabil
{
private:
    ClasaMasina clasa;
    string nrInmatriculare;
    char* marca;
    int anMasina;
    long kmRulati;
    string telefon;
    Interventie* interv;
    int* achitat;
    int nrInterventii;
    float dePlata;
public:
    Masina(ClasaMasina clasa, string nrInmatriculare, const char* marca, int anMasina, long kmRulati, int nrInterv, const Interventie* interv, int* achitat, string telefon)
    {
        this->clasa = clasa;
        this->nrInmatriculare = nrInmatriculare;
        this->marca = new char[strlen(marca) + 1];
        strcpy(this->marca, marca);
        this->anMasina = anMasina;
        this->kmRulati = kmRulati;
        this->telefon = telefon;
        this->nrInterventii = nrInterv;
        float aux = 0;
        if (nrInterv > 0)
        {
            this->interv = new Interventie[nrInterv];
            for (int i = 0; i < nrInterv;i++)
                this->interv[i] = interv[i];
            this->achitat = new int[this->nrInterventii];
            for (int i = 0; i < this->nrInterventii;i++)
            {
                this->achitat[i] = achitat[i];
            }
        }
    }
    Masina(ClasaMasina clasa, string nrInmatriculare, const char* marca, int anMasina, string telefon)
    {
        this->clasa = clasa;
        this->nrInmatriculare = nrInmatriculare;
        this->marca = new char[strlen(marca) + 1];
        strcpy(this->marca, marca);
        this->anMasina = anMasina;
        this->kmRulati = 0;
        this->telefon = telefon;
        this->nrInterventii = 0;
        this->interv = nullptr;
        this->achitat = nullptr;
    }
    Masina(string telefon, string nrInmatriculare)
    {
        this->clasa = Toate;
        this->nrInmatriculare = nrInmatriculare;
        this->marca = new char[strlen("Necunoscut") + 1];
        strcpy(this->marca, marca);
        this->anMasina = 1990;
        this->kmRulati = 0;
        this->telefon = telefon;
        this->nrInterventii = 0;
        this->interv = nullptr;
        this->achitat = nullptr;
    }
    Masina()
    {
        clasa = Mica;
        nrInmatriculare = "fara";
        this->marca = new char[strlen("Anonim") + 1];
        strcpy(this->marca, "Anonim");
        this->anMasina = 2000;
        this->kmRulati = 0;
        this->telefon = "00";
        this->nrInterventii = 0;
        this->interv = nullptr;
        this->achitat = nullptr;
    }
    ClasaMasina getClasa()
    {
        return clasa;
    }
    void setClasa(ClasaMasina c)
    {
        clasa = c;
    }
    string getNrInmatriculare()
    {
        return nrInmatriculare;
    }
    void setNrInmatriculare(string a)
    {
        if (a.length() == 9 && a != "B-00-AAA")
            nrInmatriculare = a;
        else
            throw Exceptie("Numar de inmatriculare invalid!");
    }
    char* getMarca()
    {
        return marca;
    }
    void setMarca(const char* m)
    {
        if (strlen(m) >= 3)
        {
            if (marca != NULL)
            {
                delete[] marca;
            }
            marca = new char[strlen(m) + 1];
            strcpy(marca, m);
        }
        else
            throw Exceptie("Nume Incorect!");
    }
    int getAnMasina()
    {
        return anMasina;
    }
    void setAnMasina(int an)
    {
        if (anMasina == 0 || an > 1900)
            anMasina = an;
        else
            throw Exceptie("Anul este invalid!");
    }
    long getKmRulati()
    {
        return kmRulati;
    }
    void setKm(long km)
    {
        if (km > kmRulati)
            kmRulati = km;
        else
            throw Exceptie("Kilometrajul nu se poate da inapoi!");
    }
    string getTelefon()
    {
        return telefon;
    }
    void setTelefon(string t)
    {
        if (t.length() >= 8)
            telefon = t;
        else
            throw Exceptie("Numar de telefon invalid!");
    }
    int getNrInterventii()
    {
        return nrInterventii;
    }
    Interventie getInterventie(int index)
    {
        if (index >= 0 && index < nrInterventii)
            return interv[index];
        else
            throw Exceptie("Index masina invalid!");
    }
    int* getAchitat()
    {
        return achitat;
    }
    float getCost(int i)
    {
        return interv[i].getCost();
    }
    char* getDenumire(int i)
    {
        return interv[i].getDenumire();
    }
    int getDurata(int i)
    {
        return interv[i].getDurata();
    }
    void setDurata(int d, int i)
    {
        if (d > 0)
            interv[i].setDurata(d);
        else
            throw Exceptie("Durata invalida");
    }
    //n-nr elem
    void setAchitat(const int* a, int n)
    {
        if (n == nrInterventii && achitat != 0)
        {
            delete[] achitat;
            achitat = new int[n];
            for (int i = 0; i < n; i++)
                achitat[i] = a[i];
        }
        else
            throw Exceptie("Istoric plati invalid!");

    }

    ~Masina()
    {
        //        if(strlen(this->marca) != 0)
        delete[] marca;
        if (nrInterventii > 0)
        {
            delete[] interv;
            delete[] achitat;
        }
    }
    Masina(const Masina& m)
    {
        this->clasa = m.clasa;
        this->nrInmatriculare = m.nrInmatriculare;
        if (m.marca)
        {
            this->marca = new char[strlen(m.marca) + 1];
            strcpy(this->marca, m.marca);
        }
        else
        {
            this->marca = new char[strlen("Anonim") + 1];
            strcpy(this->marca, "Anonim");
        }
        this->anMasina = m.anMasina;
        this->kmRulati = m.kmRulati;
        this->telefon = m.telefon;
        this->nrInterventii = m.nrInterventii;
        if (m.nrInterventii > 0)
        {
            this->interv = new Interventie[m.nrInterventii];
            for (int i = 0; i < m.nrInterventii;i++)
                this->interv[i] = m.interv[i];
        }
        this->achitat = new int[this->nrInterventii];
        for (int i = 0; i < this->nrInterventii;i++)
            this->achitat[i] = m.achitat[i];
    }
    Masina operator=(const Masina& m)
    {
        this->clasa = m.clasa;
        this->nrInmatriculare = m.nrInmatriculare;
        if (m.marca)
        {
            this->marca = new char[strlen(m.marca) + 1];
            strcpy(this->marca, m.marca);
        }
        else
        {
            this->marca = new char[strlen("Anonim") + 1];
            strcpy(this->marca, "Anonim");
        }
        this->anMasina = m.anMasina;
        this->kmRulati = m.kmRulati;
        this->telefon = m.telefon;
        this->nrInterventii = m.nrInterventii;
        if (m.nrInterventii > 0)
        {
            this->interv = new Interventie[m.nrInterventii];
            for (int i = 0; i < m.nrInterventii;i++)
                this->interv[i] = m.interv[i];
        }
        this->achitat = new int[this->nrInterventii];
        for (int i = 0; i < this->nrInterventii;i++)
            this->achitat[i] = m.achitat[i];
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Masina& m)
    {
        os << "Tipul masinii: ";
        switch (m.clasa)
        {
        case 0: os << "Mica" << endl; break;
        case 1: os << "Mare" << endl; break;
        case 2: os << "SUV" << endl; break;
        default: break;
        }
        os << "Marca: " << m.marca << endl;
        os << "Numarul de inmatriculare: " << m.nrInmatriculare << endl;
        os << "An masina: " << m.anMasina << endl;
        os << "Kilometraj: " << m.kmRulati << endl;
        os << "Numar interventii: " << m.nrInterventii << endl;
        for (int i = 0; i < m.nrInterventii; i++)
        {
            os << m.interv[i] << endl;
            if (m.achitat[i] == 0)
                os << "Stare: Plata restanta";
            else
                os << "Stare: Achitat";
            os << endl;
        }
        return os;
    }
    friend ofstream& operator<<(ofstream& out, const Masina& m)
    {
        out << m.clasa << "\n" << m.nrInmatriculare << "\n" << m.marca << "\n" << m.anMasina << "\n" << m.kmRulati << "\n" << m.telefon << "\n";
        out << m.nrInterventii << "\n";
        if (m.nrInterventii > 0)
        {
            for (int i = 0; i < m.nrInterventii; i++) {
                out << m.interv[i] << endl;
                out << m.achitat[i] << endl;
            }
        }
        return out;
    }
    friend ifstream& operator>>(ifstream& in, Masina& m)
    {
        int aux;
        in >> aux;
        switch (aux)
        {
        case 0: m.setClasa(Mica); break;
        case 1: m.clasa = Mare; break;
        case 2: m.clasa = SUV; break;
        case 3: m.clasa = Toate; break;
        default: break;
        };
        in >> m.nrInmatriculare;
        string a;
        in.ignore();
        getline(in, a);
        if (m.marca != nullptr)
            delete[] m.marca;
        m.marca = new char[a.length() + 1];
        strcpy(m.marca, a.c_str());
        //        in.ignore();
        in >> m.anMasina;
        in >> m.kmRulati;
        getline(in, a);
        in >> m.telefon;
        in >> m.nrInterventii;
        if (m.nrInterventii > 0)
        {
            m.interv = new Interventie[m.nrInterventii];
            m.achitat = new int[m.nrInterventii];
            int ac;
            for (int i = 0; i < m.nrInterventii; i++)
            {
                Interventie inter;
                in >> inter;
                m.interv[i] = inter;
                in >> ac;
                m.achitat[i] = ac;
            }
        }
        return in;
    }
    friend istream& operator>>(istream& is, Masina& m)
    {
        cout << endl << "Introduceti urmatoarele detalii despre masina: \n tipul masinii(0-Mica, 1-Mare, 2-SUV): ";
        int aux;
        is >> aux;
        int ok = 0;
        while (ok == 0)
        {
            switch (aux) {
            case 0:
                m.clasa = Mica;
                ok = 1;
                break;
            case 1:
                m.clasa = Mare;
                ok = 1;
                break;
            case 2:
                m.clasa = SUV;
                ok = 1;
                break;
            default:
                cout << "Tip masina inexistent. Reintroduceti: ";
                break;
            }
        }
        cout << "Marca: ";
        if (strlen(m.marca) != 0)
            delete[] m.marca;
        char a[20];
        is >> a;
        m.marca = new char[strlen(a) + 1];
        strcpy(m.marca, a);
        cout << "Numarul de inmatriculare (Forma B-00-AAA): ";
        is >> m.nrInmatriculare;
        cout << "An: ";
        is >> m.anMasina;
        cout << "Kilometraj:";
        is >> m.kmRulati;
        //        cout<<"Telefon proprietar: ";
        //        is>>m.telefon;
        return is;
    }

    //supraincarcare operatori
    bool operator==(Masina m)
    {
        if (this->nrInmatriculare == m.nrInmatriculare)
            return true;
        else
            return false;
    }
    bool operator>=(Masina m)
    {
        if (this->nrInterventii >= m.nrInterventii)
            return true;
        else
            return false;
    }
    int& operator[](int index)
    {
        if (index >= 0 && index < nrInterventii)
            return achitat[index];
    }
    //metode
    float totalPlata()
    {
        float aux = 0;
        for (int i = 0; i < nrInterventii; i++)
        {
            if (achitat[i] == 0)
                aux += interv[i].getCost();
            else
                aux += 0;
        }
        return aux;
    }
    void adaugaInterventie(Interventie inter)
    {
        nrInterventii++;
        Interventie* aux;
        int* plata;
        aux = new Interventie[nrInterventii];
        plata = new int[nrInterventii];
        for (int i = 0; i < nrInterventii - 1; i++)
        {
            aux[i] = interv[i];
            plata[i] = achitat[i];
        }
        aux[nrInterventii - 1] = inter;
        plata[nrInterventii - 1] = 0;
        delete[] interv;
        delete[] achitat;
        interv = new Interventie[nrInterventii];
        achitat = new int[nrInterventii];
        for (int i = 0; i < nrInterventii;i++)
        {
            interv[i] = aux[i];
            achitat[i] = plata[i];
        }
    }
    void plataInterventie(Interventie inter)
    {
        for (int i = 0; i < nrInterventii; i++)
            if (interv[i] == inter)
            {
                achitat[i] = 1;
                break;
            }
    }

    void afiseaza() override
    {
        cout << "\n";
        cout << "Numarul de inmatriculare: " << nrInmatriculare << endl;
        for (int i = 0; i < nrInterventii; i++)
        {
            if (achitat[i] == 0)
                interv[i].afiseaza();
        }
    }
    float getCostTotal()
    {
        float aux = 0;
        if (nrInterventii > 0)
        {
            for (int i = 0; i < nrInterventii;i++)
            {
                if (achitat[i] == 0)
                    aux += interv[i].getCost();
            }
        }
        return aux;
    }
};

class Client : public Persoana, public afisabil
{
private:
    int nrMasini;//
    vector<Masina> masini;
    const int id_client; //
    static int nrClienti;//
    float total;//
public:
    Client() : id_client(nrClienti++), Persoana()
    {
        nrMasini = 0;
        total = 0;
    }
    Client(string nume, string prenume, string telefon, int nrMasini, vector<Masina> masini) : id_client(nrClienti++), Persoana(nume, prenume, telefon), masini(masini)
    {
        this->nrMasini = nrMasini;
        float aux = 0;
        if (nrMasini > 0)
        {
            for (int i = 0; i < nrMasini; i++)
            {
                this->masini[i].setTelefon(telefon);
                if (this->masini[i].totalPlata() != 0)
                    aux += this->masini[i].totalPlata();
            }
        }
        this->total = aux;
    }
    Client(string nume, string prenume, string telefon) : id_client(nrClienti++), Persoana(nume, prenume, telefon)
    {

        nrMasini = 0;
        total = 0;
    }
    Client(const Client& c) : id_client(nrClienti++)
    {
        this->setNume(c.getNume());
        this->setPrenume(c.getPrenume());
        this->setTelefon(c.getTelefon());
        this->nrMasini = c.nrMasini;
        if (nrMasini > 0)
        {
            this->masini.clear();
            for (int i = 0; i < this->nrMasini; i++)
                this->masini.push_back(c.masini[i]);
        }
        this->total = c.total;
    }
    Client operator=(const Client& c)
    {
        this->setNume(c.getNume());
        this->setPrenume(c.getPrenume());
        this->setTelefon(c.getTelefon());
        this->nrMasini = c.nrMasini;
        if (nrMasini > 0)
        {
            this->masini.clear();
            for (int i = 0; i < this->nrMasini; i++)
                this->masini.push_back(c.masini[i]);
        }
        this->total = c.total;
        return *this;
    }
    ~Client()
    {
        nrClienti--;
        masini.clear();
    }
    //get si set
    int getId()
    {
        return id_client;
    }
    int getNrClienti()
    {
        return id_client;
    }
    float getTotal()
    {
        return this->total;
    }
    void setTotal(float t)
    {
        this->total = t;
    }
    float getNrMasini()
    {
        return nrMasini;
    }
    void setNrMasini(int n)
    {
        if (nrMasini >= 0)
            nrMasini = n;
        else
            throw Exceptie("Nu se poate modifica! Fiecare masina trebuie inregistrata");
    }
    Masina& getMasina(int index)
    {
        if (index >= 0 && index < nrMasini)
            return masini[index];
    }
    void setMasina(int index, const Masina& m)
    {
        if (index > 0 && index < nrMasini)
            masini[index] = m;
        else
            throw Exceptie("Masina inexistenta");
    }

    int nrInterventiiClient()
    {
        int aux = 0;
        for (int i = 0; i < nrMasini; i++)
        {
            aux += masini[i].getNrInterventii();
        }
        return aux;
    }
    float procent() override
    {
        if (nrInterventiiClient() >= 1)
            return  0.002 * (nrInterventiiClient() - 1);
        else
            return 0;
    }
    string pozitie() override
    {
        return "client";
    }
    void afiseaza() override
    {
        int aux = 0;
        if (nrMasini > 0)
        {
            for (int i = 0; i < nrMasini; i++)
            {
                if (this->masini[i].totalPlata() != 0)
                    aux += this->masini[i].totalPlata();
            }
        }
        total += aux;
        cout << "Total: " << total;
        cout << "\nReducere de fidelitate: " << (procent() * total);
        cout << "\nTotal de plata: " << (float)*this;
    }

    friend ostream& operator<<(ostream& os, Client& c)
    {
        os << endl << "Id Client: " << c.id_client << endl;
        os << (Persoana&)c;
        os << "Numar masini: " << c.nrMasini << endl;
        for (int i = 0; i < c.nrMasini; i++)
        {
            os << endl << c.masini[i];
        }
        os << "Total: " << c.total;
        os << "\nReducere de fidelitate: " << (c.procent() * c.total);
        os << "\nTotal de plata: " << (float)c;
        return os;
    }
    friend ofstream& operator<<(ofstream& out, Client& c)
    {
        out << (Persoana&)c;
        return out;
    }
    istream& read(istream& is)
    {
        string n;
        //is>>nume>>prenume>>telefon>>nrMasini;
        cout << "Id client: " << id_client << "\n";
        cout << "Nume: ";
        is >> n;
        setNume(n);
        cout << "Prenume: ";
        is >> n;
        setPrenume(n);
        cout << "Telefon: ";
        is >> n;
        setTelefon(n);
        cout << "Numar masini: ";
        is >> nrMasini;
        if (nrMasini > 0)
        {
            //masini.clear();
            for (int i = 0; i < nrMasini;i++)
            {
                Masina mas;
                is >> mas;
                masini.push_back(mas);
            }
        }
        return is;
    }
    friend istream& operator>>(istream& is, Client& c)
    {
        return c.read(is);
    }
    ifstream& read(ifstream& in)
    {
        string n;
        getline(in, n);
        setNume(n);
        getline(in, n);
        setPrenume(n);
        getline(in, n);
        setTelefon(n);
        return  in;
    }
    friend ifstream& operator>>(ifstream& in, Client& c)
    {
        return c.read(in);
    }

    Client operator+(Client& c)
    {
        Client result = *this;
        result.total = this->total + c.total;
        return result;
    }
    explicit operator int()
    {
        return round(total);
    }
    bool operator!=(Client& c)
    {
        if (this->nrMasini != c.nrMasini)
            return true;
        else
            return false;
    }
    operator float()
    {
        return total - total * procent();
    }

    //metode(3)

    void adaugaMasina(Masina& m)
    {
        nrMasini++;
        masini.push_back(m);
    }
    void scoateMasina(Masina& m)
    {
        nrMasini--;
        m.setTelefon("00");
        total = total - m.totalPlata();
        auto it = find(masini.begin(), masini.end(), m);
        if (it != masini.end())
            masini.erase(it);
    }
    float calculeazaRata(int n) //n-nr luni
    {
        return round(total / n);
    }
    int getIndexMasina(Masina& m)
    {
        int i = 0;
        int gasit = 0;
        vector<Masina> ::iterator ivm;
        while (ivm != masini.end() && gasit == 0)
        {
            if (m == *ivm)
            {
                gasit = 1;
                return i;
            }
            i++;
        }
    }
};
int Client::nrClienti = 1;

class Angajat : public Persoana
{
    float salariu;
    int experienta; //cate masini a reparat
    int masiniZi[7];
    Masina* masini; //masinile reparate
public:
    Angajat() : Persoana()
    {
        salariu = 0;
        experienta = 0;
        masini = nullptr;
        for (int i = 0; i < 7; i++)
            masiniZi[i] = 0;
    }
    Angajat(string nume, string prenume, string telefon, float salariu, int experienta, int masiniZi[7], const Masina* masini) : Persoana(nume, prenume, telefon)
    {
        this->salariu = salariu;
        this->experienta = experienta;
        for (int i = 0; i < 7;i++)
        {
            this->masiniZi[i] = masiniZi[i];
        }
        this->masini = new Masina[experienta];
        for (int i = 0; i < experienta; i++)
            this->masini[i] = masini[i];
    }
    Angajat(string nume, string prenume, string telefon, float salariu) : Persoana(nume, prenume, telefon)
    {
        this->salariu = salariu;
        this->experienta = 0;
        this->masini = nullptr;
        for (int i = 0; i < 7; i++)
            masiniZi[i] = 0;
    }
    Angajat(const Angajat& a) : Persoana(a)
    {
        this->salariu = a.salariu;
        this->experienta = a.experienta;
        for (int i = 0; i < 7;i++)
        {
            this->masiniZi[i] = a.masiniZi[i];
        }
        this->masini = new Masina[experienta];
        for (int i = 0; i < a.experienta; i++)
            this->masini[i] = a.masini[i];
    }
    Angajat& operator=(const Angajat& a)
    {
        this->setNume(a.getNume());
        this->setPrenume(a.getPrenume());
        this->setTelefon(a.getTelefon());
        this->salariu = a.salariu;
        this->experienta = a.experienta;
        for (int i = 0; i < 7;i++)
        {
            this->masiniZi[i] = a.masiniZi[i];
        }
        this->masini = new Masina[experienta];
        for (int i = 0; i < a.experienta; i++)
            this->masini[i] = a.masini[i];
        return *this;
    }
    ~Angajat()
    {
        delete[] masini;
    }
    float getSalariu()
    {
        return salariu;
    }
    void setSalariu(float s)
    {
        if (s < 2500)
            throw Exceptie("Salariul trebuie sa fie mai mare decat minimul pe economie!");
        else
            salariu = s;
    }
    int getExperienta()
    {
        return experienta;
    }
    void setExperienta(int e)
    {
        if (e == 0)
            experienta = e;
        else
            throw Exceptie("Nu se poate modifica!");
    }
    int getMasiniZi(int i)
    {
        return masiniZi[i];
    }
    void setMasiniZi(int m[7])
    {
        if (m[6] == 0)
        {
            for (int i = 0; i < 7; i++)
                masiniZi[i] = m[i];
        }
        else
            throw Exceptie("Nu se munceste duminica!");
    }
    Masina* getMasini()
    {
        return masini;
    }
    void setMasini(const Masina* m, int n)
    {
        if (n == experienta && n != 0)
        {
            delete[] this->masini;
            this->masini = new Masina[n];
            for (int i = 0; i < n; i++)
                this->masini[i] = m[i];
        }
        else
            throw Exceptie("Nu se pot modifica masinile!");
    }

    friend ostream& operator<<(ostream& os, const Angajat& a)
    {
        os << (Persoana&)a;
        os << "Salariu: " << a.salariu << "\nExperienta: " << a.experienta << "\nMasini lucrate saptamana curenta: \n";
        os << "Luni: " << a.masiniZi[0] << " Marti: " << a.masiniZi[1] << " Miercuri: " << a.masiniZi[2] << " Joi: " << a.masiniZi[3] << " Vineri: " << a.masiniZi[4] << " Sambata: " << a.masiniZi[5] << endl;
        os << "Masinile lucrate: " << a.experienta << "\n";
        for (int i = 0; i < a.experienta; i++)
            os << "\n" << a.masini[i].getNrInmatriculare();
        return os;
    }
    friend ofstream& operator<<(ofstream& out, const Angajat& a)
    {
        out << (Persoana&)a;
        out << a.salariu << "\n" << a.experienta << "\n";
        for (int i = 0; i < 7; i++)
            out << a.masiniZi[i] << "\n";
        for (int i = 0; i < a.experienta; i++)
            out << a.masini[i] << "\n";
        return out;
    }

    istream& read(istream& is)
    {
        int a;
        string n;
        cout << "Nume: ";
        is >> n;
        setNume(n);
        cout << "Prenume :";
        is >> n;
        setPrenume(n);
        cout << "Numar de telefon: ";
        is >> n;
        setTelefon(n);
        cout << "Salariul: ";
        is >> salariu;
        cout << "Experienta: ";
        is >> experienta;
        cout << "Masini lucrate pe zi(saptamana curenta): ";
        for (int i = 0; i < 7; i++)
            is >> masiniZi[i];
        if (experienta > 0)
        {
            cout << "Masinile la care a lucrat: ";
            masini = new Masina[experienta];
            for (int i = 0; i < experienta; i++)
            {
                int id;
                string nr;
                cout << "\n Id Client: ";
                is >> id;
                cout << "Numar inmatriculare: ";
                is >> nr;
                Masina m(getTelefon(), nr);
                masini[i] = m;
            }
        }
        return is;
    }
    ifstream& read(ifstream& in)
    {
        string n;
        in >> n;
        setNume(n);
        in.ignore();
        getline(in, n);
        setPrenume(n);
        getline(in, n);
        setTelefon(n);
        in >> salariu;
        in >> experienta;
        for (int i = 0; i < 7; i++)
            in >> masiniZi[i];
        masini = new Masina[experienta];
        for (int i = 0; i < experienta; i++)
        {
            Masina m;
            in >> m;
            m.setTelefon(getTelefon());
            masini[i] = m;
        }
        return in;

    }
    friend istream& operator>>(istream& is, Angajat& a)
    {
        return a.read(is);
    }
    friend ifstream& operator>>(ifstream& in, Angajat& a)
    {
        return a.read(in);
    }

    //supraincarcare operatori
    bool operator>=(Angajat& a)
    {
        if (this->experienta >= a.experienta)
            return true;
        else
            return false;
    }
    Angajat& operator++()
    {
        this->experienta++;
        return *this;
    }
    int operator[](int index)
    {
        if (index >= 0 && index <= 6)
            return masiniZi[index];
        else
            throw Exceptie("Index invalid");
    }
    explicit operator float()
    {
        return (salariu / 4) * procent();
    }


    //metode din cls virtuala
    string pozitie() override
    {
        return "mecanic";
    }
    float procent() override
    {
        int aux = 0;
        for (int i = 0; i < 7; i++)
            aux += masiniZi[i];
        return aux * 0.5;
    }

    //metode
    void primireSpor(int n)
    {
        salariu = salariu + n;
    }
    float procentInterventie(int i, int j)
    {
        return 0.5 * masini[i].getCost(j);
    }
    float plataSapt(int spor)
    {
        float aux = 0;
        aux = (salariu / 4) + procent() + spor;
    }
};

template<class tip>
class Fisiere
{
private:
    string fisier;
public:
    Fisiere(string fisier)
    {
        ofstream fis(fisier);
        if (!fis)
            throw Exceptie("Numele fisierului este invalid!");
        else
            this->fisier = fisier;
    }

    vector<tip> citesteFisier()
    {
        ifstream f(fisier, ios::in);
        tip m;
        vector<tip> lista;
        while (f >> m)
        {
            lista.push_back(m);
        }
        f.close();
        return lista;
    }
    void scrieFisier(tip obj)
    {
        ofstream f(fisier, ios::app);
        f << obj;
        f.close();
    }
    void scrieBinar()
    {
        tip obj;
        ofstream f(fisier, ios::binary | ios::app);
        f.write((char*)&obj, sizeof(obj));
        f.close();
    }
};

template<>
class Fisiere<Interventie>
{
private:
    string file;
public:
    Fisiere(string file)
    {
        this->file = file;
    }

    vector<Interventie> citesteFisier()
    {
        ifstream f(file, ios::in);
        Interventie m;
        vector<Interventie> lista;
        while (f >> m)
        {
            lista.push_back(m);
        }
        f.close();
        return lista;
    }

    void scrieFisier(Interventie obj)
    {
        ofstream f(file, ios::app);
        f << "\n" << obj;
        f.close();
    }

    void modificaFisier(vector<Interventie> vect, Interventie m)
    {
        vector<Interventie> ::iterator ivm;
        ofstream f(file, ios::out);
        for (ivm = vect.begin(); ivm != vect.end(); ivm++)
        {
            if (*ivm == m)
                f << m;
            else
            {
                Interventie m1;
                m1 = *ivm;
                f << m1;
            }
        }
        f.close();
    }

};
template<>
class Fisiere<Client>
{
private:
    string file;
public:
    Fisiere(string file)
    {
        this->file = file;
    }
    vector<Client> citesteFisier()
    {
        ifstream f(file, ios::in);
        Client m;
        vector<Client> lista;
        while (f >> m)
        {
            lista.push_back(m);
            m.setNrMasini(0);
        }
        f.close();
        return lista;
    }
    void scrieFisier(Client obj)
    {
        ofstream f(file, ios::app);
        f << "\n" << obj;
        f.close();
    }
};

template<>
class Fisiere<Masina> {
private:
    string file;
public:
    Fisiere() {
        this->file = "masini.txt";
    }

    vector<Masina> citesteFisier() {
        ifstream f(file, ios::in);
        vector<Masina> lista;
        while (!f.eof())
        {
            Masina m;
            f >> m;
            lista.push_back(m);
        }
        f.close();
        return lista;
    }

    void scrieFisier(Masina obj)
    {
        ofstream f(file, ios::app);
        f << "\n" << obj;
        f.close();
    }

    void modificaFisier(vector<Masina> vect, Masina m)
    {
        vector<Masina> ::iterator ivm;
        ofstream f(file);
        for (ivm = vect.begin(); ivm != vect.end(); ivm++)
        {
            //            if(*ivm == m)
            //            {  f<<m;}
            //            else
            //            {
            Masina m1;
            m1 = *ivm;
            f << m1;
            //            }
            //            f<<"\n";
        }
        f.close();
    }
};


Interventie AlegeInterventie(int a)
{
    vector<Interventie> lista;
    vector<Interventie>::iterator it;
    Fisiere<Interventie> listafisierInterventii("interventii.txt");
    lista = listafisierInterventii.citesteFisier();
    vector<Interventie> listaInterv0;
    vector<Interventie> listaInterv1;
    vector<Interventie> listaInterv2;
    for (it = lista.begin(); it != lista.end(); it++)
        switch (it->getTipMasina())
        {
        case 0:
            listaInterv0.push_back(*it);
            break;
        case 1:
            listaInterv1.push_back(*it);
            break;
        case 2:
            listaInterv2.push_back(*it);
            break;
        default:
            listaInterv0.push_back(*it);
            listaInterv1.push_back(*it);
            listaInterv2.push_back(*it);
            break;
        }
    int nrInt = 1;
    vector<Interventie> ::iterator il;
    switch (a)
    {
    case 0: for (il = listaInterv0.begin(); il != listaInterv0.end(); il++)
    {
        cout << nrInt++ << ". ";    il->afiseaza(); cout << "\n";
    } break;
    case 1:for (il = listaInterv1.begin(); il != listaInterv1.end(); il++)
    {
        cout << nrInt++ << ". ";    il->afiseaza(); cout << "\n";
    } break;
    case 2:for (il = listaInterv2.begin(); il != listaInterv2.end(); il++)
    {
        cout << nrInt++ << ". ";    il->afiseaza(); cout << "\n";
    } break;
    default: break;
    }
    cout << "\nAlege o interventie: ";
    int interventieAleasa;
    cin >> interventieAleasa;
    cout << "Ati ales interventia: \n";
    switch (a)
    {
    case 0: cout << listaInterv0[interventieAleasa - 1] << endl; return listaInterv0[interventieAleasa - 1]; break;
    case 1: cout << listaInterv1[interventieAleasa - 1] << endl; return listaInterv1[interventieAleasa - 1]; break;
    case 2: cout << listaInterv2[interventieAleasa - 1] << endl; return listaInterv2[interventieAleasa - 1]; break;
    default: break;
    }
};

map<string, Client> dictionarClienti()
{
    Fisiere<Masina> listaMasiniFisier;
    vector<Masina> listaMasini;
    listaMasini = listaMasiniFisier.citesteFisier();
    vector<Masina>::iterator ivm;
    Fisiere<Client> clientiFisier("clienti.txt");
    vector<Client> listaClienti;
    listaClienti = clientiFisier.citesteFisier();
    vector<Client> ::iterator ivc;
    map<string, Client> CautaClient;
    map<string, Client> ::iterator imc;
    for (ivc = listaClienti.begin(); ivc != listaClienti.end(); ivc++)
        CautaClient.insert({ ivc->getTelefon(), *ivc });
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        CautaClient[ivm->getTelefon()].adaugaMasina(*ivm);
    return CautaClient;
}

void meniu1()
{
    Fisiere<Masina> listaMasiniFisier;
    vector<Masina> listaMasini;
    listaMasini = listaMasiniFisier.citesteFisier();
    vector<Masina>::iterator ivm;

    Fisiere<Client> clientiFisier("clienti.txt");
    vector<Client> listaClienti;
    listaClienti = clientiFisier.citesteFisier();
    vector<Client> ::iterator ivc;

    map<string, Client> CautaClient;
    map<string, Client> ::iterator imc;
    int optiune;
    string telefon;
    Client cNou;
    Masina mNou;
    cout << "Pentru a inregistra o interventie voi avea nevoie de cateva detalii. Va rog sa raspundeti la urmatoarele intrebari: \n";
    cout << "Alegeti 0 daca clientul este nou, 1 daca clientul are deja cont: ";
    cin >> optiune;
    if (optiune == 1)
    {

        for (ivc = listaClienti.begin(); ivc != listaClienti.end(); ivc++)
            CautaClient.insert({ ivc->getTelefon(), *ivc });
        for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        {
            CautaClient[ivm->getTelefon()].adaugaMasina(*ivm);
        }

        cout << "Introduceti numarul de telefon: ";
        cin >> telefon;
        cNou = CautaClient[telefon];
        int opt;
        cout << "Masina este deja inregistrata?(0-da, 1-nu): ";
        cin >> opt;
        if (opt == 0)
        {
            mNou = cNou.getMasina(0);
        }
        else
        {
            Masina mm;
            cin >> mm;
            mNou = mm;
            cNou.adaugaMasina(mm);
            CautaClient[telefon].adaugaMasina(mm);
        }
    }
    else
    {
        cin >> cNou;
        ofstream f("clienti.txt", ios::app);
        f << cNou;
        mNou = cNou.getMasina(0);
        mNou.setTelefon(cNou.getTelefon());
    }
    int tip;
    tip = mNou.getClasa();
    cout << "Acestea sunt interventiile disponibile pentru aceasta masina: \n";
    Interventie interv;
    interv = AlegeInterventie(tip);
    if (optiune == 0)
    {
        mNou.adaugaInterventie(interv);
        Fisiere<Masina> adgmas;
        adgmas.scrieFisier(mNou);
    }
    else
    {
        mNou.adaugaInterventie(interv);
    }

    cNou.setTotal(mNou.totalPlata());
    cout << "\nAveti de achitat in total: ";
    cNou.afiseaza();
    cout << "\nSe achita la final.";

    listaMasini.push_back(mNou);
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        if (ivm->getNrInmatriculare() == mNou.getNrInmatriculare())
            *ivm = mNou;

    ofstream f("masini.txt", ios::out);
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        f << *ivm;
    f.close();
    cout << "Apasa 0 pentru a te intoarce in meniul principal: ";
    int a;
    cin >> a;
}

void meniuAchitare()
{
    Fisiere<Masina> listaMasiniFisier;
    vector<Masina> listaMasini;
    listaMasini = listaMasiniFisier.citesteFisier();
    vector<Masina>::iterator ivm;

    Fisiere<Client> clientiFisier("clienti.txt");
    vector<Client> listaClienti;
    listaClienti = clientiFisier.citesteFisier();
    vector<Client> ::iterator ivc;

    map<string, Client> CautaClient;
    map<string, Client> ::iterator imc;
    for (ivc = listaClienti.begin(); ivc != listaClienti.end(); ivc++)
        CautaClient.insert({ ivc->getTelefon(), *ivc });
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
    {
        CautaClient[ivm->getTelefon()].adaugaMasina(*ivm);
    }
    string telefon;
    cout << "Pentru achitare voi avea nevoie de urmatoarele detalii: \n";
    cout << "Introduceti numarul de telefon: ";
    cin >> telefon;
    Interventie inter;

    cout << "Alegeti interventia care a fost efectuata: \n";
    inter = AlegeInterventie(CautaClient[telefon].getMasina(0).getClasa());
    CautaClient[telefon].afiseaza();

    CautaClient[telefon].getMasina(0).plataInterventie(inter);

    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        if (ivm->getNrInmatriculare() == CautaClient[telefon].getMasina(0).getNrInmatriculare())
            *ivm = CautaClient[telefon].getMasina(0);

    cout << "\nDoriti plata in rate?(0-da, 1-nu): ";
    int opt;
    cin >> opt;
    if (opt == 0)
    {
        int inter;
        cout << "Numar rate: ";
        cin >> inter;
        cout << "\nRata lunara: " << CautaClient[telefon].calculeazaRata(inter);
    }

    ofstream f("masini.txt", ios::out);
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
        f << *ivm;
    f.close();
    cout << "\nApasa 0 pentru a te intoarce in meniul principal: ";
    int a;
    cin >> a;
}

void meniuModificareInterventii()
{
    int nrInter = 0;
    vector<Interventie> lista;
    vector<Interventie>::iterator it;
    Fisiere<Interventie> listafisierInterventii("interventii.txt");
    lista = listafisierInterventii.citesteFisier();
    cout << "Interventiile disponibile in atelier: \n";
    for (it = lista.begin(); it != lista.end(); it++)
    {
        cout << nrInter++ << ". " << *it << endl;
    }
    cout << "Alegeti o interventie: ";
    cin >> nrInter;
    cout << lista[nrInter] << endl;
    Interventie i;
    cout << "Scrieti interventia cu noile modificari:\n";
    cin >> i;
    lista[nrInter] = i;
    ofstream f("interventii.txt");
    for (it = lista.begin(); it != lista.end(); it++)
        f << *it << "\n";
    f.close();
}

void adaugaInterventie()
{
    Interventie i;
    cin >> i;
    Fisiere<Interventie> lista("interventii.txt");
    lista.scrieFisier(i);
    cout << "Interventia a fost adaugata cu succes!\n";
}

void interventiiInCurs()
{
    Fisiere<Masina> listaMasiniFisier;
    vector<Masina> listaMasini;
    listaMasini = listaMasiniFisier.citesteFisier();
    vector<Masina>::iterator ivm;
    float ct = 0;
    for (ivm = listaMasini.begin(); ivm != listaMasini.end(); ivm++)
    {
        if (ivm->totalPlata() != 0)
        {
            ivm->afiseaza();
            ct += ivm->getCostTotal();
        }
    }
    cout << "\nCost total: " << ct << endl;
    int a;
    cout << "Apasa orice numar pentru a continua.";
    cin >> a;
}

void MeniuPrincipal()
{
    int exe = 0;
    cout << "Buna!\n";
    while (exe == 0)
    {
        cout << "Te rog sa alegi una din urmatoarele actiuni:\n";
        cout << "0. Inchidere program\n1. Adaugarea unei interventii unei masini\n2. Plata unei interventii\n3. Modificarea interventiilor disponibile\n"
            "4. Adaugarea unei interventii in lista\n" << "5. Interventii in curs\n";
        cout << "Scrieti numarul corespunzator actiunii dorite: ";
        int optmp;
        cin >> optmp;
        switch (optmp) {
        case 0:
            cout << "La revedere!"; exe = 1; break;
        case 1:
            meniu1(); break;
        case 2:
            meniuAchitare(); break;
        case 3: meniuModificareInterventii(); break;
        case 4: adaugaInterventie(); break;
        case 5: interventiiInCurs(); break;
        default: break;
        }

    }
}

int main()
{
    try
    {
        MeniuPrincipal();
    }
    catch (Exceptie e)
    {
        cout << e.getMesajExceptie();
    };

    return 0;
}
