#include "GuestReservation.h"
#include "GuestInformation.h"
#include "Room.h"

GuestReservation::GuestReservation()
{

    ifstream GuestInfo("GuestInformation.txt");
    string str;

    while (getline(GuestInfo, str))
    {
        GuestNode *gn = new GuestNode;
        GuestInformation *g = new GuestInformation;
        string ID, R, name, aadhar, phone, n;
        int Count = 0;
        for (char c: str)
        {
            if (c == ',')
            {
                Count++;
                continue;
            }

            if (Count == 0)
                ID = ID + c;
            if (Count == 1)
                name = name + c;
            if (Count == 2)
                aadhar = aadhar + c;
            if (Count == 3)
                phone = phone + c;
            if (Count == 4)
                n = n + c;

        }

        gn -> BookingID = stoi(ID);
        g -> Name = name;
        g -> Aadhar = aadhar;
        g -> Phone = phone;
        g -> NoOfPeople = n;
        gn -> PersonalInfo = g;
        GuestList.push_back(*gn);

        name.clear();
        aadhar.clear();
        phone.clear();
        n.clear();
    }
    GuestInfo.close();

    ifstream GuestCheckInDate("CheckInDate.txt");
    string str1;

    while (getline(GuestCheckInDate, str1))
    {
        for (char c: str1)
        {
            CheckInDate = CheckInDate + c;
        }

        CheckIn.push_back(CheckInDate);
        CheckInDate.clear();
    }
    GuestCheckInDate.close();


    ifstream GuestCheckOutDate("CheckOutDate.txt");
    string str2;

    while (getline(GuestCheckOutDate, str2))
    {
        for (char c: str2)
        {
            CheckOutDate = CheckOutDate + c;
        }
        CheckOut.push_back(CheckOutDate);
        CheckOutDate.clear();
    }
    GuestCheckOutDate.close();


    ifstream R("RoomAllot.txt");
    string str3;

    while (getline(R, str3))
    {
        string d;
        for (char c: str3)
        {
            d = d + c;
        }
        RoomA = stoi(d);
        RoomAlloted.push_back(RoomA);
    }
    R.close();
}

int GuestReservation::BookID()
{
    if (GuestList.size() == 0)
        return 1000;

    vector <int> ID;
    list <GuestNode> :: const_iterator itGL;
    itGL = GuestList.cbegin();

    while (itGL != GuestList.cend())
    {
        int I = (itGL) -> BookingID;
        ID.push_back(I);
        ++itGL;
    }
    int a = *max_element(ID.begin(), ID.end());
    return (a + 1);
}

