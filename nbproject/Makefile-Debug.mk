#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/framework/Camera.o \
	${OBJECTDIR}/framework/Chunk.o \
	${OBJECTDIR}/framework/Mesher.o \
	${OBJECTDIR}/framework/Volume.o \
	${OBJECTDIR}/framework/World.o \
	${OBJECTDIR}/framework/opengl/GLProgram.o \
	${OBJECTDIR}/framework/opengl/Shader.o \
	${OBJECTDIR}/framework/terrain/PerlinTerrainGenerator.o \
	${OBJECTDIR}/framework/terrain/TerrainGenerator.o \
	${OBJECTDIR}/framework/terrain/noiseutils.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/util.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/lib/libSDL2.so /usr/lib/libGLEW.so /usr/lib/libGL.so /usr/lib/libGLU.so -lnoise

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer: /usr/lib/libSDL2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer: /usr/lib/libGLEW.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer: /usr/lib/libGL.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer: /usr/lib/libGLU.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/framework/Camera.o: framework/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/Camera.o framework/Camera.cpp

${OBJECTDIR}/framework/Chunk.o: framework/Chunk.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/Chunk.o framework/Chunk.cpp

${OBJECTDIR}/framework/Mesher.o: framework/Mesher.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/Mesher.o framework/Mesher.cpp

${OBJECTDIR}/framework/Volume.o: framework/Volume.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/Volume.o framework/Volume.cpp

${OBJECTDIR}/framework/World.o: framework/World.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/World.o framework/World.cpp

${OBJECTDIR}/framework/opengl/GLProgram.o: framework/opengl/GLProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/opengl/GLProgram.o framework/opengl/GLProgram.cpp

${OBJECTDIR}/framework/opengl/Shader.o: framework/opengl/Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework/opengl
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/opengl/Shader.o framework/opengl/Shader.cpp

${OBJECTDIR}/framework/terrain/PerlinTerrainGenerator.o: framework/terrain/PerlinTerrainGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework/terrain
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/terrain/PerlinTerrainGenerator.o framework/terrain/PerlinTerrainGenerator.cpp

${OBJECTDIR}/framework/terrain/TerrainGenerator.o: framework/terrain/TerrainGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework/terrain
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/terrain/TerrainGenerator.o framework/terrain/TerrainGenerator.cpp

${OBJECTDIR}/framework/terrain/noiseutils.o: framework/terrain/noiseutils.cpp 
	${MKDIR} -p ${OBJECTDIR}/framework/terrain
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framework/terrain/noiseutils.o framework/terrain/noiseutils.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/util.o: util.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SDL2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util.o util.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/salamancer

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
