# Saturn Engine
Saturn is in development interactive application and rendering engine primarily for Windows but can work on Linux and Mac with a few tweaks, most of the features in this repository are in development

## Getting Started
Visual Studio 2017 or 2019 is recommended, Saturn is officially untested on other development environments whilst we focus on a Windows build.

Start by cloning the repository with git clone https://github.com/Insomniac-Coder/Saturn-Engine.

## The Plan
The plan is to develop an Engine which is capable of loading 3D models and has basic features like Batch rendering, lighting, shadows and skybox implemented, this implementation has batch rendering implemented to a certain degree and is capable of rendering hundreds of objects and millions of vertices in just a couple of draw calls!

### Main features to come:
- Fully automatic batch renderer which takes care of the process by taking materials, shaders and vertex buffer size limit into account (almost done!)
- On the fly shader creation, it's pretty common feature in modern game engines, in which shaders get modified/created depending upon the requirements of the objects in the scene
- Procedural skybox
- Shadow (soft/hard)
- Input management system

## What the project has as of now?
Load Models (not the complex ones though!), apply textures, batch render objects, has basic point light implemented (with no attenuation). My main goal was to complete this project first and then add Vulkan Implementation but there seems to be an issue which makes Batch rendering act a bit weird when I use it on my system with RTX 3070 but the same code works perfectly fine on a system with GT 940M, so as of now this project is on hold, however I am actively working on the Vulkan based implementation! the link for that repo is : https://github.com/Insomniac-Coder/SaturnV