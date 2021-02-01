#pragma once
#include "../graphics/visualizer.h"

class Elem {
private:
	int data;
	int index;
public:
    Elem(int data_, int index_)
	 : data(data_), index(index_) {}

	 int getInd() const{
        return index;
    }

	 operator int() const {
        return data;
     };

    Elem &operator=(const Elem &tmp){
        std::cout << "Assignment" << std::endl;
        Visualizer::getInstance().pushCommand(new Assign(tmp.operator int(), getInd()));
        if (*this == tmp)
            return *this;
        this -> data = tmp.data;
        return *this;
    }

};

bool operator < (const Elem& tmp1, const Elem& tmp2){
    std::cout << "Comparing..." << std::endl;
    Visualizer::getInstance().pushCommand(new Compare(tmp1.getInd(), tmp2.getInd()));
    return tmp1.operator int() < tmp2.operator int();
}
