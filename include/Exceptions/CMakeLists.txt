target_sources(${WHACK_A_STOODENT_SERVER_PROJECT} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/DeserializationFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/ENetInitializationFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/ENetPeerSendFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/InvalidNetworkPortException.hpp"
)
