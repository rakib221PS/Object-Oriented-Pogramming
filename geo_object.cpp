#include <iostream>
#include <stdexcept>
#include <vector>

class GeoObject{
    public:
    int latitude, longitude;
    std::string label;
    
    public:
    void setters(int lat, int lon, std::string info){
        latitude = lat;
        longitude = lon;
        label = info;
    }

    void setLabel(std::string info){
        label = info;
    }

    virtual void printInfo(){
        std::cout<<"this is label from Geo object"<<std::endl;
    }

     virtual ~ GeoObject(){
        std::cout<<"geo object destructor"<<std::endl;
    }
};

class Point{
    int size;
    std::vector<GeoObject>geoVector;
    public:
    Point():size(5){
        geoVector.resize(size);
    }

    virtual ~Point(){
        std::cout<<"Point destrutor"<<std::endl;
    }
};

class Marker: public GeoObject{
    int size;
    std::string color;
    public:

    Marker(){};
    
    Marker(int lat, int lon, std::string info, int size, std::string color){
        // GeoObject::setters(lat, lon, info);
        // setters(size, color);
    }

    void setters(int size, std::string color){
        size = size;
        color = color;
    }

    virtual void printInfo(){
        std::cout<<"this is label form marker"<<std::endl;
        GeoObject::printInfo();
    }

    virtual ~Marker(){
        std::cout<<"Marker destructor"<<std::endl;
    }
};

class Polygons: public GeoObject{
    std::string fill_color, border_color;
    GeoObject *geoArray = new GeoObject[5];
    public:

    virtual ~ Polygons(){
        std::cout<<"Polygons destructor"<<std::endl;
    }
};

class Layer{
    Marker * polyObject = new Marker[5];
    public:

    Layer(std::string name){

    }

    void addObject(Marker &make){}
};

int main(){
    // GeoObject geo;
    // Point p;
    // Marker *p = new Marker();
    // GeoObject *ge = p;
    // delete ge;
    
    // Marker p;
    // p.printInfo();

    // Polygons poly;

    Layer layer("Layer 1");
    // Layer.addObject(new Marker(2,3,"point 1",10,"no point"));
    new Marker(2,3,"r",8,"rtt");

    return 0;
}