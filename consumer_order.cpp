#include <iostream>
#include <stdexcept>
#include <vector>

class ConsumerOrder
{
    static int total_consumer_order;
    int most_expensive_index = 0;
    int single_consumer_order = 0;
    int update_index;
    std::string customer_name;
    // std::string *names_of_disches = new std::string[5];
    std::vector<std::string> names_of_disches;
    // int **order_details = new int *[5];
    std::vector<std::vector<int>> order_details;

public:
    static int getOrderCount();
    ConsumerOrder();
    ConsumerOrder(std::string);
    ConsumerOrder(const ConsumerOrder &);
    void operator=(const ConsumerOrder &);
    void setCustomer();
    std::string getCustomer();
    int getID();
    void addDish(const std::string, const int);
    void removeDish(const std::string);
    int length();
    ~ConsumerOrder();
    ConsumerOrder &operator[](const int index)
    {
        if (index >= single_consumer_order)
        {
            throw std::runtime_error("Overflow");
        }
        update_index = index;
    }
    // --------------------------------------------------------------------------operator<< declaration---------------
    friend std::ostream& operator<<(std::ostream &os, const ConsumerOrder &parent);
    // void operator<<(const ConsumerOrder &);
    bool operator>(ConsumerOrder &);
};

ConsumerOrder::ConsumerOrder() : names_of_disches(5), order_details(5)
{
    for (int i = 0; i < 5; i++)
    {
        // order_details[i] = new int[2];
        order_details[i] = std::vector<int>(2);
    }
}

ConsumerOrder::ConsumerOrder(const std::string name) : names_of_disches(5), order_details(5)
{
    customer_name = name;
    for (int i = 0; i < 5; i++)
    {
        // order_details[i] = new int[2];
        order_details[i] = std::vector<int>(2);
    }
    if (single_consumer_order <= 0)
    {
        total_consumer_order++;
    }
    std::cout << customer_name << std::endl;
}

ConsumerOrder::ConsumerOrder(const ConsumerOrder &parent)
{
    if (this != &parent)
    {
        this->customer_name = parent.customer_name;
        this->single_consumer_order = parent.single_consumer_order;
        this->most_expensive_index = parent.most_expensive_index;
        this->update_index = parent.update_index;

        for (int i = 0; i < parent.single_consumer_order; i++)
        {
            names_of_disches[i] = parent.names_of_disches[i];
            order_details[i][0] = parent.order_details[i][0];
            order_details[i][1] = parent.order_details[i][1];
        }
    }
}

void ConsumerOrder::operator=(const ConsumerOrder &parent)
{
    if (this != &parent)
    {
        customer_name = parent.customer_name;
        single_consumer_order = parent.single_consumer_order;
        most_expensive_index = parent.most_expensive_index;
        update_index = parent.update_index;

        for (int i = 0; i < parent.single_consumer_order; i++)
        {
            names_of_disches[i] = parent.names_of_disches[i];
            order_details[i][0] = parent.order_details[i][0];
            order_details[i][1] = parent.order_details[i][1];
        }
    }
}

std::string ConsumerOrder::getCustomer()
{
    return customer_name;
}

int ConsumerOrder::getID()
{
    return order_details[most_expensive_index][1];
}

void ConsumerOrder::addDish(const std::string dish_name, const int price)
{
    names_of_disches[single_consumer_order] = dish_name;
    order_details[single_consumer_order][0] = price;
    order_details[single_consumer_order][1] = (single_consumer_order + 1) * 1000000;
    single_consumer_order++;
}

void ConsumerOrder::removeDish(const std::string dish_name)
{
    int deleting_index = 0;
    for (int i = 0; i < single_consumer_order; i++)
    {
        if (names_of_disches[i] == dish_name)
        {
            deleting_index = i;
            // break;
        }
    }

    names_of_disches.erase(names_of_disches.begin()+deleting_index);
    order_details[deleting_index].clear();
    order_details.erase(order_details.begin() + deleting_index);
}

int ConsumerOrder::length()
{
    return single_consumer_order;
}

int ConsumerOrder::getOrderCount()
{
    if (total_consumer_order <= 0)
    {
        return 0;
    }
    else
    {
        return total_consumer_order;
    }
}

// --------------------------------------------------------------------------------operator<< implementation----------

std::ostream& operator<<(std::ostream& os, const ConsumerOrder &present)
{
    int sum = 0;
    os << "customer; " << present.customer_name << std::endl;
    for (int i = 0; i < present.single_consumer_order; i++)
    {
        os << i + 1 << ". " << present.names_of_disches[i] << " " << present.order_details[i][1] << std::endl;
        sum = sum + present.order_details[i][0];
    }
    os << "Total cost: " << sum << std::endl;
    return os;
}


bool ConsumerOrder::operator>(ConsumerOrder &second)
{
    this->most_expensive_index = 0;
    second.most_expensive_index = 0;
    int first_order_price = this->order_details[0][0];
    for (int i = 1; i < this->single_consumer_order; i++)
    {
        if (this->order_details[i][0] > first_order_price)
        {
            first_order_price = order_details[i][0];
            this->most_expensive_index = i;
        }
    }

    int second_order_price = second.order_details[0][0];
    for (int i = 1; i < second.single_consumer_order; i++)
    {
        if (this->order_details[i][0] > first_order_price)
        {
            first_order_price = order_details[i][0];
            second.most_expensive_index = i;
        }
    }

    if (first_order_price > second_order_price)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ConsumerOrder:: ~ConsumerOrder(){
    names_of_disches.erase(names_of_disches.begin(), names_of_disches.end());
    for (int i = 0; i < single_consumer_order; i++)
    {
       order_details[i].clear();
       order_details.erase(order_details.begin());
    }
}
int ConsumerOrder::total_consumer_order = 0;

int main()
{
    std::cout << ConsumerOrder::getOrderCount() << std::endl;
    ConsumerOrder o1("Rakib Hasan");
    std::cout << o1.getCustomer() << std::endl;
    o1.addDish("vegetable soup", 20);
    o1.addDish("apple pie", 19);
    std::cout << o1.length() << std::endl;
    // -----------------------------------------------------------issue start-------------------------
    // here std::cout<<o1 is not matching with implement overloading
    std::cout<<o1;
    // -----------------------------------------------------------issue end-------------------------
    ConsumerOrder oo("Andrew Taylor");
    oo.addDish("tomato soup", 20);
    oo.addDish("grilled chicken", 45);
    oo.addDish("tomato soup", 20);
    oo.addDish("ice cream", 15);
    if (oo > o1)
        std::cout << "Order " << oo.getID() << " is more expensive than " << o1.getID();
    //  o1[1] = 21;
    oo.removeDish("tomato soup");
    std::cout << std::endl;
    std::cout << ConsumerOrder::getOrderCount() << std::endl;
    // -----------------------------------------------------------issue start-------------------------
    // here vector memory is not allocationg
    ConsumerOrder o2 = o1;
    // -----------------------------------------------------------issue end-------------------------
    ConsumerOrder o3;
    o3 = o1;
    return 0;
}

// please fix this problem or give me some resources that I can figure out
