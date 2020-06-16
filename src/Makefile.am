# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(INCLUDES) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_INCLUDES=-I$(builddir) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

EXTRA_LIBRARIES += \
	libbitcoin_server.a \
	libbitcoin_common.a \
	libbitcoin_cli.a
if ENABLE_WALLET
BITCOIN_INCLUDES += $(BDB_CPPFLAGS)
BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)
EXTRA_LIBRARIES += libbitcoin_wallet.a
endif

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =

if BUILD_BITCOIND
  bin_PROGRAMS += smileycoind
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += smileycoin-cli
endif
#if BUILD_BITCOIN_TX
bin_PROGRAMS += smileycoin-tx
#endif


.PHONY: FORCE check-symbols check-security
# bitcoin core #
BITCOIN_CORE_H = 	\
	addrman.h \
	alert.h \
	base58.h bignum.h \
	bloom.h \
	chainparams.h \
	checkpoints.h \
	checkqueue.h \
	version.h \
	coincontrol.h \
	coins.h \
	compat.h \
	core.h \
  core_io.h \
	crypter.h \
	crypto/sha2.h \
	crypto/sha1.h \
  crypto/ripemd160.h \
	crypto/scrypt.h \
	crypto/sph_blake.h \
	crypto/sph_groestl.h \
	crypto/sph_keccak.h \
	crypto/sph_bmw.h \
	crypto/sph_jh.h \
	crypto/sph_skein.h \
	crypto/sph_types.h \
	crypto/sph_echo.h \
	crypto/sph_luffa.h \
	crypto/sph_simd.h \
	crypto/sph_cubehash.h \
	crypto/sph_shavite.h \
	crypto/hashgroestl.h \
	crypto/hashskein.h \
	crypto/hashqubit.h \
	db.h \
	richlistdb.h \
	hash.h \
	init.h \
	key.h \
	keystore.h \
	leveldbwrapper.h \
	limitedmap.h \
	main.h \
	miner.h \
	mruset.h \
	netbase.h \
	net.h \
	noui.h \
	protocol.h \
	rpc/client.h \
	rpc/protocol.h \
	rpc/server.h \
	script.h \
	serialize.h \
	support/allocators/secure.h \
	support/allocators/zeroafterfree.h \
	support/cleanse.h \
	support/pagelocker.h \
	sync.h \
	threadsafety.h \
	tinyformat.h \
	txdb.h \
	txmempool.h \
	ui_interface.h \
	uint256.h \
	util.h \
	version.h \
	walletdb.h \
	wallet.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbitcoin_common_a-version.$(OBJEXT): obj/build.h

libbitcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) 
libbitcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) 
libbitcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  coins.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  richlistdb.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

libbitcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpc/dump.cpp \
  rpc/wallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(BITCOIN_CORE_H)

libbitcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_common_a_SOURCES = \
  base58.cpp \
  chainparams.cpp \
  core.cpp \
  core_read.cpp \
  core_write.cpp \
  crypto/aes_helper.c \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/cubehash.c \
  crypto/echo.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/luffa.c \
  crypto/ripemd160.cpp \
  crypto/scrypt-sse2.cpp \
  crypto/scrypt.cpp \
  crypto/sha1.cpp \
  crypto/sha2.cpp \
  crypto/shavite.c \
  crypto/simd.c \
  crypto/skein.c \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpc/protocol.cpp \
  script.cpp \
  support/cleanse.cpp \
  support/pagelocker.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoin_common_a_SOURCES += compat/glibc_compat.cpp
libbitcoin_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libbitcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libbitcoin_common_a_SOURCES = $(srcdir)/obj/build.h
#

# bitcoind binary #
smileycoind_LDADD = \
  libbitcoin_server.a \
  libbitcoin_common.a \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBUNIVALUE)
if ENABLE_WALLET
smileycoind_LDADD += libbitcoin_wallet.a
endif
smileycoind_SOURCES = bitcoind.cpp
#

if TARGET_WINDOWS
smileycoind_SOURCES += bitcoind-res.rc
endif

smileycoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS)
smileycoind_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
smileycoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

# bitcoin-cli binary #
smileycoin_cli_LDADD = \
  libbitcoin_cli.a \
  libbitcoin_common.a \
	$(LIBUNIVALUE) \
  $(BOOST_LIBS)

smileycoin_cli_SOURCES = bitcoin-cli.cpp
smileycoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
smileycoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
#

# bitcoin-tx binary #
smileycoin_tx_LDADD = \
  libbitcoin_common.a \
  $(LIBUNIVALUE) \
  $(BOOST_LIBS)
smileycoin_tx_SOURCES = bitcoin-tx.cpp
smileycoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
smileycoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
#

if TARGET_WINDOWS
smileycoin_cli_SOURCES += bitcoin-cli-res.rc
endif

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = 

clean-local:
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
			@test -f $(WINDRES)
		  $(AM_V_GEN) $(WINDRES) -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif


%.pb.cc %.pb.h: %.proto
			@test -f $(PROTOC)
			$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

LIBBITCOIN_SERVER=libbitcoin_server.a
LIBBITCOIN_WALLET=libbitcoin_wallet.a
LIBBITCOIN_COMMON=libbitcoin_common.a
LIBBITCOIN_CLI=libbitcoin_cli.a
LIBBITCOINQT=qt/libbitcoinqt.a

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
