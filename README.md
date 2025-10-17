# .obj loader/viewer for SDL3
![Alt text](/images/spinning.gif) <br />
this is the teapot.obj

### building8
- Just open the "based-engine.vxcsproj" in visual studio.
- You may need to add the SDL3 include libraries and linkers to build(have not tested)
- After building just copy the SDL3.dll and the data folder to where your executable is located
- run

### limitations8
- the obj parser cannot be fed .obj files that have vector normals.
- fully CPU
- only in orthographic view (no perspective)

