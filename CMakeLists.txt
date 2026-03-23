cmake_minimum_required(VERSION 4.1)
project(library_sys)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(src)
include_directories(docs)

add_executable(library_sys src/main.cpp
        src/Person.cpp
        include/Users/Person.h
        include/Users/Student.h
        include/Users/Staff.h
        include/Users/LibStaff.h
        src/Resource.cpp
        include/Resources/Resource.h
        include/Resources/Book.h
        include/Resources/Journal.h
        include/Resources/Conference.h
        src/Logic/Loan.cpp
        include/Logic/Loan.h
        src/Logic/ResourceList.cpp
        include/Logic/ResourceList.h
        src/Logic/UserList.cpp
        include/Logic/UserList.h
)
