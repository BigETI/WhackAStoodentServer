#################
#               #
# Include files #
#               #
#################

target_sources(${WHACK_A_STOODENT_SERVER_PROJECT} PRIVATE
	# Abstract
	"${CMAKE_CURRENT_SOURCE_DIR}/Abstract/ASerializableMessage.hpp"
	
	# Enumerators
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/EDenyPlayRequestReason.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/EDisconnectionReason.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/EErrorType.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/ELogLevel.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/ELookHole.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/EMessageType.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Enumerators/EPlayerRole.hpp"
	
	# Exceptions
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/DeserializationFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ENetInitializationFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ENetPeerSendFailedException.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/InvalidNetworkPortException.hpp"
	
	# Interfaces
	"${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IMessageParser.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/ISerializable.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/ISerializableMessage.hpp"
	
	# Messages
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AcceptPlayRequestMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AcknowledgeAuthentificationMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/AuthenticateMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/DenyAuthentificationMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/DenyPlayRequestMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/EndGameMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/ErrorMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/GetMatchHistoryMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HideMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitFailMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/HitSuccessMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LoadedGameMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LogMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/LookMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/MatchHistoryMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PingMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PlayWithRandomMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PlayWithSessionCodeMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/PongMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/RequestPlayMessage.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Messages/ScoreMoleMessage.hpp"
	
	# Misc
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Event.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Game.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Games.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/MatchHistoryEntry.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Message.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/MessageParser.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Peer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Server.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/User.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Vector2D.hpp"
	
	# Static
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/CollectionSerializer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/Defaults.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/ENetInitializer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/IPUtilities.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/Main.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/NumericCollectionSerializer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/NumericSerializer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/Rules.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/SessionCodes.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/StringSerializer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/StringUtilities.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Static/UUIDs.hpp"
)
