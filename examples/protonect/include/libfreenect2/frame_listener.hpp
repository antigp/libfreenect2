/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2014 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#ifndef FRAME_LISTENER_HPP_
#define FRAME_LISTENER_HPP_

#include <cstddef>
#include <stdint.h>
#include <libfreenect2/config.h>

namespace libfreenect2
{

struct LIBFREENECT2_API Frame
{
  enum Type
  {
    Color = 1,
    Ir = 2,
    Depth = 4
  };

  size_t width, height, bytes_per_pixel;
  unsigned char* data;
  // this is unavailable in rgb Frame
  //! @note In my environment, this increase about 267 in every frame.so this is not second or milisec.
  uint32_t timestamp;
  uint32_t sequence;

  Frame(size_t width, size_t height, size_t bytes_per_pixel) :
    width(width),
    height(height),
    bytes_per_pixel(bytes_per_pixel)
  {
    data = new unsigned char[width * height * bytes_per_pixel];
  }

  ~Frame()
  {
    delete[] data;
  }
};

class LIBFREENECT2_API FrameListener
{
public:
  virtual ~FrameListener();

  virtual bool onNewFrame(Frame::Type type, Frame *frame) = 0;
};

} /* namespace libfreenect2 */
#endif /* FRAME_LISTENER_HPP_ */
