#include "GuestInformation.h"
#include <bits/stdc++.h>
using namespace std;

void GuestInformation::GetGuestInformation()
{
    while (true)
    {
        cout<<"\n\tName: ";
        cin>>ws;
        getline(cin, Name);
        if (!Alphabet(Name))
            cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
        else
            break;
    }

    while (true)
    {
        cout<<"\n\tAadhar Number: ";
        cin>>ws;
        getline(cin, Aadhar);
        if (Aadhar.length() != 12 || !Number(Aadhar))
            cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
        else
            break;
    }

    while (true)
    {
        cout<<"\n\tPhone Number: ";
        cin>>ws;
        getline(cin, Phone);
        if (Phone.length() != 10 || !Number(Phone))
            cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
        else
            break;
    }

    while (true)
    {
        cout<<"\n\tNumber of people: ";
        cin>>ws;
        getline(cin, NoOfPeople);
        if (!Number(NoOfPeople))
            cout<<"\n\tIncorrect information\n\tTry Again"<<endl;
        else
            break;
    }
}

bool GuestInformation::Number(string s)
{
    for (char c : s)
        if (!isdigit(c))
            return false;
    return true;
}

bool GuestInformation::Alphabet(string s)
{
    for (char c : s)
        if (!isalpha(c) && !isspace(c))
            return false;
    return true;
}
