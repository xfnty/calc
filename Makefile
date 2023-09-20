MAKEFLAGS=--no-print-directory --quiet

ifeq ($(shell echo "check_quotes"),"check_quotes")
   WINDOWS := yes
else
   WINDOWS := no
endif

ifeq ($(WINDOWS),yes)
	path = "$(subst /,\,$(1))"
	exec = "$(call path,$(1)).exe"
	mkdir = mkdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
	cp = -copy /y "$(1)" "$(2)"
	rm = $(wordlist 2,65535,$(foreach FILE,$(subst /,\,$(1)),& del $(FILE) > nul 2>&1)) || (exit 0)
	rmdir = rmdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
	cd = chdir "$(call path,$(1))"
	echo = echo $(1)
else
	path = "$(1)"
	exec = "./$(1)"
	mkdir = mkdir -p $(1)
	cp = -cp -Rf "$(1)" "$(2)" > /dev/null 2>&1 || true
	rm = rm $(1) > /dev/null 2>&1 || true
	rmdir = rmdir $(1) > /dev/null 2>&1 || true
	cd = cd "$(1)"
	echo = echo "$(1)"
endif

PROJECT_NAME:=calc
CMAKE_DIR:=.cmake
OUTPUT_DIR:=bin
EXE=$(PROJECT_NAME)
TEST_EXE:=tests
TEST_DIR=bin-tests

CONFIGURE:=configure c
BUILD:=build b
RUN:=run r
DEBUG:=debug d
TEST:=test t

args?=
build_type?=Debug

_CONFIGURE=cmake -B "$(CMAKE_DIR)" -S . -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_EXPORT_COMPILE_COMMANDS=1
_COPY_CCOMMANDS=-$(call cp,"$(CMAKE_DIR)/compile_commands.json","compile_commands.json")
_BUILD=cmake --build "$(CMAKE_DIR)" -j4

all: $(CMAKE_DIR) build run

$(CONFIGURE):
	echo ----- Configuring -----
	$(call mkdir,$(CMAKE_DIR))
	$(_CONFIGURE)
	$(_COPY_CCOMMANDS)

$(BUILD):
	echo ----- Building -----
	$(call mkdir,$(OUTPUT_DIR))
	-$(call cp,$(call path,"tests/assets/."),$(call path,"$(TEST_DIR)/."))
	$(_BUILD)

$(RUN):
	echo ----- Running -----
	cd "$(OUTPUT_DIR)" && "$(call exec,$(EXE))" $(args)

$(DEBUG): build
	echo ----- Debugging -----
	cd "$(OUTPUT_DIR)" && gdb -q --return-child-result --args "$(EXE)" $(args)

$(TEST): build
	echo ----- Testing -----
	-$(call cp,$(call path,"tests/assets/."),$(call path,"$(TEST_DIR)/."))
	cd "$(TEST_DIR)" && "$(call exec,$(TEST_EXE))" --skip-benchmarks --allow-running-no-tests -v high $(args)

$(CMAKE_DIR):
	echo ----- Configuring -----
	mkdir -p "$(CMAKE_DIR)"
	$(_CONFIGURE)
	$(_COPY_CCOMMANDS)

$(OUTPUT_DIR):
	mkdir -p "$(OUTPUT_DIR)"
	$(_BUILD)

clean:
	git clean -Xdfq
	rm -rf "$(CMAKE_DIR)"

.PHONY=$(CONFIGURE) $(BUILD) $(RUN) $(DEBUG) clean
