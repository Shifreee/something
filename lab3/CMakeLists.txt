cmake_minimum_required(VERSION 3.5)
project(TableLib)
add_library(TableLib table.c myinput.c)
set_target_properties(TableLib PROPERTIES LINKER_LANGUAGE C)