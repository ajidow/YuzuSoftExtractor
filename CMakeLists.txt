#1.cmake version
cmake_minimum_required(VERSION 2.6)

#2.project name
project(YuzuSoftExtractor)


#3.head file path
INCLUDE_DIRECTORIES(include)



#4.source file path
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set enironment variable
SET(YuzuSoftExtractor ${DIR_SRCS})

#you probably need to change the sentense below by yourself
SET(OpenCV_DIR D:/mainProjects/tools/opencv/build)
FIND_PACKAGE(OpenCV REQUIRED)

#6.add executable file
ADD_EXECUTABLE(${PROJECT_NAME} ${YuzuSoftExtractor})

#7.add link library(.so files)
target_link_libraries(YuzuSoftExtractor ${OpenCV_LIBS})