
cmake_minimum_required(VERSION 3.5)
ADD_EXECUTABLE( clay_repo test_repo.cpp
    ../src/repository.cpp
    ../inc/repository.h
    )

ADD_TEST(clay_repo clay_repo)
target_link_libraries(clay_repo unity)
