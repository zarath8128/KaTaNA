			ALL 		?= 
			EXEC		?= ${ALL}
			OBJ			?= ${ALL}
			SRC			?= ${CSRS} ${CXXSRC}
			CSRC		?= ${shell find . -name '*.c'}
			CXXSRC		?= ${shell find . -name '*.cpp'}
			HEADER		?= 
			INCPATH     ?= .
override	FLAGS		+= -Wall -Wextra -mtune=native -march=native -fdiagnostics-color=auto ${addprefix -I, ${INCPATH}}${OPTIMIZE_FLAGS} 
override 	CFLAGS		+= -std=c99 ${FLAGS}
override	CXXFLAGS	+= -std=c++1y ${FLAGS}
override	LDFLAGS		+= ${OPTIMIZE_FLAGS} ${FLAGS}
			LDLIBS		?=
			CC			=  ${CXX}

			TIME		?= /usr/bin/time
define		SH_TIME_PROFILE
	@${TIME} -v ./$< 2>> $@
endef
define		CSH_TIME_PROFILE
	@${TIME} -v ./$< >>& $@
endef
			GPROF		?= gprof

.PHONY	 		: all release debug profile full

all				: ${ALL}
full			:
	@${MAKE} profile
	@${MAKE} optimize
	@${MAKE} all

clean			: 
	-rm -f ${ALL} ${EXEC} ${OBJ} *.profile *.optimized *.depend *.o gmon.out

release			: FLAGS += -DNDEBUG
release			: all

debug			: FLAGS += -g
debug			: all

profile			: ${addsuffix .profile, ${EXEC}}
%.profile		: %.for_profile
	@echo "collecting verbose profile"
	@echo "\nGNU time profiler:\n" > $@
ifeq (${notdir ${SHELL}},sh)
	${SH_TIME_PROFILE}
else ifeq (${notdir ${SHELL}},bash)
	${SH_TIME_PROFILE}
else
	${CSH_TIME_PROFILE}
endif
	@echo "\n" >> $@
	@${GPROF} $< >> $@
	@rm -f gmon.out
	@echo "done..."
%.for_profile	: FLAGS += -pg
%.for_profile	: %
	@mv $^ $@

optimize		: ${addsuffix .optimized, ${EXEC}}
%.optimized 	: OPTIMIZE_FLAGS = -fprofile-use
%.optimized		: %.for_optimized
	@${MAKE} FLAGS="-fprofile-use ${FLAGS}"
	@mv $* $@
	@rm -f $*.gcda

%.for_optimized	: OPTIMIZE_FLAGS = -fprofile-generate -static
%.for_optimized	: %
	@echo "collecting optimize profile"
	@./$^
	@cp $< $@

%.c.depend:%.c
	@${CC} ${CFLAGS} -MM $^ | sed -e "s/\($..*\)\.o[ :]*/\1.o $@ : /g" > $@
%.cpp.depend:%.cpp
	@${CXX} ${CXXFLAGS} -MM $^ | sed -e "s/\($..*\)\.o[ :]*/\1.o $@ : /g" > $@

ifneq (${CSRC}, )
-include ${notdir ${CSRC}}.depend
endif

ifneq (${CXXSRC}, )
-include ${notdir ${CXXSRC}}.depend
endif
