#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define train_file "trains.dat"
#define passengers_file "passengers.dat"
#define MAX_TRAIN 10
#define MAX_PASSENGERS 20

//enum for ticket status
typedef enum { Confirmed, Waiting, Canceled } ticket_status;

//structure to store train data
struct Train {
    unsigned int train_no;
    char name[20];
    char source[20];
    char destination[20];
    unsigned int total_seats;
    int available_seats;
};

//structure to store passenger data
struct Passenger {
    char name[20];
    unsigned int age;
    char gender;
    unsigned int train_no;
    int seat_no;
    ticket_status ts;
};

/*
 * Function: addTrain
 * Purpose : add trains initially into file (only for first time)
*/
void addTrain() {
    struct Train data[MAX_TRAIN] = {
        {202, "Rajdhani Express", "Mumbai", "Chennai", 500, 400},
        {101, "Kutchh Express", "Navsari", "Kutchh", 600, 1},
        {203, "Gujarat Express", "Rajkot", "Ambaji", 500, 370},
        {110, "BL Vadnagar", "Vadnagar", "Navsari", 600, 400},
        {215, "Vande Bharat", "Ahmedabad", "Mumbai", 400, 2},
        {106, "Puri Express", "Surat", "Puri", 1000, 708},
        {118, "Chennai Express", "Surat", "Chennai", 600, 480},
        {165, "Bengaluru Express", "Bengaluru", "Puri", 650, 0},
        {102, "Mumbai Central", "Delhi", "Mumbai", 450, 300},
        {100, "Kerala Express", "Delhi", "Kerala", 800, 3}
    };

    FILE* filePtr = NULL;
    filePtr = fopen(train_file, "wb");

    if(filePtr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    fwrite(data, sizeof(struct Train), MAX_TRAIN, filePtr);

    printf("Data successfully added into file\n");

    fclose(filePtr);
}

static unsigned int train_count = 0;

/*
 * Function: loadTrains
 * Purpose : load all train into trains array when program run
*/
void loadTrains(struct Train trains[]) {
    FILE* filePtr = NULL;
    filePtr = fopen(train_file, "rb");

    if(filePtr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    fseek(filePtr, 0, SEEK_END);
    int end = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    int total_trains = end/sizeof(struct Train);

    if(total_trains == 0)
    {
        printf("No Available Trains\n");
        return;
    }

    struct Train buffer;

    for(int i=0;i<total_trains;i++)
    {
        train_count++;
        fread(&buffer, sizeof(struct Train), 1, filePtr);
        trains[train_count-1] = buffer;
    }

    fclose(filePtr);
}

static unsigned int passenger_count = 0;

/*
 * Function: loadPassengers
 * Purpose : load all passenger into passengers array when program run
*/
void loadPassengers(struct Passenger passengers[]) {
    FILE* filePtr = NULL;
    filePtr = fopen(passengers_file, "rb");

    if(filePtr == NULL)
    {
        printf("There is no passengers available\n");
        return;
    }

    fseek(filePtr, 0, SEEK_END);
    int end = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    int total_passengers = end/sizeof(struct Passenger);

    if(total_passengers == 0)
    {
        printf("No Passengers\n");
        return;
    }

    struct Passenger buffer;

    for(int i=0;i<total_passengers;i++)
    {
        passenger_count++;
        fread(&buffer, sizeof(struct Passenger), 1, filePtr);
        passengers[passenger_count-1] = buffer;
    }

    fclose(filePtr);
}

/*
 * Function: displayTrains
 * Purpose : display all available trains
*/
void displayTrains(struct Train trains[]) {
    if(train_count == 0)
    {
        printf("No Trains Available\n");
        return;
    }

    printf("===============================\nTotal no. of trains %d\n", train_count);

    printf("Available Trains:\n------------------\n");

    for(int i=0;i<train_count;i++)
    {
        printf("Train Number: %d\nTrain Name: %s\nSource: %s → Destination: %s\nAvailable Seats: %d\n------------------\n", trains[i].train_no, trains[i].name, trains[i].source, trains[i].destination, trains[i].available_seats);
    }
}

/*
 * Function: bookTicket
 * Purpose : books a ticket and allocates seat
*/
void bookTicket(struct Train trains[], struct Passenger passengers[]) {
    unsigned int train_no;
    printf("===============================\nEnter Train number: ");

    scanf("%d", &train_no);
    int idx =-1;
    for(int i=0;i<train_count;i++)
    {
        if(train_no == trains[i].train_no)
        {
            idx = i; //entered train number found
        }
    }

    if(idx == -1)
    {
        printf("Invalid Train number\n");
        return;
    }

    if(trains[idx].available_seats == 0)  //seats are not available for entered train number
    {
        printf("Seats are not available for this train\n");
        printf("Your ticket will go into Waiting status (When available we will notify you)\n");
        printf("Are you ok with this (If yes enter 1 else 0): ");
        unsigned int ok = 0;
        scanf("%d", &ok);
        if(ok == 0)
        {
            return;
        }
    }

    printf("Enter your following details: \n");

    //create new passenger
    passenger_count++;

    unsigned int valid_name = 0;

    while(valid_name != 1) //validate name because we use name as a unique key for cancellation
    {
        char name[20];
        printf("Enter your Name: ");
        scanf("%s", name);
        unsigned int found = 0; //to check whether we found duplicate name or not
        for(int i=0;i<passenger_count;i++)
        {
            char curr_name[20];
            strcpy(curr_name, passengers[i].name);
            if(strcmp(name, curr_name) == 0) //name is already exist
            {
                found = 1;
                printf("Name is already exist, write another name\n");
                break;
            }
        }
        if(found == 0) //unique name
        {
            strcpy(passengers[passenger_count-1].name, name);
            valid_name = 1;
        }
    }

    unsigned int valid_age = 0;

    while(valid_age != 1) //validate age: (must >0 && <100)
    {
        unsigned int age;
        printf("Enter your Age: ");
        scanf("%d", &age);
        if(age<0 || age>100)
        {
            printf("Please provide valid age (0-100)\n");
        }
        else
        {
            passengers[passenger_count-1].age = age;
            valid_age = 1;
        }
    }

    printf("Enter your Gender (M/F): ");
    scanf(" %c", &passengers[passenger_count-1].gender);

    passengers[passenger_count-1].train_no = train_no;

    //automatically assign seat number
    if(trains[idx].available_seats > 0) //seats available, ticket confirmed
    {
        passengers[passenger_count-1].seat_no = trains[idx].total_seats - trains[idx].available_seats + 1; //give consecutive available seat number
        passengers[passenger_count-1].ts = Confirmed;
        trains[idx].available_seats -= 1; //reduce available seats by 1
        printf("Your ticket booked successfully\n");
        printf("Ticket Status: Confirmed\n------------------\n");
    }
    else if(trains[idx].available_seats == 0) //no seats available, ticket goes into waiting state, available seats not affected
    {
        passengers[passenger_count-1].seat_no = -1; //assign seat number to -1
        passengers[passenger_count-1].ts = Waiting;
        printf("Your ticket is in Waiting state\n");
        printf("Ticket Status: Waiting\n------------------\n");
    }

    FILE* train_ptr = fopen(train_file, "wb");

    if(train_ptr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    //overwrite all updated trains data into file - available seats changed if ticket confirmed
    fwrite(trains, sizeof(struct Train), train_count, train_ptr);

    fclose(train_ptr);

    FILE* passenger_ptr = fopen(passengers_file, "ab");

    if(passenger_ptr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    //append passenger data into file
    fwrite(&passengers[passenger_count-1], sizeof(struct Passenger), 1, passenger_ptr);

    fclose(passenger_ptr);
}

/*
 * Function: cancelTicket
 * Purpose : cancel ticket if booked earlier then notify user who have ticket status as waiting for that train whether he want to confirm his ticket or not because now seats are available due to cancellation  
*/
void cancelTicket(struct Train trains[], struct Passenger passengers[]) {
    char name[20];
    printf("===============================\nEnter Your Name: ");

    scanf("%s", name); //user's name used as key to cancle ticket
    int idx = -1;
    for(int i=0;i<passenger_count;i++)
    {
        if(strcmp(name, passengers[i].name) == 0)
        {
            idx = i; //user found - book ticket earlier
        }
    }

    if(idx == -1)
    {
        printf("Passenger record not found\n");
        return;
    }

    unsigned int train_no = passengers[idx].train_no;

    if(passengers[idx].ts == Confirmed) //if ticket confirmed, increase available seats by 1 and make ticket status as canceled
    {
        for(int i=0;i<train_count;i++)
        {
            if(train_no == trains[i].train_no)
            {
                trains[i].available_seats += 1;
                passengers[idx].ts = Canceled;
                printf("Ticket cancelled successfully\n------------------\n");
                break;
            }
        }
    }
    else if(passengers[idx].ts == Waiting) //if ticket in waiting state, only mark it as canceled, available seats not affected
    {
        passengers[idx].ts = Canceled;
        printf("Ticket cancelled successfully\n------------------\n");
    }

    //notify person who has ticket status as waiting because now seats are available for that train
    for(int i=0;i<passenger_count;i++)
    {
        if(passengers[i].train_no == train_no && passengers[i].ts == Waiting) //person found with similar train number and his ticket status is in waiting mode
        {
            printf("%s: Your seat is available for %d\n", passengers[i].name, train_no);
            unsigned int confirmed = 0; //ask user to confirm his ticket or not
            printf("Do you want to confirm it? If yes enter 1 else 0: ");
            scanf("%d", &confirmed);
            if(confirmed == 1) //if confirmed, reduce available seats by 1
            {
                for(int j=0;j<train_count;j++)
                {
                    if(train_no == trains[j].train_no)
                    {
                        passengers[i].seat_no = trains[j].total_seats - trains[j].available_seats + 1;
                        trains[j].available_seats -= 1;
                        passengers[i].ts = Confirmed; // mark status as confirmed
                        break;
                    }
                }
                printf("%s: Your ticket booked successfully\n", passengers[i].name);
                printf("Ticket Status: Confirmed\n------------------\n");
            }
            break; //if not, exit
        }
    }

    FILE* train_ptr = fopen(train_file, "wb");

    if(train_ptr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    //overwrite all updated trains data into file - available seats changed if ticket confirmed
    fwrite(trains, sizeof(struct Train), train_count, train_ptr);

    fclose(train_ptr);

    FILE* passenger_ptr = fopen(passengers_file, "wb");

    if(passenger_ptr == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    //overwrite all updated passengers data into file - ticket status changed if ticket cancelled
    fwrite(passengers, sizeof(struct Passenger), passenger_count, passenger_ptr);

    fclose(passenger_ptr);
}

/*
 * Function: displayStatus
 * Purpose : display ticket status string from enum
*/
char* displayStatus(unsigned int status) {
    char* show_status;
    if(status == 0)
    {
        show_status = "Confirmed";
    }
    else if(status == 1)
    {
        show_status = "Waiting";
    }
    else
    {
        show_status = "Cancelled";
    }
    return show_status;
}

/*
 * Function: displayPassenger
 * Purpose : display all passengers data
*/
void displayPassenger(struct Passenger passengers[]) {
    printf("===============================\n");

    if(passenger_count == 0)
    {
        printf("No Passengers\n");
        return;
    }

    printf("Passengers List:\n------------------\n");

    for(int i=0;i<passenger_count;i++)
    {
        if(passengers[i].ts == Confirmed) //seat number display if ticket confirmed
        {
            printf("Passenger Name: %s\nTrain Number: %d\nSeat Number: %d\nTicket Status: %s\n------------------\n", passengers[i].name, passengers[i].train_no, passengers[i].seat_no, displayStatus(passengers[i].ts));
        }
        else //seat number not display if ticket in waiting state or cancelled
        {
            printf("Passenger Name: %s\nTrain Number: %d\nTicket Status: %s\n------------------\n", passengers[i].name, passengers[i].train_no, displayStatus(passengers[i].ts));
        }
    }
}

/*
 * Function: showMenu
 * Purpose : display all menu options
 */
void showMenu() {
    printf("\nAvailable options:\n");
    printf("1. Display Available Trains\n");
    printf("2. Book Ticket\n");
    printf("3. Cancel Ticket\n");
    printf("4. Display Passenger Details\n");
    printf("0. Exit\n");
}

int main()
{
    struct Train trains[MAX_TRAIN];  //array to hold all train details
    struct Passenger passengers[MAX_PASSENGERS];  //array to hold all passenger details

    loadTrains(trains);
    loadPassengers(passengers);

    printf(" === Railway Reservation System === \n");

    int choice = -1;
    do {
        showMenu();
        printf("Please select any one option (eg. 1): ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: displayTrains(trains);
                    break;
            case 2: bookTicket(trains, passengers);
                    break;
            case 3: cancelTicket(trains, passengers);
                    break;
            case 4: displayPassenger(passengers);
                    break;
            default: printf("Invalid Choice\n");
        }
    } while(choice != 0);
    
    return 0;
}