# Power-Grid-Management-System
Power Grid Management System is a C++ console app that loads district data, sorts by population, and lets users view status, adjust power supply, toggle district power, assign technicians, and save/load files. It includes demand checks with warnings and a simple menu interface.

Key features include:
Power Management – Set total available power supply, shut off or restore individual districts, and see real-time updates.
Demand Monitoring – Automatically checks total power demand against supply, issuing critical warnings when shortages occur.
Technician Assignment – Add technicians to districts and instantly update their records.
Save/Load Support – Persist the current grid state to a file or load a new configuration at any time.
Sorting by Population – Ensures the most densely populated districts are listed first for priority decisions.

The user interacts through a simple numeric menu:
View all district status.
Update total power supply.
Shut off a district’s power.
Restore a district’s power.
Assign a technician.
Save the current configuration.
Load a configuration from file.
Exit the program.

This project demonstrates practical skills in struct-based data modeling, file I/O, sorting algorithms, conditional logic, and array-based storage without relying on STL containers. It’s an example of building an interactive, persistent, and logically complex application entirely in C++.
