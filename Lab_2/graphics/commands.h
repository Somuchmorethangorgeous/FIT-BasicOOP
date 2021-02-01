#include <vector> 
#include "window.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(std::vector<int> &container, std::vector<Color> &colors) const = 0;
};


class Compare : public Command{
private:
    int index1;
    int index2;
public:
    Compare(int ind1, int ind2) : index1(ind1), index2(ind2) {};
    void execute(std::vector<int> &container, std::vector<Color> &colors) const  override {
        for (int i = 0; i < colors.size(); ++i){
            if (i == index1 || i == index2)
                colors[i].set(0, 255, 0, 1);
        }
    }
};


class Assign : public Command{
private:
    int data;
    int index;
public:
    Assign(int d, int ind) : data(d), index(ind){};
    void execute(std::vector<int> &container, std::vector<Color> &colors) const  override {
        container[index] = data;
    }
};