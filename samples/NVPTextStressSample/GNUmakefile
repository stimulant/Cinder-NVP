#!gmake 

.PHONY: debug release debuConfig releaseConfig clean cleanDebug cleanRelease all

BUILD ?= release
CMAKE ?= cmake
OUTPUT_ROOT_DIR ?= linux
DEBUG_DIR ?= $(PWD)/$(OUTPUT_ROOT_DIR)/debug
RELEASE_DIR ?= $(PWD)/$(OUTPUT_ROOT_DIR)/release
BIN_DIR ?= $(PWD)/$(OUTPUT_ROOT_DIR)/bin

default: $(BUILD)

.DEFAULT:
	@$(MAKE) -C $(BUILD) $(MAKECMDGOALS)

clobber:
	rm -rf $(DEBUG_DIR) $(RELEASE_DIR) $(BIN_DIR)

clean:
	@$(MAKE) -C $(DEBUG_DIR) clean
	@$(MAKE) -C $(RELEASE_DIR) clean

cleanDebug:
	@$(MAKE) -C $(DEBUG_DIR) clean

cleanRelease:
	@$(MAKE) -C $(RELEASE_DIR) clean

all: debug release

debugConfig: 
	@mkdir -p $(DEBUG_DIR)
	@cd $(DEBUG_DIR); $(CMAKE) ../.. -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"

debug: debugConfig 
	@$(MAKE) -C $(DEBUG_DIR)

releaseConfig:
	@mkdir -p $(RELEASE_DIR)
	@cd $(RELEASE_DIR); $(CMAKE) ../.. -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles"

release: releaseConfig 
	@$(MAKE) -C $(RELEASE_DIR)



