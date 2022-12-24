#include <iostream>

class Work
{
    int number_of_work_available;
    std::string text_description;
    std::string name;

public:
    int number_of_works_available()
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
    virtual int getCost() override
    {
        return 1;
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
    Work *total_work = new Work[5];

    public:

    virtual int getCost() = 0;
};

int main()
{
    return 0;
}