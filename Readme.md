## Overview

A brute force path tracer based on the [Raytracing in one weekend](https://raytracing.github.io/) book series.

The current feature set includes what is covered in the first two books in the series with some additions:

- Geometry: Spheres.
- Materials: diffuse, metal and glass.
- Textures: Flat color, noise, ...
- Camera properties: position, fov, focus distance...
- Bounding hierachical volumes to speed up scene traversal.
- Integrated STB library to generate PNG image output.
- Multi threaded rendering.

The main executable has multiple scene samples which can be rendered at different quality presets: low, medium and high.

```raytracer --scene perlin-spheres --quality medium```

**Random spheres with materials**
<br/>
<img title="Spheres scene" src="images/spheres-01.jpg" width="700">

**Random spheres with materials + Ground texture and Motion blur**
<br />
<img title="Spheres scene with textures and blur" src="images/spheres-02.jpg" width="700">

**Textures: perlin noise**
<br />
<img title="Perlin noise" src="images/textures-perlin.jpg" width="700">
