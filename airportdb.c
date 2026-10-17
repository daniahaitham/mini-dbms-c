#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define HASH_SIZE 13

pthread_mutex_t dbLock = PTHREAD_MUTEX_INITIALIZER;


char fname[21], lname[21];
char nationality[21];
char model[21], airline[21];
char destination[21];
char serviceArea[21];
int id;
int license;
int serial;
int speed;
int ticketSerial;
int planeSerial;
int ticketDate;
float ticketPrice;

int seatNumber;
int phoneNumber;
int passengerId, crewId;



 struct Pilot {
    int pilot_id;
    char fname[21];
    char lname[21];
    int license_number;


};
 struct Plane {
    int serial_number;
    char model_name[21];
    char airline_number[21];
    int speed;
    int pilot_id;//this is  FK


};
 struct Ticket {
    int serial_number;
    int date;
    float price;
    char destination[21];


};
struct Crew {
    int crew_id;
    char fname[21];
    char lname[21];
    char service_area[21];
    int plane_serial_number;
};
 struct Passenger {
    int passenger_id;
    char fname[21];
    char lname[21];
    char nationality[21];
    int seat_number;
    int ticket_serial_number; //this is  FK
    int plane_serial_number;//this is  FK


};
 struct PassengerCrew {
    int crew_id;
    int passenger_id;

};
 struct PilotPhone {
    int pilot_id;
    int Pilot_phone_number;


};

struct PilotNode {
    struct Pilot data;
    struct PilotNode* next;
};
struct PassengerNode {
    struct  Passenger data;
    struct PassengerNode* next;
};
struct ticketNode {
    struct Ticket data;
    struct ticketNode* next;
};
struct CrewNode {
    struct Crew data;
    struct CrewNode* next;
};
struct PlaneNode {
    struct Plane data;
    struct PlaneNode* next;
};
struct PilotPhoneNode {
    struct PilotPhone data;
    struct PilotPhoneNode* next;
};
struct PassengerCrewNode {
    struct PassengerCrew data;
    struct PassengerCrewNode* next;
};



int hashFunction(int id) {
    return id % HASH_SIZE;
}

struct PassengerNode* passengerHashTable[HASH_SIZE] = {NULL};
struct PilotNode* pilotHashTable[HASH_SIZE] = {NULL};
struct CrewNode* crewHashTable[HASH_SIZE] = {NULL};
struct PlaneNode* planeHashTable[HASH_SIZE] = {NULL};
struct ticketNode* ticketHashTable[HASH_SIZE] = {NULL};
struct PilotPhoneNode* pilotPhoneHashTable[HASH_SIZE] = {NULL};
struct PassengerCrewNode* passengerCrewHashTable[HASH_SIZE] = {NULL};

//Find Functions
struct PassengerNode* findPassengerByID(int id);
struct PilotNode* findPilotByID(int id);
struct PlaneNode* findPlaneBySerial(int serial);
struct CrewNode* findCrewByID(int id);
struct ticketNode* findTicketBySerial(int serial);
struct PilotPhoneNode* findPilotPhoneByID(int id);
struct PassengerCrewNode* findPassengerCrewByPassengerID(int id);

//Insert Functions
void insertPilot(int id, char fname[], char lname[], int license);
void insertPlane(int serial, char model[], char airline[], int speed, int pilot_id);
void insertTicket(int serial, int date, float price, char destination[]);
void insertPassenger(int id, char fname[], char lname[], char nationality[], int seat, int ticket_serial, int plane_serial);
void insertCrew(int id, char fname[], char lname[], char area[], int plane_serial);
void insertPilotPhone(int phone_number, int pilot_id);
void insertPassengerCrew(int passenger_id, int crew_id);

// Update Functions
void updatePilot(int id, char newFname[], char newLname[], int newLicense);
void updatePlane(int serial, char newModel[], char newAirline[], int newSpeed, int newPilotID);
void updateTicket(int serial, int newDate, float newPrice, char newDest[]);
void updatePassenger(int id, char newFname[], char newLname[], char newNationality[], int newSeat, int newTicket, int newPlane);
void updateCrew(int id, char newFname[], char newLname[], char newArea[], int newPlaneSerial);

//Delete Functions
void deletePilot(int id);
void deletePlane(int serial);
void deleteTicket(int serial);
void deletePassenger(int id);
void deleteCrew(int id);
void deletePilotPhone(int pilot_id, int phone_number);
void deletePassengerCrew(int passenger_id, int crew_id);

// Print Functions
void printPassengerByID(int id);
void printPilotByID(int id);
void printPlaneByID(int serial);
void printTicketByID(int serial);
void printCrewByID(int id);
void printPhonesForPilot(int pilot_id);
void printPassengersForCrew(int crew_id);

