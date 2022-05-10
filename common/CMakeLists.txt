file(GLOB COMMON_SRC
     "*.cpp"
)

add_library(common STATIC ${COMMON_SRC})
