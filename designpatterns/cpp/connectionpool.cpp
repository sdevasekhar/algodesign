#include<iostream>
#include<vector>
#include<string>
/*class IStatement
{
 
};*/
class IConnection
{
public:
	virtual void execute(std::string statement) = 0;
};

class IConnectionPool
{
public:
	virtual std::unique_ptr<IConnection> acquireConnection() = 0;
	virtual void releaseConnection(std::unique_ptr<IConnection> conn) = 0;
};

class IConnectionPoolConfig
{
public:
	virtual std::string read(std::string property) = 0;	
};

class Connection: public IConnection
{	
public:
	Connection() = default;	
	Connection(const Connection & conn) = default;
	Connection& operator =(const Connection & conn) = default;
	Connection(Connection && conn) = default;
	Connection& operator = (Connection && conn) = default;
	~Connection() = default;
public:
	void execute(std::string statement) override
	{
		std::cout << "Executing the statement :" << statement << std::endl;
	}
};

class ConnectionPoolConfig : public IConnectionPoolConfig
{
public:
	ConnectionPoolConfig() = default;

public:
	std::string read(std::string property) override
	{
		if (property == "maxConnectionSize")
			return "10";
	}
};

class ConnectionPool :public IConnectionPool
{
private:
	std::vector<std::unique_ptr<IConnection>> pool;	
	int maxPoolSize;
	
	ConnectionPool()
	{
		std::unique_ptr<IConnectionPoolConfig> configurator = std::make_unique<ConnectionPoolConfig>();
		maxPoolSize =std::stoi(configurator->read("maxConnectionSize"));
		for (int i = 0; i < maxPoolSize; i++)
		{
			pool.emplace_back(std::make_unique<Connection>());
		}
	}

	
public:
	static IConnectionPool* getInstance()
	{
		//static std::unique_ptr<IConnectionPool> instance = std::make_unique<ConnectionPool>();
		IConnectionPool *instance = new ConnectionPool();
		return instance;
	};

public:
	std::unique_ptr<IConnection> acquireConnection() override
	{
		std::unique_ptr<IConnection> conn;
		if (pool.size() != 0)
		{
			conn = std::move(pool.back());
			pool.pop_back();
			std::cout << "Connection Acquired" << std::endl;
		}
		else
		{
			//throw exception
		}
		return std::move(conn);
	}
public:
	void releaseConnection(std::unique_ptr<IConnection> conn) override
	{
		pool.emplace_back(std::move(conn));
		std::cout << "Connection Relased" << std::endl;
		return;
	}
};

//Client code  --Still can be improved by adding threads and providing more configuration options and add delete functionlaity
/*
auto pool = ConnectionPool::getInstance();
int i = 6;
while (i)
{
auto conn = pool->acquireConnection();
conn->execute("sql statment");
pool->releaseConnection(std::move(conn));
}
*/


