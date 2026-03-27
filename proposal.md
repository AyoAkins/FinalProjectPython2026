# Proposal

## What will (likely) be the title of your project?
TCP Port Scanner Tool
TODO

## In just a sentence or two, summarize your project. (E.g., "A website that lets you buy and sell stocks.")
A command-line tool written in C that scans the computer to determine which ports are open, closed, or filtered, helping users understand running services.
TODO

## In a paragraph or more, detail your project. What will your software do? What features will it have? How will it be executed?
This project is a TCP port scanner written in C that allows users to input an IP address or hostname and scan ports to determine whether they are open or closed. It uses socket programming with functions like socket() and connect(), along with timeout handling to improve performance. The program will support scanning single ports or ranges, accept command-line arguments, and display results in a clear format. It will run in the terminal while focusing on efficient execution and proper error handling.
TODO

## If planning to combine 1051's final project with another course's final project, with which other course? And which aspect(s) of your proposed project would relate to 1051, and which aspect(s) would relate to the other course?
N/A

## If planning to collaborate with 1 or 2 classmates for the final project, list their names, email addresses, and the names of their assigned TAs below.
Henry Sithisane, Kai Raymomd
TODO, if applicable

## In the world of software, most everything takes longer to implement than you expect. And so it's not uncommon to accomplish less in a fixed amount of time than you hope.

### In a sentence (or list of features), define a GOOD outcome for your final project. I.e., what WILL you accomplish no matter what?

A working C program that:
Accepts an IP address
Checks at least one port
Correctly reports whether the port is open or closed

### In a sentence (or list of features), define a BETTER outcome for your final project. I.e., what do you THINK you can accomplish before the final project's deadline?

Scan a range of ports (e.g., 1–1024)
Accept command-line arguments for IP and port range
Implement timeout handling to prevent hanging connections
Clean and readable output showing open ports

### In a sentence (or list of features), define a BEST outcome for your final project. I.e., what do you HOPE to accomplish before the final project's deadline?
Multithreaded scanning for faster performance
Hostname support (e.g., scanning domains instead of just IPs)
Banner grabbing (identify services running on open ports)
Export results to a file (e.g., CSV or JSON)
Optional color-coded terminal output


## In a paragraph or more, outline your next steps. What new skills will you need to acquire? What topics will you need to research? If working with one of two classmates, who will do what?
- Socket Programming
- TCP
- What an IP address and port actually represent
- Timeouts & Control 
- Multithreading
- Performance optimization
One of us is going to deal with the socket programming and the port checking logic.
The second will deal with Timeout handling, overall program structure, debugging low-level issues
The third will deal with CLI + User Interface as well as help with design logic
