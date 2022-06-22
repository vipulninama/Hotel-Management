#ifndef ROOM_H
#define ROOM_H
#include <bits/stdc++.h>
using namespace std;

class Room
{
    friend class GuestReservation;
    public:
        Room();
        void AddRoom();
        void DisplayRoom();

    protected:

    private:
        void DeluxeRoomSingle(int Count);
        void DeluxeRoomDouble(int Count);
        void AffordableRoomSingle(int Count);
        void AffordableRoomDouble(int Count);
        void LuxuryRoomSingle(int Count);
        void LuxuryRoomDouble(int Count);
        int *DeluxeRoomSingleNo, *DeluxeRoomDoubleNo, *AffordableRoomSingleNo, *AffordableRoomDoubleNo, *LuxuryRoomSingleNo, *LuxuryRoomDoubleNo;
};
#endif // ROOM_H
