#include <iostream>
#include <queue>

class CustomError:std::exception{
    int id;
    std::string name;
    public:
    CustomError(){};
    CustomError(int id, std::string name):id(id), name(name){}
    std::string RunError(){
        return "Service < "+std::to_string(id)+", "+name+" > has been already started";
    }
};

class Process:public CustomError
{
    int pid_;
    std::string name;

    virtual void run() = 0;
    virtual void stop() = 0;
    virtual std::string getStatus() = 0;

public:
    Process(int len, std::string name) : pid_(len), name(name) {}

    int getPid()
    {
        return pid_;
    }

    void custom_run_error(){
        throw CustomError(pid_, name);
    }

    virtual ~Process()
    {
        std::cout << "Process destructor" << std::endl;
    }
};

class Service : public Process
{
    bool isRunning = false;
    static int len;
    std::string description, starting_mode;

public:
    Service(std::string name, std::string description, std::string starting_mode) : Process(len = len + 1, name), description(description), starting_mode(starting_mode) {}

    void setMode(std::string change_mode)
    {
        starting_mode = change_mode;
    }

    virtual void run() override
    {
        if (isRunning)
        {
            custom_run_error();
        }
        
        isRunning = true;
    }

    virtual void stop() override
    {
        isRunning = false;
    }

    virtual std::string getStatus() override
    {
        if (isRunning)
        {
            return "Running";
        }
        return "Stopped";
    }
};

int Service::len = 0;

class Application
{
    std::string owner_name;
    virtual void ownerName() = 0;
};

class ConsoleApplicatio : public Application
{
    std::string utf_code;

public:
    virtual void ownerName() override
    {
        std::cout << "Owner name from console application" << std::endl;
    }
};

class WindowApplication : public Application
{
    std::string dimensions;

public:
    virtual void ownerName() override
    {
        std::cout << "Owner name from window application" << std::endl;
    }
};

int main()
{
    // issue on process
    std::queue<Service *> tasks;

    Service *p1 = new Service("logger", "system logger", "automatic");
    p1->setMode("Manual");
    tasks.push(p1);

    try
    {
        Service *p = tasks.front();
        p->run();
        std::cout << p->getPid() << ":" << p->getStatus() << std::endl; // 1:running
        p->run();
    }
    // catch (Process::RunError &e)
    // {
    //     std::cerr << e.RunError() << '\n';
    // }
    catch (Process::CustomError &e)
    {
        std::cerr << e.RunError() << '\n';
    }
    return 0;
}