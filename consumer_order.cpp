#include <iostream>
#include <stdexcept>
#include <vector>

class ConsumerOrder
{
    static int unique_id_handler;
    int update_index;
    std::string customer_name;
    // std::string *names_of_disches = new std::string[5];
    std::vector<std::string> names_of_disches;
    // int **order_details = new int *[5];
    std::vector<int> order_details;
    int unique_id;

public:
    static int getOrderCount();
    ConsumerOrder();
    ConsumerOrder(std::string);
    ConsumerOrder(const ConsumerOrder &);
    void operator=(const ConsumerOrder &);
    ConsumerOrder &operator=(const int);
    void setCustomer();
    std::string getCustomer();
    int getID();
    void addDish(const std::string, const int);
    void removeDish(const std::string);
    int length();
    int getTotalCost();
    ~ConsumerOrder();
    ConsumerOrder &operator[](const int index)
    {
        if (index >= this->order_details.size())
        {
            throw std::runtime_error("Overflow");
        }
        update_index = index;
        return *this;
    }
    // --------------------------------------------------------------------------operator<< declaration---------------
    friend std::ostream &operator<<(std::ostream &os, const ConsumerOrder &parent);
    // void operator<<(const ConsumerOrder &);
    bool operator>(ConsumerOrder &);
};

ConsumerOrder::ConsumerOrder()
{
}

ConsumerOrder::ConsumerOrder(const std::string name)
{
    customer_name = name;
    unique_id = unique_id_handler++;
    std::cout << customer_name << std::endl;
}

ConsumerOrder::ConsumerOrder(const ConsumerOrder &parent)
{
    // if (this != &parent)
    // {
        this->customer_name = parent.customer_name;
        this->update_index = parent.update_index;
        this->unique_id = parent.unique_id;
        // int size = parent.order_details.size();
        // for (int i = 0; i < size; i++)
        // {
        //     this->names_of_disches.push_back(parent.names_of_disches[i]);
        //     this->order_details.push_back(parent.order_details[i]);
        // }
        this->names_of_disches = parent.names_of_disches;
        this->order_details = parent.order_details;
    // }
}

void ConsumerOrder::operator=(const ConsumerOrder &parent)
{
    if (this != &parent)
    {
        this->customer_name = parent.customer_name;
        this->update_index = parent.update_index;
        this->unique_id = parent.unique_id;
        this->names_of_disches = parent.names_of_disches;
        this->order_details = parent.order_details;
    }
}

int ConsumerOrder::getTotalCost()
{
    int total = 0;
    int size = order_details.size();
    for (int i = 0; i < size; i++)
    {
        total += order_details[i];
    }
    return total;
}

std::string ConsumerOrder::getCustomer()
{
    return customer_name;
}

int ConsumerOrder::getID()
{
    return unique_id;
}

void ConsumerOrder::addDish(const std::string dish_name, const int price)
{
    names_of_disches.push_back(dish_name);
    order_details.push_back(price);
}

void ConsumerOrder::removeDish(const std::string dish_name)
{
    int deleting_index = 0;
    bool isExists = false;
    int size = order_details.size();
    for (int i = 0; i < size; i++)
    {
        if (names_of_disches[i] == dish_name)
        {
            deleting_index = i;
            isExists = true;
            break;
        }
    }

    if (!isExists)
    {
        throw std::runtime_error(dish_name + " is not exist");
    }

    names_of_disches.erase(names_of_disches.begin() + deleting_index);
    order_details.erase(order_details.begin() + deleting_index);
}

int ConsumerOrder::length()
{
    return unique_id_handler - 1;
}

int ConsumerOrder::getOrderCount()
{
    if ((unique_id_handler - 1) <= 0)
    {
        return 0;
    }
    else
    {
        return unique_id_handler - 1;
    }
}


std::ostream &operator<<(std::ostream &os, const ConsumerOrder &present)
{
    // int sizeName = present.names_of_disches.size();
    int size = present.order_details.size();
    int sum = 0;
    os << "order no. " << present.unique_id;
    os << " customer; " << present.customer_name << std::endl;

    // std::vector<std::string>::iterator name;
    // std::vector<int>::iterator price;
    // std::vector<std::string>na = present.names_of_disches;
    // std::vector<int>order = present.order_details;
    // int i = 1;
    // price = order.begin();
    // name = na.begin();
    // while (price<order.end())
    // {
    //     std::string n = std::to_string(name);
    //     os<<i<<" "<<n<<" "<<price<<std::endl;
    //     // sum += price;
    //     name++;
    //     price++;
    // }

    int i = 0;
    while (i < size)
    {
        os << i + 1 << " " << present.names_of_disches[i] << " " << present.order_details[i] << std::endl;
        sum += present.order_details[i];
        i++;
    }

    os << "Total cost: " << sum << std::endl;
    return os;
}

ConsumerOrder &ConsumerOrder::operator=(const int price)
{
    order_details[update_index] = price;
    return *this;
}

bool ConsumerOrder::operator>(ConsumerOrder &second)
{
    if (this->getTotalCost() > second.getTotalCost())
    {
        return true;
    }
    return false;
}

ConsumerOrder::~ConsumerOrder()
{
    names_of_disches.erase(names_of_disches.begin(), names_of_disches.end());
    order_details.erase(order_details.begin(), order_details.end());
}
int ConsumerOrder::unique_id_handler = 1;

int main()
{
    std::cout << ConsumerOrder::getOrderCount() << std::endl;
    ConsumerOrder o1("Rakib Hasan");
    // std::cout << ConsumerOrder::getOrderCount() << std::endl;
    std::cout << o1.getCustomer() << std::endl;
    o1.addDish("vegetable soup", 20);
    o1.addDish("apple pie", 19);
    std::cout << o1.length() << std::endl;
    std::cout << o1;
    ConsumerOrder oo("Andrew Taylor");
    oo.addDish("tomato soup", 20);
    oo.addDish("grilled chicken", 45);
    oo.addDish("tomato soup", 20);
    oo.addDish("ice cream", 15);
    std::cout << oo;
    std::cout << "------------------------------" << std::endl;
    if (oo > o1)
        std::cout << "Order " << oo.getID() << " is more expensive than " << o1.getID();
    o1[1] = 21;
    oo.removeDish("tomato soup");
    std::cout << std::endl;
    std::cout << ConsumerOrder::getOrderCount() << std::endl;
    ConsumerOrder o2 = o1;
    ConsumerOrder o3;
    o3 = o1;
    return 0;
}
