cmake_minimum_required(VERSION 4.1)
project(library_sys)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(src)

add_executable(library_sys src/main.cpp
        src/Person.cpp
        include/Person.h
        include/Student.h
        include/Staff.h
        include/LibStaff.h
        src/Resource.cpp
        include/Resource.h
        include/Book.h
        include/Journal.h
        include/Conference.h
        src/Loan.cpp
        include/Loan.h
)
