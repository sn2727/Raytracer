#include <core/scalar.h>
#include <core/image.h>
#include <rt/cameras/orthographic.h>
#include <rt/cameras/perspective.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <rt/integrators/integrator.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <iostream>

#pragma omp parallel
#pragma omp for

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    if (samples <= 1) {
        for (uint w = 0; w < img.width(); w++) {
            for (uint h = 0; h < img.height(); h++){
                // Normalized device coordinates [0, 1]
                float ndcx = (w + 0.5f) / img.width();
                float ndcy = (h + 0.5f) / img.height();

                // Screen space coordinates [-1, 1]
                float sscx = ndcx * 2 - 1;
                float sscy = -1*(ndcy * 2 - 1);
    
                img(w,h) = integrator->getRadiance(cam->getPrimaryRay(sscx, sscy));
            }         
        }
    } else {
        for (uint w = 0; w < img.width(); w++) {
            for (uint h = 0; h < img.height(); h++){
                RGBColor radiance = RGBColor::rep(0);
                for (uint s = 0; s < samples; s++) {
                    float rand = random();
                    // Normalized device coordinates [0, 1]
                    float ndcx = (w + rand) / img.width();
                    float ndcy = (h + rand) / img.height();

                    // Screen space coordinates [-1, 1]
                    float sscx = ndcx * 2 - 1;
                    float sscy = -1*(ndcy * 2 - 1);
                    radiance = radiance + integrator->getRadiance(cam->getPrimaryRay(sscx, sscy));
                }
                img(w,h) = radiance / samples;         
            }    
        }
    }
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    for (uint w = 0; w < img.width(); w++) {
        for (uint h = 0; h < img.height(); h++){
            img(w,h) = a1computeColor(w, h, img.width(), img.height());
        }
    }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    for (uint w = 0; w < img.width(); w++) {
        for (uint h = 0; h < img.height(); h++){

            // Normalized device coordinates [0, 1]
            float ndcx = (w + 0.5f) / img.width();
            float ndcy = (h + 0.5f) / img.height();

            // Screen space coordinates [-1, 1]
            float sscx = ndcx * 2 - 1;
            float sscy = -1*(ndcy * 2 - 1);
    
            img(w,h) = a2computeColor(cam -> getPrimaryRay(sscx, sscy));
        }
    }
    
}

}
