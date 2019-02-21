#include<iostream>
#include<string>
class Employee
{
	std::string name; //requried
	int age;//requried
	int id;//requried
	std::string mobileNo; //optional
	std::string email; //optional
	std::string address; //optional
public:
	class EmployeeBuilder final
	{
		std::string name; //requried
		int age;//requried
		int id;//requried
		std::string mobileNo; //optional
		std::string email; //optional
		std::string address; //optional
	public:
		EmployeeBuilder() = delete;
		EmployeeBuilder(std::string name, int age, int id)
		{
			this->name = name;
			this->age = age;
			this->id = id;
		}
		EmployeeBuilder& setAddress(std::string addr)
		{
			address = addr;
			return *this;
		}
		EmployeeBuilder& setEmail(std::string mail)
		{
			email = mail;
			return *this;
		}
		EmployeeBuilder& setMobileNo(std::string mobile)
		{
			mobileNo = mobile;
			return *this;
		}
		std::unique_ptr<Employee> build()
		{
			return std::make_unique<Employee>(this);
		}

		std::string getName()
		{
			return name;
		}
		int getAge()
		{
			return age;
		}
		int getId()
		{
			return id;
		}
		std::string getAddress()
		{
			return address;
		}
		std::string getMobileNo()
		{
			return mobileNo;
		}
		std::string getEmail()
		{
			return email;
		}
	};

	Employee(EmployeeBuilder* emp)
	{
		this->name = emp->getName();
		this->age = emp->getAge();
		this->email = emp->getEmail();
		this->id = emp->getId();
		this->mobileNo = emp->getMobileNo();
		this->address = emp->getAddress();
	}
protected:
	Employee() = delete;
	Employee(const Employee&) = delete;
	Employee& operator = (const Employee &) = delete;
};

//Client code
/*
auto employeeBuilder = std::make_unique<Employee::EmployeeBuilder>("deva",30,1);
auto employee = employeeBuilder->setAddress("Address1").setEmail("abc@com").setMobileNo("000000").build();
auto employee1 = employeeBuilder->setAddress("Address2").build();
*/
