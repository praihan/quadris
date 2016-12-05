# CXX=clang++
CXX=g++-5
BUILD_DIR=build
EXEC=quadris

all:
	@mkdir -p ${BUILD_DIR}/
	@cmake -DCMAKE_CXX_COMPILER=${CXX} -B${BUILD_DIR}/ -H.
	@make -s -C ${BUILD_DIR}/
	@cp ${BUILD_DIR}/${EXEC} .

debug:
	@mkdir -p ${BUILD_DIR}/
	@cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=${CXX} -B${BUILD_DIR}/ -H.
	@make -s -C ${BUILD_DIR}/
	@cp ${BUILD_DIR}/${EXEC} .

release:
	@mkdir -p ${BUILD_DIR}
	@cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=${CXX} -B${BUILD_DIR}/ -H.
	@make -s -C ${BUILD_DIR}/
	@cp ${BUILD_DIR}/${EXEC} .

clean:
	@rm -rfv ${BUILD_DIR}/
	@rm -fv ${EXEC}
	@rm -rf ${EXEC}.dSYM/

.PHONY: all clean debug release
