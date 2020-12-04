cmake_minimum_required(VERSION 3.5)

project(thread_stuff LANGUAGES C)

add_executable(thread_stuff thread.c thread.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(thread_stuff PRIVATE Threads::Threads)
