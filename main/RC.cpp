#include <core/image.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/integrators/casting.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/mirror.h>
#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/spotlight.h>
#include <rt/loaders/obj.h>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace rt;

/** OPTIONS **/

int width = 200;
int height = 200;
bool toggleDOF = false;
int samples = 1;
int integratorRecDepth = 10;
Point cameraPosition = Point(0.275f, 0.143f, -0.46f);
RGBColor lightIntensity = RGBColor::rep(0.7f)*5;

/** MATERIALS **/

Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
Texture* fog = new ImageTexture("/models/fog.jpg", ImageTexture::REPEAT, ImageTexture::BILINEAR);
Material* walls = new LambertianMaterial(blacktex, whitetex);
Material* backWall = new LambertianMaterial(blacktex, fog);
Material* white = new LambertianMaterial(whitetex, whitetex);
Material* mirrorMaterial = new MirrorMaterial(2.485f, 3.433f);
Material* treeMaterial = new LambertianMaterial(blacktex, new ConstantTexture(RGBColor::rep(0.07f)));
Material* deerMaterial = new GlassMaterial(2.3f);
RGBColor warm(0.3f, 0.18f, 0.04f);
Texture* yellowtex = new ConstantTexture(warm);
Material* lighter = new LambertianMaterial(yellowtex, whitetex);
Material* moon = new LambertianMaterial(new ConstantTexture(RGBColor(0.996f, 0.988f, 0.843f)), whitetex);




void buildScene(SimpleGroup* scene, World* world) {

    //walls
    scene->add(new Quad(Point(0, 0, -0.52f), Vector(0, 0, 1.2f), Vector(0.55f, 0, 0), nullptr, mirrorMaterial)); //floor
    scene->add(new Quad(Point(0.55f, 0.55f, -0.5f), Vector(0, 0, 1.2f), Vector(-0.55f, 0, 0), nullptr, walls)); //ceiling
    scene->add(new Quad(Point(0, 0, 0.56f), Vector(0, 0.55f, 0), Vector(0.55f, 0, 0), new WorldMapper(Vector(1.7f,2,1)), backWall)); //back wall
    scene->add(new Quad(Point(0, 0, -0.56f), Vector(0.55f, 0, 0), Vector(0, 0.55f, 0), nullptr, walls)); //front wall
    scene->add(new Quad(Point(0, 0, -0.5f), Vector(0, 0.55f, 0), Vector(0, 0, 1.2f), nullptr, walls)); //right wall
    scene->add(new Quad(Point(0.55f, 0.55f, -0.5f), Vector(0, -0.55f, 0), Vector(0, 0, 1.2f), nullptr, walls)); //left wall

    scene->add(new Sphere(Point(0.275f, 0.3f, 0.53f), 0.12f, nullptr, moon)); //moon

    //light
    world->light.push_back(new SpotLight(cameraPosition, Vector(0,0.05f,1).normalize(), pi/12, 0.0001f, lightIntensity));
}

void RC() {
    Image img(width, height);
    World* world = new World();
    SimpleGroup* scene = new SimpleGroup();
    world->scene = scene;

    PerspectiveCamera* cam = new PerspectiveCamera(cameraPosition, Vector(0, 0.05f, 1).normalize(), Vector(0, 1, 0), 0.686f, 0.686f);
    DOFPerspectiveCamera* dofcam = new DOFPerspectiveCamera(cameraPosition, Vector(0, 0.05f, 1).normalize(), Vector(0, 1, 0), 0.686f, 0.686f, 0.33f, 0.001f);
    
    RecursiveRayTracingIntegrator integrator(world);
    integrator.setRecDepth(integratorRecDepth);

    Renderer engine(nullptr, nullptr);
    if (toggleDOF) engine = Renderer(dofcam, &integrator);
    if (!toggleDOF) engine = Renderer(cam, &integrator);

    engine.setSamples(samples);
    
    buildScene(scene, world);
    loadOBJ(scene, "../../models/", "bird_lowQ.obj", deerMaterial);
    loadOBJ(scene, "../../models/", "trees_lowQ.obj", treeMaterial);
    loadOBJ(scene, "../../models/", "deer.obj", deerMaterial);

    auto start = std::chrono::system_clock::now();
    std::cout<<"STARTED \n";

    engine.render(img);
    img.writePNG("RC.png");
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end-start;
    std::cout<<"DONE \n"<<"time: "<<elapsed_seconds2.count()<<" s \n";
}

