#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int totalSeats = 10;
int seats[10] = {0};
int initial = 0;

std::queue<string> waiting;
std::vector<string> stops = {"chennai", "banglore", "mumbai"}; 
std:: map<string, vector<string> > userDetails;

class Admin
{
    public:

        int menu()
        {
            int option;
            while(1)
            {
                cout << "=============Admin================" << endl;
                cout << "Press 1 to Add a stops" << endl;
                cout << "Press 2 to See all the passengen" << endl;
                cout << "Press 3 to See all Waiting List" << endl;
                cout << "Press 4 to See all Stops" << endl;
                cout << "Press 5 to Go Back" << endl;
                cout << "=================================" << endl;
                cout << "Enter Your Choice : ";
                cin >> option;
                cin.ignore();

                switch (option)
                {
                    case 1:
                        addStops();
                        break;

                    case 2:
                        showAllPassengers();
                        break;

                    case 3:
                        showAllWaitingList();
                        break;

                    case 4:
                        showTheStops();
                        break;

                    case 5:
                        return 0;
                    
                    default:
                        break;
                }

            }
        }

        void showAllPassengers()
        {
            for(auto& result : userDetails)
                cout << result.second[0] << "       " << result.second[1] << "      " << result.second[2] << "      " << result.second[3] << "      " << result.second[4] << "      " << result.second[5] << endl;
        
        }

        void addStops()
        {
            //trainStops();
            string stop;
            cout << "Enter the stop to add : ";
            getline(cin, stop);
            stops.push_back(stop);
            cout << "Successfully Added " << endl;
        }

        void showTheStops()
        {
            for(int index= 0 ; index < stops.size(); index += 1)
                cout << stops[index] << endl;
        }

        void showAllWaitingList()
        {
            queue<string> tmp;
            tmp = waiting;

            while (!tmp.empty())
            {
                string q_element = tmp.front();
                cout << q_element << endl;
                tmp.pop();
            }
        }

        int checkAvaiableSeats()
        {
            for(int index = 0 ; index < totalSeats; index += 1)
            {
                if(seats[index] == 0)
                {
                    return (index+1);
                }
            }

            return 0;
        }

        bool checkingRoutes(string source, string desgination)
        {
            
            bool existsSource = std::count(stops.begin(), stops.end(), source);
            bool existsDes = std::count(stops.begin(), stops.end(), desgination);

            if( existsSource && existsDes )
            {
                return true;
            }
            else{
                return false;
            }
        }

        void toFillCancelSeat(int seatNo)
        {
            string waitingListPhno = waiting.front();

            for(auto& result : userDetails)
            {
                if(result.first == waitingListPhno )
                {
                    result.second[5] = "Booked";
                    result.second[4] = to_string(seatNo);
                    seats[seatNo] = 1;
                }


            }
            waiting.pop();
        }


};


class User
{
    public:

        Admin admin;
        int menu()
        {
            int option;
            string name, phno, source, designation;
            while(1)
            {
                cout << "=============User================" << endl;
                cout << "Press 1 to Book a ticket" << endl;
                cout << "Press 2 to Check the status" << endl;
                cout << "Press 3 to Cancel the ticket" << endl;
                cout << "Press 4 to AutoFill the tickets" << endl;
                cout << "Press 5 to Go Back" << endl;
                cout << "=================================" << endl;
                cout << "Enter Your Choice : ";
                cin >> option;
                cin.ignore();

                switch (option)
                {
                    case 1:
                        cout << "Enter Your name to book your ticket : "  ;
                        getline(cin, name);

                        cout << "Enter the phone Number : ";
                        getline(cin, phno);

                        cout << "Enter your current station : ";
                        getline(cin, source);

                        cout << "Enter your designation : ";
                        getline(cin, designation);

                        toBookTickets(name, phno, source, designation);
                        break;

                    case 2:
                        toCheckStatus();
                        break;

                    case 3:
                        toCancelTickets();
                        break;

                    case 4:
                        autoFillTickets();
                        break;

                    case 5:
                        return 0;
                    
                    default:
                        break;
                }

            }
        }

