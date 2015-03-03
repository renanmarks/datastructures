project(tree)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(./src/avl AVL_SRC_LIST)
aux_source_directory(./src/redblack RB_SRC_LIST)

add_library(avltree STATIC ${AVL_SRC_LIST})
add_library(redblack STATIC ${RB_SRC_LIST})
