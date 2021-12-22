# Room-Booking-Manager-RBM-
Room Booking Manager (RBM) is made for course semester group Project. 
All rights belong to: CHEN Yi pu(Banjibear), LIANG Rui, XIE Yangxiaolong, LIU Sicheng, and CHEUNG, Man Fung

Room Booking Manager (RBM) is a system that applies the theory of process scheduling of an OS to schedule bookings of facilities according to time and priority conditions

The project consists of the following parts:
1. Part 1: Develop a program that allows users to add details of a booking (date, time, duration, and/or callees etc.) to the schedule. Besides the standard line by line input approach, RBM should be able to read in batch files which containing the booking requests, i.e. one or more than one booking requests are stored in such batch files. Note that the one who initiates for the booking is called the “user” or the “caller” and those others involved in the booking are called “callees”. This part of the program module is referred to as the Input Module.
2. Part 2: Extend the program developed in Part 1 with a scheduler to generate timetables for all bookings (e.g. meeting room booking schedule and tenant booking records). The scheduler will implement several scheduling algorithms similar to those covered in lectures. This is the called the Scheduling Kernel, within the Scheduling Module.
3. Part 3: Augment the program with the facilities to print booking schedule for meeting rooms and related devices in Part 2. Those rejected bookings should all be included. This constitutes the Output Module.
4. Part 4: Provide the program with the ability to generate a summary report to analyze the results produced in Part 3. Compare the different schedules (generated from different algorithms) and find out which one would make the best use of the three meeting rooms. Your program should preferably be able to process N meeting rooms (N = 3 in the existing case) to cope with the expansion of PolySME in the near future. It should also be preferably able to handle more resource types in future. By the way, an outstanding (rejected) list may also be included in this report for those requests that cannot be scheduled. This final module is the Analyzer Module.
5. Part 5: Augment the program RBM to check whether or not the required facilities are available. If so, it assigns a priority on each booking. For example, if a room is booked for a presentation and should be equipped with projector and screen, the projector and screen will be reserved for that booking with a higher priority. Even though the projector and screen have been reserved for another booking but without using a meeting room, i.e. someone reserves only the two pieces of equipment by that moment, the booking would be then rejected. Of course, you may have other assumptions on how the conflicting bookings are being scheduled/rescheduled, and the associated priority.

# Installization
The System can only be executed on Mac or Linux system
Download the source code, compile and execute the code in terminals

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.

# License
MIT
