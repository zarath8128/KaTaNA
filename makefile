			ALL 		?= test
			EXEC		?= ${ALL}
			OBJ			?= ${ALL}
			SRC			?= ${CSRS} ${CXXSRC}
			CSRC		?= ${shell find . -name '*.c'}
			CXXSRC		?= ${shell find . -name '*.cpp'}
			HEADER		?= ${shell find . -name '*.h'} 
			DEPENDS		 = ${CSRC} ${CXXSRC}
override	FLAGS		+= -Wall -Wextra -mtune=native -march=native -fdiagnostics-color=auto ${OPTIMIZE_FLAGS}
override 	CFLAGS		+= -std=c99 ${FLAGS}
override	CXXFLAGS	+= -std=c++1y ${FLAGS}
override	LDFLAGS		+= ${OPTIMIZE_FLAGS} ${FLAGS}
override	LDLIBS		+= -lstdc++
			CC			 = gcc
			CXX			 = g++

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
	@${MAKE} clean
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
	@echo "exec $@ for profiling."
	@./$@

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
#%.h.depend:%.h
#	@${CXX} ${CXXFLAGS} -MM $^ | sed -e "s/\($..*\)\.o[ :]*/\1.o $@ : /g" > $@

ifneq (${DEPENDS}, )
-include ${addsuffix .depend, ${notdir ${DEPENDS}}}
endif
