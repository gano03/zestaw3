// arraylist.h 

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert> 
#include <algorithm>   // assert()

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
        else
        {
            std::cout << "Nie skopiowano listy\n";
            return (ArrayList&)other;
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
        return *this;
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
            for (int i = last; i > 0; i--)
            {
                tab[i] = tab[i - 1];
            }
            tab[0] = item;
            last++;
        }
    } // dodanie na poczatek
    //void push_front(T&& item); // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item)
    {
        if (last == msize)
        {
            std::cout << "Kolejka jest pelna\n";
        }
        else
        {
            tab[last] = item;
            last++;
        }
    } // dodanie na koniec
    //void push_back(T&& item); // dodanie na koniec NIEOBOWIAZKOWE
    T& front()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
            return tab[-1];
        }
        else
        {
            return tab[0];
        }
    } // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
            return tab[-1];
        }
        else
        {
            return tab[last-1];
        }
    } // zwraca koniec, nie usuwa, error dla pustej listy
    void pop_front()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            for (int i = 0; i < last; i++)
            {
                tab[i] = tab[i+1];
            }
            last--;
        }
    } // usuwa poczatek, error dla pustej listy
    void pop_back()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            tab[last-1] = 0;
        }
        last--;
    } // usuwa koniec, error dla pustej listy
    void clear()
    {
        for (int i = 0; i < last; i++)
        {
            tab[i] = 0;
        }
    } // czyszczenie listy z elementow
    void display()
    {
        for (int i = 0; i < last; i++)
        {
            std::cout << tab[i] << " ";
            if (i == last-1)
            {
                std::cout << "\n";
            }
        }
    } // lepiej zdefiniowac operator<<
    void reverse()
    {
        T pom[last];
        for (int i = 0; i < last; i++)
        {
            pom[i] = tab[i];
        }
        for (int i = 0; i < last; i++)
        {
            tab[i] = pom[last-1-i];
        }
    } // odwracanie kolejnosci
    void sort()
    {
        for (int i = 0; i < last; i++)
        {
            for (int j = 0; j < last; j++)
            {
                if (tab[j-1] > tab[j])
                {
                    std::swap (tab[j-1], tab[j]);
                }
            }
        }
    } // sortowanie listy
    void merge(ArrayList& other); //  merges two sorted lists into one
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos)
    {
        if (last == msize)
        {
            std::cout << "Kolejka jest pelna\n";
            return tab[-1];
        }
        if (pos > last)
        {
            std::cout << "Niedozwolona pozycja\n";
            return tab[-1];
        }
        else
        {
            for (int i = last; i > pos; i--)
            {
                tab[i] = tab[i-1];
            }
            last++;
            return tab[pos];
        }
    } // podstawienie L[pos]=item
    const T& operator[](int pos) const
    {
        return tab[pos];
    } // odczyt L[pos]
    void erase(int pos)
    {
        for (int i = pos; i < last-1; i++ )
        {
            tab[i] = tab[i+1];
        }
        last--;
    } // usuniecie elementu na pozycji pos
    int index(const T& item)
    {
        for (int i = 0; i < last; i++)
        {
            if (tab[i] == item)
            {
                return i;
            }
        }
        return -1;
    } // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item)
    {
        if (pos > last+1)
        {
            std::cout << "Error, niedozwolona pozycja\n";
            return;
        }
        for (int i = last; i >=pos-1 ; i--)
        {
            tab[i] = tab[i-1];
        }
        tab[(pos-1)] = item;
        last++;
    } // inserts item before pos
    void insert(int pos, T&& item)
    {
        if (pos > last+1)
        {
            std::cout << "Error, niedozwolona pozycja\n";
            return;
        }
        if (pos == size())
        {
            tab[last] = item;
            last++;
            return;
        }
        for (int i = last; i >=pos-1 ; i--)
        {
            if (i == 0)
                {
                    tab[0] = item;
                    last++;
                    return;
                }
            tab[i] = tab[i-1];
        }
        tab[(pos-1)] = item;
        last++;
   
    } // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
    int retlast(void)
    {
        return last;
    }
};

#endif

// EOF