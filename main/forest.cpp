#include <core/image.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/textures/constant.h>
#include <rt/textures/perlin.h>
#include <rt/textures/imagetex.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/integrators/casting.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
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

int width = 1600;
int height = 1600;
int samples = 1;
int integratorRecDepth = 10;
Point cameraPosition = Point(0.275f, 0.143f, -0.46f);
RGBColor lightIntensity = RGBColor::rep(0.7f)*10;

/** MATERIALS **/

PerlinTexture* perlin = new PerlinTexture(0.8f*RGBColor(0.545f,0.27f,0.0745f), 0.3f*RGBColor(0.6274f,0.3215f,0.1764f));
Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
Texture* greytex = new ConstantTexture(RGBColor::rep(0.5f));
Texture* brown = new ConstantTexture(0.6f * RGBColor(0.545f, 0.27f, 0.074f)); 
Texture* greentex = new ConstantTexture(RGBColor(0,0.4f,0)); 
Texture* deertex = new ImageTexture("models/deertex.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
Texture* birdtex = new ImageTexture("models/birdtex.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
Texture* treetex = new ImageTexture("models/greenblacktex.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
Material* walls = new LambertianMaterial(blacktex, whitetex);
Material* white = new LambertianMaterial(whitetex, whitetex);
RGBColor warm = 3*RGBColor(0.3f, 0.18f, 0.04f);
Texture* yellowtex = new ConstantTexture(warm);
Material* lighter = new LambertianMaterial(yellowtex, whitetex);
Material* moon = new LambertianMaterial(new ConstantTexture(RGBColor(0.996f, 0.988f, 0.843f)), whitetex);
Material* star = new LambertianMaterial(new ConstantTexture(RGBColor::rep(1)), whitetex);
Material* weakstar = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.7f)), whitetex);

Material* groundMaterial = new LambertianMaterial(blacktex, perlin);
Material* deerMaterial = new LambertianMaterial(blacktex, deertex);
Material* woodMaterial = new LambertianMaterial(blacktex, treetex);
Material* birdMaterial = new LambertianMaterial(blacktex, birdtex);


