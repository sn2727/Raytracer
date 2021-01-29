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
#include <omp.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void blur(int w, int h, RGBColor blur, Image& img) {
    if (w >= 0 && h < img.height() && w >= 0 && w < img.width() && img(w, h).sum() < 0.1f) {
        img(w, h) = blur;
    }    
}

void Renderer::blurStars(Image& img) {
    for (int w = 0; w < img.width(); w++) {
        for (int h = 0; h < img.height(); h++) {
            if (img(w,h).sum() > 2.99f) {
                RGBColor pc(img(w,h));  
                RGBColor blurC(1, 1, 0.478f);
                int range = 3;
                for (int i = 1; i <= range; i++) {
                    blur(w-i, h, 3*(1/float(i))*blurC, img);
                    blur(w, h-i, 3*(1/float(i))*blurC, img);
                    blur(w+i, h, 3*(1/float(i))*blurC, img);
                    blur(w, h+i, 3*(1/float(i))*blurC, img);
                }
            }
        }
    }
}

void Renderer::render(Image& img) {
    int pixels = img.height()*img.width();
    int tenth = pixels/10;
    int benchmarks[9] = {tenth,
                        2*tenth,
                        3*tenth,
                        4*tenth,
                        5*tenth,
                        6*tenth,
                        7*tenth,
                        8*tenth,
                        9*tenth};

    int benchmark = benchmarks[0];
    int benchmarkpointer = 0;

    if (samples <= 1) {
        #pragma omp parallel for
        for (uint w = 0; w < img.width(); w++) {
            #pragma omp parallel for
            for (uint h = 0; h < img.height(); h++){
                // Normalized device coordinates [0, 1]
                float ndcx = (w + 0.5f) / img.width();
                float ndcy = (h + 0.5f) / img.height();

                // Screen space coordinates [-1, 1]
                float sscx = ndcx * 2 - 1;
                float sscy = -1*(ndcy * 2 - 1);
    
                img(w,h) = integrator->getRadiance(cam->getPrimaryRay(sscx, sscy));

                if (w*h > benchmark) {
                    std::cout<<(benchmarkpointer+1)*10<<" % DONE \n";
                    benchmarkpointer++;
                    benchmark = benchmarks[benchmarkpointer];
                }
            }         
        }
    } else {
        #pragma omp parallel for
        for (uint w = 0; w < img.width(); w++) {
            #pragma omp parallel for
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

                if (w*h > benchmark) {
                    std::cout<<(benchmarkpointer+1)*10<<" % DONE \n";
                    benchmarkpointer++;
                    benchmark = benchmarks[benchmarkpointer];
                }     
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
