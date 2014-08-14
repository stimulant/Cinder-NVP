#pragma once

#include "NVPInit.h"

PFNGLGENPATHSNVPROC FUNC(glGenPathsNV) = NULL;
PFNGLDELETEPATHSNVPROC FUNC(glDeletePathsNV) = NULL;
PFNGLISPATHNVPROC FUNC(glIsPathNV) = NULL;
PFNGLPATHCOMMANDSNVPROC FUNC(glPathCommandsNV) = NULL;
PFNGLPATHCOORDSNVPROC FUNC(glPathCoordsNV) = NULL;
PFNGLPATHSUBCOMMANDSNVPROC FUNC(glPathSubCommandsNV) = NULL;
PFNGLPATHSUBCOORDSNVPROC FUNC(glPathSubCoordsNV) = NULL;
PFNGLPATHSTRINGNVPROC FUNC(glPathStringNV) = NULL;
PFNGLPATHGLYPHSNVPROC FUNC(glPathGlyphsNV) = NULL;
PFNGLPATHGLYPHRANGENVPROC FUNC(glPathGlyphRangeNV) = NULL;
PFNGLWEIGHTPATHSNVPROC FUNC(glWeightPathsNV) = NULL;
PFNGLCOPYPATHNVPROC FUNC(glCopyPathNV) = NULL;
PFNGLINTERPOLATEPATHSNVPROC FUNC(glInterpolatePathsNV) = NULL;
PFNGLTRANSFORMPATHNVPROC FUNC(glTransformPathNV) = NULL;
PFNGLPATHPARAMETERIVNVPROC FUNC(glPathParameterivNV) = NULL;
PFNGLPATHPARAMETERINVPROC FUNC(glPathParameteriNV) = NULL;
PFNGLPATHPARAMETERFVNVPROC FUNC(glPathParameterfvNV) = NULL;
PFNGLPATHPARAMETERFNVPROC FUNC(glPathParameterfNV) = NULL;
PFNGLPATHDASHARRAYNVPROC FUNC(glPathDashArrayNV) = NULL;
PFNGLSTENCILFILLPATHNVPROC FUNC(glStencilFillPathNV) = NULL;
PFNGLPATHSTENCILDEPTHOFFSETNVPROC FUNC(glPathStencilDepthOffsetNV) = NULL;
PFNGLSTENCILSTROKEPATHNVPROC FUNC(glStencilStrokePathNV) = NULL;
PFNGLSTENCILFILLPATHINSTANCEDNVPROC FUNC(glStencilFillPathInstancedNV) = NULL;
PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC FUNC(glStencilStrokePathInstancedNV) = NULL;
PFNGLPATHCOVERDEPTHFUNCNVPROC FUNC(glPathCoverDepthFuncNV) = NULL;
PFNGLPATHCOLORGENNVPROC FUNC(glPathColorGenNV) = NULL;
PFNGLPATHTEXGENNVPROC FUNC(glPathTexGenNV) = NULL;
PFNGLPATHFOGGENNVPROC FUNC(glPathFogGenNV) = NULL;
PFNGLCOVERFILLPATHNVPROC FUNC(glCoverFillPathNV) = NULL;
PFNGLCOVERSTROKEPATHNVPROC FUNC(glCoverStrokePathNV) = NULL;
PFNGLCOVERFILLPATHINSTANCEDNVPROC FUNC(glCoverFillPathInstancedNV) = NULL;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC FUNC(glCoverStrokePathInstancedNV) = NULL;
PFNGLGETPATHPARAMETERIVNVPROC FUNC(glGetPathParameterivNV) = NULL;
PFNGLGETPATHPARAMETERFVNVPROC FUNC(glGetPathParameterfvNV) = NULL;
PFNGLGETPATHCOMMANDSNVPROC FUNC(glGetPathCommandsNV) = NULL;
PFNGLGETPATHCOORDSNVPROC FUNC(glGetPathCoordsNV) = NULL;
PFNGLGETPATHDASHARRAYNVPROC FUNC(glGetPathDashArrayNV) = NULL;
PFNGLGETPATHMETRICSNVPROC FUNC(glGetPathMetricsNV) = NULL;
PFNGLGETPATHMETRICRANGENVPROC FUNC(glGetPathMetricRangeNV) = NULL;
PFNGLGETPATHSPACINGNVPROC FUNC(glGetPathSpacingNV) = NULL;
PFNGLGETPATHCOLORGENIVNVPROC FUNC(glGetPathColorGenivNV) = NULL;
PFNGLGETPATHCOLORGENFVNVPROC FUNC(glGetPathColorGenfvNV) = NULL;
PFNGLGETPATHTEXGENIVNVPROC FUNC(glGetPathTexGenivNV) = NULL;
PFNGLGETPATHTEXGENFVNVPROC FUNC(glGetPathTexGenfvNV) = NULL;
PFNGLISPOINTINFILLPATHNVPROC FUNC(glIsPointInFillPathNV) = NULL;
PFNGLISPOINTINSTROKEPATHNVPROC FUNC(glIsPointInStrokePathNV) = NULL;
PFNGLGETPATHLENGTHNVPROC FUNC(glGetPathLengthNV) = NULL;
PFNGLPOINTALONGPATHNVPROC FUNC(glPointAlongPathNV) = NULL;
PFNGLPATHSTENCILFUNCNVPROC FUNC(glPathStencilFuncNV) = NULL;

# define GET_PROC_ADDRESS(name)  wglGetProcAddress(#name)

