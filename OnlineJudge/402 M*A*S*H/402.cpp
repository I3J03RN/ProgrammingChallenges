#include <forward_list>
#include <iostream>
#include <list>
#include <vector>

typedef unsigned int uint;
using namespace std;

struct node {
    node() : data(0), next(nullptr), prev(nullptr) {}
    uint data;
    node* next;
    node* prev;

    void insert_after(node* node) {
        node->prev = this;

        this->next = node;
    }

    void remove(node*& start) {
        if (this->prev != nullptr) this->prev->next = this->next;
        if (this->next != nullptr) this->next->prev = this->prev;
        if (this == start) start = this->next;
    }
};

int main() {
    uint selection = 1;
    while (true) {
        uint numberOfPeople, luckySpots;
        cin >> numberOfPeople >> luckySpots;
        if (cin.eof()) return 0;

        list<uint> cards;
        for (uint i = 0; i < 20; ++i) {
            uint tmp;
            cin >> tmp;
            cards.push_back(tmp);
        }

        node* start;
        node* people = new node[numberOfPeople];
        for (uint i = 0; i < numberOfPeople; ++i) {
            people[i].data = i + 1;
        }

        for (uint i = 1; i < numberOfPeople; ++i)
            people[i - 1].insert_after(&people[i]);

        start = people;

        if (numberOfPeople > luckySpots) {
            for (uint currentCard : cards) {
                uint counter = 0;
                for (node* it = start; it != nullptr; it = it->next) {
                    counter++;
                    if (counter == currentCard) {
                        it->remove(start);
                        counter = 0;
                        numberOfPeople--;
                        if (numberOfPeople == luckySpots) goto end;
                    }
                }
            }
        }
    end:

        cout << "Selection #" << selection++ << "\n";
        for (node* it = start; it != nullptr; it = it->next) {
            cout << it->data;
            if (it->next != nullptr) cout << " ";
        }
        cout << "\n\n";

        delete[] people;
    }
}
