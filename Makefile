CXX=g++-5
BUILD_DIR=build/
EXEC=quadris

all:
	@mkdir -p ${BUILD_DIR}
	@cmake -DCMAKE_CXX_COMPILER=${CXX} -B${BUILD_DIR} -H.
	@make -C ${BUILD_DIR}
	@cp ${BUILD_DIR}/${EXEC} .

debug:
	@mkdir -p ${BUILD_DIR}
	@cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=${CXX} -B${BUILD_DIR} -H.
	@make -C ${BUILD_DIR}
	@cp ${BUILD_DIR}/${EXEC} .

clean:
	@rm -rf ${BUILD_DIR}
	@rm -f ${EXEC}

.PHONY: all clean debug