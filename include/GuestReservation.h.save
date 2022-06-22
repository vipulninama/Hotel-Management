#ifndef GUESTRESERVATION_H
#define GUESTRESERVATION_H
#include <bits/stdc++.h>
using namespace std;

struct GuestNode
{
    int BookingID;
    class GuestInformation *PersonalInfo;
};

class GuestReservation
{
    public:
        GuestReservation();
        void CheckInGuest();
        void CheckOutGuest();
        void Display();
        bool NotFind(int i);
        int BookID();
        list <GuestNode> GuestList;
        list <string> CheckIn;
        list <string> CheckOut;
        list <int> RoomAlloted;

    protected:

    private:
        string CheckInDate;
        string CheckOutDate;
        int RoomA;
        bool Number(string s);
        bool Date(string s);
        bool DateCompInOut(string CheckInDate, string CheckOutDate);
};

#endif // GUESTRESERVATION_H
