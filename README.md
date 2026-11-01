# Separating axis theorem + AABB collision demo
A simple C++20 demo to showcase my research on collision detection algorithms for convex shapes, as well as process optimization.

## Building
```log
cmake . -B build && cmake --build build --config Debug
```
## Features
1. Simple 2D player movement with WASD controls (visuals made with raylib)
2. AABB collision with a static object (with a green overlay serving as a prediction on the player's next position based on current velocity & framerate for future implementation of swept AABB)
3. Simple .ini config file (currently saves window size and location)
## Credits
The libraries used:
- [mINI](https://github.com/metayeti/mINI) - config parsing and writing
- [raylib](https://github.com/raysan5/raylib) - 2D visuals
## References
- [Swept AABB Collision Detection and Response](https://gamedev.net/tutorials/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084) (NOTE: This implementation is non-functional, but serves as inspiration for implementation of simple AABB framerate-independent collision)
- [Separating Axis Theorem - Kansas State University](https://textbooks.cs.ksu.edu/cis580/04-collisions/04-separating-axis-theorem/)
- [Separating Axis Theorem - sevenson.com.au](https://www.sevenson.com.au/blog/sat/)
