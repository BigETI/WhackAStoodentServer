################
#              #
# Source files #
#              #
################

target_sources(${WHACK_A_STOODENT_SERVER_PROJECT} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_subdirectory("Exceptions")
add_subdirectory("Messages")
add_subdirectory("Misc")
add_subdirectory("Static")
