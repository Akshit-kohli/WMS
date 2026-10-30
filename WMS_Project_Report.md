# WMS — Weighbridge Management System
## Project Report

---

| | |
|---|---|
| **Institution** | GL Bajaj Institute of Technology and Management, Greater Noida |
| **Department** | Computer Science & Engineering |
| **Programme** | Bachelor of Technology (B.Tech) |
| **Session** | 2026 – 2027 |
| **Project Title** | WMS — Weighbridge Management System |
| **Submitted By** | Akshit · Adarsh Pandey |
| **Status** | In Progress |

---

## Table of Contents

1. [Abstract](#1-abstract)
2. [Introduction](#2-introduction)
3. [Problem Statement](#3-problem-statement)
4. [Objectives](#4-objectives)
5. [System Architecture](#5-system-architecture)
6. [Technology Stack](#6-technology-stack)
7. [Module-wise Description](#7-module-wise-description)
   - 7.1 [C++ Hardware Engine](#71-c-hardware-engine)
   - 7.2 [TypeScript Backend Server](#72-typescript-backend-server)
   - 7.3 [Web Dashboard](#73-web-dashboard)
   - 7.4 [Mobile Application](#74-mobile-application)
8. [Data Flow](#8-data-flow)
9. [Database Design](#9-database-design)
10. [Key Features](#10-key-features)
11. [Transaction Lifecycle](#11-transaction-lifecycle)
12. [Challenges & Solutions](#12-challenges--solutions)
13. [Future Scope](#13-future-scope)
14. [Conclusion](#14-conclusion)
15. [References](#15-references)
16. [Declaration](#16-declaration)

---

## 1. Abstract

WMS (Weighbridge Management System) is a full-stack industrial-grade software system designed to automate and digitize the operations of a weighbridge facility. The system reads raw hardware signals from a weighbridge machine over an RS-232 serial interface, processes the weight data through a C++ engine, stores transactions in a PostgreSQL database via a TypeScript backend, and presents analytics to operators through a Next.js web dashboard and a Kotlin-based Android mobile application.

The project was conceived from a real-world industry requirement, making it a practical, production-ready system rather than an academic exercise. It demonstrates the integration of embedded/systems programming, modern web development, mobile development, and database management within a single cohesive product.

---

## 2. Introduction

A **weighbridge** (also called a truck scale) is a large platform scale used in industrial environments to measure the weight of vehicles and the materials they carry. Industries such as mining, construction, agriculture, and logistics rely on weighbridges to calculate material quantities, generate bills, and maintain transaction records.

Traditional weighbridge setups are either fully manual (paper-based records) or use outdated standalone software that is not connected to any network or analytics system. This results in:

- Error-prone manual data entry
- No real-time monitoring capability
- Difficulty in generating reports across multiple branches
- Lack of mobile access for branch managers

WMS addresses all of these pain points by building a modern, connected, full-stack solution over the existing weighbridge hardware — without replacing the hardware itself.

---

## 3. Problem Statement

Industrial weighbridge operations are typically managed through disconnected, manual, or legacy systems that fail to provide:

- **Real-time data** from the weighbridge hardware to management dashboards
- **Accurate and automated** weight-to-charge calculation and receipt generation
- **Centralized storage** of transaction records across multiple branches
- **Remote access** for branch managers to monitor activity and revenue on mobile devices

The core challenge is bridging the gap between legacy RS-232 serial hardware and a modern, networked, full-stack software ecosystem — while ensuring reliability in a real industrial environment.

---

## 4. Objectives

1. Read live weight data from weighbridge hardware over an RS-232 serial port using a C++ engine.
2. Automate the full transaction lifecycle: gross weight → tare weight → net weight → charge calculation → receipt printing.
3. Persist all transaction data to a centralized PostgreSQL database via an HTTP API.
4. Provide a web-based dashboard for viewing transactions, revenue analytics, and activity summaries.
5. Provide a mobile application for Android giving branch managers real-time insights and alerts.
6. Design the system to be extensible for multiple branches.

---

## 5. System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                        WEIGHBRIDGE HARDWARE                     │
│              (Physical scale — RS-232 serial output)            │
└──────────────────────────────┬──────────────────────────────────┘
                               │  RS-232 Serial Signal
                               ▼
┌─────────────────────────────────────────────────────────────────┐
│                     C++ ENGINE (Layer 1)                        │
│  • Reads serial port via termios.h                              │
│  • Manages transaction lifecycle (gross → tare → net)           │
│  • Calculates charges (Net Weight × Rate/KG)                    │
│  • Prints receipt to thermal printer                            │
│  • POSTs transaction JSON to TypeScript server (cpp-httplib)    │
└──────────────────────────────┬──────────────────────────────────┘
                               │  HTTP POST (JSON)
                               ▼
┌─────────────────────────────────────────────────────────────────┐
│              TYPESCRIPT BACKEND SERVER (Layer 2)                │
│  • Bun runtime + Express.js                                     │
│  • Receives and validates transaction data                      │
│  • Persists to PostgreSQL via Prisma ORM                        │
│  • Exposes REST API endpoints for dashboard and mobile app      │
└────────────────┬────────────────────────────┬───────────────────┘
                 │  REST API                  │  REST API
                 ▼                            ▼
┌──────────────────────────┐    ┌─────────────────────────────────┐
│   WEB DASHBOARD (L3a)    │    │    MOBILE APP — Android (L3b)   │
│   Next.js, Tailwind,     │    │    Kotlin + Jetpack Compose     │
│   shadcn/ui              │    │    Real-time alerts             │
│   Revenue analytics      │    │    Transaction history          │
│   Branch monitoring      │    │    Branch manager access        │
└──────────────────────────┘    └─────────────────────────────────┘
                                       │
                      ┌────────────────┴────────────────┐
                      │     PostgreSQL 17 Database       │
                      │     (via Prisma ORM)             │
                      └─────────────────────────────────┘
```

---

## 6. Technology Stack

| Layer | Technology | Purpose |
|---|---|---|
| **Hardware Engine** | C++17 | Core transaction logic and serial port communication |
| | `termios.h` | RS-232 serial port I/O on Linux/POSIX |
| | `cpp-httplib` | HTTP client to POST data to TypeScript server |
| | `nlohmann/json` | JSON serialization of transaction payload |
| **Backend Server** | Bun | High-performance JavaScript/TypeScript runtime |
| | Express.js | REST API routing and middleware |
| | TypeScript | Type-safe server-side logic |
| **Database** | PostgreSQL 17 | Relational database for transaction storage |
| | Prisma ORM | Type-safe database client and schema management |
| **Web Dashboard** | Next.js | React-based full-stack web framework |
| | Tailwind CSS | Utility-first CSS styling |
| | shadcn/ui | Pre-built accessible UI component library |
| **Mobile App** | Kotlin | Android native development language |
| | Jetpack Compose | Modern declarative Android UI toolkit |

---

## 7. Module-wise Description

### 7.1 C++ Hardware Engine

The C++ engine is the core of the entire system and runs on the operator's machine at the weighbridge.

**Responsibilities:**
- Opens and configures the RS-232 serial port using `termios.h` for raw POSIX serial I/O
- Continuously reads weight readings from the weighbridge hardware
- Manages the full transaction workflow through operator interaction
- Performs net weight and charge calculations
- Outputs a formatted receipt to a thermal printer
- Serializes the completed transaction as JSON using `nlohmann/json` and sends it via HTTP POST to the TypeScript server using `cpp-httplib`

**Transaction fields captured:**
- Customer name, phone number
- Vehicle number and vehicle type
- Material type
- Gross weight (loaded vehicle)
- Tare weight (empty vehicle)
- Net weight (calculated)
- Rate per KG
- Total charges (calculated)
- Timestamp

---

### 7.2 TypeScript Backend Server

The backend server acts as the data hub between the C++ engine and the client applications.

**Responsibilities:**
- Listens for HTTP POST requests from the C++ engine
- Validates and sanitizes incoming transaction data
- Stores transactions in PostgreSQL using Prisma ORM
- Exposes REST API endpoints for:
  - Fetching transaction history (with filters by date, branch, vehicle type, material)
  - Revenue summaries (daily, monthly, annual)
  - Customer count analytics
  - Branch-level aggregates

**Runtime:** Bun — chosen for its fast startup time, native TypeScript support, and high-performance HTTP throughput, making it suitable for always-on industrial use.

---

### 7.3 Web Dashboard

The web dashboard is a browser-based management interface for weighbridge operators and supervisors.

**Built with:** Next.js + Tailwind CSS + shadcn/ui

**Key features:**
- View all transactions in a filterable, paginated table
- Revenue breakdown by branch, vehicle type, and material
- Daily, monthly, and annual customer count charts
- Real-time updates as new transactions come in
- Accessible, responsive UI using shadcn/ui components

---

### 7.4 Mobile Application

The Android mobile app gives branch managers on-the-go access to weighbridge data.

**Built with:** Kotlin + Jetpack Compose

**Key features:**
- Real-time transaction alerts and push notifications
- View transaction history for their assigned branch
- Revenue and activity summary at a glance
- Lightweight and optimized for field use

---

## 8. Data Flow

```
Operator Input
     │
     ▼
C++ Engine (serial read → transaction build)
     │
     │──► Receipt Printed (thermal printer)
     │
     ▼
HTTP POST → TypeScript Server → PostgreSQL
                                    │
                          ┌─────────┴──────────┐
                          ▼                    ▼
                    Web Dashboard         Mobile App
                    (Analytics)          (Alerts + History)
```

---

## 9. Database Design

The PostgreSQL database (managed via Prisma ORM) stores all transaction data. A representative schema is as follows:

```prisma
model Transaction {
  id            Int      @id @default(autoincrement())
  createdAt     DateTime @default(now())
  customerName  String
  phone         String
  vehicleNumber String
  vehicleType   String
  material      String
  grossWeight   Float    // in KG
  tareWeight    Float    // in KG
  netWeight     Float    // grossWeight - tareWeight
  ratePerKg     Float
  totalCharges  Float    // netWeight × ratePerKg
  branch        String
}
```

---

## 10. Key Features

| Feature | Description |
|---|---|
| **Real hardware integration** | Directly reads RS-232 serial signals from weighbridge scale |
| **Full transaction lifecycle** | Gross weight → Tare weight → Net weight → Charge → Receipt → DB |
| **Automated charge calculation** | Net Weight × Rate/KG, no manual arithmetic |
| **Thermal receipt printing** | Operator receives a printed record instantly |
| **Centralized data storage** | PostgreSQL stores all transactions across branches |
| **Web analytics dashboard** | Revenue, vehicle type, material, and customer trend analytics |
| **Mobile access** | Android app for branch managers with real-time alerts |
| **Multi-branch support** | Architecture designed to handle multiple locations |
| **Type-safe backend** | TypeScript + Prisma ensures reliable, predictable data handling |

---

## 11. Transaction Lifecycle

```
Step 1 — Vehicle Arrives
   └─► Operator enters: customer name, phone, vehicle number, vehicle type, material

Step 2 — Gross Weight
   └─► Loaded vehicle drives onto scale
   └─► C++ engine reads weight from serial port → Gross Weight recorded

Step 3 — Unloading
   └─► Vehicle offloads material at facility

Step 4 — Tare Weight
   └─► Empty vehicle drives onto scale again
   └─► C++ engine reads weight → Tare Weight recorded

Step 5 — Calculation
   └─► Net Weight   = Gross Weight − Tare Weight
   └─► Total Charge = Net Weight × Rate per KG

Step 6 — Output
   └─► Receipt printed to thermal printer
   └─► Transaction POSTed to TypeScript server as JSON

Step 7 — Storage & Analytics
   └─► Server saves to PostgreSQL
   └─► Dashboard and mobile app reflect updated data
```

---

## 12. Challenges & Solutions

| Challenge | Solution |
|---|---|
| Reading raw RS-232 serial signals from hardware | Used POSIX `termios.h` for low-level serial port configuration and I/O in C++ |
| Bridging C++ hardware layer with modern web stack | Used `cpp-httplib` to make HTTP POST requests directly from the C++ engine |
| Type-safe data handling across layers | TypeScript + Prisma ORM ensures consistent, validated data from API to DB |
| Fast, always-on server for industrial use | Chose Bun runtime for its high performance and native TypeScript support |
| Mobile access without complex infrastructure | REST API from TypeScript server directly consumed by Android app |
| Real-time analytics across branches | PostgreSQL aggregate queries exposed via API, rendered in Next.js dashboard |

---

## 13. Future Scope

- **Cloud deployment** — Host the TypeScript server and database on AWS/GCP for high availability
- **Multi-branch dashboard** — Centralized super-admin view across all branches
- **RFID / ANPR integration** — Automatically identify vehicles using RFID tags or license plate recognition cameras
- **Real-time WebSocket updates** — Push live weight readings to the web dashboard
- **PDF report generation** — Export daily/monthly transaction reports as PDF from the dashboard
- **SMS/WhatsApp notifications** — Automatically send receipts to customers via SMS/WhatsApp API after each transaction
- **Offline mode for C++ engine** — Queue transactions locally when the server is unreachable and sync on reconnect
- **Role-based access control (RBAC)** — Operator, supervisor, and admin roles with different permissions

---

## 14. Conclusion

WMS (Weighbridge Management System) successfully demonstrates the design and implementation of a full-stack, hardware-integrated industrial system. By directly interfacing with RS-232 serial hardware via a C++ engine and connecting it to a modern TypeScript backend, PostgreSQL database, Next.js web dashboard, and Kotlin Android app, the project bridges the gap between legacy industrial hardware and contemporary software development practices.

The system automates the entire weighbridge transaction lifecycle — eliminating manual errors, enabling real-time analytics, and providing mobile access for branch managers. The project reflects a realistic, production-oriented engineering approach and covers a broad range of domains including systems programming, backend development, database design, web development, and mobile development.

---

## 15. References

1. ISO 8217 — Standards for weighbridge equipment and calibration
2. Stroustrup, B. (2013). *The C++ Programming Language* (4th ed.). Addison-Wesley.
3. PostgreSQL Documentation — https://www.postgresql.org/docs/
4. Prisma ORM Documentation — https://www.prisma.io/docs
5. Next.js Documentation — https://nextjs.org/docs
6. Jetpack Compose Documentation — https://developer.android.com/develop/ui/compose/documentation
7. Bun Runtime Documentation — https://bun.sh/docs
8. `cpp-httplib` — https://github.com/yhirose/cpp-httplib
9. `nlohmann/json` — https://github.com/nlohmann/json
10. `termios.h` POSIX Reference — https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/termios.h.html

---

## 16. Declaration

We hereby declare that the project report titled **"WMS — Weighbridge Management System"** submitted in partial fulfilment of the requirements for the degree of Bachelor of Technology (B.Tech) in Computer Science & Engineering at GL Bajaj Institute of Technology and Management, Greater Noida, is an original work carried out by us.

The work contained in this report has not been submitted elsewhere for the award of any other degree or diploma. All sources referred to in this report have been duly acknowledged.

&nbsp;

| | |
|---|---|
| **Akshit** | **Adarsh Pandey** |
| Student | Co-Developer — System Design · Testing · Documentation |
| B.Tech (CSE), GLBITM | B.Tech (CSE), GLBITM |

&nbsp;

| | |
|---|---|
| **Supervisor / Guide:** | ___________________________ |
| **Date:** | ___________________________ |
| **Place:** | Greater Noida |

---

*Department of Computer Science & Engineering*
*GL Bajaj Institute of Technology and Management, Greater Noida*
*Session 2026 – 2027*
