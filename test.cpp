#include "arraylist.h"
#include <iostream>
#include <cstdlib>

int main ()
{   
    ArrayList<int> obj;
    ArrayList<int> L;
    obj.back();
    obj.front();
    
    std::cout << "Empty " << obj.empty() <<"\n";
    obj[0] = 1;
    obj[1] = 3;
    obj[2] = 7;
    obj.insert(1,10);
    std::cout << "Empty " << obj.empty() <<"\n";

    std::cout << obj.index(10) <<"\n";
    std::cout << obj.index(1) <<"\n";
    std::cout << obj.index(3) <<"\n";
    std::cout << obj.index(7) <<"\n";

    obj.push_front(12);
    obj.push_back(14);
    std::cout << obj.front() <<"\n";
    std::cout << obj.back() << "\n";

    L = obj;
    L.display();

    L.erase(2);
    std::cout << "last to " <<L.retlast() << "\n";
    L.display();

    std::cout << "last to " <<L.retlast() << "\n";
    L.reverse();
    L.display();
    L.reverse();
    L.display();

    std::cout << "Rozmiar listy to " <<L.size() <<"\n";

    L.pop_front();
    L.pop_back();
    L.display();

    L.sort();
    L.display();

    L.clear();
    L.display();

    return 0;
}