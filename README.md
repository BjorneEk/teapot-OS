# teapot-OS
---



![Application preview](https://github.com/BjorneEk/teapot-os/blob/master/docs/teapot-os-1.png)

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
- [ ] **Memory allocator** <span style="color:rgb(205, 120,62)">create a memory allocator</span>
- [ ] **Clean up VGA driver** <span style="color:rgb(205, 120,62)"> differentiate more between VGA driver and graphics lib</span>
- [ ] **Linear algebra** <span style="color:rgb(205, 120,62)"> port library from [this project](https://github.com/BjorneEk/3d-graphics) in preparation for 3D rendering</span>
- [ ] **3D-renderer** <span style="color:rgb(205, 120,62)"> implement 3D-renderer </span>
- [ ] **teapot time** <span style="color:rgb(205, 120,62)"> render a utah teapot referencing [this project](https://github.com/BjorneEk/3d-graphics) </span>
- [ ] **Run on hardware** <span style="color:rgb(205, 120,62)"> run teapot os natively on real hardware (potentialy 2013 MacBook Air) </span>
- [ ] **Create documentation** <span style="color:rgb(205, 120,62)"> document the code and project</span>
---
- **standard library** <span style="color:rgb(205, 120,62)">create neccesary utilities</span>
	- [x] **Fixed width ints** <span style="color:rgb(205, 120,62)"> *for neater code* </span>
	- [x] **Graphics library** <span style="color:rgb(205, 120,62)"> </span>
	- [ ] **String utils** <span style="color:rgb(205, 120,62)"> converting and concating </span>
	- [ ] **Math** <span style="color:rgb(205, 120,62)"> math functions especialy trigonometry functions like sin(x)</span>



<img alt="lang" src="https://img.shields.io/github/languages/top/bjorneek/teapot-os"/>
<img alt="size" src="https://img.shields.io/github/repo-size/bjorneek/teapot-os"/>
<img alt="lines" src="https://img.shields.io/tokei/lines/github/bjorneek/teapot-os"/>
