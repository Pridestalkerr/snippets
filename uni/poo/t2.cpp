#include<iostream>
#include<vector>

class Localitate{
protected:
    std::string denumire_;
    uint32_t cod_;
    uint32_t nrLocuitori_;
public:
    Localitate();
    Localitate(const std::string &denumire, uint32_t cod, uint32_t nrLocuitori):
        denumire_(denumire), cod_(cod), nrLocuitori_(nrLocuitori) {}
    virtual void display() const
    {
        std::cout<<"Localitate:\n\tNume: "<<denumire_<<";\n\tCod: "<<cod_<<";\n\tNumar locuitori: "<<nrLocuitori_<<'.'<<std::endl;
    }
    friend std::istream& operator >> (std::istream &in, Localitate &container);
    friend std::ostream& operator << (std::ostream &out, const Localitate &container);
};

std::istream& operator >> (std::istream &in, Localitate &container)
{
    in >> container.denumire_ >> container.cod_ >> container.nrLocuitori_;
}

std::ostream& operator << (std::ostream &out, const Localitate &container)
{
    container.display();
}

class Oras: public Localitate{
protected:
    uint32_t nrBlocuri_;
public:
    Oras();
    Oras(const std::string &denumire, uint32_t cod, uint32_t nrLocuitori, uint32_t nrBlocuri): Localitate(denumire, cod, nrLocuitori)
    {
        nrBlocuri_ = nrBlocuri;
    }
    void display() const
    {
        std::cout<<"Oras:\n\tNume: "<<denumire_<<";\n\tCod: "<<cod_<<";\n\tNumar locuitori: "<<nrLocuitori_<<";\n\tNumar blocuri: "<<nrBlocuri_<<'.'<<std::endl;
    }
    friend std::istream& operator >> (std::istream &in, Oras &container);
    friend std::ostream& operator << (std::ostream &out, const Oras &container);
};

std::istream& operator >> (std::istream &in, Oras &container)
{
    in >> container.denumire_ >> container.cod_ >> container.nrLocuitori_ >> container.nrBlocuri_;
}

std::ostream& operator << (std::ostream &out, const Oras &container)
{
    container.display();
}

class Capitala: public Oras{
protected:
    std::string numePrefect_;
public:
    Capitala();
    Capitala(const std::string &denumire, uint32_t cod, uint32_t nrLocuitori, uint32_t nrBlocuri, std::string numePrefect): Oras(denumire, cod, nrLocuitori, nrBlocuri)
    {
        numePrefect_ = numePrefect;
    }
    void display() const
    {
        std::cout<<"Capitala:\n\tNume: "<<denumire_<<";\n\tCod: "<<cod_<<";\n\tNumar locuitori: "<<nrLocuitori_<<";\n\tNumar blocuri: "<<nrBlocuri_<<";\n\tNume prefect: "<<numePrefect_<<'.'<<std::endl;
    }
    friend std::istream& operator >> (std::istream &in, Capitala &container);
    friend std::ostream& operator << (std::ostream &out, const Capitala &container);
};

std::istream& operator >> (std::istream &in, Capitala &container)
{
    in >> container.denumire_ >> container.cod_ >> container.nrLocuitori_ >> container.nrBlocuri_ >> container.numePrefect_;
}

std::ostream& operator << (std::ostream &out, const Capitala &container)
{
    container.display();
}

class Judet{
    std::vector <Localitate*> p_;
    uint32_t nrLoc_;
public:
    Judet()
    {
        nrLoc_ = 0;
    }
    void push_back(Localitate &newMember)
    {
        p_.push_back(&newMember);
        nrLoc_++;
    }
    void display() const
    {
        std::cout<<"Judet - "<<nrLoc_<<" Localitati:\n";
        for(auto itr: p_)
            itr->display();
    }
};

int main()
{
    Localitate A("LOC", 3, 44);
    A.display();
    Oras B("ORAS", 3, 77, 5000);
    B.display();
    Capitala C("CAP", 3, 21, 5000, "prefect");
    C.display();
    Judet D;
    D.push_back(A);
    D.push_back(B);
    D.push_back(C);
    D.display();
    std::cin >> A;
    A.display();
    return 0;
}
