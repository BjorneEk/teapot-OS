# teapot-OS
---

![Application preview](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-1.png)

![Application preview 2](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-2.png)
(sine wave animation)
![Application preview 3](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-3.png)
(first 3d renderer, with mouse controll)

![Application preview 4](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-4.png)
![Application preview 5](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-5.png)
![Application preview 6](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-6.png)
![Application preview 7](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-7.png)

## Current progress
- [x] **Bootloader** <span style="color:rgb(205, 120,62)"> enter 32 bit protected mode and run c code</span>
- [x] **Switch VGA mode** <span style="color:rgb(205, 120,62)">the should bootloader set the VGA mode to 320 x 200 color</span>
- [x] **Drawing on screen** <span style="color:rgb(205, 120,62)"> create a VGA driver adding a layer of abtraction to v-ram acces</span>
- [x] **Graphics library** <span style="color:rgb(205, 120,62)">enable features like fill_rect and draw_triangle via the VGA driver</span>
- [x] **Interrupts** <span style="color:rgb(205, 120,62)">handle interrupts in order to create drivers for mouse and keyboard</span>
- [x] **Keyboard driver** <span style="color:rgb(205, 120,62)"> enable keyboard input with information about keypresses</span>
- [x] **Font** <span style="color:rgb(205, 120,62)">create a custom 7x5 font in preparation for text output</span>
- [x] **Text output** <span style="color:rgb(205, 120,62)">enable the VGA driver to draw font characters</span>
- [x] **String output** <span style="color:rgb(205, 120,62)">add draw_string to graphics library  by converting chars to font indexes</span>
- [x] **Mouse driver** <span style="color:rgb(205, 120,62)">enable mouse motion and button input</span>
- [x] **Cursor [temporary]** <span style="color:rgb(205, 120,62)">implement mouse cursor directly to VGA driver</span>
- [x] **GUI [temporary]** <span style="color:rgb(205, 120,62)">use available functions display keyboard and mouse input info</span>
- [x] **Clean up VGA driver** <span style="color:rgb(205, 120,62)"> differentiate more between VGA driver and graphics lib</span>
- [x] **Linear algebra** <span style="color:rgb(205, 120,62)"> port library from [this project](https://github.com/BjorneEk/3d-graphics) in preparation for 3D rendering</span>
- [x] **3D-renderer** <span style="color:rgb(205, 120,62)"> implement 3D-renderer </span>
- [ ] **Event handeler** <span style="color:rgb(205, 120,62)">create a event handeler to interface with device drivers</span>
- [ ] **Memory allocator** <span style="color:rgb(205, 120,62)">create a memory allocator</span>
- [ ] **teapot time** <span style="color:rgb(205, 120,62)"> render a utah teapot referencing [this project](https://github.com/BjorneEk/3d-graphics) </span>
- [ ] **Run on hardware** <span style="color:rgb(205, 120,62)"> run teapot os natively on real hardware (potentialy 2013 MacBook Air) </span>
- [ ] **Create documentation** <span style="color:rgb(205, 120,62)"> document the code and project</span>
---
- **standard library** <span style="color:rgb(205, 120,62)">create neccesary utilities</span>
	- [x] **Fixed width ints** <span style="color:rgb(205, 120,62)"> *for neater code* </span>
	- [x] **Graphics library** <span style="color:rgb(205, 120,62)"> </span>
	- [x] **String utils** <span style="color:rgb(205, 120,62)"> converting and concating </span>
	- [x] **Math** <span style="color:rgb(205, 120,62)"> math functions especialy trigonometry functions like sin(x)</span>
---
- **Improved kernel GUI** <span style="color:rgb(205, 120,62)">made to handle a simple GUI for the kernel</span>
	- [x] **frame buffer** <span style="color:rgb(205, 120,62)">create a pixel depth frame buffer or something with similar functionality</span>
	- [x] **Window Manager** <span style="color:rgb(205, 120,62)">create window manager that supports drawing to windows instead of screen as a whole</span>
	- [x] **Window based events** <span style="color:rgb(205, 120,62)"> a neat way for windows to handle their own events</span>

<img alt="lang" src="https://img.shields.io/github/languages/top/bjorneek/teapot-os"/>
<img alt="size" src="https://img.shields.io/github/repo-size/bjorneek/teapot-os"/>
<img alt="lines" src="https://img.shields.io/tokei/lines/github/bjorneek/teapot-os"/>
