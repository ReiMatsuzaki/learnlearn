include ../conf.mk

${BUILD}/utest_cgraph.o: ${SRC}/utest_cgraph.cpp ${SRC}/cgraph.hpp

OBJS=$(addprefix ${BUILD}/, $(addsuffix .o, utest_cgraph))
${BUILD}/utest_cgraph.x: ${OBJS} ${BUILD}/gtest_main.a
check: ${BUILD}/utest_cgraph.x
	$<

clean: clean_all
	echo 
	echo $(call mod2obj, operation utest_operation)
