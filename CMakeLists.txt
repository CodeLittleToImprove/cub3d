cmake_minimum_required(VERSION 3.28)
project(cub3d_own_tests C)

set(CMAKE_C_STANDARD 99)

# Add the libft library
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libft/libft.a)

# Add the mlx_linux library
add_library(mlx_linux STATIC IMPORTED)
set_target_properties(mlx_linux PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/minilibx/libmlx_Linux.a)

add_executable(cub3d_own_tests srcs/main.c
        )

# Link the executable with the libft, mlx_linux, X11, and Xext libraries
target_link_libraries(cub3d_own_tests PRIVATE libft mlx_linux -lX11 -lXext m)

# Second executable (mlx_only_exec)
add_executable(mlx_test
        srcs/test_minilibx.c
)

# Link the second executable with mlx_linux and X11 libraries
target_link_libraries(mlx_test PRIVATE libft mlx_linux -lX11 -lXext m)