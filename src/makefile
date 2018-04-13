include ../conf.mk

OBJS=$(addprefix ${BUILD}/, $(addsuffix .o, utest_cgraph))
${BUILD}/utest_cgraph.x: ${OBJS}
check: ${BUILD}/utest_cgraph.x
	$<

clean: clean_all
	echo 
	echo $(call mod2obj, operation utest_operation)