        int toBookTickets(string name, string phno, string source, string desgination)
        {
            std::vector<string> details;
            
            int seatAvaiable = admin.checkAvaiableSeats();
            bool routeIsVaild = admin.checkingRoutes(source, desgination);

            if(routeIsVaild == 1)
            {
                if(seatAvaiable != 0)
                {
                    seats[initial] = 1;
                    initial += 1;
                    details.push_back(name);
                    details.push_back(phno);
                    details.push_back(source);
                    details.push_back(desgination);
                    details.push_back(to_string(seatAvaiable));
                    details.push_back("Booked");

                    userDetails.insert( {phno, details} );
                    // admin.details.pop_back();
                    // admin.details.pop_back();
                    // admin.details.pop_back();
                    // admin.details.pop_back();
                    // admin.details.pop_back();
                    // admin.details.pop_back();
                cout << "=================================" << endl;
                    cout << "Your seat is booked successfully!!!" << endl;
                    return 0;
                }
                else
                {
                    if(waiting.size() < 5)
                    {
                        cout << "Waiting list count is : " << waiting.size() << endl;
                        details.push_back(name);
                        details.push_back(phno);
                        details.push_back(source);
                        details.push_back(desgination);
                        details.push_back(to_string(-1));
                        details.push_back("Watining");

                        userDetails.insert( {phno, details} );
                        // admin.details.pop_back();
                        // admin.details.pop_back();
                        // admin.details.pop_back();
                        // admin.details.pop_back();
                        // admin.details.pop_back();
                        // admin.details.pop_back();
                        waiting.push(phno);
                        cout << "=================================" << endl;
                        cout << "There is no seat so Stay at waiting list" << endl;
                        return 0;
                    }
                    else
                    {
                        cout << "=================================" << endl;
                        cout << "There is no more seats avaiable" << endl;
                    }
                    
                }
            }
            else
            {
                cout << "Invaild Train location" << endl;
            }
            return 0;
        }

        int toCheckStatus()
        {
            string userTypedPhno;
            cout << "Enter the phone number to check your details" << endl;
            cin >> userTypedPhno;

            for(auto& result : userDetails)
            {
                
                    if(result.first == userTypedPhno )
                    {
                        cout << "===========================================================" << endl;
                        cout << "Name         : " << result.second[0] << endl;
                        cout << "Phone Number : " << result.first << endl;
                        cout << "Source       : " << result.second[2] << endl;
                        cout << "Desgination  : " << result.second[3] << endl;
                        cout << "Seat number  : " << result.second[4] << endl;
                        cout << "Status       : " << result.second[5] << endl;
                        cout << "===========================================================" << endl;
                        return 0;
                    }
            }
            return 0;
        }

        void toCancelTickets()
        {
            string userTypedPhno;
            cout << "Enter the phone number to Delete your ticket" << endl;
            getline(cin, userTypedPhno);

            for(auto& result: userDetails)
            {
                if(result.first == userTypedPhno)
                {
                    int seatNo = stoi(result.second[4]);
                    result.second[4] = "-1";
                    result.second.at(5) = "Cancled";
                    admin.toFillCancelSeat(seatNo);
                    cout << "Deleted successfully "<< endl;
                }
            }

        }

        void autoFillTickets()
        {
            for(int index = initial; index < 16; index += 1)
                toBookTickets("name",to_string(index), "chennai", "mumbai");
        }

};


int main()
{
    int choice;
    User user;
    Admin admin;

    while(1)
    {
        cout << "=============User================" << endl;
        cout << "If your user press 1" << endl;
        cout << "If your admin press 2" << endl;
        cout << "Press 3 to Exit" << endl;
        cout << "=================================" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1:
                user.menu();
                break;

            case 2:
                admin.menu();
                break;

            case 3:
                cout << "Thank You!!!!!" << endl;
                exit(1);
            
            default:
                break;
        }
    }


    return 0;
}