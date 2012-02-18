add_definitions(
	-Dlinux=1
	-std=c++0x
	-DPACKAGE_NAME="${PACKAGE_NAME}"
	-DPACKAGE_VERSION="${PACKAGE_VERSION}"
	-DPACKAGE_HOMEPAGE_URL="${PACKAGE_HOMEPAGE_URL}"
	-DVERSION="${PACKAGE_VERSION}")

add_executable(fastpurge fastpurge.cpp BaseAdapter.cpp RedisPurger.cpp)
target_link_libraries(fastpurge ${EV_LIBRARIES})
install(TARGETS fastpurge RUNTIME DESTINATION bin)
