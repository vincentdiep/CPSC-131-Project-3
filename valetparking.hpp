#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

// ATTENTION STUDENTS: DO NOT MODIFY THIS FILE TO MAKE YOUR CODE PASS. WE USE THE ORIGINAL FILE
// WHEN GRADING YOUR ASSIGNMENT.

class ValetParking
{
    public:

        ValetParking(); // default constructors
        ValetParking( size_t _numberofstalls, size_t stallcapacity, size_t queuecapacity,
                        size_t ticketnumber, double fee );        
        ~ValetParking();    // destructor

        bool parkingEmpty();        // true = stalls and checkout queue are empty
        bool parkingFull();         // true = stalls and checkout queue are full
        bool stallEmpty();          // true = stalls are empty
        bool stallFull();           // true = stalls are full
        bool queueEmpty();          // true = checkout queue is empty
        bool queueFull();           // true = checkout queue is full
        size_t getNextTicket();      // return the next ticket number to be issued to customer
        size_t checkIn();           // on success return stall# (index-1 base), on failure return 0.
        size_t stallNumber( size_t ticket); // return index-1 base stall number (stalls are numbered 1, 2, 3, ...n)
        bool checkOut( size_t stallnumber, size_t ticket ); // true = successfully removed ticket# from given stall and
                                                            // enqueue ticket# in checkout line
        size_t pay();               // return the ticket# from the front of the checkout queue after customer paid fee
        double totalSales();        // return the total sales worth based on total number of tickets issued
        double totalPaid();         // return the total cash paid based on number of paid tickets
        size_t carsInStalls();      // return total cars parked in all stalls
        size_t carsInCheckOut();    // return total cars waiting in checkout line ready to pay
        size_t availableStallSpaces();  // return number of available parking spaces in the stalls area
        size_t totalStallSpaces();  // return the number of cars that the stalls can accommodate
        
    private:

        size_t _numberofstalls;     // number of stalls (or aisles)
        size_t _stallcapacity;      // number of cars that each stall (or aisle) can accommodate
        std::vector<std::stack<size_t> > _parkingstall;    // an STL vector holding STL stall stacks
        size_t _queuecapacity;      // number of cars the checkout queue can accommodate
        std::queue<size_t> * _checkout; // an STL queue is used to implement the checkout line
        size_t _currentticket;      // this is the current ticket number issued to customer
        double _fee;                // this is the valet parking fee
        double _paid;               // this is the total transaction amount so far from paid cars exiting the lot

        // NOTE: ticket# and stall# are index-1 base, meaning they begin from numeral value 1.
}; 
