#include "valetparking.hpp"

// ATTENTION STUDENTS:
// THE CONSTRUCTORS ARE ALREADY COMPLETED.
// YOU NEED TO COMPLETE THE DESTRUCTOR AND ALL OF THE REMAINING FUNCTIONS BELOW.

// CONSTRUCTORS - ALREADY COMPLETE
ValetParking::ValetParking() : _numberofstalls(1), _stallcapacity(1), _queuecapacity(1), _currentticket(0),
_fee(5.0), _paid(0.0), _checkout(new std::queue<size_t>()), _parkingstall(_numberofstalls, std::stack<size_t>())
{}

ValetParking::ValetParking(size_t numberofstalls, size_t stallcapacity,
    size_t queuecapacity, size_t ticketnumber, double fee) : _numberofstalls(numberofstalls), _stallcapacity(stallcapacity), _queuecapacity(queuecapacity), _currentticket(ticketnumber),
    _fee(fee), _checkout(new std::queue<size_t>()), _parkingstall(_numberofstalls, std::stack<size_t>()), _paid(0.0)
{}

// written by Vincent Diep
// DESTRUCTOR
ValetParking::~ValetParking()
{
    // release dynamic queue
    delete _checkout;
    // set other variables to 0
    _numberofstalls, _stallcapacity, _queuecapacity, _currentticket = 0;
    _fee, _paid = 0.0;
}

// written by Vincent Diep
size_t ValetParking::totalStallSpaces()
// return the maximum number of cars that all stalls can accommodate
{
    // find max capacity by multiplying number of stalls and stall capacity
    return _numberofstalls * _stallcapacity;
}

// written by Vincent Diep
size_t ValetParking::carsInStalls()
// return the number of cars parked in all the stalls
{
    size_t totalCars = 0;
    for (auto e : _parkingstall)
    {
        totalCars += e.size();  // adds up total number of cars from each stall
    }
    return totalCars;
}

// written by Vincent Diep
size_t ValetParking::carsInCheckOut()
// return the number of cars waiting in checkout line to pay before exiting the lot.
{
    return _checkout->size();   // returns number in checkout queue
}

// written by Vincent Diep
size_t ValetParking::availableStallSpaces()
// return the number of available parking spaces in all the stalls
{
    return (totalStallSpaces() - carsInStalls());   // available spaces = maximum capacity - occupied spaces
}

// written by Vincent Diep
double ValetParking::totalSales()
// return the total amount based on the number of tickets issued
{
    return _currentticket;  // current ticket is also counter for total issued
}

// written by Vincent Diep
size_t ValetParking::pay()
// remove and return the ticket# of car at front of the checkout queue, and the fee is collected.
{
    _paid += _fee;  // add fee to total transaction amount
    size_t temp = _checkout->front();   // store the value at front of queue
    _checkout->pop();   // remove front of queue
    return temp;    // return the value that was at the front
}

// written by Vincent Diep
double ValetParking::totalPaid()
// return the total amount customers have paid so far based on the number of cars exited the lot.
{
    return _paid;   // returns accumulated total
}

// written by Vincent Diep
bool ValetParking::parkingEmpty()
// return true if all stalls and checkout queue are empty
{
    // checks if all stalls are empty, then if checkout queue is empty
    return (carsInStalls() == 0 &&
        _checkout->size() == 0);
}

// written by Vincent Diep
bool ValetParking::parkingFull()
// return true if all stalls and checkout queue are full
{
    //  checks occupied spaces with maximum capacity for if stalls and checkout are full
    return (carsInStalls() == totalStallSpaces()
        && _checkout->size() == _queuecapacity);
}

// written by Vincent Diep
bool ValetParking::queueEmpty()
// return true if the checkout queue is empty
{
    // compare checkout size with 0(empty)
    return (_checkout->size() == 0);
}

// written by Vincent Diep
bool ValetParking::queueFull()
// return true if the checkout queue is full
{
    // checkout is full if size equals capacity
    return (_checkout->size() == _queuecapacity);
}

// written by Vincent Diep
bool ValetParking::stallEmpty()
// return true if all stalls are empty
{
    // compares number of occupancies with 0(empty)
    return (carsInStalls() == 0);
}

// written by Vincent Diep
bool ValetParking::stallFull()
// return true if all stalls are full
{
    // compares number of occupancies with total capacity of stalls
    return (carsInStalls() == totalStallSpaces());
}

// written by Vincent Diep
size_t ValetParking::getNextTicket()
// return the next ticket number to issue to customer
{
    return ++_currentticket;    // increments ticket and gives new number to customer
}

// written by Vincent Diep
size_t ValetParking::checkIn()
// on success return stall# (index-1 base), on failure return 0.
{
    if (stallFull()) { return 0; } // check if stalls full

    for (size_t i = 0; i < _numberofstalls; i++)    // checks each stall
    {
        if (_parkingstall[i].size() != _stallcapacity)  // checks if stall is full
        {
            _parkingstall[i].push(getNextTicket());     // pushes ticket into open stall

            return i + 1;       // returns stall number (index-1 base)
        }
    }

    return 0;
}

// written by Vincent Diep
size_t ValetParking::stallNumber(size_t ticket)
// return the stall number (index-1 base) in which the ticket number resides
{

    for (auto e : _parkingstall)        // checks every stall
    {
        for (size_t i = 0; i < _numberofstalls; i++)    // check every ticket in stall
        {
            std::stack<size_t> temp = _parkingstall[i];
            for (size_t j = 0; j < _stallcapacity; j++)
            {
                if (temp.top() == ticket)       // check using temp stall to avoid pushing values
                {                               // back into original stall
                    return i + 1;
                }
                temp.pop();
            }
        }
    }

}

// written by Vincent Diep
bool ValetParking::checkOut(size_t stallnumber, size_t ticket)
// Retrieve the ticket# from the stall and place the ticket in the checkout queue.
// On success return true.
{
    if (_parkingstall[stallnumber - 1].empty()) // check for empty
    {
        return false;
    }

    std::stack<size_t> temp;
    size_t stallSize = _parkingstall[stallnumber - 1].size();   // make variable to avoid calling
                                                                // multiple times in loops

    for (size_t i = 0; i < stallSize; i++)  // searches for ticket in given stall
    {
        if (_parkingstall[stallnumber - 1].top() == ticket) // if there is a match
        {
            _parkingstall[stallnumber - 1].pop();   // remove ticket
            _checkout->push(ticket);    // add ticket to queue

            for (size_t j = 0; j < i; j++)  // add back values from temp
            {
                _parkingstall[stallnumber - 1].push(temp.top());
                temp.pop();
            }
            return true;
        }
        temp.push(_parkingstall[stallnumber - 1].top());    // store values in temp
        _parkingstall[stallnumber - 1].pop();   // pop from original stall to traverse values
    }

    size_t tempSize = temp.size();  // make variable to avoid calling
                                    // multiple times in loops

    for (size_t i = 0; i < tempSize; i++)   // returns values back to original stall from temp stall
    {
        _parkingstall[stallnumber - 1].push(temp.top());
        temp.pop();
    }
    return false;
}
