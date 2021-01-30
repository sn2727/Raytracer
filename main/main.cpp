#include <iostream>

void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();
void forest(int w, int h, std::string file);

int main(int argc, char* argv[]) {
    forest(400, 400, "thumbnail.png");
    forest(1600, 1600, "final.png"); 
    return 0;
}