#To be tested 11/10/2018 LCPT
SET(CPACK_GENERATOR "DEB")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_NAME "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
INCLUDE(${xc_utils_DIR}/CMake/debian_package_params.txt)

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++ (>=4.3), libgcc1 (>=1:4.3), libc6 (>=2.7), libvtk5 (>=5.0), libcgal2 (>=3.3), libplot2c2 (>=2.5), libmpfr1ldbl  (>=2.3), libgmp3c2 (>=4.2), libboost-regex1.34.1 (>=1.34), libmysql++3 (>=3.0), libsqlite3-0 (>=3.5), libxt6  (>=1.0), libsm6  (>=1.0), libxext6  (>=1.0), libice6  (>=1.0), libxft2  (>=2.1)")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Function library for XC and other programs.")

 
INCLUDE(CPack)
#execute fakeroot make package
