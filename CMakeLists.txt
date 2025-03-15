cmake_minimum_required(VERSION 3.28)
project(cub3d_own_tests C)

set(CMAKE_C_STANDARD 99)

# Paths for libft and MiniLibX
set(LIBFT_DIR "${CMAKE_SOURCE_DIR}/lib/libft")
set(MLX_DIR "${CMAKE_SOURCE_DIR}/lib/minilibx")

# Define a custom target for libft
add_custom_command(
        OUTPUT ${LIBFT_DIR}/libft.a
        COMMAND make -C ${LIBFT_DIR}
        COMMENT "Building libft.a..."
        WORKING_DIRECTORY ${LIBFT_DIR}
)

add_custom_target(build_libft ALL DEPENDS ${LIBFT_DIR}/libft.a)

# Define a custom target for MiniLibX
add_custom_command(
        OUTPUT ${MLX_DIR}/libmlx_Linux.a
        COMMAND make -C ${MLX_DIR}
        COMMENT "Building libmlx.a..."
        WORKING_DIRECTORY ${MLX_DIR}
)

add_custom_target(build_minilibx ALL DEPENDS ${MLX_DIR}/libmlx_Linux.a)

# Add the main executable
add_executable(cub3d_own_tests unused/main.c
        unused/player.c)

# Ensure the executable depends on both libft and MiniLibX
add_dependencies(cub3d_own_tests build_libft build_minilibx)

# Link both libraries to the executable
target_link_libraries(cub3d_own_tests PRIVATE
        ${LIBFT_DIR}/libft.a
        ${MLX_DIR}/libmlx_Linux.a
        -lX11 -lXext m
)

# Add the second executable: mlx_test
add_executable(mlx_test unused/test_minilibx.c)

# Ensure mlx_test depends on MiniLibX (and libft if needed)
add_dependencies(mlx_test build_minilibx build_libft)

# Link libraries to mlx
target_link_libraries(mlx_test PRIVATE
        ${MLX_DIR}/libmlx_Linux.a
        ${LIBFT_DIR}/libft.a
        -lX11 -lXext m
)
# Add the third executable: parser_only_test
add_executable(parser_test
        test_srcs/parser_test.c
        test_srcs/parser_utils.c
        test_srcs/parser_map_validation.c
        test_srcs/fd_utils.c
        test_srcs/parser_map_utils.c
        test_srcs/parser_color.c
        test_srcs/print_utils.c)

# Ensure libft_only_test depends only on libft
add_dependencies(parser_test build_libft)

# Link only libft to libft_only_test
target_link_libraries(parser_test PRIVATE
${LIBFT_DIR}/libft.a
)