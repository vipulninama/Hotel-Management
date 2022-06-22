#include <iostream>
#include "GuestReservation.h"
#include "Room.h"
using namespace std;

int main()
{
    GuestReservation G;
    Room R;
    char ch;
    cout<<"--------------------WELCOME--------------------"<<endl<<endl;
    do
    {
        cout<<"\n\n\tPress The following for respective functions:"<<endl<<endl;
        cout<<"\t1. Add Rooms to existing rooms in database"<<endl;
        cout<<"\t2. Display number of existing rooms in database"<<endl;
        cout<<"\t3. Check - In"<<endl;
        cout<<"\t4. Display All Existing Guests"<<endl;
        cout<<"\t5. Check - Out"<<endl;
        cout<<"\t6. Exit"<<endl;

        cout<<"\tEnter Choice: ";
        cin>>ch;

        switch(ch)
        {
            case ('1'):
            {
                R.AddRoom();
                break;
            }

            case ('2'):
            {
                R.DisplayRoom();
                break;
            }

            case ('3'):
            {
                G.CheckInGuest();
                break;
            }

            case ('4'):
            {
                G.Display();
                break;
            }

            case ('5'):
            {
                G.CheckOutGuest();
                break;
            }

            case ('6'):
            {
                cout<<"--------------------THANK YOU--------------------"<<endl<<endl;
                break;
            }

            default:
                cout<<"Please Enter Choice Again"<<endl<<endl;
        }

    }while (ch != '6');

    return 0;
}

