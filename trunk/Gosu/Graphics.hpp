//! \file Graphics.hpp
//! Interface of the Graphics class and DisplayMode structure.

#ifndef GOSU_GRAPHICS_HPP
#define GOSU_GRAPHICS_HPP

#include <Gosu/Fwd.hpp>
#include <Gosu/Color.hpp>
#include <Gosu/GraphicsBase.hpp>
#include <Gosu/Platform.hpp>
#include <boost/optional.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>

#ifdef GOSU_IS_WIN
#include <windows.h>
#endif

/*
#ifdef unix
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/gl.h>
#endif
*/

namespace Gosu
{
    //! Contains everything a Graphics object needs to be constructed.
    struct DisplayMode
    {
        // TODO: Multi-adapter support is *very* weak at the moment...
        // Improve or remove!

        unsigned adapter;
        unsigned width, height;
        bool fullscreen;
        unsigned bitDepth, refreshRate;

        // IMPR: This is a little bit minimalistic.
        //! Tries to find a display mode that matches the given parameters.
        static boost::optional<DisplayMode> find(unsigned width,
            unsigned height, bool fullscreen);
    };

    // TODO: RAII guard class for Graphics::begin/end.

    enum BorderFlags
    {
        // Flags that affect the softness of a border.
        bfSoft = 0,
        bfHardLeft = 1,
        bfHardTop = 2,
        bfHardRight = 4,
        bfHardBottom = 8,
        bfHard = bfHardLeft | bfHardTop | bfHardRight | bfHardBottom,
    };        
    
    //! Serves as the target of all drawing and provides basic drawing
    //! functionality.
    class Graphics
    {
        struct Impl;
        boost::scoped_ptr<Impl> pimpl;

    public:
        Graphics(const DisplayMode& mode);
        ~Graphics();

        // Undocumented until I have thought about this...
        double factorX() const;
        double factorY() const;
        double virtualWidth() const;
        double virtualHeight() const;
        void setVirtualResolution(double virtualWidth, double virtualHeight);
        // End of Undocumented

        unsigned width() const;
        unsigned height() const;
        bool fullscreen() const;

        //! Prepares the graphics object for drawing. Nothing must be drawn
        //! without calling begin.
        bool begin(Color clearWithColor = Colors::black);
        //! Every call to begin must have a matching call to end.
        void end();

        void drawLine(double x1, double y1, Color c1,
            double x2, double y2, Color c2,
            ZPos z, AlphaMode mode = amDefault);

        void drawTriangle(double x1, double y1, Color c1,
            double x2, double y2, Color c2,
            double x3, double y3, Color c3,
            ZPos z, AlphaMode mode = amDefault);

        void drawQuad(double x1, double y1, Color c1,
            double x2, double y2, Color c2,
            double x3, double y3, Color c3,
            double x4, double y4, Color c4,
            ZPos z, AlphaMode mode = amDefault);

        //! Turns a portion of a bitmap into something that can be drawn on
        //! this graphics object.
        std::auto_ptr<ImageData> createImage(const Bitmap& src,
            unsigned srcX, unsigned srcY, unsigned srcWidth, unsigned srcHeight,
            unsigned borderFlags);
    };
}

#endif
