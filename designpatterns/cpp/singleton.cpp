#include<iostream>

class Singleton
{
private:
	Singleton() = default;
	~Singleton()
	{
		delete obj;
	}
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton &&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton &&) = delete;
public:
	static Singleton* getInstance()
	{
		if (obj == nullptr)
		{
			obj = new Singleton();
			std::cout << "object cretaed" << std::endl;
		}
		std::cout << "object returned" << std::endl;
		return obj;
	}

private:
	static Singleton * obj;
};