void GuestReservation::CheckInGuest()
{
    cout<<endl<<endl;
    Room r;
    GuestNode *gn = new GuestNode;
    GuestInformation *g = new GuestInformation;

    g -> GetGuestInformation();
    gn -> PersonalInfo = g;
    gn -> BookingID = BookID();

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

    while (true)
    {
        while (true)
        {
            cout<<"\n\tEnter Check - In Date (in DD/MM/YYYY): ";
            cin>>ws;
            getline(cin, CheckInDate);
            if (!Date(CheckInDate))
                cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
            else
                break;
        }

        while (true)
        {
            cout<<"\n\tEnter Check - Out Date (in DD/MM/YYYY): ";
            cin>>ws;
            getline(cin, CheckOutDate);
            if (!Date(CheckOutDate))
                cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
            else
                break;
        }

        if (DateCompInOut(CheckInDate, CheckOutDate))
            break;
        else
            cout<<"\n\tEnter Valid Dates"<<endl;
    }

    int t, *RoomNoArr;

    while (true)
    {
        cout<<"\n\n\tEnter corresponding number to book type of room:"<<endl;
        cout<<"\t1. Deluxe Room Single"<<endl;
        cout<<"\t2. Deluxe Room Double"<<endl;
        cout<<"\t3. Affordable Room Single"<<endl;
        cout<<"\t4. Affordable Room Double"<<endl;
        cout<<"\t5. Luxury Room Single"<<endl;
        cout<<"\t6. Luxury Room Double"<<endl<<endl;
        cout<<"\tEnter Choice: ";
        cin>>t;

        list <string> :: const_iterator itCIn;
        list <string> :: const_iterator itCOut;
        list <int> :: const_iterator itR;

        int flagbook = 0;

        switch(t)
        {
            case (1):
            {
                RoomNoArr = r.DeluxeRoomSingleNo;

                for (int i = 0; i < ArrRoom[0]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }

            case (2):
            {
                RoomNoArr = r.DeluxeRoomDoubleNo;

                for (int i = 0; i < ArrRoom[1]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }

            case (3):
            {
                RoomNoArr = r.AffordableRoomSingleNo;

                for (int i = 0; i < ArrRoom[2]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }

            case (4):
            {
                RoomNoArr = r.AffordableRoomDoubleNo;

                for (int i = 0; i < ArrRoom[3]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }

            case (5):
            {
                RoomNoArr = r.LuxuryRoomSingleNo;

                for (int i = 0; i < ArrRoom[4]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }

            case (6):
            {
                RoomNoArr = r.LuxuryRoomDoubleNo;

                for (int i = 0; i < ArrRoom[5]; i++)
                {
                    int flag1 = 0;
                    int j = *(RoomNoArr + i);

                    if ((GuestList.size() == 0) || (NotFind(j)))
                    {
                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }

                    itCIn = CheckIn.begin();
                    itCOut = CheckOut.begin();
                    itR = RoomAlloted.begin();

                    while ((itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
                    {
                        int RN = (*itR);
                        string CInD = (*itCIn);
                        string COutD = (*itCOut);

                        if (j == RN)
                        {
                            if ((DateCompInOut(COutD, CheckInDate)) && (DateCompInOut(CInD, CheckOutDate)))
                            {
                                flag1 = 1;
                                break;
                            }
                        }

                        itCIn++;
                        itCOut++;
                        itR++;
                    }

                    if ((flag1 == 1))
                    {

                        flagbook = 1;
                        string GuestInfo;
                        GuestInfo = to_string(gn -> BookingID) + "," + g -> Name + "," + g -> Aadhar + "," + g -> Phone + "," + g -> NoOfPeople + "\n";

                        ofstream GuestFile("GuestInformation.txt", ios::app);
                        GuestFile<<GuestInfo;
                        GuestFile.close();

                        ofstream CIn("CheckInDate.txt", ios::app);
                        CIn<<CheckInDate<<"\n";
                        CIn.close();

                        ofstream COut("CheckOutDate.txt", ios::app);
                        COut<<CheckOutDate<<"\n";
                        COut.close();

                        ofstream R("RoomAllot.txt", ios::app);
                        R<<to_string(j)<<"\n";
                        R.close();

                        GuestList.push_back(*gn);
                        CheckIn.push_back(CheckInDate);
                        CheckOut.push_back(CheckOutDate);
                        RoomAlloted.push_back(j);
                        cout<<"\tBooking Confirmed"<<endl;
                        cout<<"\tRoom Alloted: "<<j<<endl;
                        cout<<"\tBooking ID: "<<gn -> BookingID<<endl<<endl;
                        break;
                    }
                }

                if (flagbook == 0)
                    cout<<"\tBooking Denied\n\tNo Rooms available"<<endl<<endl;
                break;
            }
            default:
                cout<<"\n\tEnter correct choice number"<<endl<<endl;

        }

        if (t == 1 || t == 2 || t==3 || t == 4 || t == 5 || t == 6)
        {
            break;
        }
    }
}




bool GuestReservation::Number(string s)
{
    for (char c : s)
        if (!isdigit(c))
            return false;
    return true;
}

bool GuestReservation::Date(string s)
{
    if ((s.length() == 10) && (Number(s.substr(0, 2))) && (Number(s.substr(3, 2))) && (Number(s.substr(6, 4))) && s[2] == '/' && s[5] == '/')
    {
        int d, m, y;
        d = stoi(s.substr(0, 2));
        m = stoi(s.substr(3, 2));
        y = stoi(s.substr(6, 4));

        time_t tt;
        time(&tt);
        tm TM = *localtime(&tt);

        int year    = TM.tm_year + 1900;
        int month   = TM.tm_mon + 1;
        int day     = TM.tm_mday;

        if (y < year)
            return false;
        if (m > 12)
            return false;
        if ((y <= year) && (m < month))
            return false;
        if (d > 31)
            return false;
        if ((y <= year) && (m <= month) && (d < day))
            return false;

        if (m == 2)
        {
            if (!(((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)))
                if (d > 28)
                    return false;
            if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
                if (d > 29)
                    return false;
        }

        if ((m == 4) || (m == 6) || (m == 9) || (m == 11))
            if (d > 30)
                return false;

        return true;
    }
    return false;
}

bool GuestReservation::DateCompInOut(string a, string b)
{
    int d1, m1, y1, d2, m2, y2;

    d1 = stoi(a.substr(0, 2));
    m1 = stoi(a.substr(3, 2));
    y1 = stoi(a.substr(6, 4));
    d2 = stoi(b.substr(0, 2));
    m2 = stoi(b.substr(3, 2));
    y2 = stoi(b.substr(6, 4));

    if (y1 != y2)
        return (y1 < y2);
    else if (m1 != m2)
        return (m1 < m2);
    else if (d1 != d2)
        return (d1 < d2);
    else
        return false;
}

bool GuestReservation::NotFind(int i)
{
    list<int>::iterator it;

    it = find(RoomAlloted.begin(), RoomAlloted.end(), i);

    if(it != RoomAlloted.end())
        return false;
    else
        return true;
}


void GuestReservation::Display()
{
    ifstream GuestCheckInDate("CheckInDate.txt");
    string str1;

    while (getline(GuestCheckInDate, str1))
    {
        string s = "";
        for (char c: str1)
        {
            s = s + c;
        }
    }
    GuestCheckInDate.close();

    if (GuestList.size() == 0)
    {
        cout<<"\n\tNo Guests present in the Hotel currently"<<endl<<endl;
        return;
    }

    list <GuestNode> :: const_iterator itGL;
    list <string> :: const_iterator itCIn;
    list <int> :: const_iterator itR;

    itGL = GuestList.cbegin();
    itCIn = CheckIn.cbegin();
    itR = RoomAlloted.cbegin();

    while ((itGL != GuestList.cend()) && (itCIn != CheckIn.cend()) && (itR != RoomAlloted.cend()))
    {
        int ID = 0;
        string Name = "";
        string Phone = "";
        string N = "";
        int RN = 0;
        string CInD = "";

        ID = (itGL) -> BookingID;
        Name = (itGL) -> PersonalInfo -> Name;
        Phone = (itGL) -> PersonalInfo -> Phone;
        N = (itGL) -> PersonalInfo -> NoOfPeople;
        RN = (*itR);
        CInD = (*itCIn);

        cout<<"\tBooking ID\t\t\t: "<<ID<<endl;
        cout<<"\tName\t\t\t\t: "<<Name<<endl;
        cout<<"\tPhone\t\t\t\t: "<<Phone<<endl;
        cout<<"\tNumber of people staying\t: "<<N<<endl;
        cout<<"\tRoom Number\t\t\t: "<<RN<<endl;
        cout<<"\tCheck - In Date\t\t\t: "<<CInD<<endl<<endl;

        Name.clear();
        Phone.clear();
        N.clear();
        CInD.clear();

        itGL++;
        itCIn++;
        itR++;
    }
}


void GuestReservation::CheckOutGuest()
{
    string IDs;
    cout<<"\n\tEnter Booking ID: ";
    cin>>IDs;
    cout<<endl;
    int ID = stoi(IDs);

    int arr[GuestList.size()];

    list <GuestNode> :: const_iterator itGL;
    itGL = GuestList.cbegin();
    int i = 0, f = 0;
    while (itGL != GuestList.cend())
    {
        int I = (itGL) -> BookingID;
        if (I == ID)
        {
            f = 1;
            break;
        }
        ++i;
        ++itGL;
    }

    if (f == 0)
    {
        cout<<"No Booking ID found"<<endl<<endl;
        return;
    }


    list <string> :: const_iterator itCOut = CheckOut.begin();
    advance(itCOut, i);
    CheckOut.erase(itCOut);

    list <string> :: const_iterator itCIn = CheckIn.begin();
    advance(itCIn, i);
    CheckIn.erase(itCIn);

    list <int> :: const_iterator itR = RoomAlloted.begin();
    advance(itR, i);
    RoomAlloted.erase(itR);

    list <GuestNode> :: const_iterator itG = GuestList.begin();
    advance(itG, i);
    GuestList.erase(itG);

    itCIn = CheckIn.begin();
    itCOut = CheckOut.begin();
    itR = RoomAlloted.begin();
    itG = GuestList.begin();

    ofstream GuestFile("GuestInformation.txt");
    ofstream CIn("CheckInDate.txt");
    ofstream COut("CheckOutDate.txt");
    ofstream R("RoomAllot.txt");

    while ((itG != GuestList.end()) && (itCIn != CheckIn.end()) && (itCOut != CheckOut.end()) && (itR != RoomAlloted.end()))
    {
        string GuestInfo;
        GuestInfo = to_string(itG -> BookingID) + "," + itG -> PersonalInfo -> Name + "," + itG -> PersonalInfo -> Aadhar + "," + itG -> PersonalInfo -> Phone + "," + itGL -> PersonalInfo -> NoOfPeople + "\n";
        int RN = (*itR);
        string CInD = (*itCIn);
        string COutD = (*itCOut);

        GuestFile<<GuestInfo;
        CIn<<CInD<<"\n";
        COut<<COutD<<"\n";
        R<<to_string(RN)<<"\n";

        itG++;
        itCIn++;
        itCOut++;
        itR++;
    }

    GuestFile.close();
    CIn.close();
    COut.close();
    R.close();
    cout<<"\n\tChecked out of Hotel"<<endl<<endl;
}
