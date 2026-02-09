#ifndef RAILWAY_H
#define RAILWAY_H

#include <stdio.h>
#define train_file "trains.dat"
#define passengers_file "passengers.dat"
#define MAX_TRAIN 10
#define MAX_PASSENGERS 20

/* enum for ticket status */
typedef enum {
    Confirmed,
    Waiting,
    Canceled
} ticket_status;

/* structure to store train data */
struct Train {
    unsigned int train_no;
    char name[20];
    char source[20];
    char destination[20];
    unsigned int total_seats;
    int available_seats;
};

/* structure to store passenger data */
struct Passenger {
    char name[20];
    unsigned int age;
    char gender;
    unsigned int train_no;
    int seat_no;
    ticket_status ts;
};

/* Function declarations */

/* Initial train setup */
void addTrain(void);

/* Input utility */
int readInt(void);

/* Load data from files */
void loadTrains(struct Train trains[]);
void loadPassengers(struct Passenger passengers[]);

/* Display functions */
void displayTrains(struct Train trains[]);
void displayPassenger(struct Passenger passengers[]);
char* displayStatus(unsigned int status);

/* Ticket operations */
void bookTicket(struct Train trains[], struct Passenger passengers[]);
void cancelTicket(struct Train trains[], struct Passenger passengers[]);

/* Menu */
void showMenu(void);

#endif