#include<iostream>
#include<string>
#include<exception>

class IVehicle
{
public:
	virtual void move() = 0;
};


class Car :public IVehicle
{
private:
		std::string name;
public:
	Car(std::string name)
	{
		this->name = name;
	}
	void move() override
	{
		std::cout << "Car is moving" << std::endl;
	}
};

class Bike :public IVehicle
{
private:
	std::string name;
public:
	Bike(std::string name)
	{
		this->name = name;
	}
	void move() override
	{
		std::cout << "Bike is moving" << std::endl;
	}
};

class NoVehicleTypeFoundException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "No Vehcile is found with the given type";
	}
};

class VehicleFactory {
public:
	static std::unique_ptr<IVehicle> getVehicle(std::string type, std::string name)
	{
		NoVehicleTypeFoundException noVehciletypeException;
		std::unique_ptr<IVehicle> vehicle;
		if (type == "car")
			vehicle = std::make_unique<Car>(name);
		else if (type == "bike")
			vehicle = std::make_unique<Bike>(name);
		else
			throw noVehciletypeException;
		return vehicle;
	}
};
