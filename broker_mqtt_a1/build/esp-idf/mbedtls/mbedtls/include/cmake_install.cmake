# Install script for directory: /l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/l/disk0/josemar/.espressif/tools/xtensa-esp-elf/esp-15.2.0_20251204/xtensa-esp-elf/bin/xtensa-esp32-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

