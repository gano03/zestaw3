// arraylist.h 

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; }
    ArrayList(const ArrayList& other)
    {
        last = other.last;
        msize = other.msize;
        for (int i = 0; i < last; i++)
        {
            tab[i] = other.tab[i];
        }
    } // copy constructor
    // usage:   ArrayList<int> list2(list1);
    ArrayList(ArrayList&& other)
    {
        *this = std::move(other);
        other.last = 0;
        other.msize = 0;
        for (int i = 0; i < last; i++)
        {
            other.tab[i] = 0;
        }
    } // move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));
    ArrayList& operator=(const ArrayList& other)
    {
        if (this != &other)
        {
            last = other.last;
            msize = other.msize;
            for (int i = 0; i < last; i++)
            {
                tab[i] = other.tab[i];
            }
            return *this;

        }
    } // copy assignment operator, return *this
    // usage:   list2 = list1; NIEOBOWIAZKOWE
    ArrayList& operator=(ArrayList&& other)
    {   
        if (this != &other)
        {
            *this = std::move (other);
            other.last = 0;
            other.msize = 0;
            for (int i = 0; i < last; i++)
            {
                other.tab[i] = 0;
            }
        }
        return *this
    } // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item)
    {
        if (last == msize)
        {
            std::cout << "Lista jest pelna\n";
        }
        else
        {
            for (int i = last + 1; i > 0; i--)
            {
                tab[i] = tab[i - 1];
            }
            tab[0] = item;
            last++;
        }
    } // dodanie na poczatek
    void push_front(T&& item); // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item)
    {
        if (last == msize)
        {
            std::cout << "Kolejka jest pelna\n";
        }
        else
        {
            tab[last] = item;
        }
    } // dodanie na koniec
    void push_back(T&& item); // dodanie na koniec NIEOBOWIAZKOWE
    T& front()
    {
        if (last = 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            return tab[0];
        }
    } // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back()
    {
        if (last = 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            return tab[last];
        }
    } // zwraca koniec, nie usuwa, error dla pustej listy
    void pop_front()
    {
        if (last = 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            for (int i = last; i >0; i--)
            {
                tab[i-1] = tab[i];
            }
        }
    } // usuwa poczatek, error dla pustej listy
    void pop_back()
    {
        if (last = 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            tab[last] = 0;
        }
    } // usuwa koniec, error dla pustej listy
    void clear(); // czyszczenie listy z elementow
    void display(); // lepiej zdefiniowac operator<<
    void reverse(); // odwracanie kolejnosci
    void sort(); // sortowanie listy
    void merge(ArrayList& other); //  merges two sorted lists into one
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    void erase(int pos); // usuniecie elementu na pozycji pos
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item); // inserts item before pos
    void insert(int pos, T&& item); // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF