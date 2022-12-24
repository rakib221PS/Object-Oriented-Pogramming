#include <iostream>
#include <vector>

class Work
{
    static int number_of_work_available;
    std::string text_description;
    std::string name;

public:
    Work(){}
    Work(std::string text, std::string owner):text_description(text), name(owner){
        number_of_work_available++;
    }
    static int count()
    {
        return number_of_work_available;
    }

    virtual int getCost() = 0;

    virtual ~Work()
    {
        std::cout << "Work destructor" << std::endl;
    }
};

class PieceWork : public Work
{
    int number_of_actions, cost_of_single_action;

public:
    virtual int getCost() override
    {
        return 1;
    }
    virtual ~PieceWork()
    {
        std::cout << "Piece work destructor" << std::endl;
    }
};

class FieldWork : public Work
{
    int length, wide, cost_of_per_square;

public:
    FieldWork(){}
    FieldWork(std::string name, std::string owner, int length, int wide, int cost):Work(name, owner), length(length), wide(wide), cost_of_per_square(cost){}
    virtual int getCost() override
    {
        return length * wide * cost_of_per_square;
    }
    virtual ~FieldWork()
    {
        std::cout << "Field work destructor" << std::endl;
    }
};

class TimeWork:public Work{
    int number_of_hours, salary_per_hour;

    public:
    virtual int getCost(){
        return 1;
    }
};

class Schedule{
    std::string description;
    int total_budget;
    // FieldWork *total_work = new FieldWork[5];
    // std::vector<FieldWork*>total_work;
    std::vector<Work*>total_work;

    public:
    Schedule(std::string des, int total_budget):description(des), total_budget(total_budget){}
    void insert(int id, FieldWork *p){
        total_work.push_back(p);
    }

    void cost(){
        total_work[1]->getCost();
    }
};

int Work::number_of_work_available = 0;

int main()
{
    Schedule repairs("Expected repairs of my room", 2000);
    std::cout<<Work::count();
    repairs.insert(1,new FieldWork("Floor","John",4,5,60));
    repairs.insert(4,new FieldWork("Wall","Hasan",9,89,69));
    repairs.cost();
    return 0;
}