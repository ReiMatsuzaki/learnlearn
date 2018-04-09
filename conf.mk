LEARNLEARN_ROOT=${HOME}/src/learnlearn
PROJ_ROOT=${LEARNLEARN_ROOT}

# -- basic --
CXX=gpp
CF=

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

# -- compile --
%.x:
	${CXX} ${CF} $^ -o $@
${BUILD}/%.o: ${SRC}/%.cpp
	@if [ ! -d ${BUILD} ]; \


