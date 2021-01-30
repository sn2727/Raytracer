cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    rt/primmod/bmap.cpp
    rt/primmod/bmap.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_bump.cpp
)

file(COPY
    models/stones_bump.png
    models/stones_spec.png
    models/birdtex.png
    models/deertex.png
    models/fBird.mtl
    models/fBird.obj
    models/fDeer.mtl
    models/fDeer.obj
    models/fWoods.mtl
    models/fWoods.obj
    models/greenblacktex.png
    models/ground.mtl
    models/ground.obj
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
