LEARNLEARN_ROOT=${HOME}/src/learnlearn
PROJ_ROOT=${LEARNLEARN_ROOT}

include ${PROJ_ROOT}/local.mk


# -- Directories --
SRC=${PROJ_ROOT}/src
BUILD=${PROJ_ROOT}/build
EXTERNAL=${PROJ_ROOT}/external
GTESTDIR=${EXTERNAL}/googletest/googletest
VPATH=${BUILD}:${SRC}

# -- Options --
CXX=clang++
CF=-std=c++11 -I${EIGENDIR} -I${GTESTDIR} -I${GTESTDIR}/include

# -- files --
GTEST_HEADERS = $(GTESTDIR)/include/gtest/*.h \
                $(GTESTDIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTESTDIR)/src/*.cc $(GTESTDIR)/src/*.h $(GTEST_HEADERS)

# -- command --
clean_all:
	rm -f ${BUILD}/*.o
	rm -f ${BUILD}/*.x

check_%: ${BUILD}/utest_%
	$<

# -- utils --
od2obj = $(addprefix ${BUILD}/, $(addsuffix .o, $(1)))

# -- compile --
${BUILD}/%.x:
	@[ -d ${BUILD} ] || mkdir -p ${BUILD}
	${CXX} ${CF} $^ -o $@
${BUILD}/%.o: ${SRC}/%.cpp
	@[ -d ${BUILD} ] || mkdir -p ${BUILD}
	cd ${BUILD}; ${CXX} ${CF} -c $< -o $@
${BUILD}/gtest-all.o : ${GTEST_SRCS_}
	@[ -d ${BUILD} ] || mkdir -p ${BUILD}
	${CXX} ${CPPFLAGS} ${CF} -I${GTESTDIR}/include -c -o $@ ${GTESTDIR}/src/gtest-all.cc
${BUILD}/gtest_main.o : ${GTEST_SRCS_}
	@[ -d ${BUILD} ] || mkdir -p ${BUILD}
	${CXX} ${CPPFLAGS} ${CF} -I${GTESTDIR}/include -c -o $@ ${GTESTDIR}/src/gtest_main.cc
${BUILD}/gtest_main.a : ${BUILD}/gtest_main.o ${BUILD}/gtest-all.o
	@[ -d ${BUILD} ] || mkdir -p ${BUILD}
	${AR} ${ARFLAGS} $@ $^
