# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x64)
  MatrixMul_config = debug_x64
endif
ifeq ($(config),release_x64)
  MatrixMul_config = release_x64
endif

PROJECTS := MatrixMul

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

MatrixMul:
ifneq (,$(MatrixMul_config))
	@echo "==== Building MatrixMul ($(MatrixMul_config)) ===="
	@${MAKE} --no-print-directory -C . -f MatrixMul.make config=$(MatrixMul_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f MatrixMul.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x64"
	@echo "  release_x64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   MatrixMul"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"