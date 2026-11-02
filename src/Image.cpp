#include "Renderer.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <zlib.h>

namespace raytracer {
    static uint8_t toByte(double v)
    {
        return static_cast<uint8_t>(std::clamp(v, 0.0, 1.0) * 255 + 0.5);
    }

    static void writeBigEndian(std::ofstream &out, uint32_t v)
    {
        uint8_t b[4] = {uint8_t(v >> 24), uint8_t(v >> 16), uint8_t(v >> 8), uint8_t(v)};
        out.write(reinterpret_cast<char *>(b), 4);
    }

    static void writeChunk(std::ofstream &out, const char *type, const std::vector<uint8_t> &data)
    {
        writeBigEndian(out, static_cast<uint32_t>(data.size()));
        uLong crc = crc32(0, reinterpret_cast<const Bytef *>(type), 4);
        crc = crc32(crc, data.data(), static_cast<uInt>(data.size()));
        out.write(type, 4);
        out.write(reinterpret_cast<const char *>(data.data()), data.size());
        writeBigEndian(out, static_cast<uint32_t>(crc));
    }

    static void savePng(const Image &img, std::ofstream &out)
    {
        std::vector<uint8_t> raw;
        raw.reserve(static_cast<size_t>(img.height) * (img.width * 3 + 1));
        for (int y = 0; y < img.height; y++) {
            raw.push_back(0);
            for (int x = 0; x < img.width; x++) {
                const math::Vector3 &c = img.pixels[static_cast<size_t>(y) * img.width + x];
                raw.insert(raw.end(), {toByte(c.x), toByte(c.y), toByte(c.z)});
            }
        }
        uLongf size = compressBound(raw.size());
        std::vector<uint8_t> packed(size);
        if (compress2(packed.data(), &size, raw.data(), raw.size(), 9) != Z_OK)
            throw std::runtime_error("PNG compression failed");
        packed.resize(size);

        std::vector<uint8_t> header(13, 0);
        for (int i = 0; i < 4; i++) {
            header[i] = uint8_t(img.width >> (24 - 8 * i));
            header[4 + i] = uint8_t(img.height >> (24 - 8 * i));
        }
        header[8] = 8;
        header[9] = 2;

        out.write("\x89PNG\r\n\x1a\n", 8);
        writeChunk(out, "IHDR", header);
        writeChunk(out, "IDAT", packed);
        writeChunk(out, "IEND", {});
    }

    static void savePpm(const Image &img, std::ofstream &out)
    {
        out << "P6\n" << img.width << " " << img.height << "\n255\n";
        for (const math::Vector3 &c : img.pixels) {
            uint8_t rgb[3] = {toByte(c.x), toByte(c.y), toByte(c.z)};
            out.write(reinterpret_cast<char *>(rgb), 3);
        }
    }

    void Image::save(const std::string &path) const
    {
        std::ofstream out(path, std::ios::binary);
        if (!out)
            throw std::runtime_error("cannot write " + path);
        if (path.size() >= 4 && path.compare(path.size() - 4, 4, ".png") == 0)
            savePng(*this, out);
        else
            savePpm(*this, out);
    }
}
