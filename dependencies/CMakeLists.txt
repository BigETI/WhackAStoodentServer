################
#              #
# Dependencies #
#              #
################

include("cmake-conan/conan.cmake")

macro(conan_require_find_packages)
	# set(CONAN_DISABLE_CHECK_COMPILER TRUE)
	# conan_check(REQUIRED)
	conan_cmake_configure(REQUIRES ${ARGV} GENERATORS cmake_find_package)
endmacro()

##################
#                #
# Conan packages #
#                #
##################

conan_require_find_packages(
	"nlohmann_json/3.9.1"
)

#################
#               #
# Install conan #
#               #
#################

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE "."
	BUILD missing
	REMOTE conan-center
	SETTINGS ${settings}
)