void buildScene(SimpleGroup* scene, World* world) {

    //moon
    scene->add(new Sphere(Point(0.3f, 0.625f, 1), 0.065f, new WorldMapper(Vector::rep(2)), moon));

    //stars right to left
    scene->add(new Sphere(Point(0.77f, 0.62f, 1.f), 0.0012f, nullptr, star)); 
    scene->add(new Sphere(Point(0.75f, 0.7f, 1.f), 0.0013f, nullptr, star)); 
    scene->add(new Sphere(Point(0.73f, 0.56f, 1.f), 0.0012f, nullptr, star)); 
    scene->add(new Sphere(Point(0.69f, 0.71f, 1.f), 0.00145f, nullptr, star)); 
    scene->add(new Sphere(Point(0.676f, 0.58f, 1.f), 0.0007f, nullptr, star)); 
    scene->add(new Sphere(Point(0.67f, 0.65f, 1.f), 0.0008f, nullptr, star)); 
    scene->add(new Sphere(Point(0.67f, 0.73f, 1.f), 0.0011f, nullptr, star));
    scene->add(new Sphere(Point(0.656f, 0.51f, 1.f), 0.0015f, nullptr, star)); 
    scene->add(new Sphere(Point(0.64f, 0.71f, 1.f), 0.001f, nullptr, star));
    scene->add(new Sphere(Point(0.63f, 0.657f, 1.f), 0.0004f, nullptr, weakstar));
    scene->add(new Sphere(Point(0.627f, 0.68f, 1.f), 0.0013f, nullptr, star));
    scene->add(new Sphere(Point(0.62f, 0.73f, 1.f), 0.00134f, nullptr, star));
    scene->add(new Sphere(Point(0.58f, 0.6f, 1.f), 0.00099f, nullptr, star));
    scene->add(new Sphere(Point(0.577f, 0.675f, 1.f), 0.00115f, nullptr, star)); 
    scene->add(new Sphere(Point(0.56f, 0.62f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(0.54f, 0.57f, 1.f), 0.0017f, nullptr, star)); 
    scene->add(new Sphere(Point(0.523f, 0.692f, 1.f), 0.00178f, nullptr, star));
    scene->add(new Sphere(Point(0.5f, 0.65f, 1.f), 0.001f, nullptr, weakstar));
    scene->add(new Sphere(Point(0.474f, 0.711f, 1.f), 0.0016f, nullptr, star));
    scene->add(new Sphere(Point(0.452f, 0.72f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(0.44f, 0.52f, 1.f), 0.0017f, nullptr, star)); 
    scene->add(new Sphere(Point(0.436f, 0.663f, 1.f), 0.0015f, nullptr, star)); 
    scene->add(new Sphere(Point(0.43f, 0.59f, 1.f), 0.001f, nullptr, star));
    scene->add(new Sphere(Point(0.38f, 0.67f, 1.f), 0.00105f, nullptr, star));
    scene->add(new Sphere(Point(0.365f, 0.72f, 1.f), 0.00155f, nullptr, star));
    scene->add(new Sphere(Point(0.35f, 0.65f, 1.f), 0.0008f, nullptr, star));
    scene->add(new Sphere(Point(0.325f, 0.52f, 1.f), 0.0011f, nullptr, weakstar));
    scene->add(new Sphere(Point(0.31f, 0.68f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(0.31f, 0.75f, 1.f), 0.0017f, nullptr, star));
    scene->add(new Sphere(Point(0.31f, 0.61f, 1.f), 0.0011f, nullptr, star));
    scene->add(new Sphere(Point(0.305f, 0.635f, 1.f), 0.0011f, nullptr, star)); 
    scene->add(new Sphere(Point(0.3f, 0.67f, 1.f), 0.0013f, nullptr, star));
    scene->add(new Sphere(Point(0.28f, 0.68f, 1.f), 0.0007f, nullptr, star));
    scene->add(new Sphere(Point(0.25f, 0.66f, 1.f), 0.0014f, nullptr, star));
    scene->add(new Sphere(Point(0.23f, 0.71f, 1.f), 0.0014f, nullptr, star));
    scene->add(new Sphere(Point(0.22f, 0.512f, 1.f), 0.0011f, nullptr, star));
    scene->add(new Sphere(Point(0.15f, 0.491f, 1.f), 0.0009f, nullptr, star));
    scene->add(new Sphere(Point(0.215f, 0.562f, 1.f), 0.0013f, nullptr, star));
    scene->add(new Sphere(Point(0.2f, 0.57f, 1.f), 0.0007f, nullptr, star));
    scene->add(new Sphere(Point(0.18f, 0.61f, 1.f), 0.00145f, nullptr, star));
    scene->add(new Sphere(Point(0.182f, 0.69f, 1.f), 0.0015f, nullptr, star));
    scene->add(new Sphere(Point(0.17f, 0.54f, 1.f), 0.0002f, nullptr, star));
    scene->add(new Sphere(Point(0.155f, 0.573f, 1.f), 0.0023f, nullptr, star));
    scene->add(new Sphere(Point(0.15f, 0.6f, 1.f), 0.00115f, nullptr, star));
    scene->add(new Sphere(Point(0.13f, 0.64f, 1.f), 0.0013f, nullptr, star));
    scene->add(new Sphere(Point(0.1f, 0.7f, 1.f), 0.00165f, nullptr, star));
    scene->add(new Sphere(Point(0.07f, 0.71f, 1.f), 0.0015f, nullptr, star));
    scene->add(new Sphere(Point(0.075f, 0.55f, 1.f), 0.0005f, nullptr, star));
    scene->add(new Sphere(Point(0.08f, 0.65f, 1.f), 0.0015f, nullptr, star));
    scene->add(new Sphere(Point(0.08f, 0.57f, 1.f), 0.0014f, nullptr, star));
    scene->add(new Sphere(Point(0, 0.542f, 1.f), 0.0018f, nullptr, star));
    scene->add(new Sphere(Point(0, 0.5f, 1.f), 0.0013f, nullptr, star));
    scene->add(new Sphere(Point(0, 0.63f, 1.f), 0.00126f, nullptr, star));
    scene->add(new Sphere(Point(-0.029f, 0.7f, 1.f), 0.0018f, nullptr, star));
    scene->add(new Sphere(Point(-0.051f, 0.6f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(-0.07f, 0.66f, 1.f), 0.0017f, nullptr, star));
    scene->add(new Sphere(Point(-0.08f, 0.58f, 1.f), 0.001f, nullptr, star));
    scene->add(new Sphere(Point(-0.11f, 0.72f, 1.f), 0.0015f, nullptr, star));
    scene->add(new Sphere(Point(-0.125f, 0.67f, 1.f), 0.0014f, nullptr, star));
    scene->add(new Sphere(Point(-0.112f, 0.543f, 1.f), 0.0017f, nullptr, star));
    scene->add(new Sphere(Point(-0.2f, 0.625f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(-0.18f, 0.69f, 1.f), 0.0012f, nullptr, star));
    scene->add(new Sphere(Point(-0.15f, 0.62f, 1.f), 0.0005f, nullptr, star));
    scene->add(new Sphere(Point(-0.22f, 0.69f, 1.f), 0.0011f, nullptr, star));
    scene->add(new Sphere(Point(-0.245f, 0.532f, 1.f), 0.00093f, nullptr, star));
    scene->add(new Sphere(Point(-0.275f, 0.72f, 1.f), 0.001f, nullptr, star));
    scene->add(new Sphere(Point(-0.272f, 0.669f, 1.f), 0.00096f, nullptr, star));
    scene->add(new Sphere(Point(-0.61f, 0.56f, 1.f), 0.0008f, nullptr, star));

    perlin->addOctave(0.5f, 10.0f);
    perlin->addOctave(0.25f, 20.0f);
    perlin->addOctave(0.125f, 40.0f);
    perlin->addOctave(0.125f, 80.0f);
    //bird's eye
    scene->add(new Sphere(Point(0.373f, 0.31f, 0.18f), 0.0008f, nullptr, new LambertianMaterial(yellowtex, whitetex)));
    
    //deer's eye
    scene->add(new Sphere(Point(0.217f, 0.118f, 0), 0.0015f, nullptr, new GlassMaterial(2.5f)));
    
    //lights
    Point birdLP(0.28f, 0.25f, -0.2f);
    world->light.push_back(new PointLight(birdLP, RGBColor::rep(0.25f))); // bird
    
    world->light.push_back(new PointLight(Point(0.22f, 0.115f, 0), RGBColor::rep(0.000005f))); // deer2 

    world->light.push_back(new PointLight(Point(0.3f, 0.59f, 0.9f), RGBColor::rep(0.02f))); //moon
    

}

void forest(int w, int h, std::string file) {
    Image img(w, h);
    World* world = new World();
    SimpleGroup* scene = new SimpleGroup();
    world->scene = scene;

    PerspectiveCamera* cam = new PerspectiveCamera(cameraPosition, Vector(0, 0.05f, 1).normalize(), Vector(0, 1, 0), 0.686f, 0.686f);
    
    RecursiveRayTracingIntegrator integrator(world);
    integrator.setRecDepth(integratorRecDepth);

    Renderer engine(nullptr, nullptr);
    engine = Renderer(cam, &integrator);

    engine.setSamples(samples);
    
    buildScene(scene, world);
    loadOBJ(scene, "models/", "ground.obj", groundMaterial);
    loadOBJ(scene, "models/", "fWoods2.obj", woodMaterial, new WorldMapper(Vector::rep(11)));
    loadOBJ(scene, "models/", "fDeer.obj", deerMaterial, new WorldMapper(Vector::rep(10)));
    loadOBJ(scene, "models/", "fBird.obj", birdMaterial, new WorldMapper(Vector::rep(30)));

    auto start = std::chrono::system_clock::now();
    std::cout<<"STARTED \n";

    engine.render(img);
    std::cout<<"Post Processing...\n";
    engine.blurStars(img);
    img.writePNG(file);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end-start;
    double seconds = elapsed_seconds2.count();
    if (seconds > 200) {
        std::cout<<"DONE \n"<<"time: "<<seconds/60<<" minutes \n";
    } else
    std::cout<<"DONE \n"<<"time: "<<seconds<<" seconds \n";
}

