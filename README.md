# University Library Management System

A command-line library management system implemented in C++20 as part of a university assessment. The system allows library staff to manage resources and users, handle borrowing and returning of resources, and generate various reports.

---

## Features

### Core
- Load resources (Books, Journals, Conferences) from a text file into a structured resource list
- Load system users (Students, Staff, Library Staff) from a text file into a user list
- Borrow resources with per-user limits enforced automatically
- Return borrowed resources and update records accordingly
- List all resources currently available for lending
- Report all resources currently on loan
- Report all users who have borrowed a resource

### Extended
- Sort available/loaned resource listings ascending or descending by title or author
- Save the borrowed-users report to an external text file
- Keyword search across resource titles, authors, and conference acronyms (results sorted alphabetically)
- Chronological activity log of all borrowing and returning events, viewable on demand

---

## Class Overview

| Class | Description |
|---|---|
| `Person` | Abstract base class for all users |
| `Student` | Can borrow up to **1** resource |
| `Staff` | Can borrow up to **2** resources |
| `LibStaff` | Cannot borrow any resources |
| `Resource` | Abstract base class for all library resources |
| `Book` | Borrowable; unique ID (string) |
| `Journal` | Borrowable; unique ID (string) |
| `Conference` | **Not** borrowable |
| `Loan` | Associates one resource with one user |
| `ResourceList` | Loads and manages all resources |
| `UserList` | Loads and manages all users |

---

## Building the Project

This project uses **CMake** and targets **C++20**. It is developed in **CLion**.

### Prerequisites
- CMake 4.1+
- A C++20-compatible compiler (GCC 10+, Clang 12+, or MSVC 2019+)

### Build Steps

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Or simply open the project in CLion and use the built-in build/run configurations.

---

## Usage

Run the compiled executable from the project root so that the relative paths to the data files resolve correctly:

```bash
./library_sys
```

The interface is operated from the perspective of a library staff member. On launch, resources and users are loaded automatically from the data files. You will then be presented with a menu to perform any of the supported operations.

### Borrowing Rules

| User Type | Max Resources |
|---|---|
| Student | 1 |
| Staff | 2 |
| Library Staff | 0 |

- Each `Book` or `Journal` can only be on loan to one user at a time.
- `Conference` resources cannot be borrowed.

---

## Input File Format

### `A2ResourceList.txt`
Each line represents a resource in a defined delimited format, specifying the type (Book/Journal/Conference) followed by its attributes such as ID, title, and author.

### `A2UserList.txt`
Each line represents a user, specifying the type (Student/Staff/LibStaff) followed by their attributes such as ID and name.

> Refer to the provided sample files for the exact format expected.

---

## Requirements

- C++20
- CMake
- CLion (recommended IDE)