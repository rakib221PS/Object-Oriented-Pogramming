#include <iostream>
#include <stdexcept>
#include <vector>

class Figure{
    static int figures;
    public:
    static int total_figures();
    // virtual void getNumber() = 0;
    // virtual int getScale() = 0;
    virtual void getArea(int, int, int);
    virtual void getParameter() = 0;
    virtual ~Figure();
};

Figure::~Figure(){
    std::cout<<"Figure has destroyer";
}

void Figure::getArea(int a, int b, int c){
    
}

int Figure::total_figures(){
    return figures;
}

int Figure::figures = 0;

class Circle:public Figure{
    int radius;
    public:
    Circle(){}
    Circle(float);
    void getArea();
    void getParameter();
    virtual ~Circle();
};

Circle::Circle(float radius):radius(radius){}

void Circle::getArea(){
    std::cout<<"this is my area, get out from here"<<std::endl;
}

void Circle::getParameter(){
    std::cout<<"give me some dollars as parameter"<<std::endl;
}

Circle::~Circle(){
    std::cout<<"circle destructor";
}

class FigureSet{
    int len;
    int size;
    Circle *circle_set = new Circle[size];
    public:
    FigureSet(int size):size(size){}
    void sizeOfArray(){
        std::cout<<sizeof(FigureSet[0])/sizeof(FigureSet);
    }
};

int main(){
    Circle *cir = new Circle(1.3);
    cir->getParameter();
    // delete cir;
    // FigureSet fig(4);
    // fig.sizeOfArray();
    return 0;
}