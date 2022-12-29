#include <iostream>
#include <stdexcept>
#include <vector>

class Logic_error
{
    void EmptyError()
    {
        throw std::runtime_error("");
    }
    void CapacityError()
    {
        throw std::runtime_error("");
    }
};

class Box
{
    public:
    float length, width, height;
    static int total_box;
    std::string box_contents;
    friend void accessProtected(const Box &);
    public:
    Box(float len, float wid, float hei):length(len), width(wid), height(hei){
        total_box++;
    }

    float getCapacity();
    static int getCount();
    friend std::ostream& operator<<(std::ostream& os, const Box &content);
};

float Box::getCapacity(){
    return length * width * height;
}

std::ostream& operator<<(std::ostream& os, const Box& content){
    os<<content.box_contents.size();
    return os;
}

int Box::getCount(){
    return total_box;
}

void accessProtected(const Box &access){
    std::cout<<access.length<<std::endl;
}

int Box::total_box = 0;

class ColouredBox: public Box{
    std::string color;
    public:
    ColouredBox(float, float, float, std::string);
    friend std::ostream& operator<<(std::ostream& os, const ColouredBox &colouredContent);
};

ColouredBox::ColouredBox(float len, float wid, float hei, std::string color):Box(len, wid, hei){
    color = color;
}

std::ostream& operator<<(std::ostream& os, const ColouredBox &colouredContent){
    // accessProtected(colouredContent.Box);
    // std::cout<<colouredContent.Box;
    // os<<colouredContent.Box.length;
    os<<colouredContent.color;
    return os;
}

int main()
{
    Box box1(2,3,4);
    std::cout<<box1.getCapacity()<<std::endl;
    std::cout<<box1.getCount()<<std::endl;
    std::cout<<box1<<std::endl;
    ColouredBox box2(1,2,3,"red");
    std::cout<<box2;
    return 0;
}