# Airport Mini-DBMS in C

A small in-memory database engine written in C for an airport scenario (pilots, planes, tickets, passengers, crew), built for a university database programming course.

Instead of using an existing database, it implements the storage layer itself:

- **Hash-table indexing**: every table is a hash table with chaining (`HASH_SIZE 13`) for fast lookup by primary key
- **Full CRUD**: insert, view, update and delete on 7 tables
- **Primary-key uniqueness**: inserting a record whose key already exists is rejected
- **Concurrency control**: a `pthread` mutex protects every write, and a demo at startup runs an insert thread and an update thread at the same time
- **Persistence**: tables are loaded from and saved to CSV files
- **Menu-driven console interface**

## Tables

| Table | Key | Notes |
|---|---|---|
| Pilot | `pilot_id` | name, license number |
| Plane | `serial_number` | FK to Pilot |
| Ticket | `serial_number` | date, price, destination |
| Passenger | `passenger_id` | FKs to Ticket and Plane |
| Crew | `crew_id` | FK to Plane |
| PassengerCrew | (passenger, crew) | many-to-many link |
| PilotPhone | (phone, pilot) | multi-valued attribute |

## Build and run

Requires `gcc` and POSIX threads (Linux, macOS, or MinGW/WSL on Windows).

```bash
make run
```

or manually:

```bash
gcc -Wall -pthread -o airportdb airportdb.c
cd data && ../airportdb
```

The program reads and writes the CSV files in the folder it is run from, so run it from `data/`. Choosing **Save & Back** in a table menu writes that table back to its CSV.

## Sample session

```
Main Menu
1. Passenger  2. Pilot  3. Plane  4. Ticket  5. Crew  6. PassengerCrew  7. PilotPhone  0. Exit
Select Table: 2

[Pilot Table]
1. Insert  2. View  3. Delete  4. Update  5. Save & Back
Choice: 2
Enter ID: 1
Pilot ID: 1
Name: Omar Khaled
License Number: 10234
```

## Notes

- The sample data in `data/` is fictional.
- The startup demo runs two threads (insert pilot 1, update pilot 1). Because they run concurrently, the update may run before the insert and print "Pilot not found". That is the race the mutex is there to make safe, not a crash.
- Possible improvements: enforcing foreign keys (reject a plane whose pilot does not exist, handle deletes of parent records), dynamic hash-table resizing, input validation on every field, and unit tests.

## What I learned

- Building indexes and tables from scratch with linked lists and hash functions
- Modelling a relational schema (one-to-many, many-to-many, multi-valued attributes) in data structures
- Protecting shared data with mutexes in a multi-threaded program
- Memory safety in C: sizing buffers and bounding input
