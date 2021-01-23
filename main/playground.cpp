
#include <core/image.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/textures/constant.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/aabox.h>
#include <rt/solids/triangle.h>
#include <rt/integrators/casting.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/mirror.h>
#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/directional.h>
#include <rt/loaders/obj.h>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace rt;

namespace {

void renderCornellbox(float scale, const char* filename, Camera* cam, Material* sphereMaterial, Material* floorMaterial, int numSamples=1) {
    Image img(50, 50);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    Texture* redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* yellowtex = new ConstantTexture(RGBColor(0.7f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Material* grey = new LambertianMaterial(blacktex, whitetex);
    Material* yellowmat = new LambertianMaterial(blacktex, yellowtex);
    Material* leftWallMaterial = new LambertianMaterial(blacktex, redtex);
    Material* rightWallMaterial = new LambertianMaterial(blacktex, greentex);
    
    
    loadOBJ(scene, "../../models/", "deer.obj", new GlassMaterial(2));


    //walls
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, floorMaterial)); //floor
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, nullptr, grey)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, nullptr, grey)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, grey)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, grey)); //left wall

    //scene->add(new Sphere(Point(275.0f, 100.0f, 240.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));
    //scene->add(new Sphere(Point(275.0f, 100.0f, 240.0f)*scale, 49.0f*scale, nullptr, yellowmat));

    //Lights
    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f));
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

    Quad* light = new Quad(Point(213*scale,549.99f*scale,227*scale), Vector(130*scale,0,0), Vector(0,0,105*scale), nullptr, lightsource);
    AreaLight als(light);
    //world.light.push_back(&als);
    //scene->add(light);

    //point light
    //world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,279.5f*scale),RGBColor(40000.0f*scale*scale,0,0)));
    //world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,249.5f*scale),RGBColor(5000.0f*scale*scale,30000.0f*scale*scale,5000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point(40*scale,159.99f*scale,249.5f*scale),RGBColor(0.3f,0.18f,0.04f)));
    world.light.push_back(new PointLight(Point(490*scale,159.99f*scale,279.5f*scale),RGBColor(0.3f,0.18f,0.04f)));
    world.light.push_back(new PointLight(Point(280*scale,159.99f*scale,480*scale),RGBColor(0.3f,0.18f,0.04f)));

    RecursiveRayTracingIntegrator integrator(&world);

    Renderer engine(cam, &integrator);
    if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);
}

}


void playground() {
    PerspectiveCamera* cam = new PerspectiveCamera(Point(0.278f, 0.173f, -0.800f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);
    DOFPerspectiveCamera* dofcam = new DOFPerspectiveCamera(Point(0.278f, 0.273f, -0.8f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f, 1.025f, 0.045f);

    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    Material* floorMaterial1 = new LambertianMaterial(blacktex, whitetex);
    Material* floorMaterial2 = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f);
    Material* floorMaterial3 = new MirrorMaterial(2.485f, 3.433f);

    Material* sphereGlass = new GlassMaterial(2);

    auto start = std::chrono::system_clock::now();
    std::cout<<"STARTED \n";
    renderCornellbox(0.001f, "Playground.png", cam, sphereGlass, floorMaterial1, 1);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end-start;
    std::cout<<"DONE \n"<<"time: "<<elapsed_seconds2.count()<<" s \n";
}