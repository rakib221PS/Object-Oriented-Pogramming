#include <iostream>
#include <vector>

class CapacityError : std::exception
{
    std::string label_error;
    int capacity_error;

public:
    CapacityError() {}
    CapacityError(std::string label_error, int capacity_error) : label_error(label_error), capacity_error(capacity_error) {}
    std::string what()
    {
        return label_error + " is too large -> " + std::to_string(capacity_error) + " size space available";
    }
};

class IndexError : std::exception
{
    int item_error_number;

public:
    IndexError() {}
    IndexError(int error_number) : item_error_number(error_number) {}
    std::string what()
    {
        return "Item no. " + std::to_string(item_error_number) + " not found";
    }
};

class Case
{
    static int cases;
    std::string label;
    int color;

public:
    Case() {}
    Case(std::string name, int color) : label(name), color(color) {}
    static void caseIncrease()
    {
        cases += 1;
    }
    static void caseDecrease()
    {
        cases -= 1;
    }
    static int count()
    {
        return cases;
    }
    std::string getLabel()
    {
        return label;
    }

    int getColor()
    {
        return color;
    }

    virtual float getCapacity() = 0;
};

int Case::cases = 0;

class BrickCase : public Case
{
    float lenght, width, height;

public:
    BrickCase(std::string name, int color, float lenght, float width, float height) : Case(name, color), lenght(lenght), width(width), height(height) {}
    virtual float getCapacity()
    {
        return lenght * width * height;
    }
};

class TubeCase : public Case
{
    float base_radius, height;

public:
    TubeCase(std::string name, int color, float radius, float height) : Case(name, color), base_radius(radius), height(height) {}
    virtual float getCapacity()
    {
        return base_radius * height;
    }
};

class PrismCase : public Case
{
    float base_lenght, height;

public:
    PrismCase(std::string name, int color, float lenght, float height) : Case(name, color), base_lenght(lenght), height(height) {}
    virtual float getCapacity()
    {
        return base_lenght * height;
    }
};

class Repository : public CapacityError, public IndexError
{
    std::string description;
    float total_capacity;
    float remaining_capacity;
    std::vector<Case *> cases;

public:
    Repository() {}
    Repository(std::string description, float total) : description(description), total_capacity(total), remaining_capacity(total) {}
    friend std::ostream &operator<<(std::ostream &os, const Repository &content)
    {
        os << content.description << ", Total capacity: " << content.total_capacity << ", Remaining capacity: " << content.remaining_capacity << std::endl;
        int n = content.cases.size();
        for (int i = 0; i < n; i++)
        {
            os << i + 1 << ". " << content.cases[i]->getLabel() << ", " << std::hex << content.cases[i]->getColor() << ", Volume " << content.cases[i]->getCapacity() << std::endl;
        }

        return os;
    }

    template <typename T>
    void add(T *p)
    {
        float capacity = p->getCapacity();
        if (capacity <= remaining_capacity)
        {
            Case::caseIncrease();
            cases.push_back(p);
            remaining_capacity = remaining_capacity - capacity;
        }
        else
        {
            throw CapacityError(p->getLabel(), remaining_capacity);
        }
    }

    float summeryVolume()
    {
        return total_capacity - remaining_capacity;
    }

    void remove(std::string label)
    {
        int n = 0;
        std::vector<Case>::iterator it;
        for (auto it = cases.begin(); it != cases.end(); it++)
        {
            if (cases[n]->getLabel() == label)
            {
                remaining_capacity = remaining_capacity + cases[n]->getCapacity();
                cases.erase(it);
                Case::caseDecrease();
            }
            n++;
        }
    }

    Case &operator[](const int index)
    {
        if (index >= cases.size())
        {
            throw IndexError(index);
        }
        else
        {
            return *cases[index];
        }
    }

    void clear()
    {
        int length = cases.size();
        cases.clear();
        remaining_capacity = 0;
        for (int i = 0; i < length; i++)
        {
            Case::caseDecrease();
        }
    }
};

int main()
{
    Repository repo("Warehouse", 100);
    std::cout << Case::count() << std::endl; // 0
    try
    {
        repo.add(new BrickCase("books", 0x000000, 5, 3.5, 4));  // 5 x 3.5 x 4
        repo.add(new TubeCase("posters", 0x00ff00, 1, 3));      // radius=1, height=3
        repo.add(new PrismCase("toys", 0x800080, 3, 2));        // base=3, height=2
        repo.add(new BrickCase("jewels", 0xffff00, 2, 2, 2));   // 2 x 2 x 2
        repo.add(new BrickCase("trinkets", 0x000080, 5, 1, 1)); // 5 x 1 x 1
    }
    catch (Repository::CapacityError &e)
    {
        std::cout << e.what() << std::endl; // trinkets too large - only 4.8 free space
    }
    std::cout << Case::count() << std::endl; //
    std::cout << repo;
    std::cout << repo.summeryVolume() << std::endl;
    repo.remove("toys");
    std::cout << Case::count() << std::endl;
    std::cout << repo.summeryVolume() << std::endl;
    try
    {
        std::cout << repo[1].getCapacity() << std::endl; // 70.0
        std::cout << repo[5].getCapacity() << std::endl; // IndexError exception
    }
    catch (Repository::IndexError &e)
    {
        std::cout << e.what() << std::endl; // item no. 5 not found
    }
    repo.clear();
    std::cout << Case::count() << std::endl; // 0
    return 0;
}