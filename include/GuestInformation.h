#ifndef GUESTINFORMATION_H
#define GUESTINFORMATION_H
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class GuestInformation
{
    friend class GuestReservation;

    public:
        void GetGuestInformation();

    protected:

    private:
        string Name;
        string Aadhar;
        string Phone;
        string NoOfPeople;
        bool Number(string s);
        bool Alphabet(string s);
        bool Date(string s);
};

#endif // GUESTINFORMATION_H