//CSV Load/Save Functions
void savePassengerToCSV(char* filename);
void PassengerLoadFromCSV(char* filename);
void PilotLoadFromCSV(char* filename);
void savePilotToCSV(char* filename);
void PassengerCrewLoadFromCSV(char* filename);
void savePassengerCrewToCSV(char* filename);
void CrewLoadFromCSV(char* filename);
void saveCrewToCSV(char* filename);
void PlaneLoadFromCSV(char* filename);
void savePlaneToCSV(char* filename);
void PilotPhoneLoadFromCSV(char* filename);
void savePilotPhoneToCSV(char* filename);
void TicketLoadFromCSV(char* filename);
void saveTicketToCSV(char* filename);





struct PassengerNode* findPassengerByID(int id) {
    int index = hashFunction(id);
    struct PassengerNode* temp = passengerHashTable[index];
    while (temp != NULL) {
        if (temp->data.passenger_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct PilotNode* findPilotByID(int id) {
    int index = hashFunction(id);
    struct PilotNode* temp = pilotHashTable[index];
    while (temp != NULL) {
        if (temp->data.pilot_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct PlaneNode* findPlaneBySerial(int serial) {
    int index = hashFunction(serial);
    struct PlaneNode* temp = planeHashTable[index];
    while (temp != NULL) {
        if (temp->data.serial_number == serial)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct CrewNode* findCrewByID(int id) {
    int index = hashFunction(id);
    struct CrewNode* temp = crewHashTable[index];
    while (temp != NULL) {
        if (temp->data.crew_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct ticketNode* findTicketBySerial(int serial) {
    int index = hashFunction(serial);
    struct ticketNode* temp = ticketHashTable[index];
    while (temp != NULL) {
        if (temp->data.serial_number == serial)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct PilotPhoneNode* findPilotPhoneByID(int id) {
    int index = hashFunction(id);


    struct PilotPhoneNode* temp = pilotPhoneHashTable[index];
    while (temp != NULL) {
        if (temp->data.pilot_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
struct PassengerCrewNode* findPassengerCrewByPassengerID(int id) {
    int index = hashFunction(id);
    struct PassengerCrewNode* temp = passengerCrewHashTable[index];
    while (temp != NULL) {
        if (temp->data.crew_id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void insertPilot(int id, char fname[], char lname[], int license) {
    pthread_mutex_lock(&dbLock);


     if (findPilotByID(id) != NULL) {
        printf("Pilot ID already exists. Insertion aborted.\n");
                pthread_mutex_unlock(&dbLock);

        return;
    }


    struct PilotNode* newNode =malloc(sizeof(struct PilotNode));

    newNode->data.pilot_id = id;
    strcpy(newNode->data.fname, fname);
    strcpy(newNode->data.lname, lname);
    newNode->data.license_number = license;
    newNode->next = NULL;


    int index = hashFunction(id);
    newNode->next = pilotHashTable[index]; // i am making the new created node is the head of the current list
    pilotHashTable[index] = newNode;

    printf("Pilot os inserted at the %d slot \n", index);

    pthread_mutex_unlock(&dbLock);

}
void insertPlane(int serial, char model[], char airline[], int speed, int pilot_id) {
    pthread_mutex_lock(&dbLock);


      if (findPlaneBySerial(serial) != NULL) {
        printf("Plane serial number already exists. Insertion aborted.\n");
                pthread_mutex_unlock(&dbLock);

        return;
    }



    struct PlaneNode* newNode =  malloc(sizeof(struct PlaneNode));

    newNode->data.serial_number = serial;
    strcpy(newNode->data.model_name, model);
    strcpy(newNode->data.airline_number, airline);
    newNode->data.speed = speed;
    newNode->data.pilot_id = pilot_id;


    int index = hashFunction(serial);
    newNode->next = planeHashTable[index];
    planeHashTable[index] = newNode;

    printf("Plane inserted at slot %d.\n", index);

    pthread_mutex_unlock(&dbLock);

}
void insertTicket(int serial, int date, float price, char destination[]) {

    pthread_mutex_lock(&dbLock);

     if (findTicketBySerial(serial) != NULL) {
        printf("Ticket serial already exists. Insertion aborted.\n");
                pthread_mutex_unlock(&dbLock);

        return;


    }


    struct ticketNode * newNode = malloc(sizeof(struct ticketNode ));

    newNode->data.serial_number = serial;
    newNode->data.date = date;
    newNode->data.price = price;
    strcpy(newNode->data.destination, destination);


    int index = hashFunction(serial);
    newNode->next = ticketHashTable[index];
    ticketHashTable[index] = newNode;

    printf("Ticket inserted at slot %d.\n", index);

        pthread_mutex_unlock(&dbLock);

}
void insertPassenger(int id, char fname[], char lname[], char nationality[], int seat, int ticket_serial, int plane_serial) {


    pthread_mutex_lock(&dbLock);

     if (findPassengerByID(id) != NULL) {
        printf("Passenger ID already exists. Insertion aborted.\n");
                pthread_mutex_unlock(&dbLock);

        return;
    }


    struct PassengerNode* newNode =malloc(sizeof(struct PassengerNode));

    newNode->data.passenger_id = id;
    strcpy(newNode->data.fname, fname);
    strcpy(newNode->data.lname, lname);
    strcpy(newNode->data.nationality, nationality);
    newNode->data.seat_number = seat;
    newNode->data.ticket_serial_number = ticket_serial;
    newNode->data.plane_serial_number = plane_serial;


    int index = hashFunction(id);
    newNode->next = passengerHashTable[index];
    passengerHashTable[index] = newNode;

    printf("Passenger inserted at slot %d.\n", index);

    pthread_mutex_unlock(&dbLock);

}
void insertCrew(int id, char fname[], char lname[], char area[], int plane_serial) {

        pthread_mutex_lock(&dbLock);

     if (findCrewByID(id) != NULL) {
        printf("Crew ID already exists. Insertion aborted.\n");
                pthread_mutex_unlock(&dbLock);

        return;
    }

    struct CrewNode* newNode =  malloc(sizeof(struct CrewNode));

    newNode->data.crew_id = id;
    strcpy(newNode->data.fname, fname);
    strcpy(newNode->data.lname, lname);
    strcpy(newNode->data.service_area, area);
    newNode->data.plane_serial_number = plane_serial;


    int index = hashFunction(id);
    newNode->next = crewHashTable[index];
    crewHashTable[index] = newNode;

    printf("Crew member inserted at slot %d.\n", index);

        pthread_mutex_unlock(&dbLock);

}
void insertPilotPhone(int phone_number, int pilot_id) {
    pthread_mutex_lock(&dbLock);




    struct PilotPhoneNode* newNode =    malloc(sizeof(struct PilotPhoneNode));
    newNode->data.Pilot_phone_number = phone_number;
    newNode->data.pilot_id = pilot_id;



    int index = hashFunction(pilot_id);
    newNode->next = pilotPhoneHashTable[index];
    pilotPhoneHashTable[index] = newNode;

    printf("Pilot phone inserted at slot %d\n", index);

    pthread_mutex_unlock(&dbLock);
}
void insertPassengerCrew(int passenger_id, int crew_id) {
    pthread_mutex_lock(&dbLock);

     struct PassengerCrewNode* temp = passengerCrewHashTable[hashFunction(passenger_id)];
    while (temp != NULL) {
        if (temp->data.passenger_id == passenger_id && temp->data.crew_id == crew_id) {
            printf("Passenger-Crew relationship already exist.\n");
            pthread_mutex_unlock(&dbLock);
            return;
        }
        temp = temp->next;
    }

    struct PassengerCrewNode* newNode =  malloc(sizeof(struct PassengerCrewNode));
    newNode->data.passenger_id = passenger_id;
    newNode->data.crew_id = crew_id;

    int index = hashFunction(crew_id);
    newNode->next = passengerCrewHashTable[index];
    passengerCrewHashTable[index] = newNode;

    printf("Passenger-Crew relationship inserted at slot %d\n", index);

    pthread_mutex_unlock(&dbLock);
}

void updatePilot(int id, char newFname[], char newLname[], int newLicense) {
    pthread_mutex_lock(&dbLock);

    struct PilotNode* found = findPilotByID(id);

    if (found != NULL) {



        strcpy(found->data.fname, newFname);
        strcpy(found->data.lname, newLname);
        found->data.license_number = newLicense;

         printf("Pilot updated.\n");
    } else {
        printf("Pilot not found.\n");
    }
        pthread_mutex_unlock(&dbLock);

}
void updatePlane(int serial, char newModel[], char newAirline[], int newSpeed, int newPilotID) {
        pthread_mutex_lock(&dbLock);

    struct PlaneNode* found = findPlaneBySerial (serial);

    if (found != NULL) {

         strcpy(found->data.model_name, newModel);
        strcpy(found->data.airline_number, newAirline);
        found->data.speed = newSpeed;
        found->data.pilot_id = newPilotID;

        printf("Plane updated.\n");
    } else {
        printf("Plane not found.\n");
    }
        pthread_mutex_unlock(&dbLock);

}
void updateTicket(int serial, int newDate, float newPrice, char newDest[]) {
        pthread_mutex_lock(&dbLock);

    struct ticketNode * found = findTicketBySerial(serial);

    if (found != NULL) {




        found->data.date = newDate;
        found->data.price = newPrice;
        strcpy(found->data.destination, newDest);

         printf("Ticket updated.\n");
    } else {
        printf("Ticket not found.\n");
    }
        pthread_mutex_unlock(&dbLock);

}
void updatePassenger(int id, char newFname[], char newLname[], char newNationality[], int newSeat, int newTicket, int newPlane) {
        pthread_mutex_lock(&dbLock);

    struct PassengerNode* found = findPassengerByID(id);

    if (found != NULL) {



        strcpy(found->data.fname, newFname);
        strcpy(found->data.lname, newLname);
        strcpy(found->data.nationality, newNationality);
        found->data.seat_number = newSeat;
        found->data.ticket_serial_number = newTicket;
        found->data.plane_serial_number = newPlane;

         printf("Passenger updated.\n");
    } else {
        printf("Passenger not found.\n");
    }
        pthread_mutex_unlock(&dbLock);

}
void updateCrew(int id, char newFname[], char newLname[], char newArea[], int newPlaneSerial) {
        pthread_mutex_lock(&dbLock);

    struct CrewNode* found = findCrewByID(id);

    if (found != NULL) {

        strcpy(found->data.fname, newFname);
        strcpy(found->data.lname, newLname);
        strcpy(found->data.service_area, newArea);
        found->data.plane_serial_number = newPlaneSerial;

         printf("Crew member updated.\n");
    } else {
        printf("Crew member not found.\n");
    }
        pthread_mutex_unlock(&dbLock);

}

void deletePilot(int id) {

        pthread_mutex_lock(&dbLock);

    int index = hashFunction(id);
    struct PilotNode* temp = pilotHashTable[index];
    struct PilotNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.pilot_id == id) {


            if (prev == NULL) {
                pilotHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
                        free(temp);

      pthread_mutex_unlock(&dbLock);
            printf("Pilot deleted.\n");
            return;
        }

        //ormal traverse not like the update function
        prev = temp;
        temp = temp->next;
    }

        pthread_mutex_unlock(&dbLock);
    printf("Pilot not found.\n");
}
void deletePlane(int serial) {

            pthread_mutex_lock(&dbLock);

    int index = hashFunction(serial);
    struct PlaneNode* temp = planeHashTable[index];
    struct PlaneNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.serial_number == serial) {


            if (prev == NULL) {
                planeHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            pthread_mutex_unlock(&dbLock);

            printf("Plane deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
        pthread_mutex_unlock(&dbLock);

    printf("Plane not found.\n");
}
void deleteTicket(int serial) {

        pthread_mutex_lock(&dbLock);
    int index = hashFunction(serial);
    struct ticketNode* temp = ticketHashTable[index];
    struct ticketNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.serial_number == serial) {




            if (prev == NULL) {
                ticketHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
               pthread_mutex_unlock(&dbLock);
            printf("Ticket deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
pthread_mutex_unlock(&dbLock);
    printf("Ticket not found.\n");
}
void deletePassenger(int id) {

     pthread_mutex_lock(&dbLock);
    int index = hashFunction(id);
    struct PassengerNode* temp = passengerHashTable[index];
    struct PassengerNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.passenger_id == id) {



            if (prev == NULL) {
                passengerHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            pthread_mutex_unlock(&dbLock);
            printf("Passenger deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

pthread_mutex_unlock(&dbLock);
    printf("Passenger not found.\n");
}
void deleteCrew(int id) {

     pthread_mutex_lock(&dbLock);
    int index = hashFunction(id);
    struct CrewNode* temp = crewHashTable[index];
    struct CrewNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.crew_id == id) {




            if (prev == NULL) {
                crewHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);

               pthread_mutex_unlock(&dbLock);
            printf("Crew member deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
 pthread_mutex_unlock(&dbLock);
    printf("Crew member not found.\n");
}
void deletePilotPhone(int pilot_id, int phone_number) {
    pthread_mutex_lock(&dbLock);

    int index = hashFunction(pilot_id);
    struct PilotPhoneNode* temp = pilotPhoneHashTable[index];
    struct PilotPhoneNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.pilot_id == pilot_id && temp->data.Pilot_phone_number == phone_number) {
            if (prev == NULL) {
                pilotPhoneHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Pilot phone deleted.\n");
            pthread_mutex_unlock(&dbLock);
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    pthread_mutex_unlock(&dbLock);
    printf("Pilot phone record not found.\n");
}
void deletePassengerCrew(int passenger_id, int crew_id) {
    pthread_mutex_lock(&dbLock);

    int index = hashFunction(crew_id);
    struct PassengerCrewNode* temp = passengerCrewHashTable[index];
    struct PassengerCrewNode* prev = NULL;

    while (temp != NULL) {
        if (temp->data.passenger_id == passenger_id && temp->data.crew_id == crew_id) {
            if (prev == NULL) {
                passengerCrewHashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Passenger-Crew relationship deleted.\n");
            pthread_mutex_unlock(&dbLock);
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    pthread_mutex_unlock(&dbLock);
    printf("Passenger-Crew relationship not found.\n");
}

void printPassengerByID(int id) {
    pthread_mutex_lock(&dbLock);

    struct PassengerNode* found = findPassengerByID(id);

    if (found != NULL) {
        printf("Passenger ID: %d\n", found->data.passenger_id);
        printf("Name: %s %s\n", found->data.fname, found->data.lname);
        printf("Nationality: %s\n", found->data.nationality);
        printf("Seat Number: %d\n", found->data.seat_number);
        printf("Ticket Serial: %d\n", found->data.ticket_serial_number);
        printf("Plane Serial: %d\n", found->data.plane_serial_number);
    } else {
        printf("Passenger not found.\n");
    }
    pthread_mutex_unlock(&dbLock);

}
void printPilotByID(int id) {
    pthread_mutex_lock(&dbLock);

    struct PilotNode* found = findPilotByID(id);

    if (found != NULL) {
        printf("Pilot ID: %d\n", found->data.pilot_id);
        printf("Name: %s %s\n", found->data.fname, found->data.lname);
        printf("License Number: %d\n", found->data.license_number);
    } else {
        printf("Pilot not found.\n");
    }

    pthread_mutex_unlock(&dbLock);

}
void printPlaneByID(int serial) {
    pthread_mutex_lock(&dbLock);

    struct PlaneNode* found = findPlaneBySerial(serial);

    if (found != NULL) {
        printf("Plane Serial: %d\n", found->data.serial_number);
        printf("Model: %s\n", found->data.model_name);
        printf("Airline Number: %s\n", found->data.airline_number);
        printf("Speed: %d\n", found->data.speed);
        printf("Pilot ID: %d\n", found->data.pilot_id);
    } else {
        printf("Plane not found.\n");
    }
    pthread_mutex_unlock(&dbLock);

}
void printTicketByID(int serial) {
    pthread_mutex_lock(&dbLock);

    struct ticketNode * found = findTicketBySerial(serial);

    if (found != NULL) {
        printf("Ticket Serial: %d\n", found->data.serial_number);
        printf("Date: %d\n", found->data.date);
        printf("Price: %.2f\n", found->data.price);
        printf("Destination: %s\n", found->data.destination);
    } else {
        printf("Ticket not found.\n");
    }
    pthread_mutex_unlock(&dbLock);

}
void printCrewByID(int id) {
    pthread_mutex_lock(&dbLock);

    struct CrewNode* found = findCrewByID(id);

    if (found != NULL) {
        printf("Crew ID: %d\n", found->data.crew_id);
        printf("Name: %s %s\n", found->data.fname, found->data.lname);
        printf("Service Area: %s\n", found->data.service_area);
        printf("Plane Serial: %d\n", found->data.plane_serial_number);
    } else {
        printf("Crew member not found.\n");
    }

    pthread_mutex_unlock(&dbLock);

}
void printPhonesForPilot(int pilot_id) {
    int index = hashFunction(pilot_id);
    struct PilotPhoneNode* temp = pilotPhoneHashTable[index];
    int flag = 0;

    printf("Phone numbers for Pilot ID %d:\n", pilot_id);
    while (temp != NULL) {
        if (temp->data.pilot_id == pilot_id) {
            printf("- %d\n", temp->data.Pilot_phone_number);
            flag = 1;
        }
        temp = temp->next;
    }

    if (!flag) {
        printf("No phone numbers found for this pilot.\n");
    }
}
void printPassengersForCrew(int crew_id) {
    int flag = 0;

    printf("Passenger IDs assigned to Crew ID %d:\n", crew_id);
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PassengerCrewNode* temp = passengerCrewHashTable[i];
        while (temp != NULL) {
            if (temp->data.crew_id == crew_id) {
                printf("- Passenger ID: %d\n", temp->data.passenger_id);
                flag = 1;
            }
            temp = temp->next;
        }
    }

    if (!flag) {
        printf("No passengers found for this crew member.\n");
    }
}

void savePassengerToCSV(char* filename) {

    FILE* file = fopen(filename, "w");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PassengerNode* temp = passengerHashTable[i];
        while (temp) {
            fprintf(file,"%d,%s,%s,%s,%d,%d,%d\n",
                    temp->data.passenger_id,
                    temp->data.fname,
                    temp->data.lname,
                    temp->data.nationality,
                     temp->data.seat_number,
                    temp->data.ticket_serial_number,
                    temp->data.plane_serial_number);
            temp = temp->next;
        }
    }

    fclose(file);
}
void PassengerLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Passenger file not found.\n");
        return;
    }
    printf("Opened file: %s\n", filename);


    // Clear current hash table
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PassengerNode* current = passengerHashTable[i];
        while (current) {
            struct PassengerNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        passengerHashTable[i] = NULL;


    }

    int id, seat, ticket, plane;
    char fname[21], lname[21], nationality[21];

    while (fscanf(file, "%d,%20[^,],%20[^,],%20[^,],%d,%d,%d\n",
                  &id, fname, lname, nationality, &seat, &ticket, &plane) == 7) {//==7 to ensure all are inserted without missings
        insertPassenger(id, fname, lname, nationality, seat, ticket, plane);
        printf("Loaded passenger: %d, %s, %s, %s, %d, %d, %d\n", id, fname, lname, nationality, seat, ticket, plane);


     }

    fclose(file);
}
void PilotLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Pilot file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct PilotNode* current = pilotHashTable[i];
        while (current) {
            struct PilotNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        pilotHashTable[i] = NULL;
    }

    int id, license;
    char fname[21], lname[21];
    while (fscanf(file, "%d,%20[^,],%20[^,],%d\n", &id, fname, lname, &license) == 4) {
        insertPilot(id, fname, lname, license);
    }

    fclose(file);
}
void savePilotToCSV(char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PilotNode* temp = pilotHashTable[i];
        while (temp) {
            fprintf(file, "%d,%s,%s,%d\n",
                    temp->data.pilot_id,
                    temp->data.fname,
                    temp->data.lname,
                    temp->data.license_number);
            temp = temp->next;
        }
    }
    fclose(file);
}
void PassengerCrewLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Passenger-Crew file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct PassengerCrewNode* current = passengerCrewHashTable[i];
        while (current) {
            struct PassengerCrewNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        passengerCrewHashTable[i] = NULL;
    }

    int passenger_id, crew_id;
    while (fscanf(file, "%d,%d\n", &passenger_id, &crew_id) == 2) {
        insertPassengerCrew(passenger_id, crew_id);
    }

    fclose(file);
}
void savePassengerCrewToCSV(char* filename) {
    FILE* file = fopen(filename, "w");

    for (int i = 0; i < HASH_SIZE; i++) {
        struct PassengerCrewNode* temp = passengerCrewHashTable[i];
        while (temp != NULL) {
            fprintf(file, "%d,%d\n",
                    temp->data.passenger_id,
                    temp->data.crew_id);
            temp = temp->next;
        }
    }

    fclose(file);
}
void CrewLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Crew file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct CrewNode* current = crewHashTable[i];
        while (current) {
            struct CrewNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        crewHashTable[i] = NULL;
    }

    int id, plane;
    char fname[21], lname[21], area[21];
    while (fscanf(file, "%d,%20[^,],%20[^,],%20[^,],%d\n",
                  &id, fname, lname, area, &plane) == 5) {
        insertCrew(id, fname, lname, area, plane);
    }

    fclose(file);
}
void saveCrewToCSV(char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct CrewNode* temp = crewHashTable[i];
        while (temp) {
            fprintf(file, "%d,%s,%s,%s,%d\n",
                    temp->data.crew_id,
                    temp->data.fname,
                    temp->data.lname,
                    temp->data.service_area,
                    temp->data.plane_serial_number);
            temp = temp->next;
        }
    }
    fclose(file);
}
void PlaneLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Plane file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct PlaneNode* current = planeHashTable[i];
        while (current) {
            struct PlaneNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        planeHashTable[i] = NULL;
    }

    int serial, speed, pilot;
    char model[21], airline[21];
    while (fscanf(file, "%d,%20[^,],%20[^,],%d,%d\n",
                  &serial, model, airline, &speed, &pilot) == 5) {
        insertPlane(serial, model, airline, speed, pilot);
    }

    fclose(file);
}
void savePlaneToCSV(char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PlaneNode* temp = planeHashTable[i];
        while (temp) {
            fprintf(file, "%d,%s,%s,%d,%d\n",
                    temp->data.serial_number,
                    temp->data.model_name,
                    temp->data.airline_number,
                    temp->data.speed,
                    temp->data.pilot_id);
            temp = temp->next;
        }
    }
    fclose(file);
}
void PilotPhoneLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Pilot Phone file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct PilotPhoneNode* current = pilotPhoneHashTable[i];
        while (current) {
            struct PilotPhoneNode* temDelete = current;
            current = current->next;
            free(temDelete);
        }
        pilotPhoneHashTable[i] = NULL;
    }

    int phone, pilot_id;
    while (fscanf(file, "%d,%d\n", &phone, &pilot_id) == 2) {
        insertPilotPhone(phone, pilot_id);
    }

    fclose(file);
}
void savePilotPhoneToCSV(char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct PilotPhoneNode* temp = pilotPhoneHashTable[i];
        while (temp) {
            fprintf(file, "%d,%d\n",
                    temp->data.Pilot_phone_number,
                    temp->data.pilot_id);
            temp = temp->next;
        }
    }
    fclose(file);
}
void TicketLoadFromCSV(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Ticket file not found.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct ticketNode * current = ticketHashTable[i];
        while (current) {
            struct ticketNode * temDelete = current;
            current = current->next;
            free(temDelete);
        }
        ticketHashTable[i] = NULL;
    }

    int serial, date;
    float price;
    char destination[21];
    while (fscanf(file, "%d,%d,%f,%20[^\n]\n", &serial, &date, &price, destination) == 4) {
        insertTicket(serial, date, price, destination);
    }

    fclose(file);
}
void saveTicketToCSV(char* filename) {
    FILE* file = fopen(filename, "w");


    for (int i = 0; i < HASH_SIZE; i++) {
        struct ticketNode * current = ticketHashTable[i];
        while (current != NULL) {
            fprintf(file, "%d,%d,%.2f,%s\n",
                    current->data.serial_number,
                    current->data.date,
                    current->data.price,
                    current->data.destination);
            current = current->next;
        }
    }

    fclose(file);
}




void* insertPilotThread(void* arg) {
    insertPilot(1, "Ali", "Zaid", 123);
    return NULL;
}
void* updatePilotThread(void* arg) {
    updatePilot(1, "Omar", "Zaid", 123); //  i am trying to change his name
    return NULL;
}


void FunctionalTests() {
    printf(" Functional Tests ");

     insertPassenger(200, "Maya", "Faris", "Jordanian", 15, 1000, 3000);
    struct PassengerNode* p = findPassengerByID(200);
    if (p && strcmp(p->data.fname, "Maya") == 0) {
        printf("  Passed\n");
    } else {
        printf("   Failed\n");
    }


     updatePassenger(200, "Maya", "Tariq", "Jordanian", 16, 1000, 3000);
    p = findPassengerByID(200);
    if (p && strcmp(p->data.lname, "Tariq") == 0 && p->data.seat_number == 16) {
        printf("    Passed\n");
    } else {
        printf("    Failed\n");
    }

     deletePassenger(200);
    p = findPassengerByID(200);
    if (p == NULL) {
        printf("    Passed\n");
    } else {
        printf("   Failed\n");
    }

    printf(" Functional Testing Done \n");
}



void tableMenu(int tableChoice) {
    int choice;


        switch (tableChoice) {
    case 1: { // Passenger
        PassengerLoadFromCSV("Passenger.csv");
        do {
            printf("\n[Passenger Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter ID FirstName LastName Nationality SeatNumber TicketSerial PlaneSerial:\n");
                scanf("%d %20s %20s %20s %d %d %d", &id, fname, lname, nationality, &seatNumber, &ticketSerial, &planeSerial);
                insertPassenger(id, fname, lname, nationality, seatNumber, ticketSerial, planeSerial);

            } else if (choice == 2) {
           scanf("%d", &id);
                printPassengerByID(id);
            } else if (choice == 3) {
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deletePassenger(id);

            } else if (choice == 4) {
                printf("Enter ID and New FirstName LastName Nationality SeatNumber TicketSerial PlaneSerial:\n");
                scanf("%d %20s %20s %20s %d %d %d", &id, fname, lname, nationality, &seatNumber, &ticketSerial, &planeSerial);
                updatePassenger(id, fname, lname, nationality, seatNumber, ticketSerial, planeSerial);

            }
        } while (choice != 5);
        savePassengerToCSV("Passenger.csv");
        break;
    }

    case 2: { // Pilot
        PilotLoadFromCSV("Pilot.csv");
        do {
            printf("\n[Pilot Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter ID FirstName LastName LicenseNumber:\n");
                scanf("%d %20s %20s %d", &id, fname, lname, &license);
                insertPilot(id, fname, lname, license);
            } else if (choice == 2) {
               scanf("%d", &id);

                printPilotByID(id);
            } else if (choice == 3) {
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deletePilot(id);
            } else if (choice == 4) {
                printf("Enter ID and New FirstName LastName LicenseNumber:\n");
                scanf("%d %20s %20s %d", &id, fname, lname, &license);
                updatePilot(id, fname, lname, license);
            }
        } while (choice != 5);
        savePilotToCSV("Pilot.csv");
        break;
    }

    case 3: { // Plane
        PlaneLoadFromCSV("plane.csv");
        do {
            printf("\n[Plane Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter SerialNumber Model Airline Speed PilotID:\n");
                scanf("%d %20s %20s %d %d", &serial, model, airline, &speed, &id);
                insertPlane(serial, model, airline, speed, id);
            } else if (choice == 2) {
              scanf("%d", &serial);
                printPlaneByID(serial);
            } else if (choice == 3) {
                printf("Enter Serial Number to delete: ");
                scanf("%d", &serial);
                deletePlane(serial);
            } else if (choice == 4) {
                printf("Enter SerialNumber and New Model Airline Speed PilotID:\n");
                scanf("%d %20s %20s %d %d", &serial, model, airline, &speed, &id);
                updatePlane(serial, model, airline, speed, id);
            }
        } while (choice != 5);
        savePlaneToCSV("plane.csv");
        break;
    }

    case 4: { // Ticket
        TicketLoadFromCSV("Ticket.csv");
        do {
            printf("\n[Ticket Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter SerialNumber Date Price Destination:\n");
                scanf("%d %d %f %s", &serial, &ticketDate, &ticketPrice, destination);
                insertTicket(serial, ticketDate, ticketPrice, destination);
            } else if (choice == 2) {
            scanf("%d", &serial);

                printTicketByID(serial);
            } else if (choice == 3) {
                printf("Enter Serial Number to delete: ");
                scanf("%d", &serial);
                deleteTicket(serial);
            } else if (choice == 4) {
                printf("Enter SerialNumber and New Date Price Destination:\n");
                scanf("%d %d %f %s", &serial, &ticketDate, &ticketPrice, destination);
                updateTicket(serial, ticketDate, ticketPrice, destination);
            }
        } while (choice != 5);
        saveTicketToCSV("Ticket.csv");
        break;
    }

    case 5: { // Crew
        CrewLoadFromCSV("Crew.csv");
        do {
            printf("\n[Crew Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter ID FirstName LastName ServiceArea PlaneSerial:\n");
                scanf("%d %20s %20s %20s %d", &id, fname, lname, serviceArea, &planeSerial);
                insertCrew(id, fname, lname, serviceArea, planeSerial);
            } else if (choice == 2) {
            scanf("%d", &id);

                printCrewByID(id);
            } else if (choice == 3) {
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteCrew(id);
            } else if (choice == 4) {
                printf("Enter ID and New FirstName LastName ServiceArea PlaneSerial:\n");
                scanf("%d %20s %20s %20s %d", &id, fname, lname, serviceArea, &planeSerial);
                updateCrew(id, fname, lname, serviceArea, planeSerial);
            }
        } while (choice != 5);
        saveCrewToCSV("Crew.csv");
        break;
    }

    case 6: { // Passenger-Crew Relationship
    PassengerCrewLoadFromCSV("Passenger_Crew.csv");
    do {
        printf("\n[PassengerCrew Table]\n1. Insert\n2. View\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter PassengerID and CrewID:\n");
            scanf("%d %d", &passengerId, &crewId);
            insertPassengerCrew(passengerId, crewId);
        } else if (choice == 2) {
             printPassengersForCrew(crewId);
        } else if (choice == 3) {
            printf("Enter PassengerID and CrewID to delete:\n");
            scanf("%d %d", &passengerId, &crewId);
            deletePassengerCrew(passengerId, crewId);

        }
    } while (choice != 5);
    savePassengerCrewToCSV("Passenger_Crew.csv");
    break;
}

case 7: { // Pilot Phone Numbers
    //  Load data from CSV when entering the menu
    PilotPhoneLoadFromCSV("Pilot_Phone.csv");

    do {
        printf("\n[PilotPhone Table]\n1. Insert\n2. View by Pilot\n3. Delete\n4. Update\n5. Save & Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter PilotID and PhoneNumber:\n");
            scanf("%d %d", &id, &phoneNumber);
            insertPilotPhone(id, phoneNumber);

        } else if (choice == 2) {
            printf("Enter PilotID to view phones:\n");
            scanf("%d", &id);
            printPhonesForPilot(id); // ✅ specialized view

        } else if (choice == 3) {
            printf("Enter PilotID and PhoneNumber to delete:\n");
            scanf("%d %d", &id, &phoneNumber);
            deletePilotPhone(id, phoneNumber);

        }


    } while (choice != 5);

     savePilotPhoneToCSV("Pilot_Phone.csv");
    break;
}


    default:
        printf("Invalid table.\n");
    }
}

int main() {
/*
//TESTING:

//unit testing:
insertPilot(1, "Ali", "Zaid", 123);
printPilotByID(1);
updatePilot(1, "Omar", "Tariq", 999);
printPilotByID(1);
//deletePilot(1);

insertPlane(101, "xxx737", "R123", 850, 1);
updatePlane(101, "AirbusA320", "R321", 820, 1);
deletePlane(101);

insertPassenger(10, "Lina", "Saleh", "Jordanian", 15, 200, 101);
updatePassenger(10, "Maya", "Tariq", "Jordanian", 16, 200, 101);
deletePassenger(10);

insertCrew(50, "Ahmad", "Khaled", "Medical", 101);
updateCrew(50, "Sami", "Nashat", "Security", 101);
deleteCrew(50);


insertTicket(200, 20250606, 99.5, "Amman");
updateTicket(200, 20250610, 120.0, "Aqaba");
deleteTicket(200);

insertPilotPhone(799999999,1 );
insertPilotPhone(788888888,1 );
deletePilotPhone(1, 777777777);
printPhonesForPilot(1);

insertPassengerCrew(10, 50);
deletePassengerCrew(10, 51);
printPassengersForCrew(51);*/


//FunctionalTests();

        pthread_t thread1;
        pthread_t thread2;

        pthread_create(&thread1, NULL, insertPilotThread, NULL);//all nulls is to use defualt settings , the first arg is where to stroe the thread ID
        pthread_create(&thread2, NULL, updatePilotThread, NULL);
        pthread_join(thread1, NULL); //null is for the return of the thread , the fucntion at all if for pusing the main function till this thread end
        pthread_join(thread2, NULL);//becouse not usinf them may continu to the main while the results of this is not happning




      int tableChoice;
    do {
        printf("\n Main Menu  \n");
printf("1. Passenger\n2. Pilot\n3. Plane\n4. Ticket\n5. Crew\n6. PassengerCrew\n7. PilotPhone\n0. Exit\nSelect Table: ");
        scanf("%d", &tableChoice);

        if (tableChoice >= 1 && tableChoice <= 7) {
            tableMenu(tableChoice);
        }

    } while (tableChoice != 0);




    printf("Program finished.\n");
    return 0;
}
