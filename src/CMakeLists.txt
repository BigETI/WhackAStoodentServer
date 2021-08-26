################
#              #
# Source files #
#              #
################

target_sources(${WHACK_A_STOODENT_SERVER_PROJECT} PRIVATE
	# Root
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
	
	# Exceptions
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/DeserializationFailedException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ENetInitializationFailedException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ENetPeerSendFailedException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/InvalidNetworkPortException.cpp"
	
	# Messages
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AcceptPlayRequestMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AcknowledgeAuthentificationMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AuthenticateMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/DenyAuthentificationMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/DenyPlayRequestMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/EndGameMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/ErrorMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/GetMatchHistoryMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HideMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitFailMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitSuccessMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LoadedGameMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LogMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LookMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/MatchHistoryMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PingMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PlayWithRandomMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PlayWithSessionCodeMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PongMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/RequestPlayMessage.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/ScoreMoleMessage.cpp"
	
	# Misc
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Bans.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Game.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Games.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Hole.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/MatchHistoryEntry.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Message.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Peer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Server.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/User.cpp"
	
	# Static
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/ENetInitializer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/IPUtilities.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/Program.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/SessionCodes.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/StringUtilities.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/UUIDs.cpp"
)
