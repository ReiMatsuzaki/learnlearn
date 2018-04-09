include ../conf.mk

OBJS=$(addprefix ${BUILD}/, $(addsuffix .o, operation utest_operation))
${BUILD}/utest_operation.x: ${OBJS}
check: ${BUILD}/utest_operation.x
	$<

clean: clean_all
	echo 
	echo $(call mod2obj, operation utest_operation)
