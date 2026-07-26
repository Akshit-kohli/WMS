##Status - In Progress..

---

#WMS — Weighbridge Management System 
WMS is a full-stack weighbridge management system built for real-world industrial use. It handles everything from reading raw hardware signals to generating receipts and storing transaction data.

##Why I built this :-
A contact in the industry gave me this as a real project requirement. Instead of building another todo app, I wanted something that touches actual hardware, systems programming, and modern web development at the same time.

##How it works :-
A weighbridge machine sends weight readings over an RS-232 serial cable. The C++ engine reads those signals directly from the serial port, processes them, and manages the full transaction lifecycle. Once a transaction is complete, it sends the data to a TypeScript server which stores it in PostgreSQL. A web dashboard and mobile app let managers track revenue and activity.

---

##Working:-

###C++ Engine
1.Vehicle arrives at the weighbridge
2.Operator enters customer name, phone, vehicle number, vehicle type and material
3.Loaded vehicle drives onto the scale — gross weight captured
4.Vehicle offloads material
5.Empty vehicle drives onto the scale again — tare weight captured
6.Net Weight = Gross Weight − Tare Weight
7.Charges = Net Weight × Rate per KG
8.Receipt printed to thermal printer
9.Transaction POSTed to TypeScript server as JSON

###TypeScript Server
Receives transaction data from the C++ engine via HTTP POST and saves it to PostgreSQL using Prisma ORM. Also serves API endpoints for the dashboard and mobile app.

###Web Dashboard
Built with Next.js — lets operators view transactions, monitor revenue by branch, vehicle type and material, and see daily, monthly and annual customer counts.

###Mobile App
Built with Kotlin for Android — gives branch managers real-time insights and transaction alerts on the go.

## Tech Stack

| Layer | Technology |
|---|---|
| Hardware engine | C++17, termios.h, cpp-httplib, nlohmann/json |
| Backend server | Bun, Express, TypeScript |
| Database | PostgreSQL 17, Prisma ORM |
| Web dashboard | Next.js, Tailwind CSS, shadcn/ui |
| Mobile app | Kotlin, Jetpack Compose |
