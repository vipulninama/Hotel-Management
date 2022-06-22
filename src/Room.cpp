#include "Room.h"

Room::Room()
{
    ifstream RoomCount("Room.txt");
    string str;
    int Count = 0;
    while (getline(RoomCount, str))
    {
        int n = stoi(str);
        if (Count == 0)
        {
            Count ++;
            DeluxeRoomSingle(n);
        }
        if (Count == 1)
        {
            Count ++;
            DeluxeRoomDouble(n);
        }
        if (Count == 2)
        {
            Count ++;
            AffordableRoomSingle(n);
        }
        if (Count == 3)
        {
            Count ++;
            AffordableRoomDouble(n);
        }
        if (Count == 4)
        {
            Count ++;
            LuxuryRoomSingle(n);
        }
        if (Count == 5)
        {
            LuxuryRoomDouble(n);
        }
    }
    RoomCount.close();
}

void Room::AddRoom()
{
    ifstream RoomCount("Room.txt");
    int ArrRoom[6], i = 0;
    string str;

    while (getline(RoomCount, str))
    {
        int n = stoi(str);
        ArrRoom[i] = n;
        i++;
    }
    RoomCount.close();
    int t, n, f = 0;
    while (true)
    {
        cout<<"\n\tEnter corresponding number to add type of room:"<<endl;
        cout<<"\t1. DeluxeRoomSingle"<<endl;
        cout<<"\t2. DeluxeRoomDouble"<<endl;
        cout<<"\t3. AffordableRoomSingle"<<endl;
        cout<<"\t4. AffordableRoomDouble"<<endl;
        cout<<"\t5. LuxuryRoomSingle"<<endl;
        cout<<"\t6. LuxuryRoomDouble"<<endl;
        cout<<"\t7. Exit"<<endl<<endl;
        cout<<"\tEnter Choice: ";
        cin>>t;
        if (t == 1 || t == 2 || t==3 || t == 4 || t == 5 || t == 6)
        {
            cout<<"\nEnter number of Rooms to add: ";
            cin>>n;
        }

        switch(t)
        {
            case (1):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (2):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (3):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (4):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (5):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (6):
                ArrRoom[t - 1] = ArrRoom[t - 1] + n;
                break;

            case (7):
                f = 1;
                break;

            default:
                cout<<"Enter correct choice number"<<endl;

        }
        if (f == 1)
            break;
    }

    ofstream RoomCountUpdate("Room.txt");
    for (int i = 0; i < 6; i++)
    RoomCountUpdate<<to_string(ArrRoom[i])<<endl;
    RoomCountUpdate.close();
}

void Room::DeluxeRoomSingle(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 100 + i;
    }
    DeluxeRoomSingleNo = arr;
}

void Room::DeluxeRoomDouble(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 200 + i;
    }
    DeluxeRoomDoubleNo = arr;
}

void Room::AffordableRoomSingle(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 300 + i;
    }
    AffordableRoomSingleNo = arr;
}

void Room::AffordableRoomDouble(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 400 + i;
    }
    AffordableRoomDoubleNo = arr;
}

void Room::LuxuryRoomSingle(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 500 + i;
    }
    LuxuryRoomSingleNo = arr;
}

void Room::LuxuryRoomDouble(int Count)
{
    int *arr = (int *)malloc(sizeof(int)*Count);
    for (int i = 1; i <= Count; i++)
    {
        arr[i - 1] = 600 + i;
    }
    LuxuryRoomDoubleNo = arr;
}

void Room::DisplayRoom()
{
    ifstream RoomCount("Room.txt");
    int ArrRoom[6], i = 0;
    string str;

    while (getline(RoomCount, str))
    {
        int n = stoi(str);
        ArrRoom[i] = n;
        i++;
    }
    RoomCount.close();
    cout<<endl<<endl;
    cout<<"\tDeluxe Room Single\t: "<<ArrRoom[0]<<endl;
    cout<<"\tDeluxe Room Double\t: "<<ArrRoom[1]<<endl;
    cout<<"\tAffordable Room Single\t: "<<ArrRoom[2]<<endl;
    cout<<"\tAffordable Room Double\t: "<<ArrRoom[3]<<endl;
    cout<<"\tLuxury Room Single\t: "<<ArrRoom[4]<<endl;
    cout<<"\tLuxury Room Double\t: "<<ArrRoom[5]<<endl;
    cout<<endl<<endl;
}


