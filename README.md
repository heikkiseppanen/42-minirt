<p align="center">
  <img width="512" height="512" src="https://raw.githubusercontent.com/heikkiseppanen/42-minirt/master/minirt.png">
</p>
<h1 align="center">
    MiniRT
</h1>
A small raytracer that renders basic mathematical solids from a .rt scene file.

The code is written in accordance to the 42 School [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

# Features
- Diffuse lighting
- Progressive sample rendering
- Free movement camera with preview image quality

# Build (Linux & MacOS)
```
make release
```

# Usage
```
> ./miniRT ./scenes/cornell_box.rt
```

## Input
- Left Mouse: Allows rotation of camera while down
- Right Mouse: Allows translating camera while down
- Scroll Wheel: Change flight speed
- WASD: Horizontal movement
- Space/Ctrl: Vertical movement
