#include<iostream>
#include<mutex>
#include<thread>

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
		std::mutex mutex1, mutex2;		
		if (obj == nullptr)
		{
			std::lock_guard<std::mutex> lock1(mutex1);
			if (obj == nullptr)
			{
				std::lock_guard<std::mutex> lock2(mutex2);
				obj = new Singleton();
				std::cout << "object cretaed" << std::endl;
			}			
		}
		std::cout << "object returned" << std::endl;
		return obj;
	}

private:
	static Singleton * obj;
};

Singleton* Singleton::obj = nullptr;

/*int main()
{
	std::thread t1(test);
	std::thread t2(test);
	t1.join();
	t2.join();
	//object1 = object;
	return 0;
};
void test()
{
	auto object = Singleton::getInstance();
}*/
