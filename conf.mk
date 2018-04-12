LEARNLEARN_ROOT=${HOME}/src/learnlearn
PROJ_ROOT=${LEARNLEARN_ROOT}

include ${PROJ_ROOT}/local.mk

# -- basic --
CXX=clang++
CF=-std=c++11 -I${EIGENDIR}

# -- Directories --
SRC=${PROJ_ROOT}/src
BUILD=${PROJ_ROOT}/build
EXTERNAL=${PROJ_ROOT}/external
VPATH=${BUILD}:${SRC}

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
	${CXX} ${CF} $^ -o $@
${BUILD}/%.o: ${SRC}/%.cpp
	@if [ ! -d ${BUILD} ]; \
	   then mkdir -p ${BUILD}; \
	fi
	cd ${BUILD}; ${CXX} ${CF} -c $< -o $@


