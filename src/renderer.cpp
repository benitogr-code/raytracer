#include "renderer.h"

#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "common/stbHelper.h"
#include "scene/camera.h"
#include "scene/scene.h"

namespace Renderer {

void displayProgress(float value) {
    const int barWidth = 60;
    const int pos = barWidth * value;

    std::stringstream ss;
    ss << "\rProgress [";

    for (int i = 0; i < barWidth; ++i) {
        ss << ((i <= pos) ? "*" : " ");
    }

    ss << "] " << int(value * 100.0f) << " %";

    std::cout << ss.str() << std::flush;
}

class RenderJobs {
public:
    RenderJobs(int pixelCount, int stride)
        : _pixelCount(pixelCount)
        , _stride(stride) {

        _currentPixel.store(0);
    }

    bool nextPixel(int* x, int* y) {
        auto nextPixel = _currentPixel.fetch_add(1);

        if (nextPixel < _pixelCount) {
            *y = nextPixel / _stride;
            *x = nextPixel % _stride;

            return true;
        }

        return false;
    }

    bool empty() const {
        return (_currentPixel >= _pixelCount);
    }

    float progress() const {
        return ((float)_currentPixel / (float)_pixelCount);
    }

private:
    std::atomic<int> _currentPixel;
    const int _pixelCount;
    const int _stride;
};

typedef std::shared_ptr<RenderJobs> RenderJobsPtr;

struct RenderInput {
    RenderInput(const Scene& _scene, const Camera& _camera, int _samplesPerPixel, int _maxBounces)
        : scene(_scene)
        , camera(_camera)
        , samplesPerPixel(_samplesPerPixel)
        , maxBounces(_maxBounces) {}

    const Scene& scene;
    const Camera& camera;
    const int samplesPerPixel;
    const int maxBounces;
};

typedef std::shared_ptr<RenderInput> RenderInputPtr;

struct RenderThread {
    void operator()(RenderInputPtr input, RenderJobsPtr jobs, ImageBufferPtr output) {
        const int width = output->width();
        const int height = output->height();

        int x, y;
        while (jobs->nextPixel(&x, &y)) {
            Color pixel(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < input->samplesPerPixel; ++s) {
                const float u = float(x + Math::randf()) / (width-1);
                const float v = float(y + Math::randf()) / (height-1);

                const Ray ray = input->camera.viewportRay(u, v);
                pixel += raytrace(input->scene, ray, input->maxBounces);
            }

            const float scale = 1.0f / input->samplesPerPixel;
            output->writePixel(x, y, Color::gamma2(pixel*scale));
        }
    }

private:
    Color raytrace(const Scene& scene, const Ray& ray, int bounces) {
        if (bounces <= 0)
            return Color(0.0f, 0.0f, 0.0f);

        HitInfo hit;
        if (scene.rayTrace(ray, 0.005f, Math::MaxFloat, hit)) {
            Ray scattered;
            Color attenuation;
            if (!hit.material->scatter(ray, hit, attenuation, scattered))
                return Color(0.0f, 0.0f, 0.0f);

            return attenuation * raytrace(scene, scattered, bounces-1);
        }

        const float t = 0.5f*(ray.direction.y + 1.0f);

        return (1.0f-t)*Color(1.0f, 1.0f, 1.0f) + t*Color(0.5f, 0.7f, 1.0f);
    }
};

ImageBufferPtr render(const Scene& scene, const Camera& camera, const Settings& settings) {
    const int threads = std::thread::hardware_concurrency();
    std::vector<std::future<void>> tasks;

    auto image = std::make_shared<ImageBuffer>(settings.imageWidth, settings.imageHeight);
    auto input = std::make_shared<RenderInput>(scene, camera, settings.samplesPerPixel, settings.maxBounces);
    auto jobs = std::make_shared<RenderJobs>(settings.imageWidth * settings.imageHeight, settings.imageWidth);

    for (int t = 0; t < threads; t++) {
        tasks.emplace_back(
            std::async(RenderThread(), input, jobs, image)
        );
    }

    while (!jobs->empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        displayProgress(jobs->progress());
    }

    return image;
}

void savePng(const ImageBufferPtr& image, const char* szFile) {
    const int stride = image->width() * image->channels();
    const unsigned char* end = image->data() + (image->width() * image->channels() * (image->height() - 1));
    StbHelper::writePng(szFile, image->width(), image->height(), image->channels(), end, -stride);
}

} // namespace Renderer
