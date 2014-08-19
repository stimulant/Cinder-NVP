Cinder-NVP
==========

A Cinder block for using Nvidia Path extensions

This block will only work on Nvidia Cards with a driver that has the Path SDK extensions. Visual studio 2012 project files are included. Should work on Linux as well. The Nvidia Path Rendering SDK uses a stencil and cover approach where the driver initially rasterizes paths to the stencil buffer and then covers the path's area with simple geometry which gives it shading capabilities. See https://developer.nvidia.com/nv-path-rendering for more info on the Nvidia Path Rendering SDK. 

A copy of AppImplMswRendererGl.cpp is included in the source files to allow overriding the precompiled Cinder application code that disables the stencil buffer.
A copy of an updated Glee.h and Glee.c is included in the source which has the ability to load the nvidia path extensions. You must replace your copy of glee.h and glee.c with these files and then rebuild your cinder libraries.

#Features:

Resolution independent path drawing
kerning
stroked text
Truetype and OpenType system font path loading and metrics parsing using driver’s built in freetype2 implementation
blazing fast gpu stencil buffer drawing method
instanced drawing of glyphs so each font glyph is loaded only once to the gpu and then instanced for every textbox using that font (regardless of point size)
very lightweight library (no source or include files, everything is in the nvidia driver)
underline and dash decoration
typographically accurate bounds and positioning
first class support in the OpenGL pipeline:
can be transformed in 3D with OpenGL matrix transforms, can be properly depth tested with 3D geometry, can be textured with a fragment shader, can take advantage of the driver’s stochastic multi-sampling anti-aliasing functionality

#ToDo:

generic path drawing functions
example showing 3D transformation support
example showing shader support
svg loading and rendering
svg gradient shader implementation
example showing svg path instancing
dynamic svg driven text paths
font independent stroking (different stroking for multiple text fields using the same font)

#Issues:

Requires newer version of GLEE than Cinder’s default to load extensions
must enable stencil buffer which is disabled by default in Cinder
no vertex shader support. can get a 2d mapping for texturing but cannot query 3d position in shader so no fancy shadowing text
requires Nvidia card. probably doesn’t work on Mac
hacky emScale to point conversion
dependency on Nvidia driver code