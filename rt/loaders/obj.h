#ifndef CG1RAYTRACER_LOADERS_OBJ_HEADER
#define CG1RAYTRACER_LOADERS_OBJ_HEADER

#include <string>
#include <map>
#include <vector>
#include <rt/coordmappers/coordmapper.h>

namespace rt {

class Group;
class Material;

typedef std::map<std::string, Material*> MatLib;

void loadOBJ(Group* dest, const std::string& path, const std::string& filename, Material* mat = nullptr, CoordMapper* texMapper = nullptr, MatLib* inmats=nullptr);
void loadOBJMat(MatLib* dest, const std::string& path, const std::string& filename);

}

#endif