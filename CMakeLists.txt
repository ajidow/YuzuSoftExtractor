#1.cmake version
cmake_minimum_required(VERSION 3.18.3)


#2.project name
project(YuzuSoftExtractor)


#3.head file path
INCLUDE_DIRECTORIES(include)


#4.source file path
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set enironment variable
SET(YuzuSoftExtractor ${DIR_SRCS})

#6.add executable file
ADD_EXECUTABLE(${PROJECT_NAME} ${YuzuSoftExtractor})

#7.add link library(.so files)
