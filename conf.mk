LEARNLEARN_ROOT=${HOME}/src/learnlearn
PROJ_ROOT=${LEARNLEARN_ROOT}

# -- basic --
CXX=clang++
CF=-std=c++11

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
	cd ${BUILD}; ${CXX} ${CF} -c $< -o $@


