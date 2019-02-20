#include<iostream>

class IDomianComponet
{
public:
	virtual void execute()=0;
};

class DomianComponetImpl :public IDomianComponet
{	
public:
	DomianComponetImpl() = default;
	void execute() override
	{
		std::cout << "Executing domain logic for the component"<<std::endl;
	}
};

class DomainComponetDecorator : public IDomianComponet
{
private:
	std::unique_ptr<IDomianComponet> component;
public:

	DomainComponetDecorator(std::unique_ptr<IDomianComponet> domianComponent)
	{
		component = std::move(domianComponent);
	}
public:
	void execute() override
	{
		component->execute();
	}
};

class LoggerDecorator : public DomainComponetDecorator
{
public:
	LoggerDecorator(std::unique_ptr<IDomianComponet> component) :DomainComponetDecorator(std::move(component))
	{
	};
	void execute() override
	{
		std::cout << "Logger started"<<std::endl;
		DomainComponetDecorator::execute();
		std::cout << "Logger ended" << std::endl;
	}
};

class PerfomanceMonitorDecorator : public DomainComponetDecorator
{
	public:
		PerfomanceMonitorDecorator(std::unique_ptr<IDomianComponet> component) :DomainComponetDecorator(std::move(component))
		{
		};
		void execute() override
		{
			std::cout << "Performance computaion started"<<std::endl;
			DomainComponetDecorator::execute();
			std::cout << "Performance computation endede"<<std::endl;
		}
};

//Client code
/*#include"decorator.h"

int main()
{
	std::unique_ptr<IDomianComponet> component = std::make_unique<DomianComponetImpl>();
	std::unique_ptr<IDomianComponet> component1 = std::make_unique<LoggerDecorator>(std::move(component));
	std::unique_ptr<IDomianComponet> component2 = std::make_unique<PerfomanceMonitorDecorator>(std::move(component1));
	component2->execute();
	return 0;
};*/
