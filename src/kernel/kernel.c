

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///


void main() {
    char * video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}
