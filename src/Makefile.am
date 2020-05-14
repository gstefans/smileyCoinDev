AM_CPPFLAGS = $(INCLUDES)
AM_LDFLAGS = $(PTHREAD_CFLAGS)
AM_CFLAGS = -fPIC -msse2

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
		@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
			CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
				OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

BITCOIN_INCLUDES= -I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) -msse2

noinst_LIBRARIES = \
  libbitcoin_server.a \
  libbitcoin_common.a \
  libbitcoin_cli.a
if ENABLE_WALLET
BITCOIN_INCLUDES += $(BDB_CPPFLAGS)
noinst_LIBRARIES += libbitcoin_wallet.a
endif

bin_PROGRAMS =
sbin_PROGRAMS =
TESTS =

if BUILD_BITCOIND
  sbin_PROGRAMS += smileycoind
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += smileycoin-cli
endif


.PHONY: FORCE
# bitcoin core #
BITCOIN_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
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
  crypter.h \
	crypto/sha2.h \
	crypto/sha1.h \
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
  wallet.h \
  scrypt.h \
  sph_blake.h \
  sph_groestl.h \
  sph_keccak.h \
  sph_bmw.h \
  sph_jh.h \
  sph_skein.h \
  sph_types.h \
  sph_echo.h \
  sph_luffa.h \
  sph_simd.h \
  sph_cubehash.h \
  sph_shavite.h \
  hashgroestl.h \
  hashskein.h \
  hashqubit.h

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
	@$(top_srcdir)/misc/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbitcoin_common_a-version.$(OBJEXT): obj/build.h

libbitcoin_server_a_CPPFLAGS = $(BITCOIN_INCLUDES)
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

libbitcoin_wallet_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpc/dump.cpp \
  rpc/wallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(BITCOIN_CORE_H)

libbitcoin_common_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_common_a_SOURCES = \
  base58.cpp \
  allocators.cpp \
  chainparams.cpp \
  core.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpc/protocol.cpp \
  script.cpp \
	crypto/sha2.cpp \
	crypto/sha1.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  scrypt.cpp \
  scrypt-sse2.cpp \
  blake.c \
  bmw.c \
  groestl.c \
  jh.c \
  keccak.c \
  skein.c \
  aes_helper.c \
  echo.c \
  luffa.c \
  simd.c \
  cubehash.c \
  shavite.c \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoin_common_a_SOURCES += compat/glibc_compat.cpp
libbitcoin_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

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
  $(LIBMEMENV)
if ENABLE_WALLET
smileycoind_LDADD += libbitcoin_wallet.a
endif
smileycoind_SOURCES = bitcoind.cpp
#

if TARGET_WINDOWS
smileycoind_SOURCES += bitcoind-res.rc
endif

smileycoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS)
smileycoind_CPPFLAGS = $(BITCOIN_INCLUDES)

# bitcoin-cli binary #
smileycoin_cli_LDADD = \
  libbitcoin_cli.a \
  libbitcoin_common.a \
  $(BOOST_LIBS)
smileycoin_cli_SOURCES = bitcoin-cli.cpp
smileycoin_cli_CPPFLAGS = $(BITCOIN_INCLUDES)
#

if TARGET_WINDOWS
smileycoin_cli_SOURCES += bitcoin-cli-res.rc
endif

CLEANFILES = *.gcda *.gcno
CLEANFILES += leveldb/libleveldb.a leveldb/libmemenv.a

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno

.rc.o:
			@test -f $(WINDRES)
		  $(AM_V_GEN) $(WINDRES) -i $< -o $@

.mm.o:
			$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
				$(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
			@test -f $(PROTOC)
			$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

LIBBITCOIN_SERVER=libbitcoin_server.a
LIBBITCOIN_WALLET=libbitcoin_wallet.a
LIBBITCOIN_COMMON=libbitcoin_common.a
LIBBITCOIN_CLI=libbitcoin_cli.a
LIBBITCOINQT=qt/libbitcoinqt.a

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
