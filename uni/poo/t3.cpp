#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

class Locuinta{
protected:
    std::string numeClient_;
    float suprafata_;
    float discount_;
public:
	Locuinta(const std::string &numeClient, const float &suprafata, const float &discount): 
		numeClient_(numeClient),
		suprafata_(suprafata),
		discount_(discount) {
		try{
			if(suprafata <= 0)
				throw std::domain_error("bad_surface");
		}catch(std::domain_error &err){
			std::cout << "Exception during Locuinta type initialization: " << err.what() << std::endl;
		}
		try{
			if(discount < 0 || discount > 10)
				throw std::domain_error("bad_discount");
		}catch(std::domain_error &err){
			std::cout << "Exception during Locuinta type initialization: " << err.what() << std::endl;
		}
	}
	virtual void display() const
	{
		printf("Locuinta:\n\tClient: %s\n\tSuprafata: %f\n\tDiscount: %f\n", numeClient_.data(), suprafata_, discount_);
	}
	void setDiscount(const float &discount)
	{
		discount_ = discount;
		try{
			if(discount < 0 || discount > 10)
				throw std::domain_error("bad_discount");
		}catch(std::domain_error &err){
			std::cout << "Exception during Locuinta base type initialization: " << err.what() << std::endl;
		}
	}
	friend std::istream& operator >> (std::istream &in, Locuinta lhs);
	virtual std::unique_ptr <Locuinta> clone() const 
	{
        return std::make_unique <Locuinta> (*this);
    }
};

std::istream& operator >> (std::istream &in, Locuinta lhs)
{
	std::string numeClient;
	float suprafata;
	float discount;
	in >> numeClient >> suprafata >> discount;
	lhs = Locuinta(numeClient, suprafata, discount); 
	return in;
}

class Apartament: public Locuinta{
    int etaj_;
public:
	Apartament(const std::string &numeClient, const float &suprafata, const float &discount, const unsigned int &etaj):
		Locuinta(numeClient, suprafata, discount), 
		etaj_(etaj) {}
	void display() const
	{
		printf("Locuinta:\n\tClient: %s\n\tSuprafata: %f\n\tDiscount: %f\n\tEtaj: %d\n", numeClient_.data(), suprafata_, discount_, etaj_);
	}
	friend std::istream& operator >> (std::istream &in, Apartament lhs);
	virtual std::unique_ptr <Locuinta> clone() const 
	{
        return std::make_unique <Apartament> (*this);
    }
};

std::istream& operator >> (std::istream &in, Apartament lhs)
{
	std::string numeClient;
	float suprafata;
	float discount;
	int etaj;
	in >> numeClient >> suprafata >> discount >> etaj;
	lhs = Apartament(numeClient, suprafata, discount, etaj); 
	return in;
}

class Casa: public Locuinta{
    float suprafataCurte_;
    std::size_t nrEtaje_;
    std::vector <float> suprafataEtaje_;
public:
	Casa(const std::string &numeClient, const float &suprafata, const float &discount, const float &suprafataCurte, const std::size_t &nrEtaje, const std::vector <float> &suprafataEtaje): 
		Locuinta(numeClient, suprafata, discount),
		suprafataCurte_(suprafataCurte),
		nrEtaje_(suprafataEtaje.size()),
		suprafataEtaje_(suprafataEtaje) {
		try{
			if(suprafataCurte < 0)
				throw std::domain_error("bad_surface");
		}catch(std::domain_error &err){
			std::cout << "Exception during Locuinta base type initialization: " << err.what() << std::endl;
		}
		try{
			if(nrEtaje != suprafataEtaje.size() || nrEtaje == 0)
				throw std::domain_error("bad_floor");
		}catch(std::domain_error &err){
			std::cout << "Exception during Locuinta base type initialization: " << err.what() << std::endl;
		}
	}
	void display() const
	{
		printf("Locuinta:\n\tClient: %s\n\tSuprafata: %f\n\tDiscount: %f\n\tSuprafata curte: %f\n\tNumar etaje: %zu\n\tSuprafata etaje: ", numeClient_.data(), suprafata_, discount_, suprafataCurte_, nrEtaje_);
		for(auto itr: suprafataEtaje_)
			std::cout << itr << " ";
		std::cout << std::endl;
	}
	friend std::istream& operator >> (std::istream &in, Casa lhs);
	virtual std::unique_ptr <Locuinta> clone() const 
	{
        return std::make_unique <Casa> (*this);
    }
};

std::istream& operator >> (std::istream &in, Casa lhs)
{
	std::string numeClient;
	float suprafata;
	float discount;
	std::size_t nrEtaje;
	float suprafataCurte;
	in >> numeClient >> suprafata >> discount >> suprafataCurte >> nrEtaje;
	std::vector<float> suprafataEtaje; 
	for(std::size_t itr = 0; itr < nrEtaje; ++itr)
	{
		float floor;
		in >> floor;
		suprafataEtaje.push_back(floor);
	}
	lhs = Casa(numeClient, suprafata, discount, suprafataCurte, nrEtaje, suprafataEtaje); 
	return in;
}

template <class Type>
class Gestiune{
	std::vector <std::pair <std::unique_ptr <Type>, float>> elements_;
	std::size_t count_;
public:
	Gestiune<Type>& operator +=(const std::pair <const Type&, float> &newElement)
	{
		this->elements_.push_back({newElement.first.clone(), newElement.second});
		++ this->count_;
		try{
			if(newElement.second < 0)
				throw std::domain_error("bad_rent");
		}catch(std::domain_error &err){
			std::cout << "Exception during Gestiune type insertion: " << err.what() << std::endl;
		}
		return *this;
	}
	void display()
	{
		for(std::size_t itr = 0; itr < elements_.size(); ++itr)
		{
			elements_[itr].first->display();
		}
	}
};

template <>
class Gestiune <std::string>{
	std::size_t count_;
	std::vector <std::string> clienti_;
public:
	Gestiune<std::string>& operator +=(const std::string &newElement)
	{
		this->clienti_.push_back(newElement);
		++ this->count_;
		return *this;
	}
};

int main()
{
	Locuinta a("a1", 0, 1);
	Apartament b("b1", 0, 1, 3);
	Casa c("c1", 0, 1, 3, 4, {11, 22, 33});
	a.display();
	b.display();
	c.display();
	Gestiune <Locuinta> x;
	for(std::size_t itr = 0; itr < 3; ++itr)
	{
		x += {Locuinta("a1", 0, 1), 0};
		x += {Apartament("b1", 0, 1, 3), 1};
		x += {Casa("c1", 0, 1, 3, 4, {11, 22, 33}), 2};
	}
	x.display();
    return 0;	
}