#define LOAD_PROC(type, name) \
  FUNC(name) = (type) GET_PROC_ADDRESS(name); \
  if (!FUNC(name)) { \
    fprintf(stderr, "%s: failed to GetProcAddress for %s\n", programName, #name); \
    exit(1); \
  }

int has_NV_path_rendering = 0;

void
initializeNVPR(const char *programName)
{
  
    LOAD_PROC(PFNGLGENPATHSNVPROC, glGenPathsNV);
    LOAD_PROC(PFNGLDELETEPATHSNVPROC, glDeletePathsNV);
    LOAD_PROC(PFNGLISPATHNVPROC, glIsPathNV);
    LOAD_PROC(PFNGLPATHCOMMANDSNVPROC, glPathCommandsNV);
    LOAD_PROC(PFNGLPATHCOORDSNVPROC, glPathCoordsNV);
    LOAD_PROC(PFNGLPATHSUBCOMMANDSNVPROC, glPathSubCommandsNV);
    LOAD_PROC(PFNGLPATHSUBCOORDSNVPROC, glPathSubCoordsNV);
    LOAD_PROC(PFNGLPATHSTRINGNVPROC, glPathStringNV);
    LOAD_PROC(PFNGLPATHGLYPHSNVPROC, glPathGlyphsNV);
    LOAD_PROC(PFNGLPATHGLYPHRANGENVPROC, glPathGlyphRangeNV);
    LOAD_PROC(PFNGLWEIGHTPATHSNVPROC, glWeightPathsNV);
    LOAD_PROC(PFNGLCOPYPATHNVPROC, glCopyPathNV);
    LOAD_PROC(PFNGLINTERPOLATEPATHSNVPROC, glInterpolatePathsNV);
    LOAD_PROC(PFNGLTRANSFORMPATHNVPROC, glTransformPathNV);
    LOAD_PROC(PFNGLPATHPARAMETERIVNVPROC, glPathParameterivNV);
    LOAD_PROC(PFNGLPATHPARAMETERINVPROC, glPathParameteriNV);
    LOAD_PROC(PFNGLPATHPARAMETERFVNVPROC, glPathParameterfvNV);
    LOAD_PROC(PFNGLPATHPARAMETERFNVPROC, glPathParameterfNV);
    LOAD_PROC(PFNGLPATHDASHARRAYNVPROC, glPathDashArrayNV);
    LOAD_PROC(PFNGLSTENCILFILLPATHNVPROC, glStencilFillPathNV);
    LOAD_PROC(PFNGLSTENCILSTROKEPATHNVPROC, glStencilStrokePathNV);
    LOAD_PROC(PFNGLSTENCILFILLPATHINSTANCEDNVPROC, glStencilFillPathInstancedNV);
    LOAD_PROC(PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC, glStencilStrokePathInstancedNV);
    LOAD_PROC(PFNGLPATHCOLORGENNVPROC, glPathColorGenNV);
    LOAD_PROC(PFNGLPATHTEXGENNVPROC, glPathTexGenNV);
    LOAD_PROC(PFNGLPATHFOGGENNVPROC, glPathFogGenNV);
    LOAD_PROC(PFNGLCOVERFILLPATHNVPROC, glCoverFillPathNV);
    LOAD_PROC(PFNGLCOVERSTROKEPATHNVPROC, glCoverStrokePathNV);
    LOAD_PROC(PFNGLCOVERFILLPATHINSTANCEDNVPROC, glCoverFillPathInstancedNV);
    LOAD_PROC(PFNGLCOVERSTROKEPATHINSTANCEDNVPROC, glCoverStrokePathInstancedNV);
    LOAD_PROC(PFNGLGETPATHPARAMETERIVNVPROC, glGetPathParameterivNV);
    LOAD_PROC(PFNGLGETPATHPARAMETERFVNVPROC, glGetPathParameterfvNV);
    LOAD_PROC(PFNGLGETPATHCOMMANDSNVPROC, glGetPathCommandsNV);
    LOAD_PROC(PFNGLGETPATHCOORDSNVPROC, glGetPathCoordsNV);
    LOAD_PROC(PFNGLGETPATHDASHARRAYNVPROC, glGetPathDashArrayNV);
    LOAD_PROC(PFNGLGETPATHMETRICSNVPROC, glGetPathMetricsNV);
    LOAD_PROC(PFNGLGETPATHMETRICRANGENVPROC, glGetPathMetricRangeNV);
    LOAD_PROC(PFNGLGETPATHSPACINGNVPROC, glGetPathSpacingNV);
    LOAD_PROC(PFNGLGETPATHCOLORGENIVNVPROC, glGetPathColorGenivNV);
    LOAD_PROC(PFNGLGETPATHCOLORGENFVNVPROC, glGetPathColorGenfvNV);
    LOAD_PROC(PFNGLGETPATHTEXGENIVNVPROC, glGetPathTexGenivNV);
    LOAD_PROC(PFNGLGETPATHTEXGENFVNVPROC, glGetPathTexGenfvNV);
    LOAD_PROC(PFNGLISPOINTINFILLPATHNVPROC, glIsPointInFillPathNV);
    LOAD_PROC(PFNGLISPOINTINSTROKEPATHNVPROC, glIsPointInStrokePathNV);
    LOAD_PROC(PFNGLGETPATHLENGTHNVPROC, glGetPathLengthNV);
    LOAD_PROC(PFNGLPOINTALONGPATHNVPROC, glPointAlongPathNV);
    LOAD_PROC(PFNGLPATHSTENCILFUNCNVPROC, glPathStencilFuncNV);
    LOAD_PROC(PFNGLPATHSTENCILDEPTHOFFSETNVPROC, glPathStencilDepthOffsetNV);
    LOAD_PROC(PFNGLPATHCOVERDEPTHFUNCNVPROC,  glPathCoverDepthFuncNV);
 
}