cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    rt/groups/bvh.cpp
    rt/groups/Node.cpp
    rt/groups/Node.h
)

set(ASSIGNMENT_SOURCES
    rt/groups/Node.h
    rt/groups/Node.cpp
    rt/groups/bvh.h
    rt/groups/kdtree.h
    rt/loaders/obj.cpp
    rt/loaders/obj.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_indexing.cpp
)

file(COPY
    models/cow.obj
    models/cow.mtl
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
