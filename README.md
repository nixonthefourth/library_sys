# University Library Management System
**CMP2811, Applied Programming Paradigms**  
*Mykyta Khomiakov*

A command-line library management system implemented in C++20. The system allows library staff to manage resources and users, handle borrowing and returning, generate reports, and search the catalogue – all from a styled terminal interface.

---

## Features

### Core
- Load resources (Books, Journals, Conferences) from a text file into a structured resource list
- Load system users (Students, Staff, Library Staff) from a text file into a user list
- Borrow resources with per-user limits enforced automatically
- Return borrowed resources and update all records accordingly
- List all resources currently available for lending
- Report all resources currently on loan
- Report all users who currently have borrowed resources

### Extended
- Sort available and loaned resource listings ascending or descending by **title** or **author**
- Save the borrowed-users report to an external text file (`user_report.txt`)
- Keyword search across resource titles, authors, and conference acronyms, where the results sorted alphabetically
- Chronological activity log of all borrowing and returning events, viewable on demand

---

## Class Overview

| Class | Role | Borrow Limit |
|---|---|---|
| `Person` | Base class for all system users | — |
| `Student` | Inherits from `Person` | 1 resource |
| `Staff` | Inherits from `Person` | 2 resources |
| `LibStaff` | Inherits from `Person` | 0 resources |
| `Resource` | Base class for all library resources | — |
| `Book` | Inherits from `Resource` — borrowable | — |
| `Journal` | Inherits from `Resource` — borrowable | — |
| `Conference` | Inherits from `Resource` — reference only, not borrowable | — |
| `Loan` | Associates one `Resource` with one `Person` | — |
| `ResourceList` | Owns and manages all `Resource` objects | — |
| `UserList` | Owns and manages all `Person` objects | — |
| `LibrarySystem` | Top-level controller — orchestrates all operations | — |
| `Display` | Static helper — owns all terminal rendering and ANSI styling | — |

---

## Project Structure

```
library_sys/
├── docs/
│   ├── A2ResourceList.txt      # Resource data file
│   └── A2UserList.txt          # User data file
├── include/
│   ├── Logic/
│   │   ├── LibrarySystem.h
│   │   ├── Loan.h
│   │   ├── ResourceList.h
│   │   └── UserList.h
│   ├── Resources/
│   │   ├── Book.h
│   │   ├── Conference.h
│   │   ├── Journal.h
│   │   └── Resource.h
│   ├── Users/
│   │   ├── LibStaff.h
│   │   ├── Person.h
│   │   ├── Staff.h
│   │   └── Student.h
│   └── Display.h
├── src/
│   ├── Logic/
│   │   ├── LibrarySystem.cpp
│   │   ├── Loan.cpp
│   │   ├── ResourceList.cpp
│   │   └── UserList.cpp
│   ├── Display.cpp
│   ├── main.cpp
│   ├── Person.cpp
│   └── Resource.cpp
├── CMakeLists.txt
└── README.md
```

---

## Building the Project

This project uses **CMake** and targets **C++20**.

### Prerequisites
- CMake 4.1+
- A C++20-compatible compiler (GCC 10+, Clang 12+, or MSVC 2019+)
- CLion (recommended) or any IDE with CMake support

### Build Steps

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Or open the project in CLion and use the built-in build and run configurations.

---

## Usage

Run the compiled executable from the project root so the relative paths to the data files resolve correctly:

```bash
./library_sys
```

On launch, resources and users are loaded automatically. A styled menu is then presented — all operations are accessed by entering the corresponding number.

```
────────────────────────────────────────────────────────
  MENU
────────────────────────────────────────────────────────
  1  Borrow a resource
  2  Return a resource
  3  List available
  4  Loan report
  5  User report
  6  Search resources
  7  Activity log
  0  Exit
────────────────────────────────────────────────────────
```

### Borrowing Rules

| User Type | Max Resources |
|---|---|
| Student | 1 |
| Staff | 2 |
| Library Staff | 0 |

- Each `Book` or `Journal` can only be on loan to one user at a time.
- `Conference` resources cannot be borrowed.

### Sorting (options 3 and 4)

When listing available resources or viewing the loan report, you will be asked for:
- **Order**: `a` for ascending (A → Z), `d` for descending (Z → A)
- **Field**: `t` to sort by title, `a` to sort by author

### Saving the user report (option 5)

After the report is printed, you will be asked whether to save it to `user_report.txt` in the working directory.

### Search (option 6)

Enter any keyword to search across all resource titles, book authors, and conference acronyms. Results are printed in alphabetical order by title. Resources currently on loan are tagged `(on loan)`.

### Activity log (option 7)

Displays a timestamped record of every borrow and return event that has occurred in the current session, in the order they happened.

---

## Input File Format

### `docs/A2ResourceList.txt`

Sections are delimited by `#####` lines. Each section contains one resource type:

| Section | Format (lines per entry) |
|---|---|
| Books | `Author Surname, First name` / `Title` / `Year` |
| Journals | `Title` / `Volume line 1` / `Volume line 2` |
| Conferences | `Full conference title` / `ACRONYM` (one per year, repeated) |

### `docs/A2UserList.txt`

One user per line. The first character is the type code; the remainder is the display name:

| Code | Type |
|---|---|
| `1` | Student |
| `2` | Staff |
| `3` | Library Staff |

---

## Requirements

- C++20
- CMake 4.1+
- CLion (recommended IDE)